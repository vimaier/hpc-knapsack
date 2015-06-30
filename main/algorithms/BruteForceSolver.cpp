#include "main/algorithms/BruteForceSolver.h"
#include <cmath>

const std::string BruteForceSolver::NAME =  "Brute Force (Sequential)";

BruteForceSolver::BruteForceSolver(std::string inputFilename, std::string outputFilename, int nrOfExecutions)
: KnapSackSolver(inputFilename, outputFilename, BruteForceSolver::NAME, nrOfExecutions), currentCombination(knapSack.getNumOfItems()), bestCombination(), numOfCombinations(pow(2, knapSack.getNumOfItems()))
{
	
}

void BruteForceSolver::setUp(){

	//init bit pattern with 0
	for (int i = 0; i < knapSack.getNumOfItems(); i++){
		currentCombination[i] = 0;
	}

	bestCombination.clear();
}

/**
	* Solves the KnapSack-Problem with a brute force method by trying each possible combination of
	* KnapSack-objects. The combinations are iterated by bit patterns.
	* If knapsack has n=3 items, the iteration would look like this:
	* 000 -> 001 -> 010 -> 011 -> 100 -> 101 -> 110 -> 111.
	* Each combination is checked agains the constraints of the knapsack.
	* If a combination reaches the current best worth and if its weight is below or equal to the knapsack capacity,
	* it becomes the best current combination. After the last combination has been checked, the best overall combination
	* has been determined.
	*/
void BruteForceSolver::solve() {
	KnapSackItem* items = knapSack.getItems();
	const int numOfItems = knapSack.getNumOfItems();
	const double maxWeight = knapSack.getCapacity();

	//Variable to track the worth of the current bestCombination. Used to determine if the currentCombination is better than the current bestCombination
	double bestWorth = 0;

	//iterate over the 2^n possible combinations. this is done by trying all bit combinations with n bits. (e.g. 00 -> 01 -> 10 -> 11)
	for (unsigned long long int i = 0; i < numOfCombinations; ++i) {
		double tmpWeight = 0;
		double tmpWorth = 0;

		//change the current bit combination (e.g. going from 000 to 001 or from 001 to 010 and so on ...)
		int j = numOfItems-1;
		while (currentCombination[j] != 0 && j > 0){
			currentCombination[j] = 0;
			j--;
		}
		currentCombination[j] = 1;

		//add weight and worth of all items marked with bit = 1
		for (int k = 0; k < numOfItems; k++){
			if (currentCombination[k] == 1){
				tmpWeight += items[k].weight;
				tmpWorth += items[k].worth;
			}
		}

		//check constraints for current combination and update
		if (tmpWorth > bestWorth && tmpWeight <= maxWeight){
			bestWorth = tmpWorth;
			bestCombination = currentCombination;
		}
	}
}

void BruteForceSolver::tearDown(){
	KnapSackItem* items = knapSack.getItems();
	const int numOfItems = knapSack.getNumOfItems();

	//fill best combination into solution. add item for each set bit.
	for (int i = 0; i < numOfItems; i++){
		if (bestCombination[i] == 1){
			itemsOfSolution.insert(itemsOfSolution.end(), items[i]);
		}
	}
}
