#ifndef OUTSIDE_HPP_
#define OUTSIDE_HPP_

#include "Environment.hpp"
#include "../actor/Player.hpp"
#include <ctime>

namespace lab3 {

class Outside : public Environment {

private:
	clock_t begin = 0;
	clock_t end = 0;

public:
	Outside(std::string, std::string);
	void hurtPlayer(Player *);
	void calcSeconds();
};
}
#endif
