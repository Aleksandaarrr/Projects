#include "Potion.hpp"

namespace lab3 {

// Potion konstruktor som tar in namn, beskrivning, liv, vikt och pris
Potion::Potion(std::string name, std::string desc, int hp, int weight, int price) {
	setItemName(name);
	setDescription(desc);
	setWeight(weight);
	healthRegen = hp;
	setPrice(price);
	setType("Potion");
}

// Lägger till hur mycket liv potion ska innehålla och returnerar liv
void Potion::setHealthRegen(const int hp) { healthRegen = hp; }
int Potion::getHealthRegen() const { return healthRegen; }

// När potion används utförs denna funktion
void Potion::use(Player * p){
	int maxHp = p->getMaxHealth();
	int newHp = p->getHealth() + healthRegen;
	if(newHp > maxHp) {
		p->setHealth(maxHp);
	}
	else {
		p->setHealth(newHp);
	}	
}
}
