#ifndef MISC_HPP_
#define MISC_HPP_

#include "Item.hpp"

namespace lab3 {

class Misc : public Item {

private:
	int value = 0;

public:
	Misc(std::string, std::string, int, int);
	void setValue(const int);
	int getValue() const;

};
}
#endif
