#ifndef _IMINECRAFT_CONTROLCENTER_HPP_
#define _IMINECRAFT_CONTROLCENTER_HPP_

#include <cstdlib>
#include <iostream>

#include "iminecraft/World.hpp"
#include "iminecraft/characters/CharactersGestion.hpp"
#include "iminecraft/characters/Character.hpp"
#include "iminecraft/characters/Hero.hpp"
#include "iminecraft/sound/Sounds.hpp"

#include "iminecraft/cameras/FirstPersonCamera.hpp"


namespace iminecraft {
	class ControlCenter{
	    private:
	        World& world;
	        CharactersGestion& charactersGestion;

	        FirstPersonCamera& firstPerson;
	        Sounds sound;
	        /*Sounds attackedSound;
	        Sounds attackSound;
	        Sounds constructSound;
	        Sounds moveSound;
	        Sounds cowSound;
	        Sounds sheepSound;
	        Sounds pigSound;
	        Sounds chickenSound;
	        Sounds monsterSound;*/

	        int changedDay;
	        bool startIntro;
	        bool mute;
	    public:
	        ControlCenter(World& c_world, CharactersGestion& c_charactersGestion, FirstPersonCamera& c_firstPerson);
	        virtual ~ControlCenter();

			void startProcessIntro();
			bool processIntro();

	        void rotate(float xRel, float yRel);
	        void rotateLeft(float angle);

	        bool leftClickLand();
	        bool rightClickLand();

	        void changeMaterial(int index);
	        void changeMaterialUp();
	        void changeMaterialDown();

	        void moveFrontHero();
	        void moveBackHero();
	        void moveLeftHero();
	        void moveRightHero();
	        bool gravityHero();
	        void jumpHero();

	        void moveNeutral(size_t index);
	        void gravityNeutral(size_t index);

	        void moveFrontMonster(size_t index);
	        void jumpMonster(size_t index);
	        void gravityMonster(size_t index);
	        void iaMonster(size_t index);

	        void updatePositionCamera();

	        void changeNight(){
	        	if(world.getNight()>0 && changedDay == 0){
	        		changedDay = 10;
	        		world.setNight(0);
	        	}else if(changedDay == 0){
	        		changedDay = 10;
	        		world.setNight(1);
	        	}
	        };

	        void volumeSound(int);
	        void muteSound();

	        void processOther();

	        void saveGame();
	};
}

#endif
