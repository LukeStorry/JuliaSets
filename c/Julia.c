#include<stdio.h>

typedef struct {							//defined a new datatype to ease the handling of complex numbers.
    double x;								//the real cooeficient of the complex number
    double y;								//the imaginary cooefficient
}complex;								//name of the datatype: "complex"


//default settings:
    double  minX = -2;
    double  maxX = 2;
    double  minY = -4/3;
    double  maxY = 4/3;
    long    resX = 75;
    long    resY = 50;
    double  maxIts = 98;
    complex julC = {-1,0};

void askForSettings(void){
    printf("What would you like to be the left bound of the complex plane? (current value: %f)  "),minX;
    scanf("%f",&minX);
    printf("What would you like to be the right bound of the complex plane? (current value: %f)  "),maxX;
    scanf("%f",&maxX);
    printf("What would you like to be the upper bound of the complex plane? (current value: %f)  "),maxY;
    scanf("%f",&maxY);
    printf("What would you like to be the lower bound of the complex plane? (current value: %f)  "),minY;
    scanf("%f",&minY);
    printf("How many pixels do you want in the x-direction? (current value: %f)  "),resX;
    scanf("%f",&resX);
    printf("How many pixels do you want in the y-direction? (current value: %f)  "),resX;
    scanf("%f",&resY);
    printf("At what maximum number of iterations should the loop stop? (current value: %f)  "),maxIts;
    scanf("%f",&maxIts);
    printf("What constant would you like for the Julia Function? (current value: %f + %fi)  "),julC.x,julC.y;
    //scanf("%f + %fi",&julC.x,&julC.y);

};

complex translate(long i, long j) {					//translates the (i,j) array coordinates into the required complex number
    complex output;							//declares variable is which to hold the output values
    output.x = minX + i * (maxX - minX) / resX;				//calculates the x value of the complex number that corresponds to that array cell
    output.y = maxY - j * (maxY - minY) / resY;				//calculates the y value of the complex number that corresponds to that array cell
    return output;
};

char exceededMax(unsigned long input){					//this function tests whether iterations has hit the maximum allwed
    if (input > maxIts)							//if the current number of iterations is higher than the max allowed,
        {return 1;}							//then return true
   else									//otherwise, when the iterations have not yet reached maximum,
        {return 0;};							//return false
};

char escaped(complex point){						//This function tests for if the point has escaped and will not return
    if ( point.x>2 || point.x < -2 || point.y >2 || point.y < -2)	//If the point is big,
        {return 1;}							//then return true
    else								//else, when the point is small
        {return 0;};							//return false
};

complex iterate(complex input) {					//This function performs a function upon the complex number
    complex output;							//declares variable in which to store the output complex number
    output.x = input.x * input.x - input.y * input.y + julC.x;		//calculates the new complex number's x value (z^2+C)
    output.y = 2 * input.x * input.y + julC.y;				//calculates the new complex number's x value (z^2+C)
    return output;							//returns the iterated complex number
};

long findValue(unsigned long i, unsigned long j){			//this function find the value with which to populate each cell
    complex point = translate(i,j);					//translates the (i,j) array coordinates into a (x,y) complex number
    unsigned long iterations = 0;					//declares the iteration counter
    while( ! exceededMax(iterations) && ! escaped(point) ) {		//while the point hasn't escaped, or iterations almost hit infinity
        point = iterate(point);						//perform the function on the point
        iterations++;							//increment the diagnostics counter
       // printf("%2i:(%3.2f , %3.2f)    ",iterations, point.x,point.y);//diagnostics
    };
    return iterations;							//return the number of iterations that it took for the complex to explode
};

void plotJulia(long *start) {						//this function populates the table
    unsigned long i,j;							//declares column and row counters
    for(j=0 ; j<(resY) ; j++){						//for every row,
        for(i=0 ; i<(resX) ; i++){   					//for each cell,
             *(start+(j*resX)+i) = findValue(i,j);			//set that pointer's address to be the value of the iterations
        };
    };
};

void output(long *start){						//this function outputs the table
    unsigned long i,j;							//declares column and row counters;
    for(j=0 ; j<resY ; j++){						//for each row,
        for(i=0 ; i<resX ; i++){					//for each cell,
            printf("%2i", *(start+(j*resX)+i));				//print the respective value pointed to.
        };
    printf("\n");							//at the end of every row, start a new line.
    };
};

int main(void) {							//main function. it all starts here.
    askForSettings();
    long table[resX*resY];//allocates memory space for the table	//declare and allocates memory for the table
    plotJulia(table);							//populates the table
    output(table);							//prints the table
    return 0;
}
