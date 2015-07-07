#ifndef MAIN_ALGORITHMS_DYNAMICPROGRAMMINGLOWMEMORYPARALLELSOLVER_H_
#define MAIN_ALGORITHMS_DYNAMICPROGRAMMINGLOWMEMORYPARALLELSOLVER_H_

#include <string>
#include <vector>
#include <assert.h>

#include "util/MyMath.h"
#include "main/KnapSackSolver.h"
#include "main/algorithms/DynamicProgrammingSolver.h" // for IntegerItem struct

/**
 * The DynamicProgrammingLowMemoryParallelSolver extends the KnapSackSolver class and
 * implements the abstract method solve().
 *
 * It works exactly like the DynamicProgrammingLowMemorySolver except that some parts run in parallel.
 *
 * This version is only compatible to integer input values and can not handle floating point values.
 * To handle floating point values, we could multiply them (e.g. by 100) and parse them them to integer
 * but this delivers only a low accuracy and makes the problem / matrix to solve more complex.
 * To solve problems with floating point values we have implemented the algorithm of Nemhauser and Ullmann
 */
class DynamicProgrammingLowMemoryParallelSolver : public KnapSackSolver {
public:
	static const std::string NAME;
	static const int PARALLEL_CAPACITY_THRESHOLD;
	static const int PARALLEL_ITEMS_THRESHOLD;

	DynamicProgrammingLowMemoryParallelSolver(std::string inputFilename, std::string outputFilename, int nrOfExecutions = 1);
	~DynamicProgrammingLowMemoryParallelSolver();

protected:

	void setUp();

	void tearDown();

	/**
	 * Calls solveProblem(..) to determine the max worth of the given knapSack problem
	 * and then uses determineItemsOfSolutionRecursively(..) to backtrack the packed items.
	 */
	void solve();
		
private:
	/**
	 * Equals the itemlist (itempool) of the KnapSack, except that those items worths and weights are casted to int.
	 * Thus we prevent explicit casting during solve
	 */
	IntegerItem* integerItems;

	/**
	 * Used to store the packed items during the backtracking process.
	 * In tearDown(), the items of this list are converted to KnapSackItems
	 * and put into the original itemsOfSolution. This is done because the
	 * conversion from integerItem to knapSackItem should not affect time measurement.
	 */
	std::vector<IntegerItem> integerItemsOfSolution;

	/**
	 * Solves the given knapsack problem with the dynamic programming approach.
	 * While solving, this algorithm only operates on the given solutionRow as data holder.
	 * At the beginning the solutionRow will be initialized by zeros and then will be filled
	 * for each item iteration. At the end it represents the last row of typical DP result table.
	 * The last element of the solutionRow therefore represents the solution / max worth of the given
	 * problem.
	 *
	 * Returns a pointer to the final solutionRow.
	 */
	int* solveProblem(IntegerItem* items, int itemsLength, int* solutionRow, int rowLength, int capacity);

	/**
	 * Used to determine / backtrack the items that have been packed to achieve the given solution for
	 * the given knapsack problem (items, capacity). This is needed since we do not store the solutions
	 * of all sub problems within a table.
	 *
	 * This algorithm was introduced by Hans Kellerer and Ulrich Pferschy in their book 'Knapsack Problems' on page 47.
	 * It is a recursive divide and conquer algorithm that divides the given itemlist in sublists until only one element is left
	 * within the respective sublist, from which we know it must have been packed. Therefore it uses the solveProblem algorithm
	 * several times (for each divided sublist).
	 */
	void determineItemsOfSolutionRecursively(IntegerItem* items, int numOfItems, int capacity, int solution);
};

#endif /* MAIN_ALGORITHMS_DYNAMICPROGRAMMINGLOWMEMORYPARALLELSOLVER_H_ */
