#ifndef MAIN_ALGORITHMS_NEMHAUSERULLMANNRLPPARALLELSOLVER_H_
#define MAIN_ALGORITHMS_NEMHAUSERULLMANNRLPPARALLELSOLVER_H_

#include <string>
#include <vector>
#include <cmath>
#include <omp.h>

#include "main/KnapSackSolver.h"
// For PlotPoints
#include "main/algorithms/NemhauserUllmannSolver.h"



/**
 * This is parallelized version of NemhauserUllmannRLPSolver.
 *
 */
class NemhauserUllmannRLPParallelSolver : public KnapSackSolver {
public:
	static const std::string NAME;

	NemhauserUllmannRLPParallelSolver(std::string inputFilename, std::string outputFilename, int nrOfExecutions = 1, bool sortInputItemsByWeights = true);

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

	const bool sortInputItemsByWeights;

	static const double NEG_VALUE_FOR_MARKING_NOT_OPTIMAL_POINTS;
	/**
	 * Used in "parallel for" pragma. If we have only a few items then it is faster to run it on a single
	 * thread. It depends also an the number of threads actually.
	 * For simplicity we will just take a value which delivers the best runtimes tested on a single computer
	 * with 4 cores. The best runtimes delivered 100 (from 1, 100, 500 and 1000)
	 */
	static const int THRESHOLD_OF_ITEMS_TO_PARALLELIZE;

};

#endif /* MAIN_ALGORITHMS_NEMHAUSERULLMANNRLPPARALLELSOLVER_H_ */
