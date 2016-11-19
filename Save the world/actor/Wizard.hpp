#ifndef WIZARD_HPP_
#define WIZARD_HPP_

#include "Human.hpp"
#include <string>

namespace lab3 {

class Wizard : public Human {

public:
	Wizard(std::string, std::vector<Item *>);
	void talk(std::string);

};
}
#endif