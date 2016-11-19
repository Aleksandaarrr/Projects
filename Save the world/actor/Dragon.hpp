#ifndef DRAGON_HPP_
#define DRAGON_HPP_

#include "Creature.hpp"
#include <string>

namespace lab3 {

class Dragon : public Creature {

public:
	Dragon(std::string, std::vector<Item *>);
	void talk(std::string);

};
}
#endif
