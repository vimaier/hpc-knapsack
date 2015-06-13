#ifndef IO_KNAPSACKWRITER_H_
#define IO_KNAPSACKWRITER_H_

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <assert.h>

#include "main/KnapSack.h"

class KnapSackWriter {
public:
	KnapSackWriter(std::string filename, int nrOfDistinctItems, double capacityOfKnapSack);
	virtual ~KnapSackWriter();

	void addItem(const KnapSackItem* item, int exemplarsOfThisItem);
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
