/**
 * Tests whether the dynamic programming algorithm for solving the knapsack problem works correctly.
 */

#include "main/algorithms/DynamicProgrammingSolver.h"
#include "util/TestUtils.h"
#include "test/TestData.h"

/* Content of text file
5.0 1 4
item_01                 2.0 3.0
item_02                 3.0 4.0
item_03                 4.0 5.0
item_04                 5.0 6.0
 */

/* Expected Solution
 * -----------------------------------
 * 1x item_02 -> 3 weight, 4 worth
 * 1x item_01 -> 2 weight, 3 worth
 * -----------------------------------
 * overall 5 weight and 7 worth
*/


int testBruteForceSolver() {
	DynamicProgrammingSolver* solver = new DynamicProgrammingSolver(KNAPSACK_INPUT_FILE_DP_EXAMPLE, TEST_OUTPUT_FILE);

	solver->start();

	return TestUtils::checkOutput(ASSUMED_CONTENT_FILE_DP, ASSUMED_CONTENT_LINES_FILE_DP, TEST_OUTPUT_FILE);
}

int main(int argc, char* argv[]){
	return testBruteForceSolver();
}
