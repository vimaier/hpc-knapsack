#include "KnapSack.h"

KnapSack::KnapSack(float _capacity, int _maxNumPerItem, int _numOfItems, KnapSackItem** _items)
{
	setCapacity(_capacity);
	setMaxNumPerItem(_maxNumPerItem);
	setNumOfItems(_numOfItems);
	setItems(_items);
}

//***************************GETTERS********************************//
int KnapSack::getCapacity() { return capacity; }
int KnapSack::getMaxNumPerItem()  { return maxNumPerItem; }
int KnapSack::getNumOfItems() { return numOfItems; }
KnapSack::KnapSackItem** KnapSack::getItems() { return items; }

//***************************SETTERS********************************//
void KnapSack::setCapacity(float _capacity){ capacity = _capacity; }
void KnapSack::setMaxNumPerItem(int _maxNumPerItem){ maxNumPerItem = _maxNumPerItem; }
void KnapSack::setNumOfItems(int _numOfItems){ numOfItems = _numOfItems; }
void KnapSack::setItems(KnapSackItem** _items){ items = _items; }