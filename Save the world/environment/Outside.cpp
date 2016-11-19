#include "Outside.hpp"
#include "../actor/Player.hpp"
#include <ctime>


namespace lab3 {
	
	Outside::Outside(std::string description, std::string name) {
		setDescription(description);
		setName(name);
		setType("Outside");
}

	void Outside::calcSeconds(){
		std::cout << "You are outside in the burning heat! Quickly move away from this place!" << std::endl;
		begin = clock();
		
	}
	
	void Outside::hurtPlayer(Player * player){
		end = clock();
		player->setHealth(player->getHealth() - 5);
		if(!player->isDead()) {
			std::cout << "The heat hurts you. You have: " << player->getHealth() << " hp left" << std::endl;
		}
	}
}
