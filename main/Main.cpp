#include "main/algorithms/BruteForceSolver.h"
#include "main/algorithms/DynamicProgrammingSolver.h"
using namespace std;

static const char* FIRST_KNAPSACK_INPUT_FILE = "res/firstFileExample.txt";
static const char* SECOND_KNAPSACK_INPUT_FILE = "res/secondFileExample.txt";
static const char* THIRD_KNAPSACK_INPUT_FILE = "res/thirdFileExample.txt";
static const char* KNAPSACK_OUTPUT_FILE = "knapSackOut.txt";

int main(int argc, char* argv[]){

	BruteForceSolver* bfsolver = new BruteForceSolver(FIRST_KNAPSACK_INPUT_FILE, KNAPSACK_OUTPUT_FILE);
	bfsolver->start();
	delete bfsolver;

	/*
	DynamicProgrammingSolver* dpsolver = new DynamicProgrammingSolver(FIRST_KNAPSACK_INPUT_FILE, KNAPSACK_OUTPUT_FILE);
	dpsolver->start();
	delete dpsolver;
	*/
	
}
