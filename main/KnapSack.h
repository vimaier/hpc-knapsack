#include <iostream>

struct KnapSackItem{
	// using string pointer because of memory reasons. uses less than string itself.
	std::string* name;
	float weight;
	float worth;

	~KnapSackItem()
	{
		delete name;
	}
};

class KnapSack{

private:
	float capacity;
	int maxNumPerItem;
	int numOfItems;
	KnapSackItem* items;
	KnapSack();

	void setCapacity(float _capacity);
	void setMaxNumPerItem(int _maxNumPerItem);
	void setNumOfItems(int _numOfItems);
	void setItems(KnapSackItem* _items);

public:
	KnapSack(float _capacity, int _maxNumPerItem, int _numOfItems);

	int getCapacity();
	int getMaxNumPerItem();
	int getNumOfItems();
	KnapSackItem* getItems();

	~KnapSack();
};