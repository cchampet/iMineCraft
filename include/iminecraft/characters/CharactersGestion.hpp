#ifndef _IMINECRAFT_CHARACTERSGESTION_HPP_
#define _IMINECRAFT_CHARACTERSGESTION_HPP_

#include <cstdlib>
#include <vector>
#include "iminecraft/characters/Neutral.hpp"
#include "iminecraft/characters/Hero.hpp"
#include "iminecraft/characters/Monster.hpp"

using namespace std;
using namespace iminecraft;

namespace iminecraft {
	class CharactersGestion{
	    private:
	    	Hero hero;
	    	vector<Neutral> neutralsVector;
	    	vector<Character> charactersVector;
	    	vector<Monster> monstersVector;

	    public:
	        CharactersGestion();
	        virtual ~CharactersGestion();

	        void addChar(){Character newChar; charactersVector.push_back(newChar);};
	        size_t addNeutral(neutral_type type);
	        void deleteNeutral(size_t index);
	        size_t addMonster(monster_type type);
	        void deleteMonster(size_t index);
	        Character& getChar(size_t i){return (Character&) charactersVector.at(i);};
	        Neutral& getNeutral(size_t i){return (Neutral&) neutralsVector.at(i);};
	        Monster& getMonster(size_t i){return (Monster&) monstersVector.at(i);};
	        size_t getNumberOfChar(){return charactersVector.size();};
	        size_t getNumberOfNeutrals(){return neutralsVector.size();};
	        size_t getNumberOfMonsters(){return monstersVector.size();};

	        Hero& getHero(){return (Hero&) hero;};
	};
}

#endif
