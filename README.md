## Julia Sets
-----

### Plotting Julia sets on Argand diagrams

This leads on from my Extended Essay, a [brief presentation can be found here](http://prezi.com/cyg1ladocm9d/my-extended-essay-exploring-julia-sets/).

Originally written in terrible Javascript, then as I learnt Python and C, I re-wrote the program in each of them.

I'm now slowly working towards a GUI. Thinking about rewriting in JS with dynamic programming.

### Output
Put simply, by counting the number of iterations each "cell" must go through before it explodes past a certain threshold, you can plot a rough output on Bash:

![output/bash output of f-1](https://github.com/LukeStorry/JuliaSets/blob/master/output/bash%20output%20of%20f-1.PNG?raw=true)

By colour-coding and outputting to jpg, higher resolution images are available:

![output/f-1.jpg](https://github.com/LukeStorry/JuliaSets/blob/master/output/f-1.jpg?raw=true)

And by lopoing through different parameters to the function, a funky gif can also be generated:
![fast juliasets cycle](fast juliasets cycle.gif)
