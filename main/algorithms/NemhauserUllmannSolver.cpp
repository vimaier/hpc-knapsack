#include "main/algorithms/NemhauserUllmannSolver.h"
#include <cmath>

NemhauserUllmannSolver::NemhauserUllmannSolver(std::string inputFilename, std::string outputFilename, int nrOfExecutions)
: KnapSackSolver(inputFilename, outputFilename, nrOfExecutions),
  list0(NULL),
  counter0(0),
  list1(NULL),
  counter1(0),
  list2(NULL),
  counter2(0)
{
	
}

void NemhauserUllmannSolver::setUp() {
	initPlotPointLists();
}
int ESTIMATED_MAX_NUMBER_OF_POINTS = 1000;
void NemhauserUllmannSolver::initPlotPointLists() {

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
 * Copies 'size' elements from list 'from' to 'to'. Only references will be copied.
 */
void copyItems(std::vector<KnapSackItem*>* from, std::vector<KnapSackItem*>* to) {
	to->clear();
	for(std::vector<KnapSackItem*>::iterator it = to->begin(); it != to->end(); ++it) {
		to->insert(to->end(), *it);
	}
}

void NemhauserUllmannSolver::solve() {
	KnapSackItem* items = knapSack.getItems();
	const int numOfItems = knapSack.getNumOfItems();
	const double maxWeight = knapSack.getCapacity();

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

			// Copy items and add currentItem
			copyItems( L_i[j].containingItems, LPrime_i[j].containingItems);
			LPrime_i[j].containingItems->insert(LPrime_i[j].containingItems->end(), currentItem);

			cLPrime_i++;
		}

		// Merge L_i and L'_i: Take only the points which have no points in the upper left quarter
		// within the other list.


	} // END Adding KnapSackItems
}


