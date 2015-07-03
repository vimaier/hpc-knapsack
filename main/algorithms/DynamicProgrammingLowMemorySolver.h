#ifndef MAIN_ALGORITHMS_DYNAMICPROGRAMMINGLOWMEMORYSOLVER_H_
#define MAIN_ALGORITHMS_DYNAMICPROGRAMMINGLOWMEMORYSOLVER_H_

#include <string>
#include <vector>
#include <assert.h>

#include "util/MyMath.h"
#include "main/KnapSackSolver.h"
#include "main/algorithms/DynamicProgrammingSolver.h" // for IntegerItem struct

/**
 * The DynamicProgrammingLowMemorySolver extends the KnapSackSolver class and
 * implements the abstract method solve().
 *
 * Solves the KnapSack-Problem with the dynamic programming approach (see DynamicProgrammingSolver).
 * But instead of storing the whole matrix / result table, this algorithm reduces the used storage
 * by only storing the currently needed data within two rows (instead of numOfItem rows). Instead of
 * having the whole table we just need one row which stores the previously calculated worths and uses
 * them to calculate the worths of the next iteration.
 *
 * This however causes some difficulty when trying to backtrack the items of the solution.
 * Before we could easily the stored result table to look up the items that were included in the solution.
 * Now that the table is gone, we need another approach to backtrack the picked items.
 * Therefore we use the Recursive-DP algorithm presented by Prof. Hans Kellerer and Prof. Ulrich Pferschy
 * in their book 'Knapsack Problems' (page 47).
 *
 * This version is only compatible to integer input values and can not handle floating point values.
 * To handle floating point values, we could multiply them (e.g. by 100) and parse them them to integer
 * but this delivers only a low accuracy and makes the problem / matrix to solve more complex.
 * To solve problems with floating point values we have implemented the algorithm of Nemhauser and Ullmann
 */
class DynamicProgrammingLowMemorySolver : public KnapSackSolver {
public:
	static const std::string NAME;

	DynamicProgrammingLowMemorySolver(std::string inputFilename, std::string outputFilename, int nrOfExecutions = 1);
	~DynamicProgrammingLowMemorySolver();

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

#endif /* MAIN_ALGORITHMS_DYNAMICPROGRAMMINGLOWMEMORYSOLVER_H_ */
