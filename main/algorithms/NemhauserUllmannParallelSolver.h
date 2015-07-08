#ifndef MAIN_ALGORITHMS_NEMHAUSERULLMANNPARALLELSOLVER_H_
#define MAIN_ALGORITHMS_NEMHAUSERULLMANNPARALLELSOLVER_H_

#include <omp.h>
#include <string>
#include <vector>

#include "main/KnapSackSolver.h"
#include "main/algorithms/NemhauserUllmannSolver.h"

/**
 * Based on NemhauserUllmannSolver but the method betterPointExists is parallelized here.
 */
class NemhauserUllmannParallelSolver : public KnapSackSolver {
public:
	static const std::string NAME;

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

	/**
	 * Checks whether a better point than 'ptToCheck' exists in 'list'. 'counter' is the number
	 * of points in 'list'.
	 * A better point means a point which is located in the upper left quarter, so a point with
	 * lower weight but higher worth.
	 */
	bool betterPointExists(const PlotPoint* ptToCheck, const PlotPoint* list, const int counter);

	/**
	 * Find PlotPoints which are not pareto-optimal and 'mark' them. Marking means here set the
	 * worth to a negative value. Not pareto-optimal points are points which have other points in
	 * their the upper left quarter, so points with lower weights but higher worths.
	 *
	 * Note, for the points from L_i we only need to check for better points in the list L'_i since
	 * all points in the list are pareto-optimal. The same holds for points from L'_i accordingly.
	 *
	 * @param list1
	 * @param ctr1		The number of elements in list1
	 * @param list1
	 * @param ctr2		The number of elements in list2
	 */
	void markAllNonOptimalPoints(PlotPoint* list1, const int ctr1, PlotPoint* list2, const int ctr2);


	/*
	 * The PlotPoint lists represent the lists L_i, L'_i and L_{i+i}.
	 * The names are numbered because the roles (L_*) will switch.
	 * The items in the lists are ordered ascend by weight.
	 */
	PlotPoint* list0;
	PlotPoint* list1;
	PlotPoint* list2;

	const double knapsackCapacity;

	static const double NEG_VALUE_FOR_MARKING_NOT_OPTIMAL_POINTS;
	/**
	 * Used in "parallel for" pragma. If we have only a few items then it is faster to run it on a single
	 * thread. The threshold has to be determined.
	 */
	static const int THRESHOLD_OF_ITEMS_TO_PARALLELIZE;

};

#endif /* MAIN_ALGORITHMS_NEMHAUSERULLMANNPARALLELSOLVER_H_ */
