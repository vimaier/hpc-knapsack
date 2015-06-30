#ifndef MAIN_ALGORITHMS_BRUTEFORCESOLVER_H_
#define MAIN_ALGORITHMS_BRUTEFORCESOLVER_H_

#include <string>
#include <vector>

#include "main/KnapSackSolver.h"

/**
 * The BruteForceSolver extends the KnapSackSolver class and
 * implements the abstract method solve().
 *
 * Solves the KnapSack-Problem with a brute force method by trying each possible combination of
 * KnapSack-objects. See solve() method of BruteForceSolver.cpp for more information.
 */
class BruteForceSolver : public KnapSackSolver {
public:
	static const std::string NAME;

	BruteForceSolver(std::string inputFilename, std::string outputFilename, int nrOfExecutions = 1);

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
};

#endif /* MAIN_ALGORITHMS_BRUTEFORCESOLVER_H_ */
