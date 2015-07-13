#include "KnapSackWriter.h"



KnapSackWriter::KnapSackWriter(std::string filename, int nrOfDistinctItems,	double capacityOfKnapSack):
	filename(filename),
	capacityOfKnapSack(capacityOfKnapSack),
	weight(0.0),
	worth(0.0),
	nrOfDistinctItems(nrOfDistinctItems),
	items(new KnapSackItem[nrOfDistinctItems]),
	exemplarsOfItems(new int[nrOfDistinctItems]),
	currPointerToFreeSpot(0) {
}

KnapSackWriter::~KnapSackWriter() {
	delete[] items;
}

void KnapSackWriter::addItem(const KnapSackItem* item, int exemplarsOfThisItem) {
	assert(item != NULL);
	assert(exemplarsOfThisItem > 0);
	assert(0 <= currPointerToFreeSpot && currPointerToFreeSpot < nrOfDistinctItems);

	items[currPointerToFreeSpot].name = new std::string(item->name->c_str());
	items[currPointerToFreeSpot].weight = item->weight;
	items[currPointerToFreeSpot].worth = item->worth;
	exemplarsOfItems[currPointerToFreeSpot] = exemplarsOfThisItem;

	
	weight += item->weight * exemplarsOfThisItem;
	worth += item->worth * exemplarsOfThisItem;

	currPointerToFreeSpot++;
}

bool KnapSackWriter::writeToFile() {
	FILE* fp;
	fp = fopen(filename.c_str(), "w");

	if (fp == NULL)
		return false;

	fprintf(fp, "Capacity;%.1f\n", capacityOfKnapSack);
	

	for (int i=0; i < nrOfDistinctItems ;++i) {
		fprintf(fp, "%s;%d\n", items[i].name->c_str(), exemplarsOfItems[i]);
	}

	fprintf(fp, "Total weight;%.2f\n", weight);
	fprintf(fp, "Total worth;%.2f", worth);

	fclose(fp);

	return true;
}
