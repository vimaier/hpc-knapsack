#include "../main/KnapSack.h"
#include "../util/StringUtils.h"
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

class KnapSackReader{
private:
	//Input file constraints
	static const int STRLENGTH_ITEMNAME = 13;

	KnapSackReader();
public:
	static KnapSack readKnapSackFrom(const char* fileName);
	
};

std::vector<std::string> split(std::string str, char delimiter);

