#ifndef MAIN_ALGORITHMS_DYNAMICPROGRAMMINGSOLVER_H_
#define MAIN_ALGORITHMS_DYNAMICPROGRAMMINGSOLVER_H_

#include <string>
#include <vector>

#include "util/MyMath.h"
#include "main/KnapSackSolver.h"

/**
 * The same struct as KnapSackItem but instead of having
 * double values for weight and worth we use int values.
 * This struct is used to prevent explicit casting during
 * solve of DynamicProgrammingSolver
 */
struct IntegerItem{
	std::string* name;
	int weight;
	int worth;

	bool operator==(const IntegerItem& rhs){
		return weight == rhs.weight && worth == rhs.worth && *name == *(rhs.name);
	}
};

/**
 * The DynamicProgrammingSolver extends the KnapSackSolver class and
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
 * To solve problems with floating point values we have implemented the algorithm of Nemhauser and Ullmann
 */
class DynamicProgrammingSolver : public KnapSackSolver {
public:
	static const std::string NAME;

	DynamicProgrammingSolver(std::string inputFilename, std::string outputFilename, int nrOfExecutions = 1);
	~DynamicProgrammingSolver();

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
	 * Equals the itemlist of the KnapSack, except that those items worths and weights are casted to int.
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

	/**prints the result table to the console*/
	void printTable();

};

#endif /* MAIN_ALGORITHMS_DYNAMICPROGRAMMINGSOLVER_H_ */
