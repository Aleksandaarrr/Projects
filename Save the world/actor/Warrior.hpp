#ifndef WARRIOR_HPP_
#define WARRIOR_HPP_

#include "Human.hpp"
#include <string>

namespace lab3 {

class Warrior : public Human {

public:
	Warrior(std::string, std::vector<Item *>);
	void talk(std::string);

};

}
#endif
