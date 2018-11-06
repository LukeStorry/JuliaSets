## Julia Sets
-----

### Plotting Julia sets on Argand diagrams

This leads on from my Extended Essay, a [brief presentation can be found here](http://prezi.com/cyg1ladocm9d/my-extended-essay-exploring-julia-sets/).

Originally written in terrible Javascript, then as I learnt Python and C, I re-wrote the program in each of them.


![example output](fast%20juliasets%20cycle%20-%20small%20.gif)



### Output
Put simply, by counting the number of iterations each "cell" must go through before it explodes past a certain threshold, you can plot a rough output on Bash:

![output/bash output of f-1](bash%20output%20of%20f-1.PNG)

By colour-coding and outputting to jpg, higher resolution images are available:

![output/f-1.jpg](output/f-1.jpg)

And by looping through different parameters to the function, a funky gif can also be generated:

![fast juliasets cycle](fast%20juliasets%20cycle.gif)
