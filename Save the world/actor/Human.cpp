#include "Human.hpp"
#include <string>
#include <iostream>
#include <random>

namespace lab3 {

// Human är en typ abstrakt klass som ärver från Actor och warrior, wizard ärver från human
Human::Human() {}

// Attack funktion som returnerar hur mycket aktören gör skada beroende på vilken klass
// aktören är samt vilken ability/spell den använder, även utskriften är klass-anpassad
// skadan slumpas från 0-9+den skada aktören hara
int Human::attack(std::string s) {
	std::random_device rdev;
	std::mt19937 rgen(rdev());
	std::uniform_int_distribution<int> idist(0,9+getDmg());
		
	int r = idist(rgen);

	if(r > 4){
		if(getType() == "Wizard") {
			if(r > 7) {
				std::cout << getName() << " casts a CHAOS BOLT at you dealing " << r << " damage!" << std::endl;
			}
			else {
				std::cout << getName() << " casts a FIRE BALL at you dealing " << r << " damage!" << std::endl;
			}
		}
		else if(getType() == "Warrior") {
			if(r > 7) {
				std::cout << getName() << " uses THUNDER CLAP at you dealing " << r << " damage!" << std::endl;
			}
			else {
				std::cout << getName() << " uses REND at you dealing " << r << " damage!" << std::endl;
			}
		}
		return r;

	} else{
		std::cout << getName() << " missed you." << std::endl;
		return 0;
	}
}
}