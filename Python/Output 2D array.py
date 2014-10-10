#Global Variables. Can ask for input in later versions
juliaC=[-1,0]			#Which Julia set to produce
xMin,yMin=-2.1,-2.1		#range of x coordinates for windows to contain
xMax,yMax=2,2			#range of y coordinates for windows to contain
xRes=20				#How many pixels to have in x direction
yRes=20				#how many pizels to have in y direction
iterationsLimit=100

def Exeeded(iterations):
	if iterations>iterationsLimit:
	    return true
	else
	    return false

def Escaped(x,y):
    if (abs(x)>1-juliaC[0]) and (abs(y)>1-juliaC[1]) :
        return true
	else
	    return false

def TransformJX(j):
    return xMin+j*(xMax-xMin)/xRes		# transform array j coordinate to complex plane x coordinates
    
def TransformIY(i):
    return yMax-i*(yMax-yMin)/yRes		# transform array i coordinate to complex plane y coordinate
    
def Iterate(x,y):
    return (x*x-y*y+juliaC[0]),(2*x*y+juliaC[1])# square number and add C
    
def findNumber(i,j):        		# function to find how many iterations before the number explodes. 
    iterations=0					# 
    x=TransformJX(j)                #translates array coordinates into complex numbers
    y=TransformIY(i)
    while not Escaped(x,y) and not Exeeded(iterations)): 
	    x,y = Iterate(x,y)
	    iterations+=1    			# increment iterations counter
    return iterations				# output as function value

def PlotJulia():              		# Overall Function to make a 2D array and fill it 
    outputTable = []        			# Initializes the list.
    for i in range(0,resolution):			# Make a list of rows, to the resolution wanted.
        outputTable.append([])
        for j in range(0,resolution):		# In each row list, make a list of columns.
            outputTable[i].append(findNumber(i,j))	# fill each cell with a value
    return outputTable
    

def OutputArray(table):					# Initializes the list.
    for i in range(0,resolution):			# In each row,.
        for j in range(0,resolution):		# In each cell, 
            print repr(table[i][j]).rjust(2), #output cell
        print ''     #then newline
        


#main:

OutputArray(PlotJulia())
