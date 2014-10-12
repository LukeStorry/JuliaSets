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
const complex julC = {-1,0};

complex transform(int i, int j) {
    complex output;
    output.x = minX+j*(maxX-minX)/resX;
    output.y = maxY-i*(maxY-minY)/resY;
    return output;
};

short exceededMax(int input){
    if (input = maxIts) {return 1;}
        else {return 0;};
};

short escaped(complex input){
    if (input.x>ESCX||input.y>ESCY) {return 1;}
        else {return 0;};
};

complex iterate(complex input) {
    complex output;
    output.x=input.x*input.x-input.y*input.y +julC.x;
    output.y=2*input.x*input.y +julC.y;
    return output;
};

int findValue(int i, int j){
    complex point=transform(i,j);
    int iterations=0;
    while( (! exceededMax(iterations)) && (! escaped(point))){
        iterate(point);
        iterations++;
    };
    return iterations;
};


void calcJuliaSet(int *start) {
    int i,j;
    for(j=0;j<(resY);j++){
        for(i=0;i<(resX);i++){
            *(start+(j*resY)+i)=findValue(i,j);
        };
    };
};

void output(int* start){
    int i,j;
    for(j=0;j<(resY);j++){
        for(i=0;i<(resX);i++){
            printf("%4d", *(start+(j*resY)+i));
        };
    printf("\n");
    };
};

int main(void) {
    int table[resX*resY];//allocates memory space for the table
    calcJuliaSet(table);
    output(table);
    return 0;
}

