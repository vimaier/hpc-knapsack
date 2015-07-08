#ifndef MAIN_ALGORITHMS_NEMHAUSERULLMANNSOLVER_RLP_H_
#define MAIN_ALGORITHMS_NEMHAUSERULLMANNSOLVER_RLP_H_

#include <string>
#include <vector>

#include "main/KnapSackSolver.h"
// For PlotPoints
#include "main/algorithms/NemhauserUllmannSolver.h"



/**
 * This is an improvement of NemhauserUllmannSolver.
 * The suffix RLP means "remove lightest point".
 * The points which cannot reach the best point will be omitted.
 *
 */
class NemhauserUllmannSolverRLP : public KnapSackSolver {
public:
	static const std::string NAME;

	NemhauserUllmannSolverRLP(std::string inputFilename, std::string outputFilename, int nrOfExecutions = 1, bool sortInputItemsByWeights = true);

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

	/**
	 * Checks whether a better point than 'ptToCheck' exists in 'list'. 'counter' is the number
	 * of points in 'list'.
	 * A better point means a point which is located in the upper left quarter, so a point with
	 * lower weight but higher worth.
	 */
	bool betterPointExists(PlotPoint* ptToCheck, PlotPoint* list, int counter);

	/**
	 * Sort the list of input items in knapsack by weights descending. The first element at index 0
	 * will have the highest weight. The sort will take place on the list itself.
	 */
	void sortInputItems();

	/**
	 * Removes points which cannot contribute to the optimal solution.
	 * Such a point is a point for which the worth summed with
	 * remainingWorthOfInputItems is smaller than the worth of the point
	 * with the highest weight, which is the last item in list.
	 * The list will be modified in such a way that the items will be
	 * shift to the left until no hopeless points exist.
	 *
	 * @return the number of detected and removed points
	 */
	int removeHopelessPoints(PlotPoint* list, int counter, const int& remainingWorthOfInputItems);

	/*
	 * The PlotPoint lists represent the lists L_i, L'_i and L_{i+i}.
	 * The names are numbered because the roles (L_*) will switch.
	 * The items in the lists are ordered ascend by weight.
	 */

	PlotPoint* list0;
	PlotPoint* list1;
	PlotPoint* list2;

	const double knapsackCapacity;

	const bool sortInputItemsByWeights;

};

#endif /* MAIN_ALGORITHMS_NEMHAUSERULLMANNSOLVER_RLP_H_ */
