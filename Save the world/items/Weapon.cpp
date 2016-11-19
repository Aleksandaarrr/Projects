#include "Weapon.hpp"

namespace lab3 {

// Weapon konstruktor som tar in namn, beskrivning, hastighet, skada, vikt och pris
Weapon::Weapon(std::string name, std::string desc, int spd, int dmg, int weight, int price) {
	setItemName(name);
	setDescription(desc);
	setWeight(weight);
	speed = spd;
	damage = dmg;
	setPrice(price);
	setType("Weapon");
}

// Lägger till hastighet på vapnet och returnerar hastigheten
void Weapon::setSpeed(const int spd) { speed = spd; }
int Weapon::getSpeed()const { return speed; }

// Lägger till skada på vapnet och returnerar skadan
void Weapon::setDamage(const int dmg) { damage = dmg; }
int Weapon::getDamage() const{ return damage; }

// Vid användning av ett vapen anropas denna funktion som använder vapnet
// och sätter användning till true
void Weapon::use(Player * p) { 
	p->setDmg(p->getDmg() + damage); 
	Item::setEquipped(true);
}

// Avslutar användning av ett vapen genom att minska på skada och 
// sätter användning till false
void Weapon::unUseWeapon(Player * p) { 
	p->setDmg(p->getDmg() - damage); 
	Item::setEquipped(false);
	std::cout << "You have unequipped " << getNameOfItem() << std::endl;
}
}
