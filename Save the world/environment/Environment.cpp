#include "Environment.hpp"
#include <vector>

namespace lab3 {

// En abstrakt klass i princip som Cave och Room ärver ifrån
Environment::~Environment() {}

// Lägger till beskrivning och returnerar beskrivning
void Environment::setDescription(const std::string desc) { description = desc; }
std::string Environment::getDescription() const { return description; }

// Lägger till aktörer i rummet och returnerar en lista med aktörer i rummet
void Environment::setActorsInRoom( Actor * a) { actorsInRoom.push_back(a); }
std::vector<Actor *> Environment::getActorsInRoom() const { return actorsInRoom; }

// Lägger till föremål i rummet och returnerar en lista med föremål i rummet
void Environment::setItemsInRoom( Item * i) { itemsInRoom.push_back(i); }
std::vector<Item *> Environment::getItemsInRoom()const { return itemsInRoom; }

// Lägger till vilken typ av rummet det är och returnerar typen
void Environment::setType(const std::string s){ type = s; }
std::string Environment::getType()const{ return type; }

// Tar bort en specifik aktör från rummet
void Environment::deleteActor(Actor * a) {
	for(size_t i = 0; i < actorsInRoom.size(); i++) {
		if(actorsInRoom[i]->getName() == a->getName()) {
			delete actorsInRoom[i];
			actorsInRoom.erase(actorsInRoom.begin() + i);
		}
	}
}

// Skriver ut i vilken riktning man kan gå från rummet, alla grannar
void Environment::directions() const{
	std::cout << "You can go";
	if(getNorthNeighbor())
		std::cout << " north";
	if(getSouthNeighbor())
		std::cout << " south";
	if(getEastNeighbor())
		std::cout << " east";
	if(getWestNeighbor())
		std::cout << " west";
	std::cout << std::endl;
}

// Lägger till namn och returnerar namn
void Environment::setName(const std::string n) { name = n; }
std::string Environment::getName() const { return name; }

// Lägger till granne som är norr om rummet och returnerar grannen
void Environment::setNorthNeighbor( Environment * n) { northNeighbor = n; }
Environment * Environment::getNorthNeighbor()const{ return northNeighbor; }

// Lägger till granne som är söder om rummet och returnerar grannen
void Environment::setSouthNeighbor( Environment * s) { southNeighbor = s; }
Environment * Environment::getSouthNeighbor()const { return southNeighbor; }

// Lägger till granne som är öst om rummet och returnerar grannen
void Environment::setEastNeighbor( Environment * e) { eastNeighbor = e; }
Environment * Environment::getEastNeighbor()const { return eastNeighbor; }

// Lägger till granne som är väst om rummet och returnerar grannen
void Environment::setWestNeighbor( Environment * w) { westNeighbor = w; }
Environment * Environment::getWestNeighbor()const { return westNeighbor; }

// Skriver ut vilke föremål som finns i rummet
void Environment::showRoomsInventory() const {
	for(size_t i = 0; i < itemsInRoom.size(); i++) {
		if(itemsInRoom[i]->getNameOfItem() == "Gold") {
			std::cout << itemsInRoom[i]->getType() << ": " << static_cast<Misc *>(itemsInRoom[i])->getValue() << " " << itemsInRoom[i]->getNameOfItem() << std::endl;
		}
		else {
			std::cout << itemsInRoom[i]->getType() << ": " << itemsInRoom[i]->getNameOfItem() << std::endl;
		}
	}
}

// Funktion som anropas för att plocka upp ett föremål från ett rum
Item * Environment::pick_up(std::string item) {
	for(size_t i = 0; i < itemsInRoom.size(); i++) {
		if(itemsInRoom[i]->getNameOfItem() == item) {
			Item * itm = itemsInRoom[i];
			itemsInRoom.erase(itemsInRoom.begin()+i);
			return itm;
		}
	}
	return NULL;
}
}
