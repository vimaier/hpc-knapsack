#include "KnapSack.h"

KnapSack::KnapSack(double _capacity, int _numOfItems)
  :	capacity(_capacity),
	numOfItems(_numOfItems),
	items(new KnapSackItem[_numOfItems])
{
}

KnapSack::KnapSack(const KnapSack& other)
	: capacity(other.capacity),
	  numOfItems(other.numOfItems),
	  items(new KnapSackItem[other.numOfItems]){

	for(int i=0; i < numOfItems ;++i) {
		items[i].name = new std::string(other.items[i].name->c_str());
		items[i].weight = other.items[i].weight;
		items[i].worth = other.items[i].worth;
	}
}

KnapSack::~KnapSack()
{
	for(int i=0; i < numOfItems ;++i) {
		delete items[i].name;
		items[i].name = 0;
	}
	delete[] items;
}

KnapSack& KnapSack::operator =(KnapSack other) {

	swap(*this, other);
	return *this;

}

//***************************GETTERS********************************//
double KnapSack::getCapacity() const { return capacity; }
int KnapSack::getNumOfItems() const { return numOfItems; }
KnapSackItem* KnapSack::getItems() const { return items; }


std::ostream& operator<<(std::ostream &strm, const KnapSack &v) {

	KnapSackItem* items = v.getItems();
	for (int i = 0; i < v.getNumOfItems(); i++)
	{
		strm << items[i].name->c_str() << " | " << items[i].weight << " | " << items[i].worth << "\n";
	}

	return strm;
}

void swap(KnapSack& first, KnapSack& second) {

	std::swap(first.capacity, second.capacity);
	std::swap(first.numOfItems, second.numOfItems);
	std::swap(first.items, second.items);

}

