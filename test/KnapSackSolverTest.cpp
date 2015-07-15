#include <cstdio>

#include "main/KnapSackSolver.h"
#include "util/TestUtils.h"
#include "test/TestData.h"

/**
 * Pseudo implementation of a KnapSackSolver to test wether the execution framework works correctly.
 */
class SolverImpl: public KnapSackSolver {
public:
	SolverImpl(std::string inputFilename, std::string outputFilename, int nrOfExecutions=1)
	: KnapSackSolver(inputFilename, outputFilename, "Solver Test", nrOfExecutions)
	{
	}

	virtual void solve() {
		// For the test we will just put every possible exemplar into the solution
		KnapSackItem* items = knapSack.getItems();
		for(int i=0; i < knapSack.getNumOfItems() ;++i) {
			itemsOfSolution.insert(itemsOfSolution.end(), items[i]);
		}
	}
};

const std::string ASSUMED_CONTENT_SOLVER[] {"Capacity;15.0", "XXL blue 0x;4", "gray mouse;4", "big green box;4", "yellow daisy;4", "salmon mousse;4", "Total weight;80.00", "Total worth;76.00"};
const int ASSUMED_CONTENT_LINES_SOLVER = 8;

/**
 * Tests whether the execution framework KnapSackSolver works correctly.
 * Returns 0 if test succeeds.
 * Returns -1 if actual output mismatches assumed output
 */
int testKnapSackSolver() {
	KnapSackSolver* solver = new SolverImpl(KNAPSACK_INPUT_FILE, TEST_OUTPUT_FILE);

	solver->start();

	delete solver;

	return TestUtils::checkOutput(ASSUMED_CONTENT_SOLVER, ASSUMED_CONTENT_LINES_SOLVER, TEST_OUTPUT_FILE);
}

/**
 * Tests whether the execution framework KnapSackSolver works correctly.
 * Returns 0 if test succeeds.
 * Returns -1 if actual output mismatches assumed output
 */
int main(int argc, char* argv[]){
	return testKnapSackSolver();
}
