#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "Actor.hpp"
#include <string>

namespace lab3 {

class Player : public Actor {

private:
	bool isFighting = false;
	int missValue = 1;
public:
	Player(std::string, std::vector<Item *>);
	~Player();

	int attack(std::string);
	void talk(std::string);

	void setIsFighting(const bool);
	bool getIsFighting() const;
	void setMissValue(const int);
	void calcPlayerHealth();
	int getMissValue() const;


};
}
#endif
