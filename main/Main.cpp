#include "main/algorithms/BruteForceSolver.h"
#include "main/algorithms/DynamicProgrammingSolver.h"
#include "main/algorithms/NemhauserUllmannSolver.h"
#include "main/algorithms/NemhauserUllmannParallelSolver.h"
using namespace std;

static const char* FIRST_KNAPSACK_INPUT_FILE = "res/firstFileExample.txt";
static const char* SECOND_KNAPSACK_INPUT_FILE = "res/secondFileExample.txt";
static const char* THIRD_KNAPSACK_INPUT_FILE = "res/thirdFileExample.txt";
static const char* DP_INPUT_FILE = "res/dynamicProgrammingExample.txt";
static const char* KNAPSACK_OUTPUT_FILE = "knapSackOut.txt";

int main(int argc, char* argv[]){

	/*
	BruteForceSolver* bfsolver = new BruteForceSolver(FIRST_KNAPSACK_INPUT_FILE, KNAPSACK_OUTPUT_FILE);
	bfsolver->start();
	delete bfsolver;
	 */

	/*
	NemhauserUllmannSolver* nusolver = new NemhauserUllmannSolver(THIRD_KNAPSACK_INPUT_FILE, KNAPSACK_OUTPUT_FILE);
	nusolver->start();
	delete nusolver;
	*/

	/*
	NemhauserUllmannParallelSolver* nupsolver = new NemhauserUllmannParallelSolver(THIRD_KNAPSACK_INPUT_FILE, KNAPSACK_OUTPUT_FILE);
	nupsolver->start();
	delete nupsolver;
	*/

	DynamicProgrammingSolver* dpsolver = new DynamicProgrammingSolver(DP_INPUT_FILE, KNAPSACK_OUTPUT_FILE);
	dpsolver->start();
	delete dpsolver;
}
