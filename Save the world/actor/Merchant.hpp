#ifndef MERCHANT_HPP_
#define MERCHANT_HPP_

#include "Human.hpp"
#include <string>
#include <unistd.h>
#include <sstream>
#include <iterator>
#include "Player.hpp"
#include "../environment/Environment.hpp"
#include "../items/Weapon.hpp"
#include "../items/Potion.hpp"
#include "../items/Armor.hpp"

namespace lab3 {

class Merchant : public Human {

public:
	Merchant(std::string, std::vector<Item *>);
	void talk(std::string);
	void showItems() const;
	void endTalk() const;
	void buyItem() const;
	void tellStory() const;
	void talk2Merchant(Player *, Environment *); 
	std::vector<std::string> splitInput(const std::string&);

};

}
#endif
