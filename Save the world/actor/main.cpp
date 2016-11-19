#include "Actor.hpp"
#include "Player.hpp"
#include "Creature.hpp"
#include "Dragon.hpp"
#include "Warrior.hpp"
#include "Wizard.hpp"
#include "Merchant.hpp"

#include "../environment/Environment.hpp"
#include "../environment/Room.hpp"
#include "../environment/Cave.hpp"
#include "../environment/Outside.hpp"


#include "../items/Item.hpp"
#include "../items/Weapon.hpp"
#include "../items/Potion.hpp"
#include "../items/Armor.hpp"
#include "../items/Misc.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <algorithm>
#include <map>
#include <iterator>

using namespace lab3;
struct CommandHandler;

typedef void (CommandHandler::*MFP_1)();
typedef void (CommandHandler::*MFP_2)(std::string);

// En struct behandlar alla instruktioner och det sker via funktionsanrop
struct CommandHandler {

    std::map<std::string, MFP_1> _funcmap;
    std::map<std::string, MFP_2> _funcmapargs;
    
    Player * _player = nullptr;
    Environment * _env = nullptr;
    std::vector<Environment *> rooms;
    bool skipOnLoad = false;
    bool exitGame = false;
    bool shutdown = false;

public:
	CommandHandler();
    void Call(const std::string&);
    void Call2(const std::string&, const std::string&);
    void onExit();
    int getLives();
    void setup();
    Player * getPlayer();
    Environment * getEnv();
    void addEnvironment(Environment*);
    Environment * getRespawn();
    std::string intro();
    bool getExit();
    void look();
    bool getExitGame();

private:
    void addPlayer(Player*&);
    void addRooms(std::vector<Environment*>);
    void go(std::string);
    void attack(std::string);
    void who();
    void help();
    void show();
    void stats();
    void drop(std::string);
    void use(std::string);
    void pickup(std::string);
    void save(std::string);
    void about(std::string);
    void deleteItem(std::string);
    void unUse(std::string);
    void talk(std::string);
    void load(std::string);
	void printItems2File(std::vector<Item *>, std::ofstream&, std::string&);
    void saveGame(std::vector<Environment*>, Player *, std::string&, Environment *);
    Actor * checkIfActorExist(std::vector<Actor *>, std::string&);
	void enemiesAttack(Player *, std::vector<Actor*>);
	void getEnemiesHealth(std::vector<Actor*>);
	bool loadGame(std::vector<Environment * > *, Player *&, std::string&, Environment *&);
	std::vector<std::string> splitLoad(std::string&);
	void setSkipOnLoad(bool);
	void setExit(bool);
	void exitGameNow();
	void setExitGame(bool);

};

// Avslutar spelet
bool CommandHandler::getExitGame() { return shutdown; }
void CommandHandler::setExitGame(bool b) { shutdown = b; }

void CommandHandler::exitGameNow() {
	onExit();
	setExitGame(true);
}

// Lägger till ifall spelet ska avslutas eller ej
void CommandHandler::setExit(bool b) { exitGame = b; }
bool CommandHandler::getExit() { return exitGame; }

// En hjälpvariabel som används vid load game i när spelet börjar
void CommandHandler::setSkipOnLoad(bool b) {
	skipOnLoad = b;
}

// Lägger till spelaren till structen och returnerar spelaren
void CommandHandler::addPlayer(Player*& player) { _player = player; }
Player * CommandHandler::getPlayer() { return _player; }

// Returnerar nuvarande miljön
Environment * CommandHandler::getEnv() { return _env; }
Environment * CommandHandler::getRespawn() { return rooms[0]; }

// Returnerar spelarens liv
int CommandHandler::getLives() { return _player->getLives(); }

// Lägger till den nuvarande miljöpekaren
void CommandHandler::addEnvironment(Environment * env) { _env = env; }

// Lägger till listan med alla rum
void CommandHandler::addRooms(std::vector<Environment*> r) { rooms = r; }

// En call funktion som anropas då instruktonen består endast av ett ord, t.ex. stats, who, look, help, exit, etc.
void CommandHandler::Call(const std::string& s){
    if (_funcmap.count(s)>0){
        MFP_1 fp = _funcmap[s];
        (this->*fp)();
    }else{
        std::cout << "Invalid input" << std::endl;
    }
}
// En call2 funktion som anropas då instruktonen består av två ord, t.ex. stats, go north, pick_up Sword, etc.
void CommandHandler::Call2(const std::string& s,const std::string& arg){
    if (_funcmapargs.count(s)>0){
        MFP_2 fp = _funcmapargs[s];
        (this->*fp)(arg);
    }else{
        std::cout << "Invalid input" << std::endl;
    }
}

// En funktion som skriver ut alla aktörer som finns i det nuvarande rummet
void CommandHandler::who() {
	std::vector<Actor *> actors = _env->getActorsInRoom();
		if(actors.size() == 0)
			std::cout << "You are the only person in this room" << std::endl;
		else {
			for(size_t i = 0; i < actors.size(); i++){
				std::cout << actors[i]->getType() << ": " << actors[i]->getName() << std::endl;
			}
		}
}

