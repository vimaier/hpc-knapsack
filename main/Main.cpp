#include <omp.h>
#include <stdio.h>

#include "main/algorithms/BruteForceSolver.h"
#include "main/algorithms/DynamicProgrammingSolver.h"
#include "main/algorithms/DynamicProgrammingParallelSolver.h"
#include "main/algorithms/NemhauserUllmannSolver.h"
#include "main/algorithms/NemhauserUllmannParallelSolver.h"
using namespace std;

#define PRINT_VERBOSE

static const char* FIRST_KNAPSACK_INPUT_FILE = "res/firstFileExample.txt";
static const char* SECOND_KNAPSACK_INPUT_FILE = "res/secondFileExample.txt";
static const char* THIRD_KNAPSACK_INPUT_FILE = "res/thirdFileExample.txt";
static const char* FOURTH_KNAPSACK_INPUT_FILE = "res/fourthFileExample.txt";
static const char* FIFTH_KNAPSACK_INPUT_FILE = "res/fifthFileExample.txt";
static const char* DP_INPUT_FILE = "res/dynamicProgrammingExample.txt";
static const char* KNAPSACK_OUTPUT_FILE = "knapSackOut.txt";

void executeNemhauserUllmanSolver() {
	KnapSackSolver* solver = new NemhauserUllmannSolver(FOURTH_KNAPSACK_INPUT_FILE, KNAPSACK_OUTPUT_FILE);
	solver->start();
	delete solver;
}

void executeNemhauserUllmanParallelSolver() {
	KnapSackSolver* solver = new NemhauserUllmannParallelSolver(FOURTH_KNAPSACK_INPUT_FILE, KNAPSACK_OUTPUT_FILE);
	solver->start();
	delete solver;
}

void executeBruteForceSolver(){
	BruteForceSolver* bfsolver = new BruteForceSolver(FIRST_KNAPSACK_INPUT_FILE, KNAPSACK_OUTPUT_FILE);
	bfsolver->start();
	delete bfsolver;
}

void executeDynamicProgrammingSolver(){
	DynamicProgrammingSolver* dpsolver = new DynamicProgrammingSolver(DP_INPUT_FILE, KNAPSACK_OUTPUT_FILE);
	dpsolver->start();
	delete dpsolver;
}

void executeDynamicProgrammingParallelSolver(){
	DynamicProgrammingParallelSolver* dpsolver = new DynamicProgrammingParallelSolver(DP_INPUT_FILE, KNAPSACK_OUTPUT_FILE);
	dpsolver->start();
	delete dpsolver;
}

void checkForOpenMP(){
	int id;
	#pragma omp parallel private(id)
	{
		id = omp_get_thread_num();
		printf("%d: Hello World!\n", id);
	}
}

int main(int argc, char* argv[]){

	//checkForOpenMP();

	//executeBruteForceSolver();
	//executeNemhauserUllmanSolver();
	//executeNemhauserUllmanParallelSolver();
	executeDynamicProgrammingSolver();
	executeDynamicProgrammingParallelSolver();
}
