#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "util/io/KnapSackWriter.h"
#include "main/KnapSack.h"
#include "util/MyMath.h"

/**
 * Tests the writing of a knapsack object.
 */


const char* KNAPSACK_OUTPUT_FILE = "outputForTesting.txt";
const std::string ASSUMED_CONTENT = "Kapazität;15.0\nyellow daisy;3\ngray mouse;3\nGesamtgewicht;15.0\nGesamtwert;36.00";


std::string* ITEM__NAME_1 = new std::string("yellow daisy");
const KnapSackItem TEST_ITEM_1 = {ITEM__NAME_1, 4.0, 10.0};

std::string* ITEM__NAME_2 = new std::string("gray mouse");
const KnapSackItem TEST_ITEM_2 = {ITEM__NAME_2, 1.0, 2.0};



int testReading() {
	// Create the file
	KnapSackWriter writer(KNAPSACK_OUTPUT_FILE, 2, 15.0);

	writer.addItem(&TEST_ITEM_1, 3);
	writer.addItem(&TEST_ITEM_2, 3);

	if ( ! writer.writeToFile()) {
		std::printf("Could not write to file.");
		return -1;
	}

	// Read file again
	std::ifstream ifile;
	std::string str;
	ifile.open(KNAPSACK_OUTPUT_FILE, std::ios::binary);
	if ( ! ifile.is_open()) {
		std::printf("Could not open written file.");
		return -2;
	}

	int length;
	char * buffer;

	      // get length of file:
	ifile.seekg (0, std::ios::end);
	length = ifile.tellg();
	ifile.seekg (0, std::ios::beg);

	// allocate memory:
	buffer = new char [length];

	// read data as a block:
	ifile.read (buffer,length);

	ifile.close();

	std::string readStr(buffer,length);

	delete[] buffer;

	// Compare with assumed String
    if (ASSUMED_CONTENT.compare(readStr)) {
    	// Delete file again
    	std::remove(KNAPSACK_OUTPUT_FILE);
    	return 0;
    }
    else {
    	std::printf("Mismatch between written and assumed file content\nAssumed:\n%s\n\nActual:\n%s\n", ASSUMED_CONTENT.c_str(), readStr.c_str());
		return -3;
    }
}

int main(int argc, char* argv[]){
	return testReading();
}
