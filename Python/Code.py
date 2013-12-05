#Global Variables. Can ask for input in later versions
juliaC=[-1,0]
xMin=-2
xMax=2
yMin=-2
yMax=2
resolution=10
sizeLimit=[10,10]
iterationsLimit=1000

#Main Code starts here
def PlotJulia():          			# Overall Function to make a 2D array and fill it
  outputTable = []					# Initializes the list.
  for i in range(0,resolution):			# Make a list of rows, to the resolution wanted.
    for j in range(0,resolution):		# In each row list, make a list of columns.
      outputTable[i][j]=findNumber(i,j)	# fill each cell with a value
  return outputTable
      
def findNumber(i,j):					# function to find how many iterations before the number explodes. 
  iterations=0					# 
  x=xMin+j(xMax-xMin)/resolution		# transform array j coordinate to complex plane x coordinates?
  y=yMax-i(yMax-yMin)/resolution	# transform array i coordinate to complex plane y coordinate
  while (x^2<sizelimit[0]) and (y^2<sizelimit[1]) and (iterations<iterationsLimit): 
	x,y=(x*x-y*y+juliaC[0]),(2*x*y+juliaC[1])	# apply function
	iterations+=1					# increment iterations counter
  return iterations					# output as function value

print(str(PlotJulia()))
