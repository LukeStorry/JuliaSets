#define MINX -2
#define MAXX 2
#define MINY -2
#define MAXY 2       //just some options,will ask for input in later versions of program.
#define RESX 10
#define RESY 10
#define MAXINTS 100
#define ESCX 1-JULC.x
#define ESCY 1-JULC.y

typedef struct {
    float x;
    float y;
}complex;

const complex JULC = {0,1};



#include<stdio.h>
//Is there a library for complexes?

complex Iterate(complex input) {
    return(input.x*input.x-input.y*input.y,2*input.x*input.y);
};


complex Transform(complex input) {
    complex output = {/*calculate the algorithm what goes here*/};
    return output;
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
