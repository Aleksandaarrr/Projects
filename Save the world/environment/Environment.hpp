#ifndef ENVIRONMENT_HPP_
#define ENVIRONMENT_HPP_

#include <string>
#include <vector>
#include "../actor/Actor.hpp"
#include "../items/Item.hpp"
#include "../items/Misc.hpp"

namespace lab3 {

class Environment {

private:
	std::vector<Actor *> actorsInRoom;
	std::vector<Item *> itemsInRoom;
	std::string type = "";
	std::string description = "";
	std::string name = "";
	Environment * northNeighbor = nullptr;
	Environment * southNeighbor = nullptr;
	Environment * eastNeighbor = nullptr;
	Environment * westNeighbor = nullptr;

public:
	void directions() const;
	virtual ~Environment();

	void setDescription(const std::string);
	std::string getDescription() const;

	void setName(const std::string);
	std::string getName() const;

	void setActorsInRoom(Actor *);
	std::vector<Actor *> getActorsInRoom()const;

	void deleteActor(Actor *);

	void setItemsInRoom(Item *);
	std::vector<Item *> getItemsInRoom() const;

	void setNorthNeighbor(Environment *);
	Environment * getNorthNeighbor() const;

	void setSouthNeighbor(Environment *);
	Environment * getSouthNeighbor() const;

	void setEastNeighbor(Environment *);
	Environment * getEastNeighbor() const;

	void setWestNeighbor(Environment *);
	Environment * getWestNeighbor() const;

	void showRoomsInventory() const;
	Item * pick_up(std::string);

	void setType(const std::string);
	std::string getType() const;

};
}
#endif
