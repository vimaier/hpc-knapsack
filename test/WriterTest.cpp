#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "util/io/KnapSackWriter.h"
#include "main/KnapSack.h"
#include "util/MyMath.h"
#include "util/StringUtils.h"

/**
 * Tests the writing of a knapsack object.
 */


const char* KNAPSACK_OUTPUT_FILE = "outputForTesting.txt";
const int ASSUMED_CONTENT_LENGTH = 5;
const std::string ASSUMED_CONTENT[] { "Kapazität;15.0", "yellow daisy;3", "gray mouse;3", "Gesamtgewicht;15.0", "Gesamtwert;36.00" };

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
	std::ifstream ifile(KNAPSACK_OUTPUT_FILE);
	std::string strLine;

	//compare line for line
	int i = 0;
	bool matches = true;
	std::string wholeText;
	while (std::getline(ifile, strLine) && i<ASSUMED_CONTENT_LENGTH) {
		wholeText += strLine;
		if (ASSUMED_CONTENT[i].compare(strLine) != 0){
			std::printf("Mismatch \n'%s' (assumed) \nvs \n'%s' (read)\n", ASSUMED_CONTENT[i].c_str(), strLine.c_str());
			matches = false;
			break;
		}
		i++;
	}

    if (matches) {
    	// Delete file again
    	std::remove(KNAPSACK_OUTPUT_FILE);
    	return 0;
    }
    else {
		std::string assumedText;
		for (int i = 0; i < ASSUMED_CONTENT_LENGTH; i++){
			assumedText += ASSUMED_CONTENT[i];
		}
		std::printf("Mismatch between written and assumed file content\nAssumed:\n%s\n\nActual:\n%s\n", assumedText.c_str(), wholeText.c_str());
		return -3;
    }
}

int main(int argc, char* argv[]){
	return testReading();
}
