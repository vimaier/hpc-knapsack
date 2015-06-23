#ifndef MAIN_ALGORITHMS_FEASIBLEBRUTEFORCESOLVER_H_
#define MAIN_ALGORITHMS_FEASIBLEBRUTEFORCESOLVER_H_

#include <string>
#include <vector>

#include "main/KnapSackSolver.h"

/**
 * The FeasibleBruteForceSolver extends the KnapSackSolver class and
 * implements the abstract method solve().
 *
 * Solves the KnapSack-Problem with a brute force method by trying each feasible possible combination of
 * KnapSack-objects. It is different from the other BruteForceSolver Algorithm, because it remembers
 * combinations which did not work (cause of capacity) and thus skips the ones, which contain the same (plus others) items. 
 * See solve() method of BruteForceSolver.cpp for more information.
 */
class FeasibleBruteForceSolver : public KnapSackSolver {
public:
	FeasibleBruteForceSolver(std::string inputFilename, std::string outputFilename, int nrOfExecutions = 1);

protected:

	void setUp();

	void tearDown();

	void solve();
		
private:

	/**
	* CurrentCombination is a bit pattern which describes the current combination of items
	* which is being evaluated. It is modified during solve() and used to update bestCombination
	*/
	std::vector<char> currentCombination;

	/**
	* BestCombination is a bit pattern which describes the best combination of items that has
	* been determined during solve(). It is used to track the best combination over the process
	* of evaluation each combination and to fill itemsOfSolution during tearDown().
	*/
	std::vector<char> bestCombination;

	/**
	 * The number of possible knapsack item combinations. this is always 2^n where n is the number of available knapsack items.
	 */
	const unsigned long long int numOfCombinations;

	std::vector<std::vector<char>> failedCombinations;
};

#endif /* MAIN_ALGORITHMS_FEASIBLEBRUTEFORCESOLVER_H_ */
