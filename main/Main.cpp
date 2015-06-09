#include "../io/KnapSackReader.h"
#include "KnapSack.h"
using namespace std;

static const char* KNAPSACK_INPUT_FILE = "../res/KnapSackItems.txt";

int main(int argc, char* argv[]){
	KnapSack myKnapSack = KnapSackReader::readKnapSackFrom(KNAPSACK_INPUT_FILE);

	cout << myKnapSack << endl;
}
