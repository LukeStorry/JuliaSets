#define ESCX 1-julC.x
#define ESCY 1-julC.y

#include<stdio.h>

typedef struct {
    float x;
    float y;
}complex;


 //These just some options,will ask for input in later versions of program.
const minX -2
const maxX 2
const minY -2
const maxY 2
const resX 10
const resY 10
const maxInt 100
const complex julC= {0,1};


complex Iterate(complex input) {
    complex output;
    output.x=input.x*input.x-input.y*input.y;
    output.y=2*input.x*input.y);
    return (output);
};


complex Transform(complex input) {
    complex output;
    output.x = 1/*calculate the algorithm what goes here*/;
    output.y = 1/*here too*/;
    return (output);
};

bool ExeededMax(short input){
    if (input>MAXINTS) {return true;}
        else {return false;};
};

bool Escaped(complex input)
    if (input.x>ESCX||input.y>ESCY) {return true;}
        else {return false;};
};

short FindValue(complex input){
    point=Transform(input);
    int iterations=1;
    while(!ExeededMax(iterations) && ! Escaped(point)){
        Iterate(point);
        iterations++;
    };
    return iterations;
};


short CalcJuliaSet[RESY][RESX](){
    short outputTable[RESY][RESX];
    for(short i=0;i<RESY;i++){
        for(short j=0;j<RESX;j++){
            outputTable[i][j]=FindValue({i,j});
        };
     };
};

int output(array) {
    ;
};

int main(void) {
    output(CalcJuliaSet());
    return 0;
}
