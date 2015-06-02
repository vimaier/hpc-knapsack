#include "KnapSack.h"

KnapSack::KnapSack(double _capacity, int _maxNumPerItem, int _numOfItems)
{
	setCapacity(_capacity);
	setMaxNumPerItem(_maxNumPerItem);
	setNumOfItems(_numOfItems);
	setItems(new KnapSackItem[_numOfItems]);
}

KnapSack::~KnapSack()
{
	delete[] items;
}

//***************************GETTERS********************************//
double KnapSack::getCapacity() const { return capacity; }
int KnapSack::getMaxNumPerItem() const { return maxNumPerItem; }
int KnapSack::getNumOfItems() const { return numOfItems; }
KnapSackItem* KnapSack::getItems() const { return items; }

//***************************SETTERS********************************//
void KnapSack::setCapacity(double _capacity){ capacity = _capacity; }
void KnapSack::setMaxNumPerItem(int _maxNumPerItem){ maxNumPerItem = _maxNumPerItem; }
void KnapSack::setNumOfItems(int _numOfItems){ numOfItems = _numOfItems; }
void KnapSack::setItems(KnapSackItem* _items){ items = _items; }


std::ostream& operator<<(std::ostream &strm, const KnapSack &v) {

	KnapSackItem* items = v.getItems();
	for (int i = 0; i < v.getNumOfItems(); i++)
	{
		strm << items[i].name->c_str() << " | " << items[i].weight << " | " << items[i].worth << "\n";
	}

	return strm;
}