#ifndef MAIN_KNAPSACK_H_
#define MAIN_KNAPSACK_H_

#include <utility>
#include <iostream>

struct KnapSackItem{

	// using string pointer because of memory reasons. uses less than string itself.
	std::string* name;
	double weight;
	double worth;

	bool operator==(const KnapSackItem& rhs){
		return weight == rhs.weight && worth == rhs.worth && *name == *(rhs.name);
	}
};

class KnapSack{

private:
	double capacity;
	int numOfItems;
	KnapSackItem* items;
	KnapSack();

	void setCapacity(double _capacity);
	void setNumOfItems(int _numOfItems);
	void setItems(KnapSackItem* _items);

public:
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
