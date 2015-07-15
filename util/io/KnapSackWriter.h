#ifndef IO_KNAPSACKWRITER_H_
#define IO_KNAPSACKWRITER_H_

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <assert.h>

#include "main/KnapSack.h"

/**
 * Helper class used to create an output file representing the solution of a solved
 * knapsack problem in a specific format.
 *
 * Example output file:
 *
 * ------------------------------
	Capacity;400.0
	item24;5
	item69;2
	Total weight;345.00
	Total worth;333.00
 * ------------------------------
 *
 * Meaning:
 * - The max capacity was 400.0
 * - item24 is included 5 times in the solution
 * - item69 is included 2 times in the solution
 * - The solution takes a weight of 345.00
 * - The solution is worth 333.00
 */
class KnapSackWriter {
public:
	KnapSackWriter(std::string filename, int nrOfDistinctItems, double capacityOfKnapSack);
	virtual ~KnapSackWriter();

	/**
	 * Adds an entry to the item list to be written to file.
	 * The exemplarsOfThisItem parameter specifies how often this item is included in the solution.
	 */
	void addItem(const KnapSackItem* item, int exemplarsOfThisItem);

	/**
	 * Writes the knapsackwriter object to the specified output file.
	 */
	bool writeToFile();

private:
	std::string filename;
	double capacityOfKnapSack;
	double weight;
	double worth;
	int nrOfDistinctItems;
	KnapSackItem* items;
	int* exemplarsOfItems;
	int currPointerToFreeSpot;
};

#endif /* IO_KNAPSACKWRITER_H_ */
