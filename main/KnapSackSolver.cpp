/*
 * KnapSackSolver.cpp
 *
 *  Created on: Jun 13, 2015
 *      Author: viktor
 */

#include "KnapSackSolver.h"

KnapSackSolver::KnapSackSolver(std::string inputFilename, std::string outputFilename, int nrOfExecutions)
: knapSack(0,0),
  inputFilename(inputFilename),
  outputFilename(outputFilename),
  numberOfExecutions(nrOfExecutions),
  itemsOfSolution()
{
	initKnapSack();
}

KnapSackSolver::~KnapSackSolver() {
	// TODO Auto-generated destructor stub
}

void KnapSackSolver::initKnapSack() {
	readInput();
}

void KnapSackSolver::readInput() {
	// TODO: maybe we should use a pointer otherwise we have to copy it here.
	knapSack = KnapSackReader::readKnapSackFrom(inputFilename.c_str());
}

void KnapSackSolver::start() {
	for (int i=0; i < numberOfExecutions ;++i) {
		executeOneRun();
	}
}

void KnapSackSolver::executeOneRun() {
	setUp();

	std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
	const int n = 10000,
	            r = 1000;
	const double flopsPerCalc = 2.0;
	start = getWalltime();

	solve();

	end = getWalltime();
	printWalltimeInSeconds(start, end);

	printGFLOPs( static_cast<double>(r) * static_cast<double>( n ), flopsPerCalc, elapsedSeconds( start, end ) );

	tearDown();

	writeSolution();
}

void KnapSackSolver::writeSolution() const {

	// Determine the amount of distinct knapSackItems
	std::vector<KnapSackItem> distinctItems;
	for(int i=0; i < itemsOfSolution.size() ;++i) {
		// Check if item is already in distinctItems
		bool itemIsNotAlreadyIncluded = true;
		for(int j=0; j < distinctItems.size() ;++j) {
			if (distinctItems[j] == itemsOfSolution[i]) {
				itemIsNotAlreadyIncluded = false;
				break;
			}
		}
		if (itemIsNotAlreadyIncluded) {
			distinctItems.insert(distinctItems.end(), itemsOfSolution[i]);
		}
	}

	// Create the file
	KnapSackWriter writer(outputFilename, distinctItems.size(), knapSack.getCapacity());

	for(int i=0; i < distinctItems.size() ;++i) {
		KnapSackItem& currItem = distinctItems[i];

		// Count number of exemplars
		int counter = 0;
		for (int j = 0; j < itemsOfSolution.size(); ++j) {
			if (currItem == itemsOfSolution[j])
				counter++;
		}
		assert(counter != 0);

		writer.addItem(&currItem, counter);
	}

	if ( ! writer.writeToFile()) {
		std::printf("Could not write to file.");
	}

}

void KnapSackSolver::setUp() {
	// Nothing to do in default implementation
}

void KnapSackSolver::tearDown() {
	// Nothing to do in default implementation
}