// Go funktion som ändrar miljövariablen till grannen som befinner sig i den
// riktningen som spelaren väljer att förflytta sig (om grannen finns)
void CommandHandler::go(std::string direction) { 
	if(direction == "north" && !_player->getIsFighting()) {
		if(_env->getNorthNeighbor()) {

			if((_env->getNorthNeighbor())->getName() == "Hall") {

				if((_env->getNorthNeighbor())->getActorsInRoom().size() == 0) {
					Misc * g = new Misc("Gold", "With gold you can buy items from the merchants!", 3, 1);
					Misc * g2 = new Misc("Gold", "With gold you can buy items from the merchants!", 4, 1);
					std::vector<Item *> war1;
					war1.push_back(g);
					std::vector<Item *> war2;
					war2.push_back(g2);

					Warrior * w1 = new Warrior("Skeleton1", war1);
					Warrior * w2 = new Warrior("Skeleton2", war2);
					(_env->getNorthNeighbor())->setActorsInRoom(w1);
					(_env->getNorthNeighbor())->setActorsInRoom(w2);
				}
			}
			if(_env->getNorthNeighbor()->getType() == "Outside"){
				Outside * outside = static_cast<Outside *>(_env->getNorthNeighbor());
				outside->calcSeconds();
				//outside->hurtPlayer(_player);
			}

			if(_env->getName() == "Hall") {
				std::cout << "You are trying to open the door, but it's locked!" << std::endl;
				std::vector<Item *> items = _player->getInventory();
				bool gotKey = false;
				for(size_t i = 0; i < items.size(); i++) {
					if(items[i]->getNameOfItem() == "Magic key") {
						gotKey = true;
						break;
					}
				}
				if(gotKey) {
					std::cout << "You use your Magic key to unlock the door!" << std::endl;
					_env = _env->getNorthNeighbor();
					std::cout << std::endl;
					std::cout << _env->getDescription() << std::endl;
					_env->directions();
					std::vector<Actor *> actors = _env->getActorsInRoom();
					getEnemiesHealth(actors);
					enemiesAttack(_player, actors);
				}
				else {
					std::cout << "You don't have the Magic key to unlock it!" << std::endl;
				}
			}
			else {
				_env = _env->getNorthNeighbor();
				std::cout << std::endl;
				std::cout << _env->getDescription() << std::endl;
				_env->directions();
				std::vector<Actor *> actors = _env->getActorsInRoom();
				getEnemiesHealth(actors);
				enemiesAttack(_player, actors);
			}

		} else {
			std::cout << "You cannot go " << direction << std::endl;
		}
	}
	else if(direction == "south" && !_player->getIsFighting()) {

		if(_env->getSouthNeighbor()) {

			if((_env->getSouthNeighbor())->getName() == "Hall") {

				if((_env->getSouthNeighbor())->getActorsInRoom().size() == 0) {
					Misc * g = new Misc("Gold", "With gold you can buy items from the merchants!", 3, 1);
					Misc * g2 = new Misc("Gold", "With gold you can buy items from the merchants!", 4, 1);
					std::vector<Item *> war1;
					war1.push_back(g);
					std::vector<Item *> war2;
					war2.push_back(g2);

					Warrior * w1 = new Warrior("Skeleton1", war1);
					Warrior * w2 = new Warrior("Skeleton2", war2);
					(_env->getSouthNeighbor())->setActorsInRoom(w1);
					(_env->getSouthNeighbor())->setActorsInRoom(w2);
				}
			}
			_env = _env->getSouthNeighbor();
			std::cout << std::endl;
			std::cout << _env->getDescription() << std::endl;
			_env->directions();
			std::vector<Actor *> actors = _env->getActorsInRoom();
			getEnemiesHealth(actors);
			enemiesAttack(_player, actors);

		} else {
			std::cout << "You cannot go " << direction << std::endl;
		}
	}
	else if(direction == "east" && !_player->getIsFighting()) {
		if(_env->getEastNeighbor()) {
			if(_env->getEastNeighbor()->getType() == "Outside"){
				Outside * outside = static_cast<Outside *>(_env->getEastNeighbor());
				outside->calcSeconds();
			}
				
			if(_env->getName() == "BrokenBridge2") {
				std::cout << "You are ready to run! You are running... running... and JUMP! You jumped over the broken bridge!" << std::endl;
				_env = _env->getEastNeighbor();
				std::cout << std::endl;
				std::cout << _env->getDescription() << std::endl;
				_env->directions();
				std::vector<Actor *> actors = _env->getActorsInRoom();
				getEnemiesHealth(actors);
				enemiesAttack(_player, actors);
			}
			else {
				if(_env->getType() == "Cave" && (_env->getEastNeighbor())->getType() == "Room") {
					_player->setMissValue(1);
				}
				_env = _env->getEastNeighbor();
				std::cout << std::endl;
				std::cout << _env->getDescription() << std::endl;
				_env->directions();
				std::vector<Actor *> actors = _env->getActorsInRoom();
				getEnemiesHealth(actors);
				enemiesAttack(_player, actors);
			}

		} else {
			std::cout << "You cannot go " << direction << std::endl;
		}
	}
	else if(direction == "west" && !_player->getIsFighting()) {
		if(_env->getWestNeighbor()) {					
			if(_env->getName() == "BrokenBridge1") {
				// Without shoes you can't jump over the bridge
				Item * boots = _player->findItemInInventory("Travel boots");
				if(boots && (boots->getEquipped())) {
					std::cout << "You are ready to run! You are running... running... and JUMP! You jumped over the broken bridge!" << std::endl;
					_env = _env->getWestNeighbor();
					std::cout << std::endl;
					std::cout << _env->getDescription() << std::endl;
					_env->directions();
					std::vector<Actor *> actors = _env->getActorsInRoom();
					getEnemiesHealth(actors);
					enemiesAttack(_player, actors);
				}
				else {
					std::cout << "You are ready to run! You are running... running... and JUMP! Oh nooo, you didn't jump long enough!" << std::endl;
					_player->decrementLives();
					_env = rooms[0];
					std::cout << "You have respawned in the " + rooms[0]->getName() + "!" << std::endl;
					_player->setHealth(_player->getMaxHealth());
					look();
				}
			}
			else {
				_env = _env->getWestNeighbor();
				std::cout << std::endl;
				std::cout << _env->getDescription() << std::endl;
				_env->directions();
				std::vector<Actor *> actors = _env->getActorsInRoom();
				getEnemiesHealth(actors);
				enemiesAttack(_player, actors);
			}

		} else {
			std::cout << "You cannot go " << direction << std::endl;
		}
	}
	else {
		if(_player->getIsFighting()) {
			std::cout << "You cannot run away from a fight" << std::endl;
		}
		else {
			std::cout << "That direction does not exist" << std::endl;
		}
	}
	if(_env->getType() == "Cave"){
		Cave * cave = static_cast<Cave *>(_env);
		cave->hasTorch(_player);
	}
}

