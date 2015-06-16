/**
 * Tests whether the execution framework KnapSackSolver works correctly.
 */

#include <cstdio>

#include "main/KnapSackSolver.h"

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

const char* KNAPSACK_INPUT_FILE = "../res/KnapSackItemsForUnittest.txt";
/* Content of text file
15.0 4 5
XXL blue Ox   02.0 2.00
gray mouse    01.0 2.00
big green box 12.0 4.00
yellow daisy  04.0 10.00
salmon mousse 01.0 1.00

 */

const char* KNAPSACK_OUTPUT_FILE = "outputForTesting.txt";
const std::string ASSUMED_CONTENT = "Kapazität;15.0\nXXL blue Ox;4\ngray mouse;4\nbig green box;4\nyellow daisy;4\nsalmon mousse;4\nGesamtgewicht;80.0\nGesamtwert;76.00";


int testKnapSackSolver() {
	KnapSackSolver* solver = new SolverImpl(KNAPSACK_INPUT_FILE, KNAPSACK_OUTPUT_FILE);

	solver->start();

	// Read file
	std::ifstream ifile;
	std::string str;
	ifile.open(KNAPSACK_OUTPUT_FILE, std::ios::binary);
	if ( ! ifile.is_open()) {
		std::fprintf(stderr, "Could not open written file.");
		return -1;
	}

	int length;
	char * buffer;

		  // get length of file:
	ifile.seekg (0, std::ios::end);
	length = ifile.tellg();
	ifile.seekg (0, std::ios::beg);

	// allocate memory:
	buffer = new char [length];

	// read data as a block:
	ifile.read (buffer,length);

	ifile.close();

	std::string readStr(buffer,length);

	delete[] buffer;

	// Compare with assumed String
	if (ASSUMED_CONTENT.compare(readStr)==0) {
		// Delete file again
		std::remove(KNAPSACK_OUTPUT_FILE);
		return 0;
	}
	else {
		std::fprintf(stderr, "Mismatch between written and assumed file content\nAssumed:\n%s\n\nActual:\n%s\n", ASSUMED_CONTENT.c_str(), readStr.c_str());
		return -2;
	}
}

int main(int argc, char* argv[]){
	return testKnapSackSolver();
}
