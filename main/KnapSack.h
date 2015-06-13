#ifndef MAIN_KNAPSACK_H_
#define MAIN_KNAPSACK_H_

#include <utility>
#include <iostream>

struct KnapSackItem{

	// using string pointer because of memory reasons. uses less than string itself.
	std::string* name;
	double weight;
	double worth;
};

class KnapSack{

private:
	double capacity;
	int maxNumPerItem;
	int numOfItems;
	KnapSackItem* items;
	KnapSack();

	void setCapacity(double _capacity);
	void setMaxNumPerItem(int _maxNumPerItem);
	void setNumOfItems(int _numOfItems);
	void setItems(KnapSackItem* _items);

public:
	KnapSack(double _capacity, int _maxNumPerItem, int _numOfItems);
	KnapSack(const KnapSack& other);
	~KnapSack();

	friend void swap(KnapSack& first, KnapSack& second);

	KnapSack& operator=(KnapSack other);

	double getCapacity() const;
	int getMaxNumPerItem() const;
	int getNumOfItems() const;
	KnapSackItem* getItems() const;

	
};

std::ostream& operator<<(std::ostream &strm, const KnapSack &v);
void swap(KnapSack& first, KnapSack& second);

#endif /* MAIN_KNAPSACK_H_ */
