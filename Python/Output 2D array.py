#Global Variables. Can ask for input in later versions
juliaC=[-1,0]
xMin,yMin=-2.1,-2.1
xMax,yMax=2,2
resolution=10
sizeLimit=100
iterationsLimit=100

def findNumber(i,j):				# function to find how many iterations before the number explodes. 
    iterations=0					# 
    x=xMin+j*(xMax-xMin)/resolution		# transform array j coordinate to complex plane x coordinates?
    y=yMax-i*(yMax-yMin)/resolution		# transform array i coordinate to complex plane y coordinate
    while (abs(x)<sizeLimit) and (abs(y)<sizeLimit) and (iterations<iterationsLimit): 
	    (x,y)=(x*x-y*y+juliaC[0]),(2*x*y+juliaC[1])# apply function
	    iterations++    			# increment iterations counter
    return iterations				# output as function value

def PlotJulia():              		# Overall Function to make a 2D array and fill it
    outputTable = []					# Initializes the list.
    for i in range(0,resolution):			# Make a list of rows, to the resolution wanted.
        outputTable.append([])
        for j in range(0,resolution):		# In each row list, make a list of columns.
            outputTable[i].append(findNumber(i,j))	# fill each cell with a value
    return outputTable

def OutputArray():					# Initializes the list.
    for i in range(0,resolution):			# In each row,.
        for j in range(0,resolution):		# In each cell, 
            print("%3.2f ", outputTable[i][j] #output cell
        print("\n")     #then newline
        
