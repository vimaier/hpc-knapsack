[TOC]

This is the result of the project of the course 'High Performance Computing' in the semester SS2015 at the University of Applied Sciences Kaiserslautern. The aim of the project was to solve the knapsack problem and parallelize the algorithm. The project was done by

* Kevin Keßler (keke0002@stud.hs-kl.de) and
* Viktor Maier (vima0001@stud.hs-kl.de).


# The Knapsack Problem
You have a knapsack with a limited capacity and a list of items you can put into the knapsack. All items have the properties weight and worth/profit. The problem is that you have to pack the knapsack so that the sum of the item weights does not exceed the capacity of the knapsack and the profit is maximized. This problem is in the set of NP-complete problems. This means effort to solve such a problem increases exponentially with the input size, in our case list of items (and capacity of the knapsack).

# Framework
A small execution framework was created. This section describes the package (directory) structure of the project and the framework.

## Packages
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

## Algorithm Execution Framework
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

# Algorithms
TODO

## Brute Force
The most naive approach for solving the knapsack problem is the so called *Brute Force* approach. Brute Force is a trial and error method which finds the best solution through exhaustive effort by trying every possible combination. Accordingly, its running time increases exponentially with the complexity of the problem. Thus this algorithm belongs to the complexity class O(2^n).

**Implementation:**

See class BruteForceSolver.

It is the first approach implemented during the project and was used to get a proper feeling and understanding of the knapsack problem itself. The algorithm provides correct solutions and is sufficiently fast for very small problems. As soon as the complexity of problems increases, however, the algorithm can not deliver the solutions in suitable time.

**Measurement:**

The measurement for this algorithm has been performed on (TODO: kevin laptop specs). At first it was used multiple times to solve a very simple problem (firstFileExample.txt), which contains 20 items. Accordingly, the algorithm hat to try 2^20 (1048576) combinations to find the best solution.

```
#!
Alogrithm;Brute Force (Sequential)
Number of Executions;5
Average Duration;0.2821
RMS Error;0.0083
1;0.2982
2;0.2812
3;0.2754
4;0.2782
5;0.2772
```

As one can see, the algorithm delivered the solution in suitable 0.2821 seconds, but this is only because there were only 2^20 combinations to try. For a more complex problem with, for example fourthFileExample.txt, there would be 2^56 combinations to try, which is ~69 billion times 2^20. Accordingly it would take 19 billion seconds or 614 years to solve. This shows how unsuitable this algorithm is for complex problems. Even parallelization would not make it suitable. Assuming we could parallelize the algorithm completely, we would gain a factor of n where n is the number of available cores. So to solve the previous problem within one second we would still need 614*356*24*3600 cores. Because of this, we concentrated on implementing more promising algorithms rather than wasting time on parallelizing this algorithm.

## Algorithm of Nemhauser and Ullmann
TODO
## Dynamic Programming

The Dynamic Programming Approach for solving Knapsack-Problems is based on splitting the main-problem into its sub-problems. For each of those (simpler) sub-problems the maximum profit is being calculated to be able to calculate the maximum profit of the main-problem. At that the sub-problems with a maximum capacity of zero or an item pool of zero items serve as induction basis. The maximum profit of those sub-problems automatically stays zero since you can not pick up items into a knapsack without any capacity or without any items to pack. Starting from this basis more complex problems can be calculated. Be p(i,w) the maximum profit of the sub-problem with an item pool i and a maximum capacity of w. Beginning with p(0,0) the problems can be extended bit by bit. After all capacities have been evaluated with the current pool, another item is added to create the next bigger sub-problem. With c being the maximum capacity of the main-problem and n being the number of items withing the pool the process can be described as follows: Starting from p(0,0) problems up to p(0,c) are being solved (induction basis, each is zero). Afterwards those calculated values are being used to solve problems p(1,0) to p(1,c) and those again are used to solve p(2,0) to p(2,c) and so on. After all sub-problems have been solved, the maximum profit of the main problem is represented by p(n,c).

### Default Version ###

**Based on pseudo code of:**

[7], DP-1, p.22

**Implementation:**