// Konstruktor i structen
CommandHandler::CommandHandler() {

	// Initialiserar två maps, med de instruktioner som finns i spelet
	// så att respektive instruktion anropar sin funktion via funktionspekaren

    //kommandon med inga argument
    _funcmap["look"] = &CommandHandler::look;
    _funcmap["who"] = &CommandHandler::who;
    _funcmap["help"] = &CommandHandler::help;
    _funcmap["show"] = &CommandHandler::show;
    _funcmap["stats"] = &CommandHandler::stats;
    _funcmap["exit"] = &CommandHandler::exitGameNow;


    // Kommandon med fler argument tex go north go back
    _funcmapargs["go"] = &CommandHandler::go;
    _funcmapargs["attack"] = &CommandHandler::attack;
    _funcmapargs["drop"] = &CommandHandler::drop;
    _funcmapargs["use"] = &CommandHandler::use;
    _funcmapargs["pick_up"] = &CommandHandler::pickup;
    _funcmapargs["save"] = &CommandHandler::save;
    _funcmapargs["about"] = &CommandHandler::about;
    _funcmapargs["delete"] = &CommandHandler::deleteItem;
    _funcmapargs["unUse"] = &CommandHandler::unUse;
    _funcmapargs["talk"] = &CommandHandler::talk;
    _funcmapargs["load"] = &CommandHandler::load;

}

// Skriver ut nuvarande rummets beskrivning samt åt vilka håll spelaren kan gå
void CommandHandler::look() {
	std::cout << _env->getDescription() << std::endl;
	_env->directions();
}

// Skriver ut alla föremäl som spelaren innehåller samt föremål i det nuvarande rummet
void CommandHandler::show() {
	std::cout << "--- Inventory ---" << std::endl;
	_player->showInventory();
	std::cout << "--- Items in this room ---" << std::endl;
	_env->showRoomsInventory();
	std::cout << "---------------------" << std::endl;
	std::cout << std::endl;
}

// Skriver ut spelarens stats, hur mycket liv, hur många försök kvar, hur mycket skada och armor, etc.
void CommandHandler::stats() {
	std::cout << "--- Stats ---" << std::endl;
	std::cout << "Health: " << _player->getHealth() << std::endl;
	std::cout << "Attack: " << _player->getDmg() << std::endl;
	std::cout << "Armor: " << _player->getDef() << std::endl;
	std::cout << "Lives left: " << _player->getLives() << std::endl;
	std::cout << "-------------" << std::endl;
	std::cout << std::endl;
}

// Drop funktionen lägger ner ett specifikt föremål i det nuvarande rummet
void CommandHandler::drop(std::string itemName) {
	Item * item = _player->dropItem(itemName);
	if(item != NULL) {
		std::cout << "You dropped " << itemName << std::endl;
		_env->setItemsInRoom(item);
	}	
	else {
		std::cout << "Item was not found" << std::endl;
	}
	std::cout << std::endl;
}

// Help funktionen skriver ut alla möjliga instruktioner och vad de innebär
void CommandHandler::help() {
	std::cout << "Here are the following commands you can use:" << std::endl;
	std::cout << "who - lists all the people in the room." << std::endl;
	std::cout << "go *direction* - go in that direction." << std::endl;
	std::cout << "attack *name* - fight an enemy." << std::endl;
	std::cout << "talk *name* - talk to a person." << std::endl;
	std::cout << "show - shows player's inventory and room's inventory." << std::endl;
	std::cout << "stats - shows player's stats." << std::endl;
	std::cout << "drop *item* - drop the specified item." << std::endl;
	std::cout << "pick_up *item* - pick up item from the room." << std::endl;
	std::cout << "use *item* - use the specific item." << std::endl;
	std::cout << "unUse *item* - unUse the specific item." << std::endl;
	std::cout << "about *item* - get more information about the item." << std::endl;
	std::cout << "delete *item* - delete the item from the game." << std::endl;
	std::cout << "look - shows all directions in the current room." << std::endl;
	std::cout << "save - saves the current progress." << std::endl;
	std::cout << "load *filename* - loads the game from file." << std::endl;
	std::cout << "exit - exit the game." << std::endl;
}

// Denna funktion gör så att aktörer som inte är friendly med spelaren attackerar spelaren
// då hen går in i deras rum, slagen sker i tur och ordning
void CommandHandler::enemiesAttack(Player * player, std::vector<Actor*> actors){
	for(size_t i = 0; i < actors.size(); i++){
		if(!actors[i]->getFriendly()) {
			actors[i]->talk("");
			int damage = actors[i]->attack(player->getName());
			player->calcDamage(damage);
			if(player->isDead() && _env->getName() != "Lobby") {
				std::cout << "You have been killed by " << actors[i]->getName() << "!" << std::endl;
				_player->decrementLives();
				std::cout << "You have respawned in the " + rooms[0]->getName() + "!" << std::endl;
				_env = rooms[0];
				std::cout << _env->getDescription() << std::endl;
				_env->directions();
				player->setIsFighting(false);
				player->setHealth(player->getMaxHealth());
				break;
			}
			else {
				player->setIsFighting(true);
			}
		}
	}
	if(player->getIsFighting()) {
		player->calcPlayerHealth();
	}
}

// Skriver ut aktörernas liv, alltså de som inte är friendly
void CommandHandler::getEnemiesHealth(std::vector<Actor*> actors){
	for(size_t i = 0; i < actors.size(); i++){
		if(!actors[i]->getFriendly()){
			std::cout << actors[i]->getName() << " has: " << actors[i]->getHealth() << " hp left" << std::endl;
		}
	}
}

// Kollar ifall en specifik aktör finns i rummet
Actor * CommandHandler::checkIfActorExist(std::vector<Actor *> actorsInRoom, std::string& enemy){
	for(size_t i = 0; i < actorsInRoom.size(); i++){
		if(actorsInRoom[i]->getName() == enemy){
			return actorsInRoom[i];
		}
	}
	return nullptr;
}

// Use funktionen används för alla föremål och beroende på vilket föremål det är 
// utförs olika funktioner och utskrifter
void CommandHandler::use(std::string itemName) {
	Item * item = _player->findItemInInventory(itemName);
	if(item != NULL) {
		if(item->getNameOfItem() == "Health potion") {
			static_cast<Potion *>(item)->use(_player);
			std::cout << "You have used the " << item->getNameOfItem() << " and now you have " << _player->getHealth() << " hp!" << std::endl;
			_player->deleteItem(itemName);
		}
		else if(item->getType() == "Weapon") {
			std::vector<Item *> inventory = _player->getInventory();
			//////////////////////
			// LAMBDA FUNKTION //
			////////////////////
			auto setToFalse = [&](){ for(size_t i = 0; i < inventory.size(); i++){ if((inventory[i]->getType() == "Weapon") && (inventory[i]->getEquipped())) {static_cast<Weapon *>(inventory[i])->unUseWeapon(_player);}}};
			setToFalse();
			//////////////////
			Weapon * weapon = static_cast<Weapon *>(item);
			weapon->use(_player);
			std::cout << "You have equipped " << item->getNameOfItem() << std::endl;

		}
		else if(item->getType() == "Armor") {
			Armor * armor = static_cast<Armor *>(item);
			armor->use(_player);

		}
		else if(item->getNameOfItem() == "Torch") {
			item->setEquipped(true);
			std::cout << "Torch is lit" << std::endl;
		}
	}
	else {
		std::cout << "Item was not found in your inventory" << std::endl;
	}
	std::cout << std::endl;
}

