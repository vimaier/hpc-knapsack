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
 * Tests whether a filled knapsackwriter object is properly written to file.
 * Returns 0 if test succeeds.
 * Returns -1 if actual output mismatches expected output.
 * Returns -2 if writing to file failed.
 */
int testWriting() {
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

/**
 * Performs the test by calling testWriting()
 */
int main(int argc, char* argv[]){
	return testWriting();
}
