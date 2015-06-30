#ifndef MAIN_ALGORITHMS_DYNAMICPROGRAMMINGSOLVER_H_
#define MAIN_ALGORITHMS_DYNAMICPROGRAMMINGSOLVER_H_

#include <string>
#include <vector>

#include "util/MyMath.h"
#include "main/KnapSackSolver.h"

/**
 * The BruteForceSolver extends the KnapSackSolver class and
 * implements the abstract method solve().
 *
 * Solves the KnapSack-Problem with the dynamic programming approach.
 * The main knapsack-problem is being solved in a bottom-up manner by solving
 * all sub-problems first. When the optimal worths of the base problems
 * are known, the worths of higher sub problems are calculated until
 * the worth of main problem is known. Afterwards the items belonging to the
 * calculated worth are added to the solutionlist.
 *
 * This version is only compatible to integer input values and can not handle floating point values.
 * To handle floating point values, we could multiply them (e.g. by 100) and parse them them to integer
 * but this delivers only a low accuracy and makes the problem / matrix to solve more complex.
 */
class DynamicProgrammingSolver : public KnapSackSolver {
public:
	DynamicProgrammingSolver(std::string inputFilename, std::string outputFilename, int nrOfExecutions = 1);
	~DynamicProgrammingSolver();

protected:

	void setUp();

	void tearDown();

	void solve();
		
private:

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

	/**each row represents the number of items available for the specific sub problem*/
	const int itemRows;

	/**each column represents the max capacity of the knapsack for the specific sub problem*/
	const int weightColumns;
	
	/**prints the table to the console*/
	void printTable();

};

#endif /* MAIN_ALGORITHMS_DYNAMICPROGRAMMINGSOLVER_H_ */
