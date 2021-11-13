# FlockingSimulation
A bird flocking simulation based on the boid model by [Craig Reynolds](http://www.red3d.com/cwr/boids/).

## Features
Basic traits of boids are implemented according to the boid model. Boids of two types, prey and predator, are introduced.

Prey has the following behaviours:
- Separation
- Alignment
- Cohesion
- Escape

Predator has the following behaviours:
- Separation
- Chase

A simple 3D vector library is included just for fun :)


## Installation
Clone this repository to your local directory, and to compile, run the command `make` in the directory. 

A folder `build` together with an executable file `flocking_sim` inside it should be created.

You might want to run `make clean` before running `make` if you want to start the compilation fresh.

## Running
Just execute the file `flocking_sim`.

## Sample output
Stored in the same folder `build`, including:
- `animation.xyz`: Position array of the flocking boids, can be visualized using the software [VMD](https://www.ks.uiuc.edu/Research/vmd/).
- `avgvelocity_plot.csv`: Average velocity of the boids at different time, for analysis. 
- `rdf_plot.csv`: Radial distribution function of the boids at different time, also for analysis. 

## Note
This was my first try on writing header files, it might seems amateurish because it is.

For some bizarre reasons, year 2 me thought it was a good idea to hard-code the variables in the program. Yeah, good job me. Might revisit this project some other time.

