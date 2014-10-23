#include "qdbmp.h"
#include <stdio.h>
#include <stdlib.h>

#define NOOFSETTINGS 9

typedef struct {							//defined a new datatype to ease the handling of complex numbers.
    double x;								//the real cooeficient of the complex number
    double y;								//the imaginary cooefficient
}complex;								//name of the datatype: "complex"


//default settings:
    double  minX = -1.8;
    double  maxX = 1.8;
    double  minY = -1.3;
    double  maxY = 1.3;
    long    resX = 1280;
    long    resY = 1024;
    double  maxIts = 255;
    complex julC = {-1,0};


int fixSettings(int argc, char** argv) {
    if (argc == 1) {				    //If not extra parameters,
	return 1;				    //just leave the default values
    } else if (argc != (NOOFSETTINGS+1)){	    //if some parameters but not enough,
	return 0;				    //fail
    } else {					    //otherwise, if there are enough parameters,
	minX = atof(argv[1]);			    //set the globals from the parameters
	maxX = atof(argv[2]);
	minY = atof(argv[3]);
	maxY = atof(argv[4]);
	resX = atof(argv[5]);
	resY = atof(argv[6]);	
	maxIts = atof(argv[7]);
	julC.x = atof(argv[8]);
	julC.y = atof(argv[9]);
	return 1;
    };
};


complex translate(long i, long j) {					//translates the (i,j) array coordinates into the required complex number
    complex output;							//declares variable is which to hold the output values
    output.x = minX + i * (maxX - minX) / resX;				//calculates the x value of the complex number that corresponds to that array cell
    output.y = maxY - j * (maxY - minY) / resY;				//calculates the y value of the complex number that corresponds to that array cell
    return output;
};


char exceededMax(unsigned long input) {					//this function tests whether iterations has hit the maximum allwed
    if (input > maxIts) {						//if the current number of iterations is higher than the max allowed,
        return 1;							//then return true
    } else {								//otherwise, when the iterations have not yet reached maximum,
        return 0;							//return false
    };
};


char escaped(complex point) {					//This function tests for if the point has escaped and will not return
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


long findValue(unsigned long i, unsigned long j) {			//this function find the value with which to populate each cell
    complex point = translate(i,j);					//translates the (i,j) array coordinates into a (x,y) complex number
    unsigned long iterations = 0;					//declares the iteration counter
    while( ! exceededMax(iterations) && ! escaped(point) ) {		//while the point hasn't escaped, or iterations almost hit infinity
        point = iterate(point);						//perform the function on the point
        iterations++;							//increment the diagnostics counter
    };
    return iterations;							//return the number of iterations that it took for the complex to explode
};

void createBMP(void) {
    unsigned int i, j;
    BMP* bmp = BMP_Create(resX,resY,8);
    for(j=0 ; j<resY ; j++){						//for each row,
        for(i=0 ; i<resX ; i++){					//for each cell,
            BMP_SetPixelRGB(bmp,i,j,100,160, findValue(i,j));
        };
    };
    BMP_WriteFile(bmp,"output.bmp");
    BMP_Free(bmp);
};

int main(int argc, char** argv) {					//main function. it all starts here.
    if (fixSettings(argc,argv)==1) {
	createBMP();							//prints the table
	return 0;
    } else {
	printf("Incorrect Parameters\n");
     	printf("They should be: minX maxX minY maxY resX resY maxIts julC.x julC.y \n");
        return 1;
    };
};
