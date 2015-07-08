#include "main/algorithms/BruteForceSolver.h"
#include "util/TestUtils.h"
#include "test/TestData.h"

/**
 * Tests whether the brute force algorithm for solving the knapsack problem works correctly.
 * Returns 0 if test succeeds.
 * Returns -1 if actual output mismatches assumed output.
 */
int testBruteForceSolver() {
	BruteForceSolver* solver = new BruteForceSolver(KNAPSACK_INPUT_FILE, TEST_OUTPUT_FILE);

	solver->start();

	delete solver;

	return TestUtils::checkOutput(ASSUMED_CONTENT_FILE_1, ASSUMED_CONTENT_LINES_FILE_1, TEST_OUTPUT_FILE);
}

/**
 * Tests whether the brute force algorithm for solving the knapsack problem works correctly.
 * Returns 0 if test succeeds.
 * Returns -1 if actual output mismatches assumed output.
 */
int main(int argc, char* argv[]){
	return testBruteForceSolver();
}
