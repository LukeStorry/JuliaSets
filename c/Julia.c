#include<stdio.h>

typedef struct {
    double x;
    double y;
}complex;

//These just some options,will ask for input in later versions of program.
const double  minX = -2;
const double  maxX = 2;
const double  minY = -2;
const double  maxY = 2;
const long    resX = 10;
const long    resY = 10;
const double  maxIts = 999;
const complex julC = {-1,0};

complex transform(long i, long j) {
    complex output;
    output.x = minX + i * (maxX - minX) / resX;
    output.y = maxY - j * (maxY - minY) / resY;
    return output;
};

char exceededMax(unsigned long input){
    if (input == maxIts) {return 1;}
        else {return 0;};
};

char escaped(complex point){
    if ( point.x>1.5 || point.x < -1.5 || point.y > 1.5 || point.y < -1.5  )
        {return 1;}
    else
        {return 0;};
};

complex iterate(complex input) {
    complex output;
    output.x = input.x * input.x - input.y * input.y + julC.x;
    output.y = 2 * input.x * input.y + julC.y;
    return output;
};

long findValue(unsigned long i, unsigned long j){
    complex point = transform(i,j);
    unsigned long iterations = 0;
    while( ! exceededMax(iterations) && ! escaped(point) ) {
        point = iterate(point);
        iterations++;
        printf("%2i:(%3.2f , %3.2f)    ",iterations, point.x,point.y);
};
    return iterations;
};

void plotJulia(long *start) {
    unsigned long i,j;
    for(j=0 ; j<(resX) ; j++){
        for(i=0 ; i<(resY) ; i++){   
             *(start+(j*resX)+i) = findValue(i,j);
        };
    };
};

void output(long *start){
    unsigned long i,j;
    for(j=0 ; j<resX ; j++){
        for(i=0 ; i<resY ; i++){
            printf("%3i ", *(start+(j*resY)+i));
        };
    printf("\n");
    };
};

int main(void) {
    long table[resX*resY];//allocates memory space for the table
    plotJulia(table);
    output(table);
    return 0;
}
