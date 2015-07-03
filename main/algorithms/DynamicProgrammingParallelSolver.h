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
 * To solve problems with floating point values we have implemented the algorithm of Nemhauser and Ullmann
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
	static const int PARALLEL_CAPACITY_THRESHOLD;
	static const int PARALLEL_ITEM_THRESHOLD;

	static const std::string NAME;

	DynamicProgrammingParallelSolver(std::string inputFilename,
			std::string outputFilename, int nrOfExecutions = 1);

	~DynamicProgrammingParallelSolver();

protected:

	void setUp();

	void tearDown();

	/**
	 * Solves every subproblem of the given knapsack problem including the knapsack problem itself.
	 * Each entry of the table represents the best worth achievable by the specific sub problem.
	 * The problems are being solved in a bottom-up manner.
	 * We start by solving the lowest subproblem [1,1] and end up solving the main problem at [numOfItems, maxCapacity].
	 *
	 * Why don't we start at [0,0] ? Because worths of row[0] and worths of column[0] stay 0.
	 * This is because a knapsack with 0 capacity can not have any items and a knapsack with 0 items can not weigh anything (0 capacity = 0 items).
	 * Thus the best worths of our base-problems (the sub problems at [i,0] for all [0 <= i < cols] and the sub problems at [0, c] for all [0 <= c < rows])
	 * stay 0.
	 *
	 * In this version the independent elements in each row are calculated in parallel.
	 * Meaning: each row i has c elements where i = index of itemRows and c = index of weightColumns.
	 * All c elements can be calculated in parallel, since they are independent from each other.
	 * We can not calculate several rows or columns in parallel, since they are dependant from each other.
	 */
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
	 * Equals the itemlist (itempool) of the KnapSack, except that those items worths and weights are casted to int.
	 * Thus we prevent explicit casting during solve
	 */
	IntegerItem* integerItems;

	/**
	 * Determines items included in the optimal solution by
	 * traversing the populated result table.
	 * This happens top-down, meaning we start at the most lower right table entry.
	 * This entry contains the optimal worths for the main knapsack problem.
	 * By comparing the worths of specific sub problems we can determine if a
	 * specific item is part of the optimal solution or not.
	 *
	 * If the optimal worths of entries of two rows
	 * table[currItem][currWeight] and table[currItem-1][currWeight]
	 * differ from each other, the item of the current row must be part of the solution.
	 * We add the item and decrease the capacity by the weight of that item.
	 * Thus, new sub problems with the new capacity will be checked until we checked all items.
	 */
	void backtrackItemsOfSolution();

	/**prints the table to the console*/
	void printTable();

};

#endif /* MAIN_ALGORITHMS_DYNAMICPROGRAMMINGPARALLELSOLVER_H_ */
