#ifndef POTION_HPP_
#define POTION_HPP_

#include "Usable.hpp"
#include "../actor/Player.hpp"

namespace lab3 {

class Potion : public Usable {

private:
	int healthRegen = 0;

public:
	Potion(std::string, std::string, int, int, int);
	void setHealthRegen(const int);
	int getHealthRegen() const;
	void use(Player *);
};
}
#endif
