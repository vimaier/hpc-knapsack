#include "main/algorithms/NemhauserUllmannParallelSolver.h"
#include <cmath>

NemhauserUllmannParallelSolver::NemhauserUllmannParallelSolver(std::string inputFilename, std::string outputFilename, int nrOfExecutions)
: KnapSackSolver(inputFilename, outputFilename, nrOfExecutions),
  list0(NULL),
  counter0(0),
  list1(NULL),
  counter1(0),
  list2(NULL),
  counter2(0),
  knapsackCapacity(knapSack.getCapacity())
{
	
}

void NemhauserUllmannParallelSolver::setUp() {
	initPlotPointLists();
}
int ESTIMATED_MAX_NUMBER_OF_POINTS = 100000;
void NemhauserUllmannParallelSolver::initPlotPointLists() {

	list0 = new PlotPoint[ESTIMATED_MAX_NUMBER_OF_POINTS];
	list1 = new PlotPoint[ESTIMATED_MAX_NUMBER_OF_POINTS];
	list2 = new PlotPoint[ESTIMATED_MAX_NUMBER_OF_POINTS];
	counter0= 0;
	counter1= 0;
	counter2= 0;

	for (int i=0; i < ESTIMATED_MAX_NUMBER_OF_POINTS ;++i) {
		list0[i].containingItems = new std::vector<KnapSackItem*>();
		list1[i].containingItems = new std::vector<KnapSackItem*>();
		list2[i].containingItems = new std::vector<KnapSackItem*>();
	}
}

void NemhauserUllmannParallelSolver::tearDown() {
	deletePlotPointLists();
}
void NemhauserUllmannParallelSolver::deletePlotPointLists() {
	for (int i=0; i < ESTIMATED_MAX_NUMBER_OF_POINTS ;++i) {
		delete list0[i].containingItems;
		delete list1[i].containingItems;
		delete list2[i].containingItems;
	}

	delete[] list0; list0 = NULL;
	delete[] list1; list1 = NULL;
	delete[] list2; list2 = NULL;
}


/**
 * Checks whether a better point than 'ptToCheck' exists in 'list'. 'counter' is the number
 * of points in 'list'.
 * A better point means a point which is located in the upper left quarter, so a point with
 * lower weight but higher worth.
 */
bool betterPointExists(const PlotPoint* ptToCheck, const PlotPoint* list, const int counter) {

	for (int i=0; i < counter ;++i) {
		if(list[i].weight > ptToCheck->weight)
			break;  // This is a sorted list (by weights) thus we do not need to check further items
		if(list[i].worth > ptToCheck->worth)
			// Here we have a point with lower weight but bigger worth
			return true;
	}

	return false;
}

const double NEG_VALUE_FOR_MARKING_NOT_OPTIMAL_POINTS = -1.0;

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
void markAllNonOptimalPoints(PlotPoint* list1, const int ctr1, PlotPoint* list2, const int ctr2) {

	assert(list1 != NULL && ctr1 > 0 && list2 != NULL && ctr2 > 0 );

	for (int i=0; i < ctr1 ;++i) {
		if (betterPointExists(&(list1[i]), list2, ctr2))
			list1[i].worth = NEG_VALUE_FOR_MARKING_NOT_OPTIMAL_POINTS;
	}

	for (int i=0; i < ctr2;++i) {
		if (betterPointExists(&(list2[i]), list1, ctr1))
			list2[i].worth = NEG_VALUE_FOR_MARKING_NOT_OPTIMAL_POINTS;
	}
}

