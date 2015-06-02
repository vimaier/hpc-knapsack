#include "KnapSackReader.h"

/*
*	Example File:
*
*	---------------------
*	10.0 4 2
*	XXL blue Ox		3.0 2.00
*	gray mouse		1.0 2.45
*	---------------------
*
*	Capacity = 10.0
*	MaxNumPerItem = 4
*	NumOfItems = 2
*	Item 1: Name(XXL blue Ox), Weight(3.0), Worth(2.00)
*	Item 2: Name(gray mouse), Weight(1.0), Worth(2.45)
*	Itemnames are always 13 characters long
*/

KnapSack* KnapSackReader::readKnapSackFrom(const char* fileName){

	//allocate objects on stack by auto calling constructors ifstream(filename) and string()
	std::ifstream input(fileName);
	std::string strLine;

	//read first line: capacity, MaxNumPerItem and numOfItems
	std::getline(input, strLine);
	std::cout << "constraints: " << strLine << '\n';
	const float capacity = std::atof(strLine.substr(INDEX_START_CAPACITY, STRLENGTH_CAPACITY).c_str());
	const int maxNumPerItem = std::atoi(strLine.substr(INDEX_START_MAXNUM, STRLENGTH_MAXNUM).c_str());
	const int numOfItems = std::atoi(strLine.substr(INDEX_START_NUMOFITEMS, STRLENGTH_NUMOFITEMS).c_str());

	KnapSack* knapSack = new KnapSack(capacity, maxNumPerItem, numOfItems);
	KnapSackItem* items = knapSack->getItems();

	//read / populate items
	int i = 0;
	while (std::getline(input, strLine)) {
		std::cout << "item: " << strLine << '\n';

		// Read name, weight and worth
		std::string* name = new std::string(strLine.substr(INDEX_START_ITEMNAME, STRLENGTH_ITEMNAME));
		const float weight = std::atof(strLine.substr(INDEX_START_WEIGHT, STRLENGTH_WEIGHT).c_str());
		const float worth = std::atof(strLine.substr(INDEX_START_WORTH, STRLENGTH_WORTH).c_str());

		// Add item
		items[i].name = name;
		items[i].weight = weight;
		items[i].worth = worth;
		i++;
	}

	return knapSack;
}