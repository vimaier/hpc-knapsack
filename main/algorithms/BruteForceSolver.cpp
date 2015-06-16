#include "main/KnapSackSolver.h"
#include <cmath>

class BruteForceSolver : public KnapSackSolver {
public:
	BruteForceSolver(std::string inputFilename, std::string outputFilename, int nrOfExecutions = 1)
		: KnapSackSolver(inputFilename, outputFilename, nrOfExecutions)
	{
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
	virtual void solve() {
		KnapSackItem* items = knapSack.getItems();
		const int numOfItems = knapSack.getNumOfItems();
		const double maxWeight = knapSack.getCapacity();

		//init combination tracker with 0. used to update best combination after each iteration
		std::vector<char> currentCombination(numOfItems);
		for (int i = 0; i < numOfItems; i++){
			currentCombination[i] = 0;
		}

		//used to store current best combination
		std::vector<char> bestCombination;
		double bestWorth = 0;

		//iterate over the 2^n possible combinations. this is done by trying all bit combinations with n bits. (e.g. 00 -> 01 -> 10 -> 11)
		unsigned long long int numOfCombinations = pow(2, numOfItems);
		for (unsigned long long int i = 0; i < numOfCombinations; ++i) {
			double tmpWeight = 0;
			double tmpWorth = 0;

			//change the current bit combination (e.g. going from 000 to 001 or from 001 to 010 and so on ...)
			int j = numOfItems;
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

		//fill best combination into solution. add item for each set bit.
		for (int i = 0; i < numOfItems; i++){
			if (bestCombination[i] == 1){
				itemsOfSolution.insert(itemsOfSolution.end(), items[i]);
			}
		}
	}
};