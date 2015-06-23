#ifndef MAIN_ALGORITHMS_NEMHAUSERULLMANNSOLVER_H_
#define MAIN_ALGORITHMS_NEMHAUSERULLMANNSOLVER_H_

#include <string>
#include <vector>

#include "main/KnapSackSolver.h"

/**
 * A PlotPoint represents a point in the worth vs. weight plot.
 * Therefore we need the worth, the need and the containing items.
 */
struct PlotPoint {
	double worth;
	double weight;
	std::vector<KnapSackItem*>* containingItems;
};

/**
 * The NemhauserUllmannSolver extends the KnapSackSolver class and
 * implements the abstract method solve().
 *
 * This algorithm is a sequential algorithm. The idea of this algorithm is
 * based on the plot worth vs. weight. Here are only the most upper points
 * interesting (Pareto-optimal). During the construction we can omit a lot of points to check.
 * For more information see http://www-i1.informatik.rwth-aachen.de/~algorithmus/algo15.php
 */
class NemhauserUllmannSolver : public KnapSackSolver {
public:
	NemhauserUllmannSolver(std::string inputFilename, std::string outputFilename, int nrOfExecutions = 1);

protected:

	void setUp();

	void tearDown();

	void solve();
		
private:

	void initPlotPointLists();
	void deletePlotPointLists();

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

};

#endif /* MAIN_ALGORITHMS_NEMHAUSERULLMANNSOLVER_H_ */
