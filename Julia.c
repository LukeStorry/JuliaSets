/* A Julia set plotter/drawer in C. Written by Luke Storry*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define NOOFSETTINGS 11 

typedef struct {							//defined a new datatype to ease the handling of complex numbers.
    double x;								//the real cooeficient of the complex number
    double y;								//the imaginary cooefficient
}complex;								//name of the datatype: "complex"

typedef enum {false,true} bool;

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

bool fixSettings(int argc, char** argv, settings * s) {
    bool allOK = true;
    switch (argc) {
	case 1:
	    printf("5\n");
	    (*s) = (settings){-1.5,1.5,-1.5,1.5,200,200,255, 50,(complex){-1,0},"output.ppm"}; //default settings
	    printf("6\n");
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
	    allOK = false;						
    };
    return allOK;
};


bool exceededMax(unsigned int input, unsigned maxIts) {					//this function tests whether iterations has hit the maximum allwed
    bool output; 
    if (input > maxIts) {						//if the current number of iterations is higher than the max allowed,
        output = true;							//then return true
    } else {								//otherwise, when the iterations have not yet reached maximum,
        output = false;							//return false
    };
    return output;
};


bool escaped(complex point, double escMax) {					//This function tests for if the point has escaped and will not return
    bool output;
    if ( (abs(point.x) > escMax) || (abs(point.y) > escMax)){	//If the point is big,
        output = true;							//then return true
    } else {								//else, when the point is small
        output = false;							//return false
    };
    return output;
};


complex iterate(complex input, complex julC) {    					//This function performs a function upon the complex number
    complex output;							//declares variable in which to store the output complex number
    output.x = input.x * input.x - input.y * input.y + julC.x;		//calculates the new complex number's x value (z^2+C)
    output.y = 2 * input.x * input.y + julC.y;				//calculates the new complex number's x value (z^2+C)
    return output;							//returns the iterated complex number
};


long findValue(double x, double y, settings  s) {			//this function find the value with which to populate each cell
    complex point = {x,y};					//translates the (i,j) array coordinates into a (x,y) complex number
    unsigned int iterations = 0;					//declares the iteration counter
    while( ! exceededMax(iterations,s.maxIts) && ! escaped(point,s.escMax) ) {		//while the point hasn't escaped, or iterations almost hit infinity
        point = iterate(point,s.julC);						//perform the function on the point
        iterations++;							//increment the diagnostics counter
    };
    return iterations;					//return the number of iterations that it took for the complex to explode
};


void fillPPM(FILE*file, settings s) {
    double x,y;
    for( y = s.maxY ; y >= s.minY ; y -= ((s.maxY-s.minY)/s.resY) ) {						//for every row,
	for( x = s.minX ; x <= s.maxX ; x += ((s.maxX-s.minX)/s.resX) ) {   					//for each cell,
             fprintf(file,"%i %i %li ",0,0,findValue(x,y,s));
        };
    };
};

//using http://www.physics.emory.edu/faculty/weeks//graphics/mkppm.html
void createPPM(settings s) {
    FILE* file = fopen(s.filepath,"w");
    fprintf(file,"P3\n");
    fprintf(file,"#A Julia set image, generated in C by Luke Storry\n");
    fprintf(file,"%lu %lu\n%d\n", s.resX, s.resY, 255);
    printf("1\n");
    fillPPM(file,s);
    printf("2\n");
    fclose(file);
};


int main(int argc, char** argv) {					//main function. it all starts here.
    settings s;
    printf("3\n");
    if (fixSettings(argc,argv,&s) == true){
        printf("4\n");
	//createPPM(s);							//prints the array
    } else {
	printf("Incorrect Parameters\n");
     	printf("They should be: minX maxX minY maxY resX resY maxIts julC.x julC.y filepath\n");
    };
    return 0;
};
