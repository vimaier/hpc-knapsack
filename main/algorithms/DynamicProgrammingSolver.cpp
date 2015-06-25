#include "main/algorithms/DynamicProgrammingSolver.h"
#include <cmath>

DynamicProgrammingSolver::DynamicProgrammingSolver(std::string inputFilename, std::string outputFilename, int nrOfExecutions)
: KnapSackSolver(inputFilename, outputFilename, nrOfExecutions), rows(knapSack.getNumOfItems() + 1), cols(knapSack.getCapacity() + 1) // +1 for zero row and zero col
{
	// init result table with zeros
	table = new double*[rows];
	for(int i=0; i<rows; i++){
		table[i] = new double[cols];
		for(int j=0; j<cols; j++)
			table[i][j] = 0.0;
	}
}

DynamicProgrammingSolver::~DynamicProgrammingSolver(){
	for(int i=0; i<knapSack.getNumOfItems(); i++)
		delete[] table[i];
	delete[] table;
}

void DynamicProgrammingSolver::setUp(){

}

void DynamicProgrammingSolver::solve() {
	KnapSackItem* items = knapSack.getItems();

	// fill result table. we start at [1,1] because values of row zero and values of column zero stay 0.0 (0 capacity = 0 items)
	for(int i=1; i<rows; i++){
		//items index must be i-1 because index 0 represents row 1, index 1 represents row 2 etc...
		int itemsIndex = i-1;
		for(int j=1; j<cols; j++){
			if(j < items[itemsIndex].weight){ //can not pick item
				table[i,j] = table[i-1, j];
			}else{ //can pick item. choose if we should pick or not
				double worthOfNotUsingItem = table[i-1][j];
				double worthOfUsingItem = items[itemsIndex].worth + table[i-1][j-(int)items[itemsIndex].weight];
				table[i][j] = worthOfNotUsingItem < worthOfUsingItem ? worthOfUsingItem : worthOfNotUsingItem;
			}
		}
	}

	//print table
	printTable();

	// determine included items
	int n = rows-1;
	int c = cols-1;
	while(c > 0){
		const double a = table[n][c];
		const double b = table[n-1][c];

		// item is included
		if(!MyMath::almostEqual(a, b)){

			itemsOfSolution.insert(itemsOfSolution.end(), items[n]);
			//move column left
			c-=items[n-1].weight;
		}
		// else item not included in optimal solution

		//move row up
		n--;
	}
}

void DynamicProgrammingSolver::tearDown(){
	for(int i=0; i<itemsOfSolution.size(); i++){
		std::printf("item: %s\n", itemsOfSolution[i].name->c_str());
	}
}

void DynamicProgrammingSolver::printTable(){
	std::printf(" \t|");
	for(int j=0; j<cols; j++){
		std::printf("[w:%d]\t|", j);
	}
	std:printf("\n------------------------------------------------------------------------------------------------------------------\n");
	for(int i=0; i<rows; i++){
			std::printf("[i:%d]\t| ", i);
			for(int j=0; j<cols; j++){
				std::printf("%.1f\t| ", table[i][j]);
			}
			std::printf("\n------------------------------------------------------------------------------------------------------------------\n");
	}
}
