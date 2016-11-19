#ifndef HUMAN_HPP_
#define HUMAN_HPP_

#include "Actor.hpp"
#include <string>

namespace lab3 {

class Human : public Actor {
public:
	Human();
	int attack(std::string);
	virtual void talk(std::string) = 0;
};
}
#endif
