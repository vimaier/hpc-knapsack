#include "main/algorithms/DynamicProgrammingSolver.h"

const std::string DynamicProgrammingSolver::NAME =  "Dynamic Programming (Sequential)";

DynamicProgrammingSolver::DynamicProgrammingSolver(std::string inputFilename, std::string outputFilename, int nrOfExecutions)
: KnapSackSolver(inputFilename, outputFilename, DynamicProgrammingSolver::NAME, nrOfExecutions),
  //init rows and columns with +1 for zero row and zero column
  itemRows(knapSack.getNumOfItems() + 1), weightColumns(knapSack.getCapacity() + 1), table(new int*[itemRows]), integerItems(new IntegerItem[knapSack.getNumOfItems()])
{
	// we can parallelize this since it is not being measured
	#pragma omp parallel if(itemRows > 5000)
	{
		#pragma omp for
		for(int i=0; i<itemRows; i++){
			table[i] = new int[weightColumns];
		}
	
		// fill integerItem list to prevent explicit casting during solve
		KnapSackItem* items = knapSack.getItems();
		#pragma omp for
		for(int i=0; i < knapSack.getNumOfItems() ;++i) {
			integerItems[i].name = items[i].name;
			integerItems[i].weight = (int)items[i].weight;
			integerItems[i].worth = (int)items[i].worth;
		}
	}
}

DynamicProgrammingSolver::~DynamicProgrammingSolver(){
	// delete allocated table arrays
	for(int i=0; i<knapSack.getNumOfItems(); i++)
		delete[] table[i];
	delete[] table;
	
	// delete integerItems
	delete[] integerItems;
}

// we can parallelize setup since it is not being measured
void DynamicProgrammingSolver::setUp(){
	// init table entries with zeros
	#pragma omp parallel for if(itemRows > 5000 || weightColumns > 5000) collapse(2)
	for(int i=0; i<itemRows; i++){
		for(int j=0; j<weightColumns; j++)
			table[i][j] = 0;
	}
}

void DynamicProgrammingSolver::solve() {
	
	// iterate through rows, representing the item coordinate of the subproblem
	for(int i=1; i < itemRows; i++){
		
		//items index must be i-1 because index 0 represents row 1, index 1 represents row 2 etc...
		int itemsIndex = i-1;
		int itemWeight = integerItems[itemsIndex].weight;
		int itemWorth = integerItems[itemsIndex].worth;
		
		// copying previous row ensures the correct worths for all entries where the item can not be picked
		std::copy(table[i-1], table[i-1] + weightColumns, table[i]);

		// for all columns where the item could be picked, check if it's worth it and if so, pick it
		for(int c=itemWeight; c < weightColumns; c++){
			int worthOfNotUsingItem = table[i-1][c];
			int worthOfUsingItem = itemWorth + table[i-1][c-itemWeight];
			if(worthOfNotUsingItem < worthOfUsingItem)
				table[i][c] = worthOfUsingItem;
		}
	}
	backtrackItemsOfSolution();
}

void DynamicProgrammingSolver::backtrackItemsOfSolution(){
	int currItem = knapSack.getNumOfItems();
	int currCapacity = knapSack.getCapacity();
	KnapSackItem* items = knapSack.getItems();

	while(currItem > 0){
		// compare optimal worths of current sub problems and add item if they differ
		const int a = table[currItem][currCapacity];
		const int b = table[currItem-1][currCapacity];
		if(a!=b){
			// items index must be currItem-1 because index 0 represents row 1, index 1 represents row 2 etc...
			int itemsIndex = currItem-1;

			// add item to solution and move item.weight columns to the left since the added item decreases capacity
			itemsOfSolution.insert(itemsOfSolution.end(), items[itemsIndex]);
			currCapacity -= integerItems[itemsIndex].weight;
		}

		//move one row up to the next item
		currItem--;
	}
}


void DynamicProgrammingSolver::tearDown(){

}

void DynamicProgrammingSolver::printTable(){
	std::printf(" \t|");
	for(int j=0; j<weightColumns; j++){
		std::printf("[c:%d]\t|", j);
	}
	std:printf("\n----------------------------------------------------\n");
	for(int i=0; i<itemRows; i++){
			std::printf("[i:%d]\t| ", i);
			for(int j=0; j<weightColumns; j++){
				std::printf("%d\t| ", table[i][j]);
			}
			std::printf("\n----------------------------------------------------\n");
	}
}
