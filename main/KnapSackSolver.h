/*
 * KnapSackSolver.h
 *
 *  Created on: Jun 13, 2015
 *      Author: viktor
 */

#ifndef MAIN_KNAPSACKSOLVER_H_
#define MAIN_KNAPSACKSOLVER_H_

#include "main/KnapSack.h"

/**
 * The KnapSackSolver is the main class for solving the knapsack problem.
 * It is an abstract class from which each algorithm should extend and
 * implement the abstract method solve().
 *
 * setUp(): The abstract function setUp() can be used to transform the standard
 * data format (see class Knapsack) in a specific format for the algorithm.
 *
 * tearDown(): The abstract function tearDown() can be used to clean something up or
 * to transform a specific format to our standard format (see class KnapSack).
 *
 * The functions setUp() and tearDown() are excluded from the time measuring. Solely
 * solve() will be measured.
 */
class KnapSackSolver {
public:
	KnapSackSolver();
	virtual ~KnapSackSolver();

	/**
	 * Can be used to transform the standard data format (see class Knapsack) in a
	 * specific format for the algorithm.
	 */
	virtual void setUp();

	/**
	 * Can be used to clean something up or to transform a specific format to our
	 * standard format (see class KnapSack).
	 */
	virtual void setTearDown();

	/**
	 * Abstract function to solve the knapsack problem. This function will be time measured.
	 */
	virtual void solve() = 0;
};

#endif /* MAIN_KNAPSACKSOLVER_H_ */
