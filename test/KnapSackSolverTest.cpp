/**
 * Tests whether the execution framework KnapSackSolver works correctly.
 */

#include <cstdio>

#include "main/KnapSackSolver.h"
#include "util/TestUtils.h"

class SolverImpl: public KnapSackSolver {
public:
	SolverImpl(std::string inputFilename, std::string outputFilename, int nrOfExecutions=1)
	: KnapSackSolver(inputFilename, outputFilename, nrOfExecutions)
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

const char* KNAPSACK_INPUT_FILE = "res/KnapSackItemsForUnittest.txt";
/* Content of text file
15.0 4 5
XXL blue Ox   02.0 2.00
gray mouse    01.0 2.00
big green box 12.0 4.00
yellow daisy  04.0 10.00
salmon mousse 01.0 1.00

 */

const char* TEST_OUTPUT_FILE = "outputForTesting.txt";
const std::string ASSUMED_CONTENT[] {"Kapazität;15.0", "XXL blue 0x;4", "gray mouse;4", "big green box;4", "yellow daisy;4", "salmon mousse;4", "Gesamtgewicht;80.0", "Gesamtwert;76.00"};
const int ASSUMED_CONTENT_LENGTH = 8;

int testKnapSackSolver() {
	KnapSackSolver* solver = new SolverImpl(KNAPSACK_INPUT_FILE, TEST_OUTPUT_FILE);

	solver->start();

	return TestUtils::checkOutput(ASSUMED_CONTENT, ASSUMED_CONTENT_LENGTH, TEST_OUTPUT_FILE);
}

int main(int argc, char* argv[]){
	return testKnapSackSolver();
}
