#include "KnapSackReader.h"

KnapSack KnapSackReader::readKnapSackFrom(const char* fileName){

#ifdef PRINT_VERBOSE
	std::cout << "**************************" << std::endl;
	std::cout << "reading " << fileName << " ... " << std::endl;
#endif

	//allocate objects on stack by auto calling constructors ifstream(filename) and string()
	std::ifstream input(fileName);
	std::string strLine;

	//read first line: capacity, MaxNumPerItem and numOfItems
	std::getline(input, strLine);

#ifdef PRINT_VERBOSE
	std::cout << "constraints: " << strLine << '\n';
#endif

	std::vector<std::string> firstLine = StringUtils::split(strLine, ' ');
	const double capacity = std::atof(firstLine[0].c_str());
	const int numOfInstancesPerItem = std::atoi(firstLine[1].c_str());
	const int numOfItems = std::atoi(firstLine[2].c_str());

	const int totalNumOfItems = numOfInstancesPerItem * numOfItems;
	KnapSack knapSack(capacity, totalNumOfItems);
	KnapSackItem* items = knapSack.getItems();

	//read / populate items
	int i = 0;
	while (std::getline(input, strLine)) {
		if (strLine.length() < STRLENGTH_ITEMNAME)
			continue; // Probably an empty line

#ifdef PRINT_VERBOSE
		std::cout << "item: " << strLine << '\n';
#endif

		// Read name, weight and worth
		std::string name(strLine.substr(0, STRLENGTH_ITEMNAME));
		StringUtils::trim(name);
		std::string valueString = strLine.substr(STRLENGTH_ITEMNAME + 1);
		valueString = StringUtils::trim(valueString);
		std::vector<std::string> values = StringUtils::split(valueString, ' ');
		const double weight = std::atof(values[0].c_str());
		const double worth = std::atof(values[1].c_str());

		// Add item x times, where x is the number of possible instances per item
		for (int j = 0; j < numOfInstancesPerItem; j++){
			items[i].name = new std::string(name);
			items[i].weight = weight;
			items[i].worth = worth;
			i++;
		}
	}

#ifdef PRINT_VERBOSE
	std::cout << "reading complete" << std::endl;
	std::cout << "**************************" << std::endl;
#endif

	return knapSack;
}

