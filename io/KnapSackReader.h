#include "../main/KnapSack.h"
#include <iostream>
#include <fstream>
#include <string>

class KnapSackReader{
private:
	//Input file constraints
	static const int STRLENGTH_SPACE = 1;
	static const int STRLENGTH_CAPACITY = 4;
	static const int STRLENGTH_MAXNUM = 1;
	static const int STRLENGTH_NUMOFITEMS = 1;
	static const int STRLENGTH_ITEMNAME = 13;
	static const int STRLENGTH_WEIGHT = 3;
	static const int STRLENGTH_WORTH = 4;

	static const int INDEX_START_CAPACITY = 0;
	static const int INDEX_START_MAXNUM = INDEX_START_CAPACITY + STRLENGTH_CAPACITY + STRLENGTH_SPACE;
	static const int INDEX_START_NUMOFITEMS = INDEX_START_MAXNUM + STRLENGTH_MAXNUM + STRLENGTH_SPACE;
	static const int INDEX_START_ITEMNAME = 0;
	static const int INDEX_START_WEIGHT = INDEX_START_ITEMNAME + STRLENGTH_ITEMNAME + STRLENGTH_SPACE;
	static const int INDEX_START_WORTH = INDEX_START_WEIGHT + STRLENGTH_WEIGHT + STRLENGTH_SPACE;

	KnapSackReader();
public:
	static KnapSack* readKnapSackFrom(const char* fileName);
};