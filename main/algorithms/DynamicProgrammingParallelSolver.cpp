#include "main/algorithms/DynamicProgrammingParallelSolver.h"

const std::string DynamicProgrammingParallelSolver::NAME =  "Dynamic Programming (Parallel)";

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
	// initialize result table structure.
	// each row represents the number of items available for the specific sub problem
	// each column represents the max capacity of the knapsack for the specific sub problem
	for(int i=0; i<itemRows; i++){
		table[i] = new int[weightColumns];
		for(int j=0; j<weightColumns; j++)
			table[i][j] = 0;
	}

	// fill integerItem list to prevent explicit casting during solve
	KnapSackItem* items = knapSack.getItems();
	for(int i=0; i < knapSack.getNumOfItems() ;++i) {
		integerItems[i].name = items[i].name;
		integerItems[i].weight = (int)items[i].weight;
		integerItems[i].worth = (int)items[i].worth;
	}
}

/**
 * Solves every subproblem of the given knapsack problem including the knapsack problem itself.
 * Each entry of the table represents the best worth achievable by the specific sub problem.
 * The problems are being solved in a bottom-up manner.
 * We start by solving the lowest subproblem [1,1] and end up solving the main problem at [numOfItems, maxCapacity].
 *
 * Why don't we start at [0,0] ? Because worths of row[0] and worths of column[0] stay 0.
 * This is because a knapsack with 0 capacity can not have any items and a knapsack with 0 items can not weigh anything (0 capacity = 0 items).
 * Thus the best worths of our base-problems (the sub problems at [i,0] for all [0 <= i < cols] and the sub problems at [0, c] for all [0 <= c < rows])
 * stay 0.
 *
 * In this version the independent elements in each row are calculated in parallel.
 * Meaning: each row i has c elements where i = index of itemRows and c = index of weightColumns.
 * All c elements can be calculated in parallel, since they are independent from each other.
 * We can not calculate several rows or columns in parallel, since they are dependant from each other.
 */
void DynamicProgrammingParallelSolver::solve() {
	
	// instantiate threads only if it's worth it (enough columns).
	// we instantiate threads here, since we do not want to instantiate them again for every i of the outer loop
	#pragma omp parallel if(weightColumns > PARALLEL_CAPACITY_THRESHOLD)
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

		}
	}

	//printTable();
}

/**
 * Determines items included in the optimal solution by
 * traversing the populated result table.
 * This happens top-down, meaning we start at the most lower right table entry.
 * This entry contains the optimal worths for the main knapsack problem.
 * By comparing the worths of specific sub problems we can determine if a
 * specific item is part of the optimal solution or not.
 *
 * If the optimal worths of entries of two rows
 * table[currItem][currWeight] and table[currItem-1][currWeight]
 * differ from each other, the item of the current row must be part of the solution.
 * We add the item and decrease the capacity by the weight of that item.
 * Thus, new sub problems with the new capacity will be checked until we checked all items.
 */
void DynamicProgrammingParallelSolver::tearDown(){
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

void DynamicProgrammingParallelSolver::printTable(){
	// +1 for zero row and zero column
	const int rows = knapSack.getNumOfItems() + 1;
	const int cols = knapSack.getCapacity() + 1;

	std::printf(" \t|");
	for(int j=0; j<cols; j++){
		std::printf("[c:%d]\t|", j);
	}
	std:printf("\n----------------------------------------------------\n");
	for(int i=0; i<rows; i++){
			std::printf("[i:%d]\t| ", i);
			for(int j=0; j<cols; j++){
				std::printf("%d\t| ", table[i][j]);
			}
			std::printf("\n----------------------------------------------------\n");
	}
}
