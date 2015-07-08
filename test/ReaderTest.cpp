#include <cstdio>

#include "util/io/KnapSackReader.h"
#include "main/KnapSack.h"
#include "util/MyMath.h"
#include "TestData.h"

/**
 * Used to check whether the given items have the same properties
 */
bool itemsAreEqual(const KnapSackItem* a, const KnapSackItem& b) {
	return a->name->compare(*(b.name)) == 0 && MyMath::almostEqual(a->weight, b.weight) && MyMath::almostEqual(a->worth, b.worth);
}

/**
 * Used to check whether the given (read) item belongs to the expected test items
 */
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

/**
 * Tests whether the reading of the default input file works correctly.
 * Returns 0 if test succeeds.
 * Returns -1 if read capacity mismatches expected capacity
 * Returns -3 if read numofitems mismatches expected numofitems
 * Returns -4 if a read item is not part of the expected test items
 */
int testReadingInputFile() {
	std::printf("\nTesting input file: %s\n", KNAPSACK_INPUT_FILE);
	KnapSack myKnapSack = KnapSackReader::readKnapSackFrom(KNAPSACK_INPUT_FILE);

	if (! MyMath::almostEqual(15.0, myKnapSack.getCapacity())) {
		std::fprintf(stderr, "Wrong read capacity %f, should be 15.0\n", myKnapSack.getCapacity());
		return -1;
	}

	if (myKnapSack.getNumOfItems() != 5*4) {
		std::fprintf(stderr, "Wrong read numOfItems %d, should be 5\n", myKnapSack.getNumOfItems());
		return -3;
	}

	for (int i=0; i < myKnapSack.getNumOfItems() ;++i) {
		KnapSackItem* item = &(myKnapSack.getItems()[i]);
		if ( ! isInTestItems(item) ) {
			std::fprintf(stderr, "Item(%s, %f, %f) is not in the test items.\n", item->name->c_str(), item->weight, item->worth);
			return -4;
		}
	}

	return 0;
}

/**
 * Tests whether the reading of the third first file example works correctly.
 * Returns 0 if test succeeds.
 * Returns -1 if read capacity mismatches expected capacity
 * Returns -3 if read numofitems mismatches expected numofitems
 * Returns -4 if a read item is not part of the expected test items
 */
int testReadingInputFileFirstExample() {
	std::printf("\nTesting input file: %s\n", KNAPSACK_INPUT_FILE_FIRST_EXAMPLE);
	KnapSack myKnapSack = KnapSackReader::readKnapSackFrom(KNAPSACK_INPUT_FILE_FIRST_EXAMPLE);

	if (! MyMath::almostEqual(15.0, myKnapSack.getCapacity())) {
		std::fprintf(stderr, "Wrong read capacity %f, should be 15.0\n", myKnapSack.getCapacity());
		return -1;
	}

	if (myKnapSack.getNumOfItems() != 5*4) {
		std::fprintf(stderr, "Wrong read numOfItems %d, should be 5\n", myKnapSack.getNumOfItems());
		return -3;
	}

	for (int i=0; i < myKnapSack.getNumOfItems() ;++i) {
		KnapSackItem* item = &(myKnapSack.getItems()[i]);
		if ( ! isInTestItems(item) ) {
			std::fprintf(stderr, "Item(%s, %f, %f) is not in the test items.\n", item->name->c_str(), item->weight, item->worth);
			return -4;
		}
	}

	return 0;
}

/**
 * Tests whether the reading of the second input file example works correctly.
 * Returns 0 if test succeeds.
 * Returns -1 if read capacity mismatches expected capacity
 * Returns -3 if read numofitems mismatches expected numofitems
 * Returns -4 if a read item is not part of the expected test items
 */
