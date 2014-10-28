//Global Variables. Can ask for input in later versions
var juliaC = [0,0];
var xMin = -1.8;
var xMax = 1.8;
var yMin = -1.4;
var yMax = 1.4;
var resolution = 20;
var iterLimit= 9;
var explosLimit = 3

var findNumber = function(i,j) {    			//function to find how many iterations before the number explodes. 
  var a, b, iterations = 0;					
  x = xMin+j*(xMax-xMin)/resolution;             //transform array j coordinate to complex plane x coordinates?
  y = yMax-i*(yMax-yMin)/resolution;	             // transform array i coordinate to complex plane y coordinate
  while (Math.abs(x)<explosLimit && Math.abs(y)<explosLimit && iterations<iterLimit) { 
    a = x*x-y*y+juliaC[0];                   //apply function to temp variables
    b = 2*x*y+juliaC[1];	
    x = a;                                       //reassign values to x&y
    y = b;
    iterations = iterations + 1;                                //increment iterations counter
  }; 
  return iterations;                             //output as function value
};

var findArray = function() {                    //Overall Function to make a 2D array and fill it
  var outputTable = [];                         //Initializes the array
  for (var i=0 ; i < resolution ; i++) {        	//Make a list of rows, to the resolution wanted.
    outputTable[i] = [];                        //Initializes the array within each array value
    for (var j=0 ; j < resolution ; j++) {	   	//In each row list, make a list of columns.
      outputTable[i][j] = findNumber(i,j);      //fill each cell with a value
    }
  };
  return outputTable;
};

console.log(findArray());
