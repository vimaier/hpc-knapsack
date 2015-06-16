/**
 * Tests the reading of the input.
 */
 #include <cstdio>

#include "../io/KnapSackReader.h"
#include "../main/KnapSack.h"
#include "../util/MyMath.h"
#include "testData.h"


bool itemsAreEqual(const KnapSackItem* a, const KnapSackItem& b) {
	return a->name->compare(*(b.name)) == 0 && MyMath::almostEqual(a->weight, b.weight) && MyMath::almostEqual(a->worth, b.worth);
}

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
