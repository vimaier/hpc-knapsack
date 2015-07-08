#include "main/algorithms/DynamicProgrammingLowMemoryParallelSolver.h"
#include "util/TestUtils.h"
#include "test/TestData.h"

/**
 * Tests whether the parallel dynamic programming low memory algorithm for solving the knapsack problem works correctly.
 * Returns 0 if test succeeds.
 * Returns -1 if actual output missmatches assumed output.
 */
int testDPLMPSolver(const char* inputFile, const char* outputFile, const std::string* assumedContent, int assumedContentLength) {
	KnapSackSolver* solver = new DynamicProgrammingLowMemoryParallelSolver(inputFile, outputFile);

	solver->start();

	delete solver;

	return TestUtils::checkOutput(assumedContent, assumedContentLength, outputFile);
}

/**
 * Tests whether the parallel dynamic programming low memory algorithm for solving the knapsack problem works correctly.
 * Returns 0 if test succeeds.
 * Returns 1 if actual output of KNAPSACK_INPUT_FILE_FIRST_EXAMPLE missmatches assumed output.
 * Returns 2 if actual output of KNAPSACK_INPUT_FILE_THIRD_EXAMPLE missmatches assumed output.
 * Returns 3 if actual output of KNAPSACK_INPUT_FILE_DP_EXAMPLE missmatches assumed output.
 */
int main(int argc, char* argv[]){
	int returnCode = testDPLMPSolver(KNAPSACK_INPUT_FILE_FIRST_EXAMPLE, TEST_OUTPUT_FILE,
			ASSUMED_CONTENT_FILE_1, ASSUMED_CONTENT_LINES_FILE_1);
	if (0 != returnCode)
		return 1;

	returnCode = testDPLMPSolver(KNAPSACK_INPUT_FILE_THIRD_EXAMPLE, TEST_OUTPUT_FILE,
			ASSUMED_CONTENT_FILE_3, ASSUMED_CONTENT_LINES_FILE_3);
	if (0 != returnCode)
		return 2;

	returnCode = testDPLMPSolver(KNAPSACK_INPUT_FILE_DP_EXAMPLE, TEST_OUTPUT_FILE,
			ASSUMED_CONTENT_FILE_DP_DIFFERENT_ORDER, ASSUMED_CONTENT_LINES_FILE_DP);

	if (0 != returnCode)
		return 3;

	return returnCode;
}