See class DynamicProgrammingSolver

A result table (n x c) serves as underlying data structure of the default implementation. Each entry of the table represents the maximum profit of the respective sub-problem p(i,w). The table is being populated by the previously described process, such that the solution of the main-problem resides in the last column of the table's last row (n,c). After the calculations are done, the list of items contained within the solution is being backtracked starting from the position (n,c).

**Measurement:**

In order to find out where the default algorithm can be optimized, it has been applied several times to the dynamic programming example problem (secondDynamicProgrammingExample.txt), which is a problem with an item pool of 10000 items and a maximum capacity of 45000. The average duration for solving the problem with this algorithm was 1.8431 seconds.

(TODO: kevin laptop specs)

```
#!
Algorithm;Dynamic Programming (Sequential)
Number of Executions;5
Average Duration;1.8431
RMS Error;0.0158
1;1.8467
2;1.8326
3;1.8463
4;1.8685
5;1.8213
```

**Performance Analysis:**

After solving the problem several times the algorithm was subject to a performance analysis, which yielded that the algorithm spent more than 80% of the duration within the inner for-loop (lines 63 - 68).

![Unbenannt.PNG](https://bitbucket.org/repo/agqbex/images/1766757010-Unbenannt.PNG)

```
#!c++
63  for(int c=itemWeight; c < weightColumns; c++){
64	      int worthOfNotUsingItem = table[i-1][c];
65	      int worthOfUsingItem = itemWorth + table[i-1][c-itemWeight];
66	      if(worthOfNotUsingItem < worthOfUsingItem)
67	  	           table[i][c] = worthOfUsingItem;
68  }
```

If you could parallelize this loop, you could expect a significant reduction of the time needed for solving the problem.

### Parallelized Version ###

**Idea:**

The inner for-loop is responsible for calculating the columns of the current item row. Luckily those columns are independent from each other. Thus the calculation of each row's columns can be done in parallel. The rows themselves still have to be calculated one after each other because they are depending on each other (row i+1 depends on row i).  

**Implementation:**

See commit 37d359775aa49bac04f25ea1d1b1eee939fe3a09

By using OpenMP it was very easy to implement the idea of the parallelization. Therefore the following pragma was used:

```
#!c++
#pragma omp parallel for if(weightColumns > DynamicProgrammingParallelSolver::PARALLEL_CAPACITY_THRESHOLD)
for(int c=itemWeight; c < weightColumns; c++) { ... }
```

The pragma causes the loop to be divided into equally sized parts which are distributed among n threads, where n is the number of cores available. Because starting separate threads is consuming a lot of resources, a threshold condition has been added which ensures that separate threads are only instantiated when the problem to solve owns a certain complexity. If you would go without the threshold condition at this point and thus would start separate threads for even very small problems, then the process of starting the threads would already take more time than just solving the problem sequentially.

A closer look at the differences of the parallel and sequential implementation shows that the inner loop of the parallelized version starts at ```i=1``` while the loop of the sequential version starts at ```i=itemWeight```. This is because, in the sequential case, it is more favorable to preallocate the current row with the values of the previous row since we can save one if-condition for each iteration. The parallel version, however, profits from this if condition within the loop rather than copying the allocation, because the workload of the loop is being distributed among the threads. Alternatively to copying you could run the process of preallocation in a separate for-loop which can be parallelized. This has been attempted but was discarded because the workload distribution was worse than it was when having everything within one loop.

**Measurement:**

To compare the durations of this algorithm to the durations of the sequential one the example problem has been solved and measured under the same circumstances. The average duration was 1.15 seconds. On first sight the parallelization provides a reduction of the duration from 1.84 seconds to 1.15 seconds what corresponds to a speedup of ~1.6.

(TODO: KEVIN LAPTOP SPECS?)

```
#!
Algorithm;Dynamic Programming (Parallel) (Version 1)
Number of Executions;5
Average Duration;1.1500
RMS Error;0.0104
1;1.1406
2;1.1508
3;1.1597
4;1.1361
5;1.1628
```

### Further Parallelization ###

**Idea:**

By looking at the introduced parallel implementation one can see that the ```#pragma omp parallel``` is written inside the outer loop. Thus you can assume that the threads for the inner loop are being instantiated again and again for each iteration of the outer loop. To prevent this you could try to instantiate them before the outer loop is being entered. Thus the inner loop would only access the threads instead of instantiating them.

**Implementation:**

See class DynamicProgrammingParallelSolver

The implementation was done by inserting a ```#pragma omp parallel```-block in front of the outer loop. Accordingly the pragma of the inner loop has been changed to ```#pragma omp for``` (without the parallel keyword). But there is a disadvantage that comes with this solution. Everything within the parallel-block is now being executed multiple times (once per core). Many different approaches have been tried to achieve single execution of the outer loop while the parallel-block is preceding. All approaches, e.g. ```#pragma omp single```, ```#pragma omp critical```, explizites Setzen der Thread Anzahl, etc. resulted either in single execution of both loops or in having multiple parallel-blocks which caused a significant performance lost. Accordingly it remained to the multiple execution of the outer loop. Admittedly this does not change anything at the algorithm's result, but now it has to be examined how this affects the runtime.

**Measurement:**

Again the algorithm has been used to solve the example problem in the same environment as before to acquire comparable metrics. The average duration was 0.6989 seconds. In comparison to the first parallel version we gain a reduction of the runtime from 1.15 seconds to 0.7 seconds which corresponds to a speedup of ~1.64. Compared to the sequential version we fall from 1.84 seconds to 0.7 seconds and obtain an overall speedup of ~2.6.

```
#!
Algorithm;Dynamic Programming (Parallel) (Version 2)
Number of Executions;5
Average Duration;0.6989
RMS Error;0.0136
1;0.6965
2;0.6825
3;0.7195
4;0.7085
5;0.6875
```

So the second parallel version of the algorithm is faster than the previous one. However it is not clear yet why this is the case. Assuming that the preliminary ideas are correct, one might suspect that the creation of threads in the inner loop produces more overhead than the multiple execution of the outer loop. However, this assumption would only be true if the threads actually are recreated in each iteration of the inner loop. Research in this regard revealed that most compilers implement a thread pool for OpenMP internally, so that after the first use of a ```#pragma omp parallel``` the threads are not being recreated and thus just being taken from the pool. Accordingly, the above explanation for the speedup is invalid. At this point, the obtained speedup feels absolutely anti-intuitive. Why should the execution become faster when the outer loop is executed more often and thread management stays the same? This question has been examined intensively and ultimately a public discussion on the collaborative question-and-answer page StackOverflow about this issue yielded a plausible answer [8]. It turned out that only the outer loop is being executed multiple times. The inner loop is, in spite of the outer parallel block, only running once (distributed among all cores). In the first approach, all separate threads must wait for the main thread to reach the inner loop during the current iteration of the outer loop. Only then they are allowed to start the calculation of their workload. Since in the second approach each of the threads controls the outer loop by itself, they do not have to wait for any other thread. Thus they can start working on their workload immediately. In addition to that, these OpenMP parallel-blocks always define a group of threads which are taken from the thread pool. It might be that the allocation of those groups takes some significant time which would also be in favor of the second approach. Now that this has been examined and explained, other aspects of the algorithm can be examined.

Now the algorithm indeed is very fast in solving knapsack problems, however, it still suffers from memory problems. Both previously implemented versions store the maximum profits of their sub-problems within a i x w matrix, where i is equal to the number of objects and w represents the maximum capacity. With increasing complexity of the problems, the matrix is getting larger and larger which, at some point, leads to memory problems. So to be able to handle very complex problems, we need an alternative data structure for storing the calculated sub-problem solutions.

### Sequential Memory Optimized Version ###

**Idea:**

Theoretically, the matrix can consist of only a single row by calculating its columns from back to front. Accordingly the previously calculated values of this row are used to calculate the values of the next iteration, which then override the previous ones. Thus, only one row is used for calculation and storage, which diminishes the used memory dramatically. However, this leads to the fact that the sub-solutions of the upper rows are no longer available when backtracking the packed items. Accordingly the overhead of backtracking increases, which will generally lead to longer durations. Nevertheless, this solution needs to be considered since very complex knapsack problems can be solved by it.

**Based on pseudo code of**:  

[7], p.23 and p.47, DP-2 and Recursive-DP

**Implementation:**

See class DynamicProgrammingLowMemorySolver

Like it has been described in the idea section, instead of using the complete result table now only one row is being used. This is possible because the row gets filled from back to front and the values of the previous iteration are used for calculation.

```
#!c++
54 for(int c=capacity; c >= itemWeight; c--){
55			int worthOfPickingItem = solutionRow[c - itemWeight] + itemWorth;
56			if( worthOfPickingItem > solutionRow[c])
57				solutionRow[c] = worthOfPickingItem;
58 }
```

In contrast to both previous approaches this one causes the backtracking to become considerably complicated. During the backtracking the item list gets divided into two sub lists of which each is used to apply the solution algorithm again. By using the new solutions you can determine the capacities which belong to the sub lists and thus repeat the procedure. Indeed the procedure is being repeated recursively until the lists consist of only one remaining element. This element is part of the solution list. To be able to call the solution algorithm multiple times, its logic has been transferred to a method called DynamicProgrammingLowMemorySolver::solveProblem(). The framework's DynamicProgrammingLowMemorySolver::solve() Method calls this method in order to calculate the maximum profit of the main problem and then starts the recursive backtracking by calling DynamicProgrammingLowMemorySolver::determineItemsOfSolutionRecursively().

**Measurement:**

Again the example problem has been solved multiple times, now by this algorithm, to determine which part of it can be optimized. The average running time was 2.9278 seconds. This shows that there is a significant speed loss in comparison to the standard sequential implementation, which only took 1.84 seconds for solving. However, this has been expected. It is the price you have to pay for having an algorithm that is able to solve complex knapsack problems while using very little memory.

```
#!
Algorithm;Dynamic Programming Low Memory (Sequential)
Number of Executions;5
Average Duration;2.9278
RMS Error;0.0405
1;2.9142
2;2.9244
3;2.9222
4;3.0013
5;2.8771
```

**Performance Analysis:**

By using the data, which has been collected during solving, a performance analysis (Eclipse and gprof) has been performed. The analysis yielded that the algorithm spends most of the time by solving sub problems. Accordingly it stays more than 98% of running time within the DynamicProgrammingLowMemorySolver::solveProblem() method.

![dplm.PNG](https://bitbucket.org/repo/agqbex/images/1898645986-dplm.PNG)

Now it has to be examined how this time can be diminished.

### Parallel Memory Optimized Version ###

**Idea:**

A closer look at the DynamicProgrammingLowMemorySolver::solveProblem() method yields that only the initialization of the solution row can be parallelized. The calculation of each of the row's columns can not be parallelized (as opposed to the other sequential algorithm), as they are dependent on each other due to the new structure.

However we can have a closer look at the backtracking (DynamicProgrammingLowMemorySolver::determineItemsOfSolutionRecursively()). There, the original item list is divided into two approximately equals parts. To each of those parts the solution algorithm (DynamicProgrammingLowMemorySolver::solveProblem()) is being applied. This means for every recursive call of DynamicProgrammingLowMemorySolver::determineItemsOfSolutionRecursively() the DynamicProgrammingLowMemorySolver::solveProblem() method is called twice.

```
#!c++
97  int* subSolutionRow1 = new int[rowLength];
98  int* subSolutionRow2 = new int[rowLength];
99  subSolutionRow1 = solveProblem(items1, numOfItems1, subSolutionRow1, rowLength, capacity);
100 subSolutionRow2 = solveProblem(items2, numOfItems2, subSolutionRow2, rowLength, capacity);
```

Those calls are completely independent from each other and thus can be delegated to two separate threads while the main thread waits for them to finish. By this, a significant reduction of the running time should already be achieved. Furthermore the backtracking algorithm is called recursively. For each call it will be called twice recursively (once for each part of the item list). The recursion ends when the item list to divide has reached the size of one, which represents the item that has been packed.

```
#!c++
117	if(numOfItems1 == 1 && subSolution1 > 0)
118		integerItemsOfSolution.insert(integerItemsOfSolution.end(), items1[0]);
119	else if(numOfItems1 > 1)
120		determineItemsOfSolutionRecursively(items1, numOfItems1, c1, subSolution1);
121
122	if(numOfItems2 == 1 && subSolution2 > 0)
123		integerItemsOfSolution.insert(integerItemsOfSolution.end(), items2[0]);
124	else if(numOfItems2 > 1)
125		determineItemsOfSolutionRecursively(items2, numOfItems2, c2, subSolution2);
```

Those two recursive calls (lines 120 and 125) are completely independent from each other. Thus they also could run in two separate threads to reduce running time even further.

**Implementation:**

See class DynamicProgrammingLowMemoryParallelSolver

The two calls of the solving algorithm have been parallelized by using OpenMP sections.

```
#!c++
108	// Runs the two independent solveProblem calls in two seperate threads.
    // By Default the sections block is waiting until all sections are finished.
109	#pragma omp parallel sections
110	{
111		//this section runs in a different thread than the next section
112		#pragma omp section
113			subSolutionRow1 = solveProblem(items1, numOfItems1, subSolutionRow1, rowLength, capacity);
114
115		//this section runs in a different thread than the previous section
116		#pragma omp section
117			subSolutionRow2 = solveProblem(items2, numOfItems2, subSolutionRow2, rowLength, capacity);
118	}

```

Each of the sections within the ```#pragma omp parallel sections```-block gets an own thread assigned which causes the two DynamicProgrammingLowMemoryParallelSolver::solveProblem() calls to run in parallel. In line 118 the main thread waits for the calls to finish before it executes the code below.

Similarly it has been tried to parallelize the two recursive calls. This approach, however, has been discarded because the recursion caused to start more and more threads which could not come to an end before the lists reached the size of one. Thus, a giant number of threads would be instantiated for complex problems which would cause the program to freeze or to run extremely slow. In future work one could try to use a helper variable to monitor the number of instantiated threads which could be used to only allow new threads if this number is below the number of available cores. However, this is pretty difficult to implement in combination with the above presented parallel sections. Each recursive thread would require two additional threads to perform the DynamicProgrammingLowMemoryParallelSolver::solveProblem() calls in parallel which would end in a pretty complex implementation. For time reasons this approach has not been investigated any further.

**Measurement:**

The measurements of solving the example problem with this algorithm yielded an average running time of 2.2157 seconds. This is a reduction of roughly 700 milliseconds which corresponds to a speedup of ~1.32. As expected, this implementation is also slower than the standard implementation, however, it can handle much more complex problems.

```
#!
Algorithmus;Dynamic Programming Low Memory (Parallel)
Anzahl Durchlaeufe;5
Durchschnittliche Laufzeit;2.2157
RMS Error;0.0604
1;2.3134
2;2.1674
3;2.1425
4;2.2083
5;2.2469
```


# Conclusion
TODO: hier alle Algorithmen vergleichen.

# Build and Tests #
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

# List of References

* [1] http://www-i1.informatik.rwth-aachen.de/~algorithmus/algo15.php
* [2] gprof https://sourceware.org/binutils/docs/gprof/Compiling.html#Compiling
* [3] gprof eclispe manual https://wiki.eclipse.org/Linux_Tools_Project/GProf/User_Guide
* [4] OpenMP http://openmp.org/wp/
* [5] Intel VTune Amplifier https://software.intel.com/en-us/intel-vtune-amplifier-xe/
* [6] VTune Amplifier and OpenMP https://software.intel.com/en-us/articles/profiling-openmp-applications-with-intel-vtune-amplifier-xe
* [7] Kellerer, H & Pferschy, U & Pisinger, D 2004, *Knapsack Problems*, Springer Verlag
* [8] StackOverflow discussion thread http://stackoverflow.com/questions/31321071/openmp-nested-for-loop-becomes-faster-when-having-parallel-before-outer-loop/31382775
