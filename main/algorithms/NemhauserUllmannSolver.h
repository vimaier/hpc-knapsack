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
 * based on the plot worth vs. weight. Every possible combination represents a point in the plot.
 * For example a point could be consist of item1, item2 and item3. The point would be located at <br/>
 *  x = w1 + w2 + w3, where w* is an abbreviation for weight of item* <br/>
 *  y = p1 + p2 + p3, where p* is an abbreviation for profit (==worth) of item*<br/>
 * In this plot only the most upper points are interesting. They are called (Pareto-optimal).
 * During the construction we can omit a lot of points to check.<br/>
 * The rough algorithm is (implemented in solve-function):
 *
 *   L_0 := [(0,0)]  // A list with pareto optimal points. In the beginning only the point (0,0) is available <br/>
 *   foreach item x in input do: <br/>
 *      1. Copy new items in L'_i<br/>
 *      	L'_i := L_i + x  // This means create a new list L'_i with points equal to the list L_i and add to all points the current item x (weight and worth)
 *      2. Remove not pareto-optimal points in lists L_i and L'_i
 *      3. Merge both list sorted<br/>
 *      	L_{i+1} := sort_with_ascending_weight( L_i, L'_i )<br/>
 *
 *   After adding of all items the optimal solution is at the end of list L_n where n is the number of input items.
 *
 * For more information see http://www-i1.informatik.rwth-aachen.de/~algorithmus/algo15.php
 */
class NemhauserUllmannSolver : public KnapSackSolver {
public:
	static const std::string NAME;

	NemhauserUllmannSolver(std::string inputFilename, std::string outputFilename, int nrOfExecutions = 1);

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
	 * The names are numbered because the roles (L_*) will switch.
	 * The items in the lists are ordered ascend by weight.
	 */
	PlotPoint* list0;
	PlotPoint* list1;
	PlotPoint* list2;

	const double knapsackCapacity;

};

#endif /* MAIN_ALGORITHMS_NEMHAUSERULLMANNSOLVER_H_ */
