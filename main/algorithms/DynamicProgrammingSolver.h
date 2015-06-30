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
 */
class DynamicProgrammingSolver : public KnapSackSolver {
public:
	static const std::string NAME;

	DynamicProgrammingSolver(std::string inputFilename, std::string outputFilename, int nrOfExecutions = 1);
	~DynamicProgrammingSolver();

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

#endif /* MAIN_ALGORITHMS_DYNAMICPROGRAMMINGSOLVER_H_ */