int testReadingInputFileSecondExample() {
	std::printf("\nTesting input file: %s\n", KNAPSACK_INPUT_FILE_SECOND_EXAMPLE);
	KnapSack myKnapSack = KnapSackReader::readKnapSackFrom(KNAPSACK_INPUT_FILE_SECOND_EXAMPLE);

	if (! MyMath::almostEqual(15.0, myKnapSack.getCapacity())) {
		std::fprintf(stderr, "Wrong read capacity %f, should be 15.0\n", myKnapSack.getCapacity());
		return -1;
	}

	if (myKnapSack.getNumOfItems() != 6*1) {
		std::fprintf(stderr, "Wrong read numOfItems %d, should be 6\n", myKnapSack.getNumOfItems());
		return -3;
	}

	for (int i=0; i < myKnapSack.getNumOfItems() ;++i) {
		KnapSackItem* item = &(myKnapSack.getItems()[i]);
		// if item is not in the following test items
		if ( ! (	itemsAreEqual(item, TEST_ITEM_1) ||
					itemsAreEqual(item, TEST_ITEM_2) ||
					itemsAreEqual(item, TEST_ITEM_3) ||
					itemsAreEqual(item, TEST_ITEM_4) ||
					itemsAreEqual(item, TEST_ITEM_5) ||
					itemsAreEqual(item, TEST_ITEM_6)) ) {
			std::fprintf(stderr, "Item(%s, %f, %f) is not in the test items.\n", item->name->c_str(), item->weight, item->worth);
			return -4;
		}
	}

	return 0;
}

/**
 * Tests whether the reading of the third input file example works correctly.
 * Returns 0 if test succeeds.
 * Returns -1 if read capacity mismatches expected capacity
 * Returns -3 if read numofitems mismatches expected numofitems
 * Returns -4 if a read item is not part of the expected test items
 */
int testReadingInputFileThirdExample() {
	std::printf("\nTesting input file: %s\n", KNAPSACK_INPUT_FILE_THIRD_EXAMPLE);
	KnapSack myKnapSack = KnapSackReader::readKnapSackFrom(KNAPSACK_INPUT_FILE_THIRD_EXAMPLE);

	if (! MyMath::almostEqual(645.0, myKnapSack.getCapacity())) {
		std::fprintf(stderr, "Wrong read capacity %f, should be 645.0\n", myKnapSack.getCapacity());
		return -1;
	}

	if (myKnapSack.getNumOfItems() != 8*7) {
		std::fprintf(stderr, "Wrong read numOfItems %d, should be 8\n", myKnapSack.getNumOfItems());
		return -3;
	}

	for (int i=0; i < myKnapSack.getNumOfItems() ;++i) {
		KnapSackItem* item = &(myKnapSack.getItems()[i]);
		// if item is not in the following test items
		if ( ! (	itemsAreEqual(item, TEST_ITEM_EINS) ||
					itemsAreEqual(item, TEST_ITEM_ZWEI) ||
					itemsAreEqual(item, TEST_ITEM_DREI) ||
					itemsAreEqual(item, TEST_ITEM_VIERE) ||
					itemsAreEqual(item, TEST_ITEM_FUENF) ||
					itemsAreEqual(item, TEST_ITEM_SECHS) ||
					itemsAreEqual(item, TEST_ITEM_SIEBEN) ||
					itemsAreEqual(item, TEST_ITEM_ACHT)) ) {
			std::fprintf(stderr, "Item(%s, %f, %f) is not in the test items.\n", item->name->c_str(), item->weight, item->worth);
			return -4;
		}
	}

	return 0;
}



/**
 * Tests whether the reading of the knapsack problem input files works correctly.
 * Returns 0 if test succeeds.
 * Returns -1 if read capacity mismatches expected capacity
 * Returns -3 if read numofitems mismatches expected numofitems
 * Returns -4 if a read item is not part of the expected test items
 */
int testReading() {
	int returnCode = testReadingInputFile();

	if (returnCode != 0)
		return returnCode;

	returnCode = testReadingInputFileFirstExample();

	if (returnCode != 0)
		return returnCode;

	returnCode = testReadingInputFileSecondExample();

	if (returnCode != 0)
		return returnCode;

	returnCode = testReadingInputFileThirdExample();

	if (returnCode != 0)
		return returnCode;

	return 0;
}

/**
 * Executes the test by calling testReading()
 */
int main(int argc, char* argv[]){
	return testReading();
}