// Funktionen anropas då spelaren väljer att plocka upp ett föremål från rummet
void CommandHandler::pickup(std::string itemName) {
	Item * item = _env->pick_up(itemName);
	if(item != NULL) {
		std::cout << "You picked up " << itemName << std::endl;
		_player->addItem(item);
	}	
	else {
		std::cout << "Item was not found" << std::endl;
	}
	std::cout << std::endl;
}

// Attack funktionen används då spelaren väljer att attackera en aktör som inte är friendly
void CommandHandler::attack(std::string act) {
	Actor * enemy = checkIfActorExist(_env->getActorsInRoom(), act);
	std::vector<Actor *> actors = _env->getActorsInRoom();
	if(enemy &&(!enemy->getFriendly())) {
		int dmg = _player->attack(act);
		enemy->calcDamage(dmg);

		if(enemy->isDead() && enemy->getType() == "Dragon") {
			std::cout << "You have killed the " << enemy->getName() << "!" << std::endl;
			std::cout << "Congratulations! You have found the Dragon and killed it! You didn't let it grow big enough to kill everyone!" << std::endl;
			std::cout << "Thank you for playing!" << std::endl;
			exitGameNow();
	
		}
		else if(enemy->isDead()) {
			std::cout << "You have killed the " << enemy->getName() << "!" << std::endl;
			std::cout << "--- " << enemy->getName() << "'s inventory ---"<< std::endl;
			enemy->showInventory();
			std::cout << "-----------------------------" << std::endl;
			std::cout << "Do you want to loot the " << enemy->getName() << "?" << std::endl;
			std::string in;
			std::getline(std::cin, in);
			if(in == "yes") {
				std::vector<Item *> enemyItems = enemy->getInventory();
				std::vector<Item *> playerItems = _player->getInventory();
				for(size_t i = 0; i < enemyItems.size(); i++) {
					bool skip = false;
					Item * playerItem = _player->findItemInInventory("Gold");
					if((playerItem != NULL) &&(enemyItems[i]->getNameOfItem() == "Gold")) {
						int value = static_cast<Misc*>(playerItem)->getValue() + static_cast<Misc*>(enemyItems[i])->getValue();
						static_cast<Misc*>(playerItem)->setValue(value);
						delete enemyItems[i];
						skip = true;
					}
					if(!skip) {
						_player->addItem(enemy->getInventory()[i]);
					}
				}
				enemy->getInventory().clear();
				_env->deleteActor(enemy);
				std::cout << "You have looted!" << std::endl;
			} 
			else {
				enemy->deleteInventory();
				_env->deleteActor(enemy);
			}
			std::vector<Actor *> actorsRemaining = _env->getActorsInRoom();
			int counter = 0;
			// Check if the remaining actors are only friendly or there are no actors in room.
			for(size_t i = 0; i < actorsRemaining.size(); i++){
				if(actorsRemaining[i]->getFriendly())
					counter++;
			}
			if(counter == actorsRemaining.size() || actorsRemaining.size() == (unsigned)0){
				_player->setIsFighting(false);
				std::cout << "You have killed all enemies in this room. \n" << std::endl;
				_env->directions();
			}
			else{
				enemiesAttack(_player, actorsRemaining);
				getEnemiesHealth(actorsRemaining);
			}

		} else {
			getEnemiesHealth(actors);
			enemiesAttack(_player, actors);
		}

	} else {
		if(enemy && enemy->getFriendly()) {
			std::cout << "You cannot attack friendly actors" << std::endl;
		}
		else {
			std::cout << "That enemy does not exist here" << std::endl;
		}
	}
	std::cout << std::endl;
}

// Save funktonen som anropar saveGame som utför hela jobbet
void CommandHandler::save(std::string name) {
	if(name != "" && (!_player->getIsFighting())) {
		saveGame(rooms, _player, name, _env);
	}
	else if(_player->getIsFighting()) {
		std::cout << "You cannot save while fighting" << std::endl;
	} else{
		std::cout << "You must type save *name*" << std::endl;
	}
}

// SaveGame funktionen som sparar spelets tillstånd till en fil
// rad 1: består av det rummet som spelaren börjar i samt där man börjar vid respawn
// de kommande raderna är vad rummet innehåller, t.ex. kommer först alla föremål
// och sedan den aktör som ska innehålla alla dessa föremål
// Efter alla rum kommer hur rummen är kopplade, alltså vilka som gränsar med vilka
// Sist skrivs ut spelarens väska, liv, etc.
void CommandHandler::saveGame(std::vector<Environment*> rooms, Player * p, std::string& filename, Environment * env) {
	std::ofstream myfile;
  	myfile.open (filename + ".txt");

	for(size_t i = 0; i < rooms.size(); i++) {
		std::vector<Actor *> tempActors = rooms[i]->getActorsInRoom();
		std::vector<Item *> tempItems = rooms[i]->getItemsInRoom();

		if(rooms[i]->getType() == "Room") {
			myfile << "Room:" + rooms[i]->getDescription() + ":" + rooms[i]->getName() + ":" + "\n";
		}
		else if(rooms[i]->getType() == "Outside") {
			myfile << "Outside:" + rooms[i]->getDescription() + ":" + rooms[i]->getName() + ":" + "\n";
		}
		else {
			myfile << "Cave:" + rooms[i]->getDescription() + ":" + rooms[i]->getName() + ":" + "\n";
		}
		std::string tempS2 = "Env";
		printItems2File(tempItems, myfile, tempS2);
		std::string tempS3 = "Actor";
		for(size_t j = 0; j < tempActors.size(); j++) {
			std::vector<Item *> actorsItems = tempActors[j]->getInventory();
			printItems2File(actorsItems, myfile, tempS3);
			myfile << tempActors[j]->getType() + ":" + tempActors[j]->getName() + ":" + "\n";
		}
	}

	for(size_t i = 0; i < rooms.size(); i++) {
		myfile << "=:" + rooms[i]->getName() + ":";

		if(rooms[i]->getNorthNeighbor()) {
			myfile << "north:"<< (rooms[i]->getNorthNeighbor())->getName() + ":";
		}
		if(rooms[i]->getSouthNeighbor()) {
			myfile << "south:" << (rooms[i]->getSouthNeighbor())->getName() + ":";
		}
		if(rooms[i]->getEastNeighbor()) {
			myfile << "east:" << (rooms[i]->getEastNeighbor())->getName() + ":";
		}
		if(rooms[i]->getWestNeighbor()) {
			myfile << "west:" << (rooms[i]->getWestNeighbor())->getName() + ":";
		}
		myfile << "\n";
	}

	std::vector<Item *> temp = p->getInventory();
	std::string tempS = "Actor";
	printItems2File(temp, myfile, tempS);

	myfile << p->getType() + ":" + p->getName() + ":" + env->getName() + ":" + std::to_string(p->getHealth()) + ":" + std::to_string(p->getLives()) + ":" + "\n";

	myfile.flush();
	myfile.close();
	std::cout << "Game progress has been saved to " + filename + ".txt" << std::endl;
}

