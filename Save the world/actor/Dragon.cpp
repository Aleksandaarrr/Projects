#include "Dragon.hpp"

namespace lab3 {

// Dragon konstruktor som tar in namn och en lista med föremål
Dragon::Dragon(std::string name, std::vector<Item *> items) {
	setName(name);
	setHealth(100);
	setDmg(5);
	setDef(2);
	setFriendly(false);
	setType("Dragon");
	for(size_t i = 0; i < items.size(); i++) {
		addItem(items[i]);
	}
}

// Drakens pratfunktion
void Dragon::talk(std::string) {
	std::cout << getName() << ": WRAAAAAH!" << std::endl;
}
}
