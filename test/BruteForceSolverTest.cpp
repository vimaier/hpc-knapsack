/**
 * Tests whether the brute force algorithm for solving the knapsack problem works correctly.
 */

#include "main/algorithms/BruteForceSolver.h"
#include "main/algorithms/NemhauserUllmannSolver.h"
#include "util/TestUtils.h"
#include "test/TestData.h"

/* Content of text file
15.0 4 5
XXL blue Ox   02.0 2.00
gray mouse    01.0 2.00
big green box 12.0 4.00
yellow daisy  04.0 10.00
salmon mousse 01.0 1.00
 */

/* Expected Solution
 * -----------------------------------
 * 3x gray mouse -> 3 weight, 6 worth
 * 3x yellow daisy -> 12 weight, 30 worth
 * -----------------------------------
 * overall 15 weight and 36 worth
*/

const char* TEST_OUTPUT_FILE = "outputForTesting.txt";

/**/
const std::string ASSUMED_CONTENT[] {"Kapazität;15.0", "gray mouse;3", "yellow daisy;3", "Gesamtgewicht;15.0", "Gesamtwert;36.00"};
const int ASSUMED_CONTENT_LENGTH = 5;


int testBruteForceSolver() {
	BruteForceSolver* solver = new BruteForceSolver(KNAPSACK_INPUT_FILE, TEST_OUTPUT_FILE);

	solver->start();

	return TestUtils::checkOutput(ASSUMED_CONTENT, ASSUMED_CONTENT_LENGTH, TEST_OUTPUT_FILE);
}

int main(int argc, char* argv[]){
	return testBruteForceSolver();
}
