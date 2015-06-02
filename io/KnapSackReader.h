#include "../main/KnapSack.h"

class KnapSackReader{
private:
	KnapSackReader();
public:
	static KnapSack* readKnapSackFrom(const char* fileName);
};