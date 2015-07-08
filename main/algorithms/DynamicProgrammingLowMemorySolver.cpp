#include "main/algorithms/DynamicProgrammingLowMemorySolver.h"
#include <cstring>
const std::string DynamicProgrammingLowMemorySolver::NAME =  "Dynamic Programming Low Memory (Sequential)";

DynamicProgrammingLowMemorySolver::DynamicProgrammingLowMemorySolver(std::string inputFilename, std::string outputFilename, int nrOfExecutions)
: KnapSackSolver(inputFilename, outputFilename, DynamicProgrammingLowMemorySolver::NAME, nrOfExecutions),
  integerItems(new IntegerItem[knapSack.getNumOfItems()]),
  integerItemsOfSolution()
{
	// fill integerItem list to prevent explicit casting during solve
	KnapSackItem* items = knapSack.getItems();
	int numOfItems = knapSack.getNumOfItems();
	#pragma omp parallel for if(numOfItems > 5000)
	for(int i=0; i < numOfItems; ++i) {
		integerItems[i].name = items[i].name;
		integerItems[i].weight = (int)items[i].weight;
		integerItems[i].worth = (int)items[i].worth;
	}
}

DynamicProgrammingLowMemorySolver::~DynamicProgrammingLowMemorySolver(){
	delete[] integerItems;
}

// we can parallelize this, since this is not part of the measurement
void DynamicProgrammingLowMemorySolver::setUp(){
	// nothing to do here. integerItemsOfSolution is getting cleared in tearDown
}

void DynamicProgrammingLowMemorySolver::solve() {
	int cap = knapSack.getCapacity();
	int* solutionRow = new int[cap+1];
	int solution = solveProblem(integerItems, knapSack.getNumOfItems(), solutionRow, cap+1, cap)[cap];
	delete[] solutionRow;

	determineItemsOfSolutionRecursively(integerItems, knapSack.getNumOfItems(), knapSack.getCapacity(), solution);
}

int* DynamicProgrammingLowMemorySolver::solveProblem(IntegerItem* items, int itemsLength, int* solutionRow, int rowLength, int capacity){
	assert(rowLength > capacity);

	for(int i=0; i<rowLength; i++){
		solutionRow[i] = 0;
	}

	// iterate through rows, representing the item coordinate of the subproblem
	for(int i=0; i < itemsLength; i++){

		// items index must be i-1 because index 0 represents row 1, index 1 represents row 2 etc...
		int itemWeight = items[i].weight;
		int itemWorth = items[i].worth;

		// check if it's worth to pack the item for each column where the item fits in
		for(int c=capacity; c >= itemWeight; c--){
			int worthOfPickingItem = solutionRow[c - itemWeight] + itemWorth;
			if( worthOfPickingItem > solutionRow[c])
				solutionRow[c] = worthOfPickingItem;
		}
	}

	//solution now stands at the last position of the currentRow (currentRow[capacity-1])
	return solutionRow;
}

void DynamicProgrammingLowMemorySolver::tearDown(){

	// convert collected integeritems to knapsack items
	for(int i=0; i<integerItemsOfSolution.size(); i++){
		IntegerItem itemToAdd = integerItemsOfSolution[i];

		KnapSackItem ksi;
		ksi.name = itemToAdd.name;
		ksi.weight = itemToAdd.weight;
		ksi.worth = itemToAdd.worth;

		// pack item
		itemsOfSolution.insert(itemsOfSolution.end(), ksi);
	}

	integerItemsOfSolution.clear();
}

void DynamicProgrammingLowMemorySolver::determineItemsOfSolutionRecursively(IntegerItem* items, int numOfItems, int capacity, int solution){
	if(capacity <= 0)
		return;

	// split itemset into two sub sets
	int numOfItems1 = numOfItems/2;
	int numOfItems2 = numOfItems - numOfItems1;
	IntegerItem items1[numOfItems1];
	IntegerItem items2[numOfItems2];
	std::copy(items, items + numOfItems1, items1);
	std::copy(items + numOfItems1, items + numOfItems1 + numOfItems2, items2);

	// Find C1 and C2 with C1+C2 = C such that solve(items1,C) + solve(items2,C) = solve(items,C).
	int rowLength = capacity+1;
	int* subSolutionRow1 = new int[rowLength];
	subSolutionRow1 = solveProblem(items1, numOfItems1, subSolutionRow1, rowLength, capacity);
	int* subSolutionRow2 = new int[rowLength];
	subSolutionRow2 = solveProblem(items2, numOfItems2, subSolutionRow2, rowLength, capacity);
	int c1=0;
	int c2=capacity;
	int subSolution1 = 0;
	int subSolution2 = 0;
	for(; c1<rowLength; c1++, c2--){
		subSolution1 = subSolutionRow1[c1];
		subSolution2 = subSolutionRow2[c2];
		if(subSolution1 + subSolution2 == solution){
			break;
		}
	}
	delete[] subSolutionRow1;
	delete[] subSolutionRow2;
	assert(subSolution1 + subSolution2 == solution);

	// conquer -> check if subsolution consists of only one item and has a worth, then pack it. else go deeper into recursion
	if(numOfItems1 == 1 && subSolution1 > 0)
		integerItemsOfSolution.insert(integerItemsOfSolution.end(), items1[0]);
	else if(numOfItems1 > 1)
		determineItemsOfSolutionRecursively(items1, numOfItems1, c1, subSolution1);

	if(numOfItems2 == 1 && subSolution2 > 0)
		integerItemsOfSolution.insert(integerItemsOfSolution.end(), items2[0]);
	else if(numOfItems2 > 1)
		determineItemsOfSolutionRecursively(items2, numOfItems2, c2, subSolution2);
}


