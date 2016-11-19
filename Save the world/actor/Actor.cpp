#include "Actor.hpp"
#include "../items/Armor.hpp"
#include "../items/Weapon.hpp"
#include "../items/Misc.hpp"

namespace lab3 {

Actor::Actor() {}
Actor::~Actor() {}

// Set-funktioner och get-funktioner för respektive instansvariabler
void Actor::setName(const std::string s) { name = s; }
std::string Actor::getName() const { return name; }

void Actor::setHealth(const int hp) { health = hp; }
int Actor::getHealth() const { return health; }

void Actor::setMaxHealth(const int hp) { maxHealth = hp; }
int Actor::getMaxHealth() const { return maxHealth; }

void Actor::setDefaultDef(const int def) { defaultDef = def; }
int Actor::getDefaultDef() const { return defaultDef; }

void Actor::setDefaultArmor(const int arm) { defaultArmor = arm; }
int Actor::getDefaultArmor() const { return defaultArmor; }

void Actor::setType(const std::string t) { type = t; }
std::string Actor::getType() const { return type; }

void Actor::setDef(const int def) { defence = def; }
int Actor::getDef() const { return defence; }

void Actor::setDmg(const int dmg) { damage = dmg; }
int Actor::getDmg() const { return damage; }

void Actor::setFriendly(const bool f) { friendly = f; }
bool Actor::getFriendly() const { return friendly; }

void Actor::addItem(Item * i) { inventory.push_back(i); }
std::vector<Item *> Actor::getInventory() const { return inventory; }

// Beräknar skadan på denna aktöre med hänsyn till hur mycket armor som aktören har
// Beräknade värdet tas sedan bort från nuvarande liv
void Actor::calcDamage(int atk) {
	setHealth(getHealth() - atk*(ceil(100-defence)/100));
}

// Kollar ifall aktören är död, alltså liv <= 0
bool Actor::isDead() const { return getHealth() <= 0; }

// Lägger till liv på aktören och returnerar liv
void Actor::setLives(const int i) { livesLeft = i; }
int Actor::getLives() const { return livesLeft; }

// Minskar liv med ett
void Actor::decrementLives() { livesLeft--; }

// Tar bort aktörens väska och allt innehåll
void Actor::deleteInventory() {
	for(size_t i = 0; i < inventory.size(); i++) {
		delete inventory[i];
	}
	inventory.clear();
}

// Tar bort ett specifikt föremål ur aktörens väska  
void Actor::deleteItem(std::string& item) {
	for(size_t i = 0; i < inventory.size(); i++) {
		if(inventory[i]->getNameOfItem() == item) {
			delete inventory[i];
			inventory.erase(inventory.begin() + i);
			break;
		}
	}
}

// Söker efter ett specifikt föremål i aktörens väska
Item * Actor::findItemInInventory(std::string item) const {
	for(size_t i = 0; i < inventory.size(); i++) {
		if(inventory[i]->getNameOfItem() == item) {
			Item * itm = inventory[i];
			return itm;
		}
	}
	return NULL;
}

// Skriver ut innehållet i aktörens väska
void Actor::showInventory() const {
	for(size_t i = 0; i < inventory.size(); i++) {
		if(inventory[i]->getNameOfItem() == "Gold") {
			std::cout << inventory[i]->getType() << ": " << static_cast<Misc*>(inventory[i])->getValue() << " " << inventory[i]->getNameOfItem() << std::endl;
		}
		else {
			if(inventory[i]->getType() == "Weapon") {
				if(inventory[i]->getEquipped())
					std::cout << inventory[i]->getType() << ": " << inventory[i]->getNameOfItem() << " [EQUIPPED]" << std::endl;
				else{
					std::cout << inventory[i]->getType() << ": " << inventory[i]->getNameOfItem() << std::endl;
				}	
			} 
			else if(inventory[i]->getType() == "Armor") {
				if(inventory[i]->getEquipped())
					std::cout << inventory[i]->getType() << ": " << inventory[i]->getNameOfItem() << " [EQUIPPED]" << std::endl;
				else{
					std::cout << inventory[i]->getType() << ": " << inventory[i]->getNameOfItem() << std::endl;
				}	
			}
			else if((inventory[i]->getNameOfItem() == "Torch") && (inventory[i]->getEquipped())) {
				std::cout << inventory[i]->getType() << ": " << inventory[i]->getNameOfItem() << " [TURNED ON]" << std::endl;
			}
			else {
				std::cout << inventory[i]->getType() << ": " << inventory[i]->getNameOfItem() << std::endl;
			}
		}
	}
}

// Lägger ner ett specifik föremål i det nuvarande rummet och tar bort från aktörens väska
Item * Actor::dropItem(std::string& item) {
	for(size_t i = 0; i < inventory.size(); i++) {
		if(inventory[i]->getNameOfItem() == item) {
			Item * itm = inventory[i];
			inventory.erase(inventory.begin()+i);
			return itm;
		}
	}
	return NULL;
}

}
