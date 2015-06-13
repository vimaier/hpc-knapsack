/*
 * KnapSackSolver.cpp
 *
 *  Created on: Jun 13, 2015
 *      Author: viktor
 */

#include "KnapSackSolver.h"

KnapSackSolver::KnapSackSolver(std::string inputFilename, std::string outputFilename, int nrOfExecutions)
: knapSack(0,0,0),
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

void KnapSackSolver::writeSolution() const {
	KnapSackItem* items = knapSack.getItems();

	// Determine the amount of distinct knapSackItems
	std::vector<KnapSackItem> distinctItems;
	for(int i=0; i < knapSack.getNumOfItems() ;++i) {
		// Check if item is already in distinctItems
		bool itemIsNotAlreadyIncluded = true;
		for(int j=0; j < distinctItems.size() ;++j) {
			if (items[i] == distinctItems[j]) {
				itemIsNotAlreadyIncluded = false;
				break;
			}
		}
		if (itemIsNotAlreadyIncluded) {
			distinctItems.insert(distinctItems.end(), items[i]);
		}
	}

	// Create the file
	KnapSackWriter writer(outputFilename, distinctItems.size(), knapSack.getCapacity());

	for(int i=0; i < distinctItems.size() ;++i) {
		KnapSackItem& currItem = distinctItems[i];

		// Count number of exemplars
		int counter = 0;
		for (int j=0; j < knapSack.getNumOfItems() ;++j) {
			if (currItem == items[j])
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

void KnapSackSolver::setTearDown() {
	// Nothing to do in default implementation
}
