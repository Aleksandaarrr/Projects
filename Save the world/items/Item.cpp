#include "Item.hpp"

namespace lab3 {

Item::Item() {}
Item::~Item() {}

// Lägg till vilken typ av föremålet det är och returnerar en sträng med typen
void Item::setType(const std::string t) {type = t;}
std::string Item::getType() const { return type; }

// Lägger till vikten av föremålet och returnerar vikten
void Item::setWeight(const double w) { weight = w; }
double Item::getWeight() const { return weight; }

// Lägger till priset på föremålet och returnerar priset
void Item::setPrice(const int p) { price = p; }
int Item::getPrice() const { return price; }

// Lägger till namnet på föremålet och returnerar namnet
void Item::setItemName( const std::string item) { itemName = item; }
std::string Item::getNameOfItem() const { return itemName; }

// Lägger till föremålets beskrivning och returnerar beskrivning
void Item::setDescription(const std::string desc) {description = desc; }
std::string Item::getDescription() const { return description; }

// Lägger till en föremålet används eller inte och returnerar ifall föremålet används
void Item::setEquipped(const bool b) { equipped = b; }
bool Item::getEquipped() const{ return equipped; }
}