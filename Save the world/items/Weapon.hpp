#ifndef WEAPON_HPP_
#define WEAPON_HPP_

#include "Usable.hpp"
#include <string>
#include "../actor/Player.hpp"

namespace lab3 {

class Weapon : public Usable {

	private:
		int speed = 0;
		int damage = 0;

	public:
		Weapon(std::string, std::string, int, int, int, int);
		void setSpeed(const int);
		int getSpeed() const;
		void setDamage(const int);
		int getDamage() const;
		void use(Player *);
		void unUseWeapon(Player *); 

};
}
#endif
