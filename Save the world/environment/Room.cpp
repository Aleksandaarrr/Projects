#include "Room.hpp"

namespace lab3 {
// Room konstruktor som tar in beskrivning och namn på rummet
Room::Room(std::string description, std::string name) {
	setDescription(description);
	setName(name);
	setType("Room");
}
}