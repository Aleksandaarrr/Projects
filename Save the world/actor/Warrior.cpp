#include "Warrior.hpp"

namespace lab3 {

// Warrior konstruktor som tar in ett namn och en lista med föremål
Warrior::Warrior(std::string name, std::vector<Item *> items) {
	setName(name);
	setHealth(10);
	setDmg(2);
	setDef(3);
	setFriendly(false);
	setType("Warrior");
	for(size_t i = 0; i < items.size(); i++) {
		addItem(items[i]);
	}

}

void Warrior::talk(std::string) {
	std::cout << getName() << " shouts: I will kill you!" << std::endl;
}

}
