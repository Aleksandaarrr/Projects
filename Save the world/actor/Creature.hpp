#ifndef CREATURE_HPP_
#define CREATURE_HPP_

#include "Actor.hpp"
#include <string>

namespace lab3 {

class Creature : public Actor {
public:
	Creature();

	int attack(std::string);
	virtual void talk(std::string) = 0;
};
}
#endif
