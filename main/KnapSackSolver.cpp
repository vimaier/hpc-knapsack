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
	// TODO Auto-generated stub

}

void KnapSackSolver::setUp() {
	// Nothing to do in default implementation
}

void KnapSackSolver::setTearDown() {
	// Nothing to do in default implementation
}
