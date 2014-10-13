#include<stdio.h>

typedef struct {
    float x;
    float y;
}complex;

//These just some options,will ask for input in later versions of program.
const minX = -2.01;
const maxX = 2.001;
const minY = -2.01;
const maxY = 2.001;
const resX = 10;
const resY = 10;
const maxIts = 999;
const complex julC = {0,0};

complex transform(int i, int j) {
    complex output;
    output.x = minX + i * (maxX - minX) / resX;
    output.y = maxY - j * (maxY - minY) / resY; //The bug is in these transformations. Everything else is ok.
    return output;
};

short exceededMax(int input){
    if (input == maxIts) {return 1;}
        else {return 0;};
};

short escaped(complex point){
    if (point.x>0 || point.y>0)//( abs(point.x + julC.x) > 5 ) || ( abs(point.y + julC.y) > 5 ) )
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

int findValue(int i, int j){
    complex point = transform(i,j);
    int iterations = 0;
    while( ! exceededMax(iterations) && ! escaped(point) ) {
        iterate(point);
        iterations++;
    };
    return iterations;
};

void plotJulia(int *start) {
    int i,j;
    for(j=0 ; j<(resX) ; j++){
        for(i=0 ; i<(resY) ; i++){   
             *(start+(i*resY)+j) = findValue(i,j);
        };
    };
};

void output(int* start){
    int i,j;
    for(j=0 ; j<(resX) ; j++){
        for(i=0 ; i<(resY) ; i++){
            printf("(%3i %3i)   ",transform(i,j).x,transform(i,j).y);// *(start+(j*resY)+i));
        };
    printf("\n");
    };
};

int main(void) {
    int table[resX*resY];//allocates memory space for the table
    plotJulia(table);
    output(table);
    return 0;
}
