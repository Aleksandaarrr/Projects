#include "Misc.hpp"

namespace lab3 {

// Misc konstruktor som tar in namn, beskrivning, värde och vikt
Misc::Misc(std::string name, std::string desc, int v, int weight) {
	setItemName(name);
	setDescription(desc);
	value = v;
	setWeight(weight);
	setType("Misc");
}

// Lägger till värde på föremålet och returnerar värdet
void Misc::setValue(const int v) { value = v; }
int Misc::getValue() const { return value; }
}