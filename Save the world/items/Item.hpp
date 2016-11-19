#ifndef ITEM_HPP_
#define ITEM_HPP_

#include <string>

namespace lab3 {

class Item {

private:
	std::string type = "";
	double weight = 0;
	int price = 0;
	std::string itemName = "";
	std::string description = "";
	bool equipped = false;

public:
	Item();
	virtual ~Item();
	void setType(const std::string);
	std::string getType() const;
	void setItemName( const std::string);
	std::string getNameOfItem() const;
	void setWeight(const double);
	double getWeight() const;
	void setPrice(const int);
	int getPrice() const;
	void setDescription(const std::string);
	std::string getDescription()const;

	void setEquipped(const bool);
	bool getEquipped() const;

};
}
#endif
