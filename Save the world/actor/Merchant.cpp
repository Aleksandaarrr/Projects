#include "Merchant.hpp"

namespace lab3 {

// Merchant konstruktor som tar in namn, och en lista med föremål
Merchant::Merchant(std::string name, std::vector<Item *> items) {
	setName(name);
	setHealth(100);
	setDmg(3);
	setDef(3);
	setFriendly(true);
	setType("Merchant");
	for(size_t i = 0; i < items.size(); i++) {
		addItem(items[i]);
	}
}

// Talk funktion 
void Merchant::talk(std::string say) {
	std::cout << "Welcome to knivbergsmarknad! What can I do for you, sir?" << std::endl;
}

// Skriver ut alla föremål som merchant innehåller
void Merchant::showItems() const {
	std::cout << "--- Items for sale ---" << std::endl;
	for(size_t i = 0; i < getInventory().size(); i++) {
		std::cout << getInventory()[i]->getType() << ": " << getInventory()[i]->getNameOfItem() << " " << getInventory()[i]->getPrice() << " Gold" << std::endl;
	}
}

// Vid köp anropas denna funktion
void Merchant::buyItem() const {
	std::cout << "Do you want to buy something else?"<< std::endl;
}

// Vid avslutat samtal anropas denna funktion
void Merchant::endTalk() const {
	std::cout << "Thank you, please come again!" << std::endl;
}

// Denna funktion anropas då spelaren väljer att lyssna på berättelsen om slottet
void Merchant::tellStory() const {
	std::string story = "Hundreds of years, this castle has been abandoned and nobody dared to investigate it. \nThis castle belonged to the King Alexander, \nwho managed to catch a furious dragon and lock it in the basement of the castle. \nI dare you to find it and kill it before it grows even bigger! \nPlease help us to survive!";
	for(size_t i = 0; i < story.length(); i++) {
		std::cout << story[i] << std::flush;
			usleep(40000);
	}
	std::cout << std::endl;
}

// Split funktion som splittar på mellanslag och returnerar en lista med strängar
std::vector<std::string> Merchant::splitInput(const std::string& line) {
    std::istringstream is(line);
    return std::vector<std::string>(std::istream_iterator<std::string>(is), std::istream_iterator<std::string>());
}

// Denna funktion anropas när spelaren pratar med merchant
void Merchant::talk2Merchant(Player * p, Environment * env) {
	talk(p->getName());
	std::cout << "1. Tell me about this place" << std::endl;
	std::cout << "2. Buy items" << std::endl;
	std::cout << "3. Nothing" << std::endl;
	std::string input;
	while(true) {
		std::getline(std::cin, input);
		std::vector<std::string> split = splitInput(input);

		if(input == "1") {
			tellStory();
			std::cout << "1. Tell me about this place, again" << std::endl;
			std::cout << "2. Buy items" << std::endl;
			std::cout << "3. Nothing" << std::endl;
		}
		else if(input == "2") {
			showItems();
			std::cout << "----------------------" << std::endl;
			std::cout << "HINT: buy *item* - to buy the item" << std::endl;
		}
		else if(input == "3") {
			endTalk();
			env->directions();
			break;
		}
		else if(split[0] == "buy") {
			std::string temp;
			if(split.size() > 2) {
				for(size_t i = 1; i < split.size()-1; i++) {
					temp += split[i] + " ";
				}
				temp += split[split.size()-1];
			}
			else {
				temp = split[1];
			}

			std::vector<Item *> items = getInventory();
			std::vector<Item *> playersItems = p->getInventory();

			Item * it = p->findItemInInventory("Gold");
			Misc * gold = static_cast<Misc *>(it);

			if(gold != NULL) {
				int money = gold->getValue();
				std::string it;

					Item * item = findItemInInventory(temp);
					Item * playerItem = p->findItemInInventory(temp);

					if(item != NULL) {
						if((playerItem != NULL) && (playerItem->getType() == "Weapon" || playerItem->getType() == "Armor")) {
							std::cout << "You already have this item in your inventory" << std::endl;
							showItems();
							std::cout << "----------------------" << std::endl;
							std::cout << "HINT: buy *item* - to buy the item" << std::endl;
						}
						else if(money >= item->getPrice()) {
							it = item->getNameOfItem();
							if(item->getType() == "Weapon") {
								Weapon * wea = new Weapon(*(static_cast<Weapon *>(item)));
								gold->setValue(money - item->getPrice());
								p->addItem(wea);
							}
							else if(item->getType() == "Potion") {
								Potion * port = new Potion(*(static_cast<Potion *>(item)));
								gold->setValue(money - item->getPrice());
								p->addItem(port);
							}
							else {
								Armor * arm = new Armor(*(static_cast<Armor *>(item)));
								gold->setValue(money - item->getPrice());
								p->addItem(arm);
							}
							std::cout << "You have bought " + it << std::endl;
							buyItem();
							std::string input2;
							std::getline(std::cin, input2);
							if(input2 == "yes") {
								showItems();
								std::cout << "----------------------" << std::endl;
								std::cout << "HINT: buy *item* - to buy the item" << std::endl;
							}
							else {
								std::cout << "1. Tell me about this place" << std::endl;
								std::cout << "2. Buy items" << std::endl;
								std::cout << "3. Nothing" << std::endl;
							}

						}
						else {
							std::cout << "You don't have enough gold" << std::endl;
							split.clear();
							std::cout << "1. Tell me about this place" << std::endl;
							std::cout << "2. Buy items" << std::endl;
							std::cout << "3. Nothing" << std::endl;
						}

				}
				else {
					std::cout << "Item was not found" << std::endl;
					showItems();
					std::cout << "----------------------" << std::endl;
					std::cout << "HINT: buy *item* - to buy the item" << std::endl;
				}
					split.clear();
			}
			else {
				std::cout << std::endl;
				std::cout << "You don't have enough gold" << std::endl;
				split.clear();
				std::cout << "1. Tell me about this place" << std::endl;
				std::cout << "2. Buy items" << std::endl;
				std::cout << "3. Nothing" << std::endl;
			}
		}
		split.clear();
	}
}

}
