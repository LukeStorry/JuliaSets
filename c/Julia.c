#define ESCX 1-julC.x
#define ESCY 1-julC.y

#include<stdio.h>

typedef struct {
    float x;
    float y;
}complex;

//These just some options,will ask for input in later versions of program.
const minX = -2;
const maxX = 2;
const minY = -2;
const maxY = 2;
const resX = 10;
const resY = 10;
const maxIts = 100;
const complex julC = {0,1};

complex Transform(int i,j) {
    complex output;
    output.x = 1/*calculate the algorithm what goes here*/;
    output.y = 1/*here too*/;
    return output;
};

short ExceededMax(int input){
    if (input>maxIts) {return 1;}
        else {return 0;};
};

short Escaped(complex input){
    if (input.x>ESCX||input.y>ESCY) {return 1;}
        else {return 0;};
};

complex Iterate(complex input) {
    complex output;
    output.x=input.x*input.x-input.y*input.y +julC.x;
    output.y=2*input.x*input.y +julC.y;
    return output;
};

int FindValue(int i,j){
    complex point=Transform(i,j);
    int iterations=1;
    while( (! ExceededMax(iterations)) && (! Escaped(point))){
        Iterate(point);
        iterations++;
    };
    return iterations;
};


void CalcJuliaSet(int *start) {
    int i,j;
    for(i=0;i<resX;i++){
        for(j=0;j<resY;j++){
           // complex input = {i,j};
            start+(resX*i)+j=FindValue(i,j);
        };
     };
    return 0;
};

void Output(int* input){
    ;
};

int Main(void) {
    int table[resX*resY];//allocates memory space for the table
    CalcJuliaSet(&table);
    Output(&table);
    return 0;
}

