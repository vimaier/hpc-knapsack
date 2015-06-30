#ifndef MAIN_ALGORITHMS_DYNAMICPROGRAMMINGPARALLELSOLVER_H_
#define MAIN_ALGORITHMS_DYNAMICPROGRAMMINGPARALLELSOLVER_H_

#include <string>
#include <vector>

#include "util/MyMath.h"
#include "main/KnapSackSolver.h"
#include "main/algorithms/DynamicProgrammingSolver.h" // for IntegerItem struct
/**
 * The DynamicProgrammingParallelSolver extends the KnapSackSolver class and
 * implements the abstract method solve().
 *
 * It follows the same approach as the DynamicProgramminParallelSolver
 * (see DynamicProgrammingSolver.h)
 * but calculates the entries of each row in parallel.
 *
 * This version is only compatible to integer input values and can not handle floating point values.
 * To handle floating point values, we could multiply them (e.g. by 100) and parse them them to integer
 * but this delivers only a low accuracy and makes the problem / matrix to solve more complex.
 */
class DynamicProgrammingParallelSolver: public KnapSackSolver {
public:
	/**
	 * This threshold is used to determine whether the problem should be solved in parallel.
	 * It is not necessary to start several threads and calculate the elements in parallel
	 * when the number of elements of one row is lower than a certain threshold.
	 * In this case it would take more time to start the threads than just solving the
	 * problem sequentially.
	 *
	 * The number of elements per row is depending on the max capacity of the knapsack,
	 * since there are as many columns as the value of the capacity.
	 */
	const int PARALLEL_CAPACITY_THRESHOLD = 100;

	static const std::string NAME;

	DynamicProgrammingParallelSolver(std::string inputFilename,
			std::string outputFilename, int nrOfExecutions = 1);

	~DynamicProgrammingParallelSolver();

protected:

	void setUp();

	void tearDown();

	void solve();

private:
	/**each row represents the number of items available for the specific sub problem*/
	const int itemRows;

	/**each column represents the max capacity of the knapsack for the specific sub problem*/
	const int weightColumns;

	/**
	 * The result table.
	 * Each row represents the number of items available for the specific sub problem
	 * Each column represents the max capacity of the knapsack for the specific sub problem
	 *
	 * The upper left entry represents the optimal worth for the sub-problem [0,0]
	 * (a knapsack that can choose among 0 items and has a capacity of 0).
	 *
	 * The lower right entry represents the optimal worth for the main-problem
	 * (the knapsack that can choose among all available items and has the highest capacity possible).
	 *
	 * Example table:

	 |[c:0]|[c:1]|[c:2]|[c:3]|[c:4]|[c:5]
	 -----------------------------------------
	 [i:0]| 0	| 0	  | 0	| 0	  | 0	| 0
	 -----------------------------------------
	 [i:1]| 0	| 0	  | 3	| 3	  | 3	| 3
	 -----------------------------------------
	 [i:2]| 0	| 0	  | 3	| 4	  | 4	| 7
	 -----------------------------------------
	 [i:3]| 0	| 0	  | 3	| 4	  | 5	| 7
	 -----------------------------------------
	 [i:4]| 0	| 0	  | 3	| 4	  | 5	| 7
	 -----------------------------------------
	 *
	 */
	int** table;

	/**
	 * Equals the itemlist of the KnapSack, except that those items worths and weights are casted to int.
	 * Thus we prevent explicit casting during solve
	 */
	IntegerItem* integerItems;

	/**prints the table to the console*/
	void printTable();

};

#endif /* MAIN_ALGORITHMS_DYNAMICPROGRAMMINGPARALLELSOLVER_H_ */
