#ifndef MAIN_KNAPSACK_H_
#define MAIN_KNAPSACK_H_

#include <utility>
#include <iostream>
#include "util/MyMath.h"

/**
 * Represents an item from the item pool of the knapsack
 */
struct KnapSackItem{

	// using string pointer because of performance reasons.
	std::string* name;
	double weight;
	double worth;

	bool operator==(const KnapSackItem& rhs){
		return MyMath::almostEqual(weight, rhs.weight) && MyMath::almostEqual(worth, rhs.worth) && *name == *(rhs.name);
	}
};

class KnapSack{

private:
	/**
	 * The maximum capacity the knapsack can take
	 */
	double capacity;

	/**
	 * the number of items available in the item pool
	 */
	int numOfItems;

	/**
	 * the item pool from which the items can be picked
	 */
	KnapSackItem* items;


	KnapSack();

public:
	/**
	 * Initializes a knapSack object with _capacity as max capacity and allocates an array of knapsackitems of the size of _numOfItems on the heap.
	 */
	KnapSack(double _capacity, int _numOfItems);
	KnapSack(const KnapSack& other);
	~KnapSack();

	friend void swap(KnapSack& first, KnapSack& second);

	KnapSack& operator=(KnapSack other);

	double getCapacity() const;
	int getNumOfItems() const;
	KnapSackItem* getItems() const;

	
};

std::ostream& operator<<(std::ostream &strm, const KnapSack &v);
void swap(KnapSack& first, KnapSack& second);

#endif /* MAIN_KNAPSACK_H_ */
