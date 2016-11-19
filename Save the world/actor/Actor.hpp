#ifndef ACTOR_HPP_
#define ACTOR_HPP_

#include <iostream>
#include <string>
#include "../items/Item.hpp"
#include <list>
#include <vector>
#include <math.h>

namespace lab3 {

class Actor {

private:
	// Variables
	std::string type = "";	
	std::string name = "";
	int maxHealth = 0;
	int defaultDef = 0;
	int defaultArmor = 0;
	int health = 0;
	std::vector<Item *> inventory;
	int damage = 0;
	int defence = 0;
	bool friendly = false;
	int livesLeft = 1;

public:

	Actor();
	virtual ~Actor();
	virtual int attack(std::string) = 0;
	virtual void talk(std::string) = 0;

	void setName(const std::string);
	std::string getName() const;

	void setMaxHealth(const int);
	int getMaxHealth() const;

	void setDefaultDef(const int);
	int getDefaultDef() const;

	void setDefaultArmor(const int);
	int getDefaultArmor() const;

	void setLives(const int);
	int getLives()const;
	void decrementLives();

	void setHealth(const int);
	int getHealth() const;

	void setType(const std::string);
	std::string getType() const;

	void setDef(const int);
	int getDef() const;

	void setDmg(const int);
	int getDmg() const;

	void setFriendly(const bool);
	bool getFriendly() const;

	void addItem(Item *);
	std::vector<Item *> getInventory() const;

	void calcDamage(int);
	bool isDead() const;
	void deleteItem(std::string&);
	void showInventory() const;
	void deleteInventory();
	Item * dropItem(std::string&);
	Item * findItemInInventory(std::string) const;

};

}
#endif
