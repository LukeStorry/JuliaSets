#define ESCX 1-julC.x
#define ESCY 1-julC.y

#include<stdio.h>

typedef struct {
    float x;
    float y;
}complex;

typedef struct {
     int outputTable[5][5];
}

//These just some options,will ask for input in later versions of program.
const minX = -2;
const maxX = 2;
const minY = -2;
const maxY = 2;
const resX = 10;
const resY = 10;
const maxIts = 100;
const complex julC = {0,1};


complex Iterate(complex input) {
    complex output;
    output.x=input.x*input.x-input.y*input.y +julC.x;
    output.y=2*input.x*input.y +julC.y;
    return (output);
};


complex Transform(complex input) {
    complex output;
    output.x = 1/*calculate the algorithm what goes here*/;
    output.y = 1/*here too*/;
    return (output);
};

short ExceededMax(int input){
    if (input>maxIts) {return 1;}
        else {return 0;};
};

short Escaped(complex input){
    if (input.x>ESCX||input.y>ESCY) {return 1;}
        else {return 0;};
};

int FindValue(complex input){
    complex point=Transform(input);
    int iterations=1;
    while( (! ExceededMax(iterations)) && (! Escaped(point))){
        Iterate(point);
        iterations++;
    };
    return iterations;
};


int** CalcJuliaSet(void) {
    int i,j;
    static int outputTable[5][5];
    for(i=0;i<resY;i++){
        for(j=0;j<resX;j++){
            complex input = {i,j};
            outputTable[i][j]=FindValue(input);
        };
     };
    return outputTable;
};

int output(int** input){
    ;
};

int main(void) {
    int** table = CalcJuliaSet;
    output(table);
    return 0;
}

