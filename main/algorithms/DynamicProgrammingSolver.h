#ifndef MAIN_ALGORITHMS_DYNAMICPROGRAMMINGSOLVER_H_
#define MAIN_ALGORITHMS_DYNAMICPROGRAMMINGSOLVER_H_

#include <string>
#include <vector>

#include "main/KnapSackSolver.h"

/**
 * The BruteForceSolver extends the KnapSackSolver class and
 * implements the abstract method solve().
 *
 * Solves the KnapSack-Problem with the dynamic programming approach.
 */
class DynamicProgrammingSolver : public KnapSackSolver {
public:
	DynamicProgrammingSolver(std::string inputFilename, std::string outputFilename, int nrOfExecutions = 1);

protected:

	void setUp();

	void tearDown();

	void solve();
		
private:

	
};

#endif /* MAIN_ALGORITHMS_DYNAMICPROGRAMMINGSOLVER_H_ */
