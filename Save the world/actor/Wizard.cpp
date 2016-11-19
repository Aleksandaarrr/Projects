#include "Wizard.hpp"

namespace lab3 {

// Wizard konstruktor som tar in ett namn och en lista med föremål
Wizard::Wizard(std::string name, std::vector<Item *> items) {
	setName(name);
	setHealth(10);
	setDmg(3);
	setDef(3);
	setFriendly(false);
	setType("Wizard");
	for(size_t i = 0; i < items.size(); i++) {
		addItem(items[i]);
	}

}

void Wizard::talk(std::string) {
	std::cout << getName() << " says: You shall not pass!" << std::endl;
}

}
