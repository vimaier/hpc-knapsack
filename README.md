# HPC - Knapsack #

[TOC]

This is the result of the project of the course 'High Performance Computing' in the semester SS2015 at the University of Applied Sciences Kaiserslautern. The aim of the project was to solve the knapsack problem and parallelize the algorithm. The project was done by

* Kevin Keßler (keke0002@stud.hs-kl.de) and
* Viktor Maier (vima0001@stud.hs-kl.de).


## The Knapsack Problem ##
You have a knapsack with a limited capacity and a list of items you can put into the knapsack. All items have the properties weight and worth/profit. The problem is that you have to pack the knapsack so that the sum of the items weight does not exceed the capacity of the knapsack and the profit is maximized. The problem is in the set of NP-complete problems. This means effort to solve such a problem increases exponentially with the input size, in our case list of items (and capacity of the knapsack).

## Framework ##
A small execution framework was created. This section describes the package (directory) structure of the project and the framework.

### Packages ###
**main**

This package contains the most part of the project. The file *Main.cpp* contains the starter function `int main(int argc, char* argv[])`. The created binary *knapsackStarter* (see section *Build and Tests*) executes this main function. The classes KnapSack and KnapSackSolver and the package *algorithms* are also contained here.

**res**

This directory contains the input files for the knapsack problem. During the CMake project generation this directory will be copied to the build directory. The syntax explains itself best with an example:
~~~
15.0 4 5
XXL blue 0x                  2.0 2.0
gray mouse                    1.0 2.0
big green box                 12.0 4.0
yellow daisy                   4.0 10.0
salmon mousse                 1.0 1.0
~~~
The first line contains information about the knapsack and the following items. *15.0* is the capacity of the knapsack. *4* represents the number of exemplars of each item. *5* is the number of distinct items and also the number of following lines. Each of the following lines represents an item. The line consists of a name with maximal 13 characters, followed by the weight and the profit/worth. For example the item with the name *gray mouse* has a weight of *1.0* and a worth of *2.0*.

There is also the script `run_and_collect_statistics.sh` which was used with *cron* to collects some data.

**test**

This package stores our unit tests. We use CMake to create tests for us. These tests are executables. In case they terminate with the result code 0 then the test will be treated as passed. Is the return code not equals 0 then the test failed. [ctest](http://www.cmake.org/Wiki/CMake/Testing_With_CTest) can be used to execute the tests (see section *Build and Tests*). The header file *TestData.h* contains the commonly used test data, for example paths to test files. There is a test for every implemented algorithm and further tests for testing input and output operations.

**util**

This package stores helper classes. Here are helpful functions for string and IO operations.

### Algorithm Execution Framework ###
To avoid common tasks in the solving of a knapsack problem we use a small algorithm execution framework, the abstract class KnapSackSolver. This class is responsible for the following tasks:

* Reading input files (supported by KnapSackReader)
* Writing solutions (supported by KnapSackWriter)
* Executing algorithms and measuring time  (supported by GetWalltime)
* Collect and write statistics for benchmarks  (supported by StatisticsWriter)

An knapsack solving algorithm has to extend the class KnapSackSolver and implement the function *solve()*. Thus one can concentrate on the implementation and cut out the management details. Additionally the functions *setUp()* and *tearDown()*. The first function can be used to prepare data in front of each run. The latter can be used to make some finishing operations. The two functions will not be included in the time measurement. The idea behind is that we have a strict input format represented by the class KnapSack, but some algorithms need a different structure. Maybe it is possible to deliver this structure directly without conversion thus it we exclude the input conversion from time measurement. Additionally the time executed in this functions in the implemented algorithms are negligible.

The following snippet provides a minimal implementation of an algorithm (taken from *test/KnapSackSolverTest.cpp*):

~~~{.cpp}
class SolverImpl: public KnapSackSolver {
public:
	SolverImpl(std::string inputFilename, std::string outputFilename, int nrOfExecutions=1)
	: KnapSackSolver(inputFilename, outputFilename, "Solver Test", nrOfExecutions)
	{
	}

	virtual void solve() {
		// For the test we will just put every possible exemplar into the solution
		KnapSackItem* items = knapSack.getItems();
		for(int i=0; i < knapSack.getNumOfItems() ;++i) {
			itemsOfSolution.insert(itemsOfSolution.end(), items[i]);
		}
	}
};
~~~

The algorithm can be executed with the following lines:
~~~{.cpp}
KnapSackSolver* solver = new SolverImpl(KNAPSACK_INPUT_FILE, TEST_OUTPUT_FILE);
solver->start();
delete solver;
~~~

This will solve the problem given by *KNAPSACK_INPUT_FILE* and write the solution to *TEST_OUTPUT_FILE*. It will also write a statistic file with the mean and the rms error for the execution durations.

## Algorithms ##
TODO

### Bruteforce ###
TODO

### Algorithm of Nemhauser and Ullmann ###
TODO

### Dynamic Programming ###
TODO
@phineliner hab oben erwähnt, dass das Problem NP-vollständig ist. Im Buch hab ich gelesen, dass es semi-polynomial (oder ähnlich) ist. Weißte was ich meine? Kannst du ja hier kurz erwähnen.

## Build and Tests ##
We use [CMake](http://www.cmake.org/) to build the project. The build is as easy as

~~~{.sh}
mkdir build
cd build
cmake /path/to/hpc-knapsack/
make
~~~

The `cmake-gui` can also be used for easier handling of the available options.
Note that [OpenMP](http://openmp.org/wp/) has to be installed. CMake tries to find it. In case it is not installed `cmake` will not finish.

To run the tests just run `make test` or `ctest` in the build directory.

## List of References

* [1] http://www-i1.informatik.rwth-aachen.de/~algorithmus/algo15.php
* [2] gprof https://sourceware.org/binutils/docs/gprof/Compiling.html#Compiling
* [3] gprof eclispe manual https://wiki.eclipse.org/Linux_Tools_Project/GProf/User_Guide
* [4] OpenMP http://openmp.org/wp/
* [5] Intel VTune Amplifier https://software.intel.com/en-us/intel-vtune-amplifier-xe/
* [6] VTune Amplifier and OpenMP https://software.intel.com/en-us/articles/profiling-openmp-applications-with-intel-vtune-amplifier-xe