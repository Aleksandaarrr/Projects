#include "Cave.hpp"

namespace lab3 {

// Cave konstruktor som tar in beskrivning och namn på grottan
Cave::Cave(std::string description, std::string name) {
	setDescription(description);
	setName(name);
	setType("Cave");
}

// Funktion som kollar ifall spelaren har tänt lampan/facklan
// Om inte kommer spelaren missa mycket oftare p.g.a. dålig syn i mörkret
void Cave::hasTorch(Player * p){
	std::vector<Item *> inventory = p->getInventory();
	Item * torch = p->findItemInInventory("Torch");	
	if((torch == NULL) || (!torch->getEquipped())) {
		p->setMissValue(7);
		std::cout << "You are in a cave without a torch, which means you see badly and miss more often." << std::endl;
	} else{
		p->setMissValue(1);
	}
}
}