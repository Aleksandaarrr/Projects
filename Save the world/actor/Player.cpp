#include "Player.hpp"
#include <string>
#include <iostream>
#include <stdio.h>
#include <random>

namespace lab3 {

// Player konstruktor som tar in ett namn och en lista med föremål
Player::Player(std::string name, std::vector<Item *> items){
	setName(name);
	setHealth(100);
	setMaxHealth(100);
	setDefaultArmor(1);
	setDefaultDef(1);
	setDmg(1);
	setDef(1);
	setFriendly(true);
	setLives(3);
	setType("Player");
	for(size_t i = 0; i < items.size(); i++) {
		addItem(items[i]);
	}
	missValue = 1;
}

Player::~Player(){}

// Attack funktionen som är anpassad för spelaren
// Beroende på vilken ability som spelaren använder blir det olika mycket skada och utskrift
// Det finns även chans till critical hit som gör den dubbla skadan
// Skada slumpas mellan 0-9+spelarense skada
int Player::attack(std::string s) {
	std::cout << std::endl;

	std::random_device rdev;
	std::mt19937 rgen(rdev());
	std::uniform_int_distribution<int> idist(0,9+getDmg());
	
	int r = idist(rgen);

	if(r > missValue){
		// Critical strike
		if(r % 6 == 0) {
			std::cout << "You are in a rage mode dealing " << (r*2) << " critical damage!" << std::endl;
			return r*2;
		}
		else {
			std::cout << "You hit your enemy with " << r << " damage!" << std::endl;
		}
		return r;

	} else{
		std::cout << "You swing, but missed your enemy" << std::endl;
		return 0;
	}

}

// Spelarens pratfunktion
void Player::talk(std::string s) { std::cout << " You try talking to" << std::endl; }

// Lägger till ifall spelaren slåss och returnernar om spelare slåss eller inte
void Player::setIsFighting(const bool b) { isFighting = b; }
bool Player::getIsFighting() const { return isFighting; }

// Förändrar miss värdet beroende på om spelare är i en grotta utan fackla eller ej
// Returnerar också miss värdet
void Player::setMissValue(const int value){ missValue = value;}
int Player::getMissValue()const{ return missValue;}

// Beräknar spelarens nuvarande liv och skriver ut
void Player::calcPlayerHealth(){
	std::cout << "You have: " << getHealth() << " hp left" << std::endl;
}
}
