#ifndef MAIN_ALGORITHMS_NEMHAUSERULLMANNPARALLELSOLVER_H_
#define MAIN_ALGORITHMS_NEMHAUSERULLMANNPARALLELSOLVER_H_

#include <string>
#include <vector>

#include "main/KnapSackSolver.h"
#include "main/algorithms/NemhauserUllmannSolver.h"

/**
 * Based on NemhauserUllmannSolver but the method betterPointExists is parallelized here.
 */

class NemhauserUllmannParallelSolver : public KnapSackSolver {
public:
	NemhauserUllmannParallelSolver(std::string inputFilename, std::string outputFilename, int nrOfExecutions = 1);

protected:

	void setUp();

	void tearDown();

	void solve();
		
private:

	void initPlotPointLists();
	void deletePlotPointLists();
	/**
	 * Copies PlotPoint 'from' to 'to' only if 'from's weight does not exceed the maximal allowed weight
	 * of our knapsack.
	 * Returns true if the item was actually copied, otherwise false.
	 */
	bool copyPlotPointIfItFitsIntoKnapsack(PlotPoint* from, PlotPoint* to);

	/*
	 * The PlotPoint lists represent the lists L_i, L'_i and L_{i+i}.
	 * The corresponding counter represent the amount of items in the
	 * list. The names are numbered because the roles (L_*) will switch.
	 * The items in the lists are ordered ascend by weight.
	 */

	PlotPoint* list0;
	int counter0;
	PlotPoint* list1;
	int counter1;
	PlotPoint* list2;
	int counter2;

	const double knapsackCapacity;

};

#endif /* MAIN_ALGORITHMS_NEMHAUSERULLMANNPARALLELSOLVER_H_ */
