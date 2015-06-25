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
	 * number of rows. each row represents the number of items available for the specific sub problem.
	 */
	const int rows;

	/**
	 * number of colums. each column represents the max capacity of the knapsack for the specific sub problem.
	 */
	const int cols;
	double** table;
	
	void printTable();

};

#endif /* MAIN_ALGORITHMS_DYNAMICPROGRAMMINGSOLVER_H_ */
