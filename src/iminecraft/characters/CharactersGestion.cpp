#include "iminecraft/characters/CharactersGestion.hpp"
#include "iminecraft/characters/Neutral.hpp"

namespace iminecraft {
	// Constructeur
    CharactersGestion::CharactersGestion(){
    	// some neutral
    	/*Neutral cow_1 = Neutral(cow);
    	Neutral sheep_1 = Neutral(sheep);
    	Neutral pig_1 = Neutral(pig);

    	charactersVector.push_back(cow_1);
    	charactersVector.push_back(sheep_1);
    	charactersVector.push_back(pig_1);*/
    }

    size_t CharactersGestion::addNeutral(neutral_type type){
    	Neutral newNeutral(type);
    	neutralsVector.push_back(newNeutral);
    	return getNumberOfNeutrals()-1;
    }

    void CharactersGestion::deleteNeutral(size_t index){
    	neutralsVector.erase(neutralsVector.begin()+index);
    }

    size_t CharactersGestion::addMonster(monster_type type){
        Monster newMonster(type);
        monstersVector.push_back(newMonster);
        return getNumberOfMonsters()-1;
    }

    void CharactersGestion::deleteMonster(size_t index){
        monstersVector.erase(monstersVector.begin()+index);
    }

    // destructeur
    CharactersGestion::~CharactersGestion(){
    	charactersVector.clear();
    }
}
