#ifndef USABLE_HPP_
#define USABLE_HPP_

#include "Item.hpp"
#include "../actor/Player.hpp"

namespace lab3 {

class Usable : public Item {

	virtual void use(Player *) = 0;

};
}
#endif