// Hjälpfunktion till saveGame då den skriver ut till fil specifik information som är nödvändig
// för respektive klass
void CommandHandler::printItems2File(std::vector<Item *> tempItems, std::ofstream& myfile, std::string& type) {
	for(size_t j = 0; j < tempItems.size(); j++) {
		if(tempItems[j]->getType() == "Armor") {
			myfile << tempItems[j]->getType() + ":" + tempItems[j]->getNameOfItem() + ":" + tempItems[j]->getDescription() + ":" + std::to_string(static_cast<Armor *>(tempItems[j])->getArmor()) + ":" + std::to_string((int)tempItems[j]->getWeight()) + ":" + std::to_string(tempItems[j]->getPrice()) + ":" + std::to_string(tempItems[j]->getEquipped()) + ":" + type + ":" + "\n";
		}
		else if (tempItems[j]->getType() == "Weapon") {
			myfile << tempItems[j]->getType() + ":" + tempItems[j]->getNameOfItem() + ":" + tempItems[j]->getDescription() + ":" + std::to_string(static_cast<Weapon *>(tempItems[j])->getSpeed()) + ":" + std::to_string(static_cast<Weapon *>(tempItems[j])->getDamage()) + ":" + std::to_string((int)tempItems[j]->getWeight()) + ":" + std::to_string(tempItems[j]->getPrice()) + ":" + std::to_string(tempItems[j]->getEquipped()) + ":" + type + ":" + "\n";
		}
		else if (tempItems[j]->getType() == "Potion") {
			myfile << tempItems[j]->getType() + ":" + tempItems[j]->getNameOfItem() + ":" + tempItems[j]->getDescription() + ":" + std::to_string(static_cast<Potion *>(tempItems[j])->getHealthRegen()) + ":" + std::to_string((int)tempItems[j]->getWeight()) + ":" + std::to_string(tempItems[j]->getPrice()) + ":" + type + ":" + "\n";
		}
		else if (tempItems[j]->getType() == "Misc") {
			myfile << tempItems[j]->getType() + ":" + tempItems[j]->getNameOfItem() + ":" + tempItems[j]->getDescription() + ":" + std::to_string(static_cast<Misc *>(tempItems[j])->getValue()) + ":" + std::to_string((int)tempItems[j]->getWeight()) + ":" + type + ":" + "\n";
		}
	}
}

// Funktionen skriver ut föremålets beskrivning
void CommandHandler::about(std::string itemName) {
	Item * item = _player->findItemInInventory(itemName);
	if(item != NULL) {
		std::cout << item->getType() << ": " << item->getDescription() << std::endl;
	}
	else {
		std::cout << "Item was not found in your inventory" << std::endl;
	}
	std::cout << std::endl;
}

// Funktionen tar bort ett föremål ur spelet, alltså för alltid
void CommandHandler::deleteItem(std::string itemName) {
	Item * item = _player->findItemInInventory(itemName);
	if(item != NULL) {
		if(item->getEquipped() && item->getType() == "Armor") {
			static_cast<Armor *>(item)->unUseArmor(_player);
		}
		else if((item->getEquipped() && item->getType() == "Weapon") ) {
			static_cast<Weapon *>(item)->unUseWeapon(_player);
		}
		std::cout << item->getNameOfItem() << " was deleted" << std::endl;
		_player->deleteItem(itemName);
	}
	else {
		std::cout << "Item was not found in your inventory" << std::endl;
	}
}

// Motsatsen till use funktionen, de saker som har används, används inte
// längre och equipped variablen sätts till false
void CommandHandler::unUse(std::string itemName) {
	Item * item = _player->findItemInInventory(itemName);
	if(item != NULL && item->getEquipped()) {
		if(item->getType() == "Armor") {
			static_cast<Armor *>(item)->unUseArmor(_player);
		}
		else if(item->getType() == "Weapon") {
			static_cast<Weapon *>(item)->unUseWeapon(_player);
		}
		else {
			if(item->getNameOfItem() == "Torch") {
				std::cout << "Torch is lit off" << std::endl;
			}
			item->setEquipped(false);
		}
	}
	else {
		std::cout << "Item is not being used" << std::endl;
	}
}

// Talk funktionen som anropas då spelaren väljer att prata med en aktör
void CommandHandler::talk(std::string actor) {
	Actor * act = checkIfActorExist(_env->getActorsInRoom(), actor);
	if(act &&(act->getType() == "Merchant")) {
		static_cast<Merchant *>(act)->talk2Merchant(_player, _env);
	}
	else {
		std::cout << "That actor does not exist here or it won't talk to you" << std::endl;
	}
	std::cout << std::endl;
}

// Load funktionen anropar loadGame som utför hela inläsningen från fil
void CommandHandler::load(std::string name) {
	if(loadGame(&rooms, _player, name, _env)) {
		std::cout << _env->getDescription() << std::endl;
		_env->directions();
	}
}

// Motsatsen till saveGame, i samma ordning läser in från fil och skapar respektive objekt
// Alltså uppfyller denna och saveGame 3.2 och 3.3
bool CommandHandler::loadGame(std::vector<Environment * > * rooms, Player *& p, std::string& filename, Environment *& env) {
	std::ifstream myfile(filename);
	if (myfile.is_open() && myfile.good()) {
		std::cout << "File " + filename + " was found and the game is loading..." << std::endl;
		if(!skipOnLoad) {
			onExit();
		}
		else {
			setSkipOnLoad(false);
		}
		std::string input;
		Environment * tempEnv = nullptr;
		std::vector<Item *> itemVec;
		while(std::getline (myfile,input)) {
			std::vector<std::string> temp = splitLoad(input);
			if(temp[0] == "Room") {
				Room * r = new Room(temp[1], temp[2]);
				rooms->push_back(r);
				tempEnv = r;
			}
			else if(temp[0] == "Outside") {
				Outside * o = new Outside(temp[1], temp[2]);
				rooms->push_back(o);
				tempEnv = o;
			}
			else if(temp[0] == "Cave") {
				Cave * c = new Cave(temp[1], temp[2]);
				rooms->push_back(c);
				tempEnv = c;
			}

			if(temp[0] == "Misc") {
				if(temp[temp.size()-1] == "Env") {
					tempEnv->setItemsInRoom(new Misc(temp[1], temp[2], std::stoi(temp[3]), std::stoi(temp[4])));
				}
				else {
					itemVec.push_back(new Misc(temp[1], temp[2], std::stoi(temp[3]), std::stoi(temp[4])));
				}
			}
			else if(temp[0] == "Weapon") {
				Weapon * w = new Weapon(temp[1], temp[2], std::stoi(temp[3]), std::stoi(temp[4]), std::stoi(temp[5]), std::stoi(temp[6]));
				if(temp[temp.size()-2] == "1") {
					w->setEquipped(true);
				} 
				if(temp[temp.size()-1] == "Env") {
					tempEnv->setItemsInRoom(w);
				}
				else {
					itemVec.push_back(w);
				}
			}
			else if(temp[0] == "Armor") {
				Armor * a = new Armor(temp[1], temp[2], std::stoi(temp[3]), std::stoi(temp[4]), std::stoi(temp[5]));
				if(temp[temp.size()-2] == "1") {
					a->setEquipped(true);
				} 
				if(temp[temp.size()-1] == "Env") {
					tempEnv->setItemsInRoom(a);
				}
				else {
					itemVec.push_back(a);
				}
			}
			else if(temp[0] == "Potion") {
				if(temp[temp.size()-1] == "Env") {
					tempEnv->setItemsInRoom(new Potion(temp[1], temp[2], std::stoi(temp[3]), std::stoi(temp[4]), std::stoi(temp[5])));
				}
				else {
					itemVec.push_back(new Potion(temp[1], temp[2], std::stoi(temp[3]), std::stoi(temp[4]), std::stoi(temp[5])));
				}
			}
			else if(temp[0] == "Wizard") {
				tempEnv->setActorsInRoom(new Wizard(temp[1], itemVec));
				itemVec.clear();
			}
			else if(temp[0] == "Warrior") {
				tempEnv->setActorsInRoom(new Warrior(temp[1], itemVec));
				itemVec.clear();
			}
			else if(temp[0] == "Merchant") {
				tempEnv->setActorsInRoom(new Merchant(temp[1], itemVec));
				itemVec.clear();
			}
			else if(temp[0] == "Player") {
				p = new Player(temp[1], itemVec);
				p->setHealth(std::stoi(temp[3]));
				p->setLives(std::stoi(temp[4]));
				for(size_t k = 0; k < rooms->size(); k++) {
					if((*rooms)[k]->getName() == temp[2]) {
						env = (*rooms)[k];
						break;
					}
				}
				for(size_t i = 0; i < itemVec.size(); i++) {
					if(itemVec[i]->getEquipped()) {
						if(itemVec[i]->getType() == "Weapon") {
							static_cast<Weapon*>(itemVec[i])->use(p);
						}
						else if(itemVec[i]->getType() == "Armor") {
							itemVec[i]->setEquipped(false);
							static_cast<Armor*>(itemVec[i])->use(p);
						}
					}
				}
				itemVec.clear();
			}
			else if(temp[0] == "Dragon") {
				tempEnv->setActorsInRoom(new Dragon(temp[1], itemVec));
				itemVec.clear();
			}

			else if(temp[0] == "=") {
				tempEnv = nullptr;
				for(size_t i = 0; i < rooms->size(); i++) {
					if(((*rooms)[i])->getName() == temp[1]) {
						tempEnv = (*rooms)[i];
						break;
					}
				}
				for(size_t j = 2; j < temp.size()-1; j++) {

					if(temp[j] == "north") {
						for(size_t k = 0; k < rooms->size(); k++) {
							if((*rooms)[k]->getName() == temp[j+1]) {
								tempEnv->setNorthNeighbor((*rooms)[k]);
								j++;
								break;
							}
						}
					} 
					else if(temp[j] == "south") {
						for(size_t k = 0; k < rooms->size(); k++) {
							if((*rooms)[k]->getName() == temp[j+1]) {
								tempEnv->setSouthNeighbor((*rooms)[k]);
								j++;
								break;
							}
						}
					}
					else if(temp[j] == "east") {
						for(size_t k = 0; k < rooms->size(); k++) {
							if((*rooms)[k]->getName() == temp[j+1]) {
								tempEnv->setEastNeighbor((*rooms)[k]);
								j++;
								break;
							}
						}
					}
					else if(temp[j] == "west") {
						for(size_t k = 0; k < rooms->size(); k++) {
							if((*rooms)[k]->getName() == temp[j+1]) {
								tempEnv->setWestNeighbor((*rooms)[k]);
								j++;
								break;
							}
						}
					}
				}
			}

		}
		tempEnv = nullptr;
		myfile.close();
		std::cout << "Loading is completed, enjoy the game!" << std::endl;
		return true;
	}
	else {
		std::cout << "File " + filename + " was not found, please try again" << std::endl;
		return false;
	}
}

