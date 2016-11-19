#include "Creature.hpp"
#include <string>
#include <iostream>
#include <random>

namespace lab3 {

Creature::Creature() {}

// Anpassad attack funktion för varelser, monster, etc.
// Slumpvis skada från 0-9+varelsens skada
int Creature::attack(std::string s) {
	std::random_device rdev;
	std::mt19937 rgen(rdev());
	std::uniform_int_distribution<int> idist(0,9+getDmg());
		
	int r = idist(rgen);

	if(r > 2) {
		std::cout << getName() << " throws FIRE BLAST at you dealing " << r << " damage!" << std::endl;
		return r;

	} else {
		std::cout << getName() << " missed you." << std::endl;
		return 0;
	}
}
}