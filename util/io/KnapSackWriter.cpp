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

	weight += item->weight;
	worth += item->worth;

	currPointerToFreeSpot++;
}

bool KnapSackWriter::writeToFile() {
	std::ofstream outFile;
	outFile.open (filename.c_str());

	if ( ! outFile.is_open())
		return false;

	outFile << "Kapazität;" << capacityOfKnapSack << "\n";

	for (int i=0; i < nrOfDistinctItems ;++i) {
		outFile << items[i].name << ";" << exemplarsOfItems[i] << "\n";
	}

	outFile << "Gesamtgewicht;" << weight << "\n";
	outFile << "Gesamtwert;" << worth;
	outFile.close();

	return true;
}
