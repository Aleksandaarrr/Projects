#include "Armor.hpp"

namespace lab3 {

// Armor konstruktor som tar in namn, beskrivning, armor, vikt och pris
Armor::Armor(std::string name, std::string desc, int def, int weight, int price) {
	setItemName(name);
	setDescription(desc);
	armor = def;
	setWeight(weight);
	setPrice(price);
	setType("Armor");
}

// Lägger till armor och returnerar armor
void Armor::setArmor(const int a) { armor = a; }
int Armor::getArmor() const { return armor; }

// Använder föremålet och sätter variabeln för användning till true
void Armor::use(Player * p) { 
	Item * temp = p->findItemInInventory(getNameOfItem());
	if(temp != NULL && !temp->getEquipped()) {
		p->setDef(p->getDef() + armor); 
		setEquipped(true);
		std::cout << "You have equipped " << getNameOfItem() << std::endl;
	}
	else {
		std::cout << getNameOfItem() << " is already being used" << std::endl;
	}
}

// Slutar använda ett föremål och sätter variabeln för användning till false
void Armor::unUseArmor(Player * p) { 
	p->setDef(p->getDef() - armor); 
	setEquipped(false);
	std::cout << "You have unequipped " << getNameOfItem() << std::endl;
}
}
