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
#include "test/TestData.h"

/**
 * Tests the writing of a knapsack object.
 */

int testReading() {
	// Create the file
	KnapSackWriter writer(TEST_OUTPUT_FILE, 2, 15.0);

	writer.addItem(&TEST_ITEM_2, 3);
	writer.addItem(&TEST_ITEM_4, 3);

	if ( ! writer.writeToFile()) {
		std::printf("Could not write to file.");
		return -2;
	}

	return TestUtils::checkOutput(ASSUMED_CONTENT_FILE_1, ASSUMED_CONTENT_LINES_FILE_1, TEST_OUTPUT_FILE);
}

int main(int argc, char* argv[]){
	return testReading();
}