// En split funktion som används vid loadGame och splittar på : istället för mellanslag
std::vector<std::string> CommandHandler::splitLoad(std::string& input) {
	std::vector<std::string> splitVec;
	std::string s = "";
	for(size_t i = 0; i < input.length(); i++) {
		if(input[i] != ':') {
			s += input[i];
		}
		else {
			splitVec.push_back(s);
			s = "";
		}
	}
	return splitVec;
}

// Denna funktione anropas vid slut av spelet, t.ex. vid exit eller försök kvar = 0
// Den ser till att det inte sker några läckor vid avslutningen
void CommandHandler::onExit() {
	// Loopar igenom alla rum
	for(size_t i = 0; i < rooms.size(); i++) {
		std::vector<Actor *> tempActors = rooms[i]->getActorsInRoom();
		std::vector<Item *> tempItems = rooms[i]->getItemsInRoom();

		// Loopa igenom alla aktörer i rummen och ta bort dem
		for(size_t i = 0; i < tempActors.size(); i++) {
			tempActors[i]->deleteInventory();	
			delete tempActors[i];
		}
		// Ta bort aktörernas inventory
		for(size_t i = 0; i < tempItems.size(); i++) {
			delete tempItems[i];
		}
		// Ta bort rummet
		delete rooms[i];
	}

	rooms.clear();
	std::vector<Item *> temp = _player->getInventory();
	// Loopa igenom spelarens inventory och ta bort varje föremål
	for(size_t i = 0; i < temp.size(); i++) {
		delete temp[i];
	}
	temp.clear();
	// Ta bort spelaren
	delete _player;
	setExit(true);
}

// Setup funktion som anropas då spelaren väljer att starta ett nytt spel i början, alltså ett spel
// som inte är sparat till fil
void CommandHandler::setup() {
// Create items
	Weapon * sword = new Weapon("Two-handed Sword", "A powerful sword that increase your stats!", 1, 5, 1, 3);
	
	Weapon * cheatSword = new Weapon("Cheat Sword", "A powerful sword that increase your stats!", 10, 50, 10, 30);
	Misc * gold = new Misc("Gold", "With gold you can buy items from the merchants!", 5, 1);
	Misc * gold2 = new Misc("Gold", "With gold you can buy items from the merchants!", 5, 1);
	Misc * gold3 = new Misc("Gold", "With gold you can buy items from the merchants!",  3, 1);
	Misc * key = new Misc("Magic key", "This key is a quest item and opens a special door!", 0, 1);
	Armor * boots = new Armor("Travel boots", "These boots gives you faster movement speed and longer jump range!", 1, 1, 1);
	Armor * helmet = new Armor("Helmet", "Protect your head! Always.", 15, 5, 6);
	Armor * pants = new Armor("Pants", "A man needs pants.", 10, 5, 5);
	Armor * dragonGloves = new Armor("Dragon gloves", "Useful gloves when fighting a dragon!", 10, 4, 5);
	Armor * shield = new Armor("Shield", "A useless shield", 2, 2, 2);
	Potion * pot = new Potion("Health potion", "This item will recover you health by 30!", 30, 1, 2);
	Misc * torch = new Misc("Torch", "To light your way through the darkness", 1, 1);

	// Setup inventory
	std::vector<Item *> mobs;
	std::vector<Item *> mobs2;
	std::vector<Item *> pl;
	mobs.push_back(gold);
	mobs2.push_back(gold2);
	pl.push_back(sword);
	pl.push_back(cheatSword);
	pl.push_back(shield);
	pl.push_back(torch);

	// Create actors
	Player* p = new Player("Player", pl);
	sword->use(p);
	shield->use(p);
	Wizard * d = new Wizard("Wizard1", mobs);
	Wizard * w = new Wizard("Wizard2", mobs2);

	std::vector<Item *> merch;
	merch.push_back(boots);
	merch.push_back(helmet);
	merch.push_back(pants);
	merch.push_back(dragonGloves);
	Merchant * m = new Merchant("Merchant", merch);
	
	std::vector<Item *> skel;
	skel.push_back(gold3);
	skel.push_back(key);
	Warrior * war = new Warrior("Skeleton", skel);
	std::vector<Item *> dragItems;
	Misc * gold4 = new Misc("Gold", "With gold you can buy items from the merchants!",  10, 1);
	dragItems.push_back(gold4);
	Dragon * drag = new Dragon("Dragon", dragItems);

	// Create rooms
	std::vector<Environment *> rooms;
	Room* lobby = new Room("You are in the Lobby! Write 'help' if you need any help.", "Lobby");
	rooms.push_back(lobby);
	Room* wizardRoom = new Room("You are in an empty room with something dark in front of you...", "WizardRoom");
	rooms.push_back(wizardRoom);
	Room* potitionRoom = new Room("You are in an empty room... maybe there is something hidden in it?", "PotionRoom");
	rooms.push_back(potitionRoom);
	Room* marketRoom = new Room("You are at Knivbergsmarknad, a person is standing in the room, go talk to him?", "MarketRoom");
	rooms.push_back(marketRoom);
	Outside* skeletonRoom = new Outside("You are in a room that has been abandoned for a long time! A skeleton is lying on the ground.. Wait, it moves!", "SkeletonRoom");
	rooms.push_back(skeletonRoom);
	Cave* brokenBridge1 = new Cave("You are in a cave with a broken bridge on the west side, the gap is huge, do you want to jump?", "BrokenBridge1");
	rooms.push_back(brokenBridge1);
	Cave* brokenBridge2 = new Cave("You are in a cave with a broken bridge on the east side, the gap is huge, do you want to jump?", "BrokenBridge2");
	rooms.push_back(brokenBridge2);
	Cave* stairs = new Cave("The screaming voice is louder now! The dragon must be down the stairs!", "Stairs");
	rooms.push_back(stairs);
	Cave* preDragonRoom = new Cave("You are in a long and empty hall with a closed door at the other end. You walk slowly, but something is behind you!", "Hall");
	rooms.push_back(preDragonRoom);
	Cave* dragonRoom = new Cave("You have entered the room with the Dragon! The door behind you is closed and locked! Fight for your life!", "DragonRoom");
	rooms.push_back(dragonRoom);

	// Linking rooms
	lobby->setNorthNeighbor(wizardRoom);
	lobby->setEastNeighbor(potitionRoom);
	lobby->setWestNeighbor(brokenBridge1);

	wizardRoom->setSouthNeighbor(lobby);
	wizardRoom->setEastNeighbor(marketRoom);
	marketRoom->setWestNeighbor(wizardRoom);
	marketRoom->setEastNeighbor(skeletonRoom);
	potitionRoom->setWestNeighbor(lobby);
	potitionRoom->setNorthNeighbor(skeletonRoom);
	skeletonRoom->setSouthNeighbor(potitionRoom);
	skeletonRoom->setWestNeighbor(marketRoom);
	

	brokenBridge1->setEastNeighbor(lobby);
	// JUMP WEST
	brokenBridge1->setWestNeighbor(brokenBridge2);
	// JUMP EAST
	brokenBridge2->setEastNeighbor(brokenBridge1);

	brokenBridge2->setWestNeighbor(stairs);
	stairs->setEastNeighbor(brokenBridge2);
	stairs->setNorthNeighbor(preDragonRoom);
	preDragonRoom->setSouthNeighbor(stairs);
	preDragonRoom->setNorthNeighbor(dragonRoom);
	dragonRoom->setSouthNeighbor(preDragonRoom);

	// Put actors in rooms
	wizardRoom->setActorsInRoom(d);
	wizardRoom->setActorsInRoom(w);
	marketRoom->setActorsInRoom(m);

	potitionRoom->setItemsInRoom(pot);
	skeletonRoom->setActorsInRoom(war);

	dragonRoom->setActorsInRoom(drag);

	// Env is the current room
	Environment * env = lobby; // change depending on save state
	std::cout << env->getDescription() << std::endl;
	env->directions();

	addPlayer(p);
	addEnvironment(env);
	addRooms(rooms);

}

