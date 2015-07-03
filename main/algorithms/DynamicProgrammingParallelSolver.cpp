#include "main/algorithms/DynamicProgrammingParallelSolver.h"

const std::string DynamicProgrammingParallelSolver::NAME =  "Dynamic Programming (Parallel)";
const int DynamicProgrammingParallelSolver::PARALLEL_CAPACITY_THRESHOLD = 5000;
const int DynamicProgrammingParallelSolver::PARALLEL_ITEM_THRESHOLD = 5000;

DynamicProgrammingParallelSolver::DynamicProgrammingParallelSolver(std::string inputFilename, std::string outputFilename, int nrOfExecutions)
: KnapSackSolver(inputFilename, outputFilename, DynamicProgrammingParallelSolver::NAME, nrOfExecutions),
  //init rows and columns with +1 for zero row and zero column
  itemRows(knapSack.getNumOfItems() + 1), weightColumns(knapSack.getCapacity() + 1), table(new int*[itemRows]), integerItems(new IntegerItem[knapSack.getNumOfItems()])
{
	
}

DynamicProgrammingParallelSolver::~DynamicProgrammingParallelSolver(){
	// delete allocated table arrays
	for(int i=0; i<knapSack.getNumOfItems(); i++)
		delete[] table[i];
	delete[] table;
	
	// delete integerItems
	delete[] integerItems;
}

void DynamicProgrammingParallelSolver::setUp(){
	#pragma omp parallel if(itemRows > DynamicProgrammingParallelSolver::PARALLEL_ITEM_THRESHOLD)
	{
		// initialize result table structure.
		// each row represents the number of items available for the specific sub problem
		// each column represents the max capacity of the knapsack for the specific sub problem
		#pragma omp for
		for(int i=0; i<itemRows; i++){
			table[i] = new int[weightColumns];
			for(int j=0; j<weightColumns; j++)
				table[i][j] = 0;
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

void DynamicProgrammingParallelSolver::solve() {
	
	// instantiate threads only if it's worth it (enough columns).
	// we instantiate threads here, since we do not want to instantiate them again for every i of the outer loop
	#pragma omp parallel if(weightColumns > DynamicProgrammingParallelSolver::PARALLEL_CAPACITY_THRESHOLD)
	{
		// iterate through columns, representing the capacity coordinate of the subproblem
		for(int i=1; i < itemRows; i++){

			//items index must be i-1 because index 0 represents row 1, index 1 represents row 2 etc...
			int itemsIndex = i-1;
			int itemWeight = integerItems[itemsIndex].weight;
			int itemWorth = integerItems[itemsIndex].worth;

			// iterate through columns, representing the capacity coordinate of the subproblem
			// we can do this in parallel, since the entries of the same row are not depending on each other
			// we only want to do this in parallel, if there are more columns than PARALLEL_WEIGHT_THRESHOLD
			#pragma omp for
			for(int c=1; c < weightColumns; c++){

				//can not pick item, set to same worth of subproblem of previous item
				if(c < itemWeight){
					table[i][c] = table[i-1][c];

				//can pick item. choose if we should pick or not and set worth according to decision
				}else{
					int worthOfNotUsingItem = table[i-1][c];
					int worthOfUsingItem = itemWorth + table[i-1][c-itemWeight];
					table[i][c] = worthOfNotUsingItem < worthOfUsingItem ? worthOfUsingItem : worthOfNotUsingItem;
				}
			}


			/*
			THE FOLLOWING APPROACH HAS BEEN TRIED, BUT WAS NOT CHOSEN SINCE IT BECAME SLOWER

			// copying previous row ensures the correct worths for all entries where the item can not be picked
			std::copy(table[i-1], table[i-1] + weightColumns, table[i]);

			#pragma omp for
			for(int c=itemWeight; c < weightColumns; c++){
				int worthOfNotUsingItem = table[i-1][c];
				int worthOfUsingItem = itemWorth + table[i-1][c-itemWeight];
				if(worthOfNotUsingItem < worthOfUsingItem)
					table[i][c] = worthOfUsingItem;
			}
			*/

		}
	}

	backtrackItemsOfSolution();
}

void DynamicProgrammingParallelSolver::backtrackItemsOfSolution(){
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


void DynamicProgrammingParallelSolver::tearDown(){

}

void DynamicProgrammingParallelSolver::printTable(){
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
