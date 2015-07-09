# HPC - Knapsack #
TODO: description...

This is the result of the project of the course 'High Performance Computing' in the semester SS2015 at the University of Applied Sciences Kaiserslautern. The aim of the project was to solve the knapsack problem and parallelize the algorithm. The project was done by 

* Kevin Keßler (keke0002@stud.hs-kl.de) and
* Viktor Maier (vima0001@stud.hs-kl.de).

## The Knapsack Problem ##
You have a knapsack with a limited capacity and a list of items you can put into the knapsack. All items have the properties weight and worth/profit. The problem is that you have to pack the knapsack so that the sum of the items weight does not exceed the capacity of the knapsack and the profit is maximized. The problem is in the set of NP-complete problems. This means effort to solve such a problem increases exponentially with the input size, in our case list of items (and capacity of the knapsack). 

## Framework ##
TODO: describe KnapSackSolver, utils and test.

## Algorithms ##
TODO

### Bruteforce ###
TODO

### Algorithm of Nemhauser and Ullmann ###
TODO

### Dynamic Programming ###
TODO
@phineliner hab oben erwähnt, dass das Problem NP-vollständig ist. Im Buch hab ich gelesen, dass es semi-polynomial (oder ähnlich) ist. Weißte was ich meine? Kannst du ja hier kurz erwähnen. @vimaier ne weiß nich was du meinst^^

### TODO ###
@vimaier irgendwo müssen wir noch unsere überlegungen / verbesserungen dann hier unterbringen. Also das was wir im Wiki schon haben.

## Build and Tests ##
We use [CMake](http://www.cmake.org/) to build the project. The build is as easy as
```
mkdir build
cd build
cmake /path/to/hpc-knapsack/
make
```
The `cmake-gui` can also be used for easier handling of the available options.

To run the tests just run `make test` or `ctest` in the build directory.