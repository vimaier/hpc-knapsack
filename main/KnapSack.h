#include <iostream>

struct KnapSackItem{
	// using string pointer because of memory reasons. uses less than string itself.
	std::string* name;
	double weight;
	double worth;

	~KnapSackItem()
	{
		delete name;
	}
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
	~KnapSack();

	double getCapacity() const;
	int getMaxNumPerItem() const;
	int getNumOfItems() const;
	KnapSackItem* getItems() const;

	
};

std::ostream& operator<<(std::ostream &strm, const KnapSack &v);