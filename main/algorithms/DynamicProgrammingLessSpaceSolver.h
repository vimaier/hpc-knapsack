#ifndef MAIN_ALGORITHMS_DYNAMICPROGRAMMINGLESSSPACESOLVER_H_
#define MAIN_ALGORITHMS_DYNAMICPROGRAMMINGLESSSPACESOLVER_H_

#include <string>
#include <vector>
#include <assert.h>

#include "util/MyMath.h"
#include "main/KnapSackSolver.h"
#include "main/algorithms/DynamicProgrammingSolver.h" // for IntegerItem struct

/**
 * The DynamicProgrammingLessSpaceSolver extends the KnapSackSolver class and
 * implements the abstract method solve().
 *
 * Solves the KnapSack-Problem with the dynamic programming approach (see DynamicProgrammingSolver).
 * But instead of storing the whole matrix / result table, this algorithm reduces the used storage
 * by only storing the currently needed data within two rows (instead of numOfItem rows). Instead of
 * having the whole table we just need one row which stores the previously calculated worths and uses
 * them to calculate the worths of the next iteration.
 * This however causes some difficulty when trying to backtrack the items of the solution.
 * TODO: explain backtracking. siehe seite 66 in kellerer buch
 *
 * This version is only compatible to integer input values and can not handle floating point values.
 * To handle floating point values, we could multiply them (e.g. by 100) and parse them them to integer
 * but this delivers only a low accuracy and makes the problem / matrix to solve more complex.
 * To solve problems with floating point values we have implemented the algorithm of Nemhauser and Ullmann
 */
class DynamicProgrammingLessSpaceSolver : public KnapSackSolver {
public:
	static const std::string NAME;

	DynamicProgrammingLessSpaceSolver(std::string inputFilename, std::string outputFilename, int nrOfExecutions = 1);
	~DynamicProgrammingLessSpaceSolver();

protected:

	void setUp();

	void tearDown();

	void solve();
		
private:
	/**
	 * Equals the itemlist (itempool) of the KnapSack, except that those items worths and weights are casted to int.
	 * Thus we prevent explicit casting during solve
	 */
	IntegerItem* integerItems;
	std::vector<IntegerItem> integerItemsOfSolution;

	int* solveProblem(IntegerItem* items, int itemsLength, int* currentRow, int rowLength, int capacity);
	void determineItemsOfSolutionRecursively(IntegerItem* items, int numOfItems, int capacity, int solution);
};

#endif /* MAIN_ALGORITHMS_DYNAMICPROGRAMMINGLESSSPACESOLVER_H_ */
