#include <cstdio>

#include "../io/KnapSackReader.h"
#include "../main/KnapSack.h"
#include "../util/MyMath.h"

/**
 * Tests the reading of the input.
 */


static const char* KNAPSACK_INPUT_FILE = "../hpc-knapsack/res/KnapSackItemsForUnittest.txt";
/* Content of text file
15.0 4 5
XXL blue Ox   02.0 2.00
gray mouse    01.0 2.00
big green box 12.0 4.00
yellow daisy  04.0 10.00
salmon mousse 01.0 1.00

 */

bool itemsAreEqual(const KnapSackItem* a, const KnapSackItem& b) {
	return a->name->compare(*(b.name)) == 0 && MyMath::almostEqual(a->weight, b.weight) && MyMath::almostEqual(a->worth, b.worth);
}

std::string* ITEM__NAME_1 = new std::string("XXL blue Ox");
const KnapSackItem TEST_ITEM_1 = {ITEM__NAME_1, 2.0, 2.0};

std::string* ITEM__NAME_2 = new std::string("gray mouse");
const KnapSackItem TEST_ITEM_2 = {ITEM__NAME_2, 1.0, 2.0};

std::string* ITEM__NAME_3 = new std::string("big green box");
const KnapSackItem TEST_ITEM_3 = {ITEM__NAME_3, 12.0, 4.0};

std::string* ITEM__NAME_4 = new std::string("yellow daisy");
const KnapSackItem TEST_ITEM_4 = {ITEM__NAME_4, 4.0, 10.0};

std::string* ITEM__NAME_5 = new std::string("salmon mousse");
const KnapSackItem TEST_ITEM_5 = {ITEM__NAME_5, 1.0, 1.0};

bool isInTestItems(const KnapSackItem* item) {
	if (	itemsAreEqual(item, TEST_ITEM_1) ||
			itemsAreEqual(item, TEST_ITEM_2) ||
			itemsAreEqual(item, TEST_ITEM_3) ||
			itemsAreEqual(item, TEST_ITEM_4) ||
			itemsAreEqual(item, TEST_ITEM_5)) {
		return true;
	}else
		return false;
}

int testReading() {
	KnapSack myKnapSack = KnapSackReader::readKnapSackFrom(KNAPSACK_INPUT_FILE);

	if (! MyMath::almostEqual(15.0, myKnapSack.getCapacity())) {
		std::printf("Wrong read capacity %f, should be 15.0", myKnapSack.getCapacity());
		return -1;
	}

	if (myKnapSack.getMaxNumPerItem() != 4) {
		std::printf("Wrong read exemplarsPerItem %d, should be 4", myKnapSack.getMaxNumPerItem());
		return -2;
	}

	if (myKnapSack.getNumOfItems() != 5) {
		std::printf("Wrong read numOfItems %d, should be 5", myKnapSack.getNumOfItems());
		return -3;
	}

	for (int i=0; i < myKnapSack.getNumOfItems() ;++i) {
		KnapSackItem* item = &(myKnapSack.getItems()[i]);
		if ( ! isInTestItems(item) ) {
			std::printf("Item(%s, %f, %f) is not in the test items.", item->name->c_str(), item->weight, item->worth);
			return -4;
		}
	}

	return 0;
}

int main(int argc, char* argv[]){
	return testReading();
}
