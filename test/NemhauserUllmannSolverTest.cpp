#include "main/algorithms/BruteForceSolver.h"
#include "main/algorithms/NemhauserUllmannSolver.h"
#include "util/TestUtils.h"
#include "test/TestData.h"

/**
 * Tests whether the nemhauser ullmann algorithm for solving the knapsack problem works correctly.
 * Returns 0 if test succeeds.
 * Returns -1 if actual output mismatches assumed output
 */
int testNemhauserUllmannSolver(const char* inputFile, const char* outputFile, const std::string* assumedContent, int assumedContentLength) {
	NemhauserUllmannSolver* solver = new NemhauserUllmannSolver(inputFile, outputFile);

	solver->start();

	delete solver;

	return TestUtils::checkOutput(assumedContent, assumedContentLength, outputFile);
}

/**
 * Tests whether the nemhauser ullmann algorithm for solving the knapsack problem works correctly.
 * Returns 0 if test succeeds.
 * Returns 1 if actual output of KNAPSACK_INPUT_FILE_FIRST_EXAMPLE mismatches assumed output.
 * Returns 2 if actual output of KNAPSACK_INPUT_FILE_SECOND_EXAMPLE mismatches assumed output.
 * Returns 3 if actual output of KNAPSACK_INPUT_FILE_THIRD_EXAMPLE mismatches assumed output.
 */
int main(int argc, char* argv[]){
	int returnCode = testNemhauserUllmannSolver(KNAPSACK_INPUT_FILE_FIRST_EXAMPLE, TEST_OUTPUT_FILE,
												ASSUMED_CONTENT_FILE_1, ASSUMED_CONTENT_LINES_FILE_1);
	if (0 != returnCode)
		return 1;

	returnCode = testNemhauserUllmannSolver(KNAPSACK_INPUT_FILE_SECOND_EXAMPLE, TEST_OUTPUT_FILE,
												ASSUMED_CONTENT_FILE_2, ASSUMED_CONTENT_LINES_FILE_2);
	if (0 != returnCode)
		return 2;

	returnCode = testNemhauserUllmannSolver(KNAPSACK_INPUT_FILE_THIRD_EXAMPLE, TEST_OUTPUT_FILE,
												ASSUMED_CONTENT_FILE_3, ASSUMED_CONTENT_LINES_FILE_3);
	if (0 != returnCode)
		return 3;

	return returnCode;
}
