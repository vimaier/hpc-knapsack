#include "main/algorithms/DynamicProgrammingLessSpaceSolver.h"
#include <cstring>
const std::string DynamicProgrammingLessSpaceSolver::NAME =  "Dynamic Programming Less Space (Sequential)";

DynamicProgrammingLessSpaceSolver::DynamicProgrammingLessSpaceSolver(std::string inputFilename, std::string outputFilename, int nrOfExecutions)
: KnapSackSolver(inputFilename, outputFilename, DynamicProgrammingLessSpaceSolver::NAME, nrOfExecutions),
  //init rows and columns with +1 for zero row and zero column
  itemRows(knapSack.getNumOfItems() + 1),
  weightColumns(knapSack.getCapacity() + 1),
  currentRow(new int[weightColumns]),
  integerItems(new IntegerItem[knapSack.getNumOfItems()])
{

}

DynamicProgrammingLessSpaceSolver::~DynamicProgrammingLessSpaceSolver(){
	delete[] currentRow;
	delete[] integerItems;
}

void DynamicProgrammingLessSpaceSolver::setUp(){
	for(int i=0; i<weightColumns; i++){
		currentRow[i] = 0;
	}

	// fill integerItem list to prevent explicit casting during solve
	KnapSackItem* items = knapSack.getItems();
	for(int i=0; i < knapSack.getNumOfItems() ;++i) {
		integerItems[i].name = items[i].name;
		integerItems[i].weight = (int)items[i].weight;
		integerItems[i].worth = (int)items[i].worth;
	}
}

void DynamicProgrammingLessSpaceSolver::solve() {
	
	// iterate through rows, representing the item coordinate of the subproblem
	for(int i=1; i < itemRows; i++){
		
		// items index must be i-1 because index 0 represents row 1, index 1 represents row 2 etc...
		int itemsIndex = i-1;
		int itemWeight = integerItems[itemsIndex].weight;
		int itemWorth = integerItems[itemsIndex].worth;
		
		// check if it's worth to pack the item for each column where the item fits in
		for(int c=weightColumns; c > itemWeight; c--){
			int worthOfPickingItem = currentRow[c - itemWeight] + itemWorth;
			if( worthOfPickingItem > currentRow[c])
				currentRow[c] = worthOfPickingItem;
		}
	}

	//solution now stands at the last position of the currentRow
}

void DynamicProgrammingLessSpaceSolver::tearDown(){
	int currItem = knapSack.getNumOfItems();
	int currCapacity = knapSack.getCapacity();
	KnapSackItem* items = knapSack.getItems();

	std::printf("!!! %d vs 2521441\n", currentRow[weightColumns]);
}

void DynamicProgrammingLessSpaceSolver::printTable(){

}
