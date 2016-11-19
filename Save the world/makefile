OBJS = Main.o Actor.o Creature.o Human.o Dragon.o Merchant.o Player.o Warrior.o Wizard.o Environment.o Cave.o Room.o Outside.o Item.o Armor.o Weapon.o Potion.o Misc.o Usable.o

CXXFLAGS = g++ -std=c++11 -Wall -c
CXX = g++

FLAGS = -std=c++11 -g -Wall -pedantic

main: $(OBJS)
	$(CXX) $(FLAGS) -o main $(OBJS) 

Main.o: Actor/main.cpp
	 $(CXXFLAGS) Actor/main.cpp

Actor.o: Actor/Actor.cpp Actor/Actor.hpp
	$(CXXFLAGS) Actor/Actor.cpp

Creature.o: Actor/Creature.hpp Actor/Creature.cpp 
	$(CXXFLAGS) Actor/Creature.cpp

Player.o: Actor/Player.hpp Actor/Player.cpp 
	$(CXXFLAGS) Actor/Player.cpp

Human.o: Actor/Human.hpp Actor/Human.cpp 
	$(CXXFLAGS) Actor/Human.cpp

Dragon.o: Actor/Dragon.hpp Actor/Dragon.cpp
	$(CXXFLAGS) Actor/Dragon.cpp

Merchant.o: Actor/Merchant.hpp Actor/Merchant.cpp
	$(CXXFLAGS) Actor/Merchant.cpp	

Wizard.o: Actor/Wizard.hpp Actor/Wizard.cpp
	$(CXXFLAGS) Actor/Wizard.cpp	

Warrior.o: Actor/Warrior.hpp Actor/Warrior.cpp
	$(CXXFLAGS) Actor/Warrior.cpp	

Environment.o: Environment/Environment.hpp Environment/Environment.cpp
	$(CXXFLAGS) Environment/Environment.cpp

Cave.o: Environment/Cave.hpp Environment/Cave.cpp
	$(CXXFLAGS) Environment/Cave.cpp

Room.o: Environment/Room.hpp Environment/Room.cpp
	$(CXXFLAGS) Environment/Room.cpp

Outside.o: Environment/Outside.hpp Environment/Outside.cpp
	$(CXXFLAGS) Environment/Outside.cpp	

Item.o: Items/Item.hpp Items/Item.cpp
	$(CXXFLAGS) Items/Item.cpp

Armor.o: Items/Armor.hpp Items/Armor.cpp
	$(CXXFLAGS) Items/Armor.cpp

Weapon.o: Items/Weapon.hpp Items/Weapon.cpp
	$(CXXFLAGS) Items/Weapon.cpp

Potion.o: Items/Potion.hpp Items/Potion.cpp
	$(CXXFLAGS) Items/Potion.cpp

Misc.o: Items/Misc.hpp Items/Misc.cpp
	$(CXXFLAGS) Items/Misc.cpp	

Usable.o: Items/Usable.hpp Items/Usable.cpp
	$(CXXFLAGS) Items/Usable.cpp			

clean:
	rm -rf *.o main