void NemhauserUllmannParallelSolver::solve() {
	KnapSackItem* items = knapSack.getItems();
	const int numOfItems = knapSack.getNumOfItems();
	const double maxWeight = knapsackCapacity;

	PlotPoint* L_i = list0;
	int cL_i = 0;
	PlotPoint* LPrime_i = list1;  // L'_i
	int cLPrime_i = 0;
	PlotPoint* L_ip1 = list2;  // L_{i+1}
	int cL_ip1 = 0;

	// Insert first element
	L_i[cL_i].worth = 0;
	L_i[cL_i].weight = 0;
	cL_i++;

	// Adding KnapSackItems
	for(int i=0; i < numOfItems ;++i) {

		KnapSackItem* currentItem = &(items[i]);

		// Create L'_i: This list contains all points of L_i plus the currentItem
		for (int j=0; j < cL_i ;j++) {
			LPrime_i[j].worth = L_i[j].worth + currentItem->worth;
			LPrime_i[j].weight = L_i[j].weight + currentItem->weight;

			// Copy items and ...
			*(LPrime_i[j].containingItems) = *(L_i[j].containingItems);
			// ... add currentItem
			LPrime_i[j].containingItems->insert(LPrime_i[j].containingItems->end(), currentItem);

			cLPrime_i++;

		}

		markAllNonOptimalPoints(L_i, cL_i, LPrime_i, cLPrime_i);

		// Merge L_i and L'_i into L_{i+1}: Take only the points which are pareto-optimal.

		// Pointers point to the PltPoint which has to be processed next
		// Note, unlike cL* which is a counter ptr* points to the last element.
		int ptrL_i = 0;
		int ptrLPrime_i = 0;

		while (true) {
			// Basic idea: L_i and L'_i are sorted lists. It is sorted by ascending weights.
			// Know we copy elements into L_{i+1} that way that these elements will also be
			// sorted.

			// Catch special cases in which one of the lists is completely copied. Then we have to
			// copy the other list and we are done. This occurs as soon as one list is processed.
			if(ptrLPrime_i >= cLPrime_i) {
				// No elements in L'_i left. Copy remaining elements of L_i and leave the while(true)-loop
				while (ptrL_i < cL_i) {
					if (L_i[ptrL_i].worth >= 0)  // Then L_i[ptrL_i] is a pareto-optimal point
						if (copyPlotPointIfItFitsIntoKnapsack(&(L_i[ptrL_i]), &(L_ip1[cL_ip1])))
							cL_ip1++;

					ptrL_i++;
				}
				break;
			}
			if(ptrL_i >= cL_i) {
				// No elements in L_i left. Copy remaining elements of L'_i and leave the while(true)-loop
				while (ptrLPrime_i < cLPrime_i) {
					if (LPrime_i[ptrLPrime_i].worth >= 0)  // Then LPrime_i[ptrLPrime_i] is a pareto-optimal point
						if (copyPlotPointIfItFitsIntoKnapsack(&(LPrime_i[ptrLPrime_i]), &(L_ip1[cL_ip1])))
							cL_ip1++;

					ptrLPrime_i++;
				}
				break;
			}

			// Copy the element only we have not a better point in the other list
			// Note, through the construction of a list, say L_i, we cannot have 'better' points in this list.
			// A 'better' point can only occur in the other list, L'_i.

			// Choose the smallest element of L_i and L'_i
			PlotPoint* smallestWeightPoint;
			if (L_i[ptrL_i].weight < LPrime_i[ptrLPrime_i].weight) {
				smallestWeightPoint = &(L_i[ptrL_i]);
				ptrL_i++;
				if (smallestWeightPoint->worth < 0)
					continue; // No need to copy this non pareto-optimal point
			} else {
				smallestWeightPoint = &(LPrime_i[ptrLPrime_i]);
				ptrLPrime_i++;
				if (smallestWeightPoint->worth < 0)
					continue; // No need to copy this non pareto-optimal point
			}

			if (copyPlotPointIfItFitsIntoKnapsack(smallestWeightPoint, &(L_ip1[cL_ip1])))
				cL_ip1++;
		}

		// Switch the roles f the lists
		PlotPoint* tempList = L_i;
		L_i = L_ip1;
		cL_i = cL_ip1;
		L_ip1 = tempList;
		cL_ip1 = 0;  // 'Resets' the lists
		cLPrime_i = 0;

	} // END Adding KnapSackItems

	// The optimal solution is the last point in L_i
	std::vector<KnapSackItem*>* listOfBestItems = L_i[cL_i - 1].containingItems;

	// Just copy the list of items
	for(std::vector<KnapSackItem*>::iterator it = listOfBestItems->begin(); it != listOfBestItems->end(); ++it) {
		itemsOfSolution.insert(itemsOfSolution.end(), *(*it));
	}

}

bool NemhauserUllmannParallelSolver::copyPlotPointIfItFitsIntoKnapsack(PlotPoint* from, PlotPoint* to) {
	if (from->weight > knapsackCapacity)
		return false;
	to->worth = from->worth;
	to->weight = from->weight;

	*(to->containingItems) = *(from->containingItems);

	return true;
}
