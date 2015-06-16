#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "util/io/KnapSackWriter.h"
#include "main/KnapSack.h"
#include "util/MyMath.h"
#include "util/StringUtils.h"
#include "util/TestUtils.h"

/**
 * Tests the writing of a knapsack object.
 */

const int ASSUMED_CONTENT_LENGTH = 5;
const std::string ASSUMED_CONTENT[] { "Kapazität;15.0", "yellow daisy;3", "gray mouse;3", "Gesamtgewicht;15.0", "Gesamtwert;36.00" };

std::string* ITEM__NAME_1 = new std::string("yellow daisy");
const KnapSackItem TEST_ITEM_1 = {ITEM__NAME_1, 4.0, 10.0};

std::string* ITEM__NAME_2 = new std::string("gray mouse");
const KnapSackItem TEST_ITEM_2 = {ITEM__NAME_2, 1.0, 2.0};

const static char* TEST_OUTPUT_FILE = "outputForTesting.txt";

int testReading() {
	// Create the file
	KnapSackWriter writer(TEST_OUTPUT_FILE, 2, 15.0);

	writer.addItem(&TEST_ITEM_1, 3);
	writer.addItem(&TEST_ITEM_2, 3);

	if ( ! writer.writeToFile()) {
		std::printf("Could not write to file.");
		return -2;
	}

	return TestUtils::checkOutput(ASSUMED_CONTENT, ASSUMED_CONTENT_LENGTH, TEST_OUTPUT_FILE);
}

int main(int argc, char* argv[]){
	return testReading();
}