// Intro funktionen används endast vid val av nytt spel, och den berättar en händelse där spelaren
// får välja sitt namn, etc.
std::string CommandHandler::intro() {
	while(true) {
		std::cout << "Welcome to the Dragon Slayer game!" << std::endl;
		std::cout << "1. Start new game" << std::endl;
		std::cout << "2. Load saved game" << std::endl;	
		std::cout << "3. Exit game" << std::endl;	
		std::string in2;
		std::getline (std::cin, in2);
		if(in2 == "1") {
			std::cout << "Find out what your Dragon Slayer name is, write your name:" << std::endl;
			std::string in;
			std::getline (std::cin, in);
			std::string temp = "Bloodthirsty " + in;
			std::cout << temp + " is your Dragon Slayer name!" << std::endl;
			std::cout << "Are you ready to face the Dragon?" << std::endl;
			std::string yn;
			std::getline (std::cin, yn);
			if(!yn.compare("yes")) {
				std::string story = "Once upon a time a warrior called " + temp + " lived in north Sweden. \nHe lived alone because people were scared of him. One day he found an abandoned castle in the forest. \nIt was in the middle of a dark forest, but " + temp + " was not scared to go inside!";
				for(size_t i = 0; i < story.length(); i++) {
					std::cout << story[i] << std::flush;
					usleep(40000);
				}
				std::cout << std::endl;
				return temp;
			}
			else {
				std::cout << "Oh poor you, come back later when you feel stronger!" << std::endl;
				return "";
			}
		}
		else if(in2 == "2") {
			std::cout << "Please enter the file name i.e. foo.txt" << std::endl;	
			std::string in;
			std::getline (std::cin, in);
			setSkipOnLoad(true);
			if(loadGame(&rooms, _player, in, _env)) {
				std::cout << _env->getDescription() << std::endl;
				_env->directions();
				return "loaddaol";
			}
		}
		else if(in2 == "3") {
			return "";
		}
		else {
			std::cout << "Invalid input, please try again!" << std::endl;
		}
	}
}

// Denna funktion används då man vill använda eller plocka upp ett föremål
// som består av två eller flera ord, alltså den lägger in det som en sträng
std::string getItemName(std::vector<std::string> split){
	std::string temp;
	if(split.size() > 2) {
		for(size_t i = 1; i < split.size()-1; i++) {
			temp += split[i] + " ";
		}
		temp += split[split.size()-1];
	}
	else {
		temp = split[1];
	}
	return temp;
}

// Splittar input på mellanslag
std::vector<std::string> splitInput(const std::string& line) {
    std::istringstream is(line);
    return std::vector<std::string>(std::istream_iterator<std::string>(is), std::istream_iterator<std::string>());
}

int main(){

	// Skapar structen
	CommandHandler funpoint;

	// Intro, spelets startmeny
	std::string name = funpoint.intro();
	if(name == "") {
		return 0;
	}
	else if(name != "loaddaol") {
		funpoint.setup();
		Player * p = funpoint.getPlayer();
		p->setName(name);
	}

	// När spelet har börjat, while-slingan körs tills spelaren väljer att skriva exit
	// eller antalet försök kvar = 0
	// Resten av tiden delar den upp input och anropas respektive funktion som i sin tur
	// anropar rätt funktionspekare och den önskade instruktionen utförs
	std::string input;
	while(true) {

		if(funpoint.getExit() && funpoint.getExitGame()) {
			break;
		}

		if((funpoint.getEnv())->getType() == "Outside"){
			Outside * outside = static_cast<Outside *>(funpoint.getEnv());
			outside->hurtPlayer(funpoint.getPlayer());
			if(funpoint.getPlayer()->isDead()) {
				funpoint.getPlayer()->decrementLives();
				funpoint.addEnvironment(funpoint.getRespawn());
				std::cout << "The heat has killed you, you have respawned in the " + funpoint.getEnv()->getName() + "!" << std::endl;
				funpoint.getPlayer()->setHealth(funpoint.getPlayer()->getMaxHealth());
				funpoint.look(); 
			}
		}

		if((funpoint.getPlayer() != NULL) &&(funpoint.getLives() == 0)) {
			std::cout << "Oh you don't have any lives left, Game is over!" << std::endl;
			funpoint.onExit();
			break;
		}

		
		std::getline (std::cin, input);

		// SPLIT
		std::vector<std::string> split = splitInput(input);
	
		if (split.size() == 1) { 
			funpoint.Call(split[0]); 
		}
		else if(split.size() > 1) {
			std::string itemName = getItemName(split);
			funpoint.Call2(split[0], itemName);
		}
		else {
			std::cout << "Invalid input" << std::endl;
		}

		split.clear();
	}

}

