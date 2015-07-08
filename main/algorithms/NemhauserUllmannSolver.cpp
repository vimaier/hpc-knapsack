#include "main/algorithms/NemhauserUllmannSolver.h"
#include <cmath>

const std::string NemhauserUllmannSolver::NAME =  "Algorithm of Nemhauser and Ullmann (Sequential)";

NemhauserUllmannSolver::NemhauserUllmannSolver(std::string inputFilename, std::string outputFilename, int nrOfExecutions)
: KnapSackSolver(inputFilename, outputFilename, NemhauserUllmannSolver::NAME, nrOfExecutions),
  list0(NULL),
  list1(NULL),
  list2(NULL),
  knapsackCapacity(knapSack.getCapacity())
{
	
}

void NemhauserUllmannSolver::setUp() {
	initPlotPointLists();
}

/**
 * This represents the number of maximal pareto optimal points which we can hold.
 * It is difficult to guess the number of maximal pareto optimal points since it
 * depends on the input items.
 * We simply take here 100000 points due to observed previous runs of this algorithm
 * One PlotPoint has the size of 24 bytes. The size of a list is
 * 100000 * 24 bytes = 2400000 bytes = 2343.75 kb = 2.29mb
 * We have three lists, so we need approximately 6.9mb for the lists.
 * Space should not be the bottleneck of this algorithm.
 */
int ESTIMATED_MAX_NUMBER_OF_POINTS = 100000;

void NemhauserUllmannSolver::initPlotPointLists() {

	list0 = new PlotPoint[ESTIMATED_MAX_NUMBER_OF_POINTS];
	list1 = new PlotPoint[ESTIMATED_MAX_NUMBER_OF_POINTS];
	list2 = new PlotPoint[ESTIMATED_MAX_NUMBER_OF_POINTS];

	for (int i=0; i < ESTIMATED_MAX_NUMBER_OF_POINTS ;++i) {
		list0[i].containingItems = new std::vector<KnapSackItem*>();
		list1[i].containingItems = new std::vector<KnapSackItem*>();
		list2[i].containingItems = new std::vector<KnapSackItem*>();
	}
}

void NemhauserUllmannSolver::tearDown() {
	deletePlotPointLists();
}
void NemhauserUllmannSolver::deletePlotPointLists() {
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
bool betterPointExists(PlotPoint* ptToCheck, PlotPoint* list, int counter) {

	for (int i=0; i < counter ;++i) {
		if(list[i].weight > ptToCheck->weight)
			break;  // This is a sorted list (by weights) thus we do not need to check further items
		if(list[i].worth > ptToCheck->worth)
			// Here we have a point with lower weight but bigger worth
			return true;
	}

	return false;
}

void NemhauserUllmannSolver::solve() {
	KnapSackItem* items = knapSack.getItems();
	const int numOfItems = knapSack.getNumOfItems();
	const double maxWeight = knapsackCapacity;

	PlotPoint* L_i = list0;
	int cL_i = 0;  // counts the items in array L_i
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

		// Merge L_i and L'_i into L_{i+1}: Take only the points which have no points in the upper left quarter
		// within the other list.

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
					if (! betterPointExists(&(L_i[ptrL_i]), LPrime_i, cLPrime_i))
						if (copyPlotPointIfItFitsIntoKnapsack(&(L_i[ptrL_i]), &(L_ip1[cL_ip1])))
							cL_ip1++;

					ptrL_i++;
				}
				break;
			}
			if(ptrL_i >= cL_i) {
				// No elements in L_i left. Copy remaining elements of L'_i and leave the while(true)-loop
				while (ptrLPrime_i < cLPrime_i) {
					if (! betterPointExists(&(LPrime_i[ptrLPrime_i]), L_i, cL_i))
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
				if (betterPointExists(smallestWeightPoint, LPrime_i, cLPrime_i))
					continue; // No need to copy this point
			} else {
				smallestWeightPoint = &(LPrime_i[ptrLPrime_i]);
				ptrLPrime_i++;
				if (betterPointExists(smallestWeightPoint, L_i, cL_i))
					continue; // No need to copy this point
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

bool NemhauserUllmannSolver::copyPlotPointIfItFitsIntoKnapsack(PlotPoint* from, PlotPoint* to) {
	if (from->weight > knapsackCapacity)
		return false;
	to->worth = from->worth;
	to->weight = from->weight;

	*(to->containingItems) = *(from->containingItems);

	return true;
}
