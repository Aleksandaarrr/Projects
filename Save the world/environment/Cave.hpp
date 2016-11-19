#ifndef CAVE_HPP_
#define CAVE_HPP_

#include "Environment.hpp"
#include "../actor/Player.hpp"

namespace lab3 {

class Cave : public Environment {

public:
	Cave(std::string, std::string);
	void hasTorch(Player * p);

};
}
#endif
