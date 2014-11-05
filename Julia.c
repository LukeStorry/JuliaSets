/* A Julia set plotter/drawer in C. Written by Luke Storry*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define NOOFSETTINGS 11 

typedef struct {							//defined a new datatype to ease the handling of complex numbers.
    double x;								//the real cooeficient of the complex number
    double y;								//the imaginary cooefficient
}complex;								//name of the datatype: "complex"


//default settings:
typedef struct {
    double  minX;
    double  maxX;
    double  minY;
    double  maxY;
    long    resX;
    long    resY;
    unsigned  maxIts;
    double  escMax;
    complex julC;
    char filepath[100];
}settings;

int fixSettings(int argc, char** argv, settings*s) {
    switch (argc) {
	case 1:
	    (*s) = (settings){-1.5,1.5,-1.5,1.5,200,200,255, 50,(complex){-1,0},"output.ppm"}; //default settings
	case 2:
	    (*s) = (settings){-1.5,1.5,-1.5,1.5,200,200,255, 50,(complex){-1,0},""}; //defaults
	    strcpy((*s).filepath,argv[1]);
	    break;
	case NOOFSETTINGS:
	    (*s).minX = atof(argv[1]);
	    (*s).maxX = atof(argv[2]);
	    (*s).minY = atof(argv[3]);
	    (*s).maxY = atof(argv[4]);
	    (*s).resX = atof(argv[5]);
	    (*s).resY = atof(argv[6]);	
	    (*s).maxIts = atof(argv[7]);
	    (*s).julC.x = atof(argv[8]);
	    (*s).julC.y = atof(argv[9]);
	    strcpy((*s).filepath,argv[10]);
	    break;
	default:
	    return 0;						
    };
    return 1;
};


int exceededMax(unsigned int input, unsigned maxIts) {					//this function tests whether iterations has hit the maximum allwed
    if (input > maxIts) {						//if the current number of iterations is higher than the max allowed,
        return 1;							//then return true
    } else {								//otherwise, when the iterations have not yet reached maximum,
        return 0;							//return false
    };
};


int escaped(complex point, escMax) {					//This function tests for if the point has escaped and will not return
    if ( (abs(point.x + julC.x) > escMax) || (abs(point.y + julC.y) > escMax)){	//If the point is big,
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


long findValue(double x, double y, settings * s) {			//this function find the value with which to populate each cell
    complex point = {x,y};					//translates the (i,j) array coordinates into a (x,y) complex number
    unsigned int iterations = 0;					//declares the iteration counter
    while( ! exceededMax(iterations,s.maxIts)) && ! escaped(point,s.escMax) ) {		//while the point hasn't escaped, or iterations almost hit infinity
        point = iterate(point);						//perform the function on the point
        iterations++;							//increment the diagnostics counter
    };
    return iterations;					//return the number of iterations that it took for the complex to explode
};


void fillPPM(FILE*file, settings*s) {
    double x,y;
    for(y=maxY ; y>=minY ; y-=((maxY-minY)/resY)){						//for every row,
	for(x=minX ; x<=maxX ; x+=((maxX-minX)/resX)){   					//for each cell,
             fprintf(file,"%i %i %li ",0,0,findValue(x,y,s));
        };
    };
};

//using http://www.physics.emory.edu/faculty/weeks//graphics/mkppm.html
void createPPM(settings * s) {
    FILE* file = fopen(filepath,"w");
    fprintf(file,"P3\n");
    fprintf(file,"#A Julia set image, generated in C by Luke Storry\n");
    fprintf(file,"%lu %lu\n%d\n", s.resX, s.resY, 255);
    fillPPM(file,s);
    fclose(file);
};


int main(int argc, char** argv) {					//main function. it all starts here.
    settings s;
    if (fixSettings(argc,argv,&s)==1){
      	createPPM(s);							//prints the array
	return 0;
    } else {
	printf("Incorrect Parameters\n");
     	printf("They should be: minX maxX minY maxY resX resY maxIts julC.x julC.y filepath\n");
        return 1;
    };
};
