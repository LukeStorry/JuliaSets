#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define NOOFSETTINGS 11 

typedef struct {							//defined a new datatype to ease the handling of complex numbers.
    double x;								//the real cooeficient of the complex number
    double y;								//the imaginary cooefficient
}complex;								//name of the datatype: "complex"


//default settings:
    double  minX = -1.8;
    double  maxX = 1.8;
    double  minY = -1.44;
    double  maxY = 1.44;
    long    resX = 1280;
    long    resY = 1024;
    unsigned int  maxIts = 254;
    complex julC = {-1,0};
    char filepath[100] = "output.ppm";

int fixSettings(int argc, char** argv) {
    switch (argc) {
	case 1:
	    break;
	case 2:
	    strcpy(filepath,argv[1]);
	    break;
	case NOOFSETTINGS:
	    minX = atof(argv[1]);
	    maxX = atof(argv[2]);
	    minY = atof(argv[3]);
	    maxY = atof(argv[4]);
	    resX = atof(argv[5]);
	    resY = atof(argv[6]);	
	    maxIts = atof(argv[7]);
	    julC.x = atof(argv[8]);
	    julC.y = atof(argv[9]);
	    strcpy(filepath,argv[10]);
	    break;
	default:
	    return 0;						
    };
    return 1;
};


int exceededMax(unsigned int input) {					//this function tests whether iterations has hit the maximum allwed
    if (input > maxIts) {						//if the current number of iterations is higher than the max allowed,
        return 1;							//then return true
    } else {								//otherwise, when the iterations have not yet reached maximum,
        return 0;							//return false
    };
};


int escaped(complex point) {					//This function tests for if the point has escaped and will not return
    if ( (abs(point.x + julC.x) > 5) || (abs(point.y + julC.y) > 5)){	//If the point is big,
        return 1;							//then return true
    } else {								//else, when the point is small
        return 0;							//return false
    };
};


complex iterate(complex input) {    					//This function performs a function upon the complex number
    complex output;							//declares variable in which to store the output complex number
    output.x = input.x * input.x - input.y * input.y + julC.x;		//calculates the new complex number's x value (z^2+C)
    output.y = 2 * input.x * input.y + julC.y;				//calculates the new complex number's x value (z^2+C)
    return output;							//returns the iterated complex number
};


long findValue(double i, double j) {			//this function find the value with which to populate each cell
    printf("%2f\n", i);
    complex point = {i,j};					//translates the (i,j) array coordinates into a (x,y) complex number
    unsigned int iterations = 0;					//declares the iteration counter
    while( ! exceededMax(iterations) && ! escaped(point) ) {		//while the point hasn't escaped, or iterations almost hit infinity
        point = iterate(point);						//perform the function on the point
        iterations++;							//increment the diagnostics counter
    };
    return iterations;					//return the number of iterations that it took for the complex to explode
};


void fillPPM(FILE* file) {
    double i,j;
    for(j=maxY ; j>minY ; j-=(maxY-minY)/resY){						//for every row,
        for(i=minX ; i<maxX ; i+=(maxX-maxX)/resX){   					//for each cell,
             fprintf(file,"%i %i %li ",0,0,findValue(i,j));
        };
    };
};

//using http://www.physics.emory.edu/faculty/weeks//graphics/mkppm.html
void createPPM() {
    printf("0\n");
    FILE* file = fopen(filepath,"w");
    fprintf(file,"P3\n");
    fprintf(file,"#A Julia set image, generated in C by Luke Storry\n");
    fprintf(file,"%lu %lu\n%d\n", resX, resY,255);
    printf("1\n");
    fillPPM(file);
    printf("2\n");
    fclose(file);
    return ;
};


int main(int argc, char** argv) {					//main function. it all starts here.
    printf("000\n");
    if (fixSettings(argc,argv)==1){
        printf("test\n");
      	createPPM();							//prints the array
	return 0;
    } else {
	printf("Incorrect Parameters\n");
     	printf("They should be: minX maxX minY maxY resX resY maxIts julC.x julC.y filepath\n");
        return 1;
    };
};
