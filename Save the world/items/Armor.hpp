#ifndef ARMOR_HPP_
#define ARMOR_HPP_

#include "Usable.hpp"
#include "../actor/Player.hpp"

namespace lab3 {

class Armor : public Usable {

private:
	int armor = 0;

public:
	Armor(std::string, std::string, int, int, int);
	void setArmor(const int);
	int getArmor() const;
	void use(Player *);
	void unUseArmor(Player *);

};
}
#endif
