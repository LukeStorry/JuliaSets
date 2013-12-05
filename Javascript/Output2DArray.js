 //Global Variables. Can ask for input in later versions
var juliaC = [0,0];
var xMin = -2.1;
var xMax = 2;
var yMin = -2.1;
var yMax = 2;
var resolution = 10;
var sizeLimit=100;
var iterLimit=100;

var findArray = function() {                    //Overall Function to make a 2D array and fill it
  var outputTable = [];                         //Initializes the array
  for (var i=0 ; i < resolution ; i++) {        	//Make a list of rows, to the resolution wanted.
    outputTable[i] = [];                        //Initializes the array within each array value
    for (var j=0 ; j < resolution ; j++) {	   	//In each row list, make a list of columns.
      outputTable[i][j] = findNumber(i,j);      //fill each cell with a value
  } };
  return outputTable;
};

var findNumber = function(i,j) {				//function to find how many iterations before the number explodes. 
  var iterations = 0;					
  x = xMin+j*(xMax-xMin)/resolution;             //transform array j coordinate to complex plane x coordinates?
  y = yMax-i*(yMax-yMin)/resolution;	             // transform array i coordinate to complex plane y coordinate
  while (Math.abs(x)<sizeLimit && Math.abs(y)<sizeLimit && iterations<iterLimit) { 
	  var a = x*x-y*y+juliaC[0];                   //apply function to temp variables
    var b = 2*x*y+juliaC[1];	
    x = a;                                       //reassign values to x&y
    y = b;
   iterations = iterations + 1;                                //increment iterations counter
  } 
  return iterations;                             //output as function value
};

console.log(findArray());
