#include "iminecraft/ControlCenter.hpp"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <cstdlib>
#include <cmath>

namespace iminecraft {
    // Constructeur
    ControlCenter::ControlCenter(World& c_world, CharactersGestion& c_charactersGestion, FirstPersonCamera& c_firstPerson): world(c_world), charactersGestion(c_charactersGestion), firstPerson(c_firstPerson){
        firstPerson.setPosition(glm::vec3(charactersGestion.getHero().position().x, charactersGestion.getHero().position().y-1.5, charactersGestion.getHero().position().z));
        int y=100;

        charactersGestion.getHero().position(glm::vec3(charactersGestion.getHero().position().x, y, charactersGestion.getHero().position().z));

        charactersGestion.getHero().direction(firstPerson.getAngles().x);

        startIntro = false;
        mute = false;
        changedDay = 0;
    }

    void ControlCenter::startProcessIntro(){
   		startIntro = true;
    }

    bool ControlCenter::processIntro(){
    	glm::vec3 positionHero = charactersGestion.getHero().position();
    	world.completeCreationOfChunk(floor(positionHero.x), floor(positionHero.z));
		world.manageChunkVector(floor(positionHero.x), floor(positionHero.z));
    	updatePositionCamera();

    	if(startIntro){
    		if(world.getValue(glm::vec3(positionHero.x,positionHero.y-1,positionHero.z)) != 0)
    			return true; // end of the intro!
    		else if(positionHero.y -1 > 32)
    			charactersGestion.getHero().position(glm::vec3(positionHero.x,positionHero.y-0.2,positionHero.z));
    		else
    			charactersGestion.getHero().position(glm::vec3(positionHero.x,positionHero.y-0.05,positionHero.z));
    	}
    	return false;
    }

    void ControlCenter::rotate(float xRel, float yRel){
        firstPerson.rotateLeft(-xRel * 0.25f);
        firstPerson.rotateUp(yRel * 0.25f);
        charactersGestion.getHero().direction(firstPerson.getAngles().x);
    }

    void ControlCenter::rotateLeft(float angle){
        firstPerson.rotateLeft(-angle * 0.25f);
        charactersGestion.getHero().direction(firstPerson.getAngles().x);
    }

    bool ControlCenter::rightClickLand(){
    	if(charactersGestion.getHero().isDoingAction())
    		return false;

    	bool res = false;
    	glm::vec3 ray = glm::normalize(firstPerson.getFrontVector());
    	glm::vec3 Point = firstPerson.getPosition();
    	int typeBlocQueJeVise = 0;

    	glm::vec3 Regard = Point;
    	for (int i = 0; i < 35; ++i)
    	{
    		Regard += glm::vec3(ray.x*0.1, ray.y*0.1, ray.z*0.1);

	    	typeBlocQueJeVise = world.getValue(glm::vec3(floor(Regard.x), floor(Regard.y), floor(Regard.z)));
	    	if(typeBlocQueJeVise > 0){
	    		break;
	    	}
    	}

    	if(typeBlocQueJeVise > 0){
			int xPosRegard = floor(Regard.x-(ray.x*0.1));
			int yPosRegard = floor(Regard.y-(ray.y*0.1));
			int zPosRegard = floor(Regard.z-(ray.z*0.1));

			if(world.getValue(glm::vec3(xPosRegard, yPosRegard, zPosRegard)) == 0 ){
				//TODO : enlever de la solidité au bloc, si le bloc est cassé, le mettre dans l'inventaire.
				int rightChunk = world.getChuckFromPosition(xPosRegard, zPosRegard);
				glm::vec3 ici(0, yPosRegard, 0);
				if(xPosRegard >= 0) ici.x = xPosRegard%16;
				if(xPosRegard < 0) ici.x = (16+(xPosRegard%16))%16;

				if(zPosRegard >= 0) ici.z = zPosRegard%16;
				if(zPosRegard < 0) ici.z = (16+(zPosRegard%16))%16;
				size_t mat = charactersGestion.getHero().currentMaterial();
				res = true;
				if(charactersGestion.getHero().inventory(charactersGestion.getHero().currentMaterial(), -1)){
					charactersGestion.getHero().doAction();
					//constructSound.play(2);
					sound.play(2);
					world.changeTypeOfABlock(ici.x, ici.y, ici.z, mat, rightChunk);
					iminecraft::Chunk chunk = world.getChunkVector().at(rightChunk);
					world.refreshMeshChunk(chunk.getXPosition(), chunk.getZPosition(), chunk.getCubeDataVector());
				}else{
					//std::cerr<<"Plus de matériaux en stock"<<std::endl;
				}
			}
    	}
    	return res;
    }

  bool ControlCenter::leftClickLand(){
  	if(charactersGestion.getHero().isDoingAction())
  		return false;

	  bool res = false;
    	glm::vec3 ray = glm::normalize(firstPerson.getFrontVector());
    	glm::vec3 Point = firstPerson.getPosition();

    	int targetedAnimal = -1;
    	int targetedMonster = -1;
    	glm::vec3 Regard = Point;
    	for (int i = 0; i < 35; ++i)
    	{
    		Regard += glm::vec3(ray.x*0.1, ray.y*0.1, ray.z*0.1);

    		int xPosRegard = floor(Regard.x);
	    	int yPosRegard = floor(Regard.y);
	    	int zPosRegard = floor(Regard.z);
	    	for(size_t j=0; j<charactersGestion.getNumberOfNeutrals(); ++j)
	    		if(targetedAnimal < 0)
					for(float h=0; h<=charactersGestion.getNeutral(j).height(); h += 0.1)
						if(glm::distance2(glm::vec3(Regard.x, Regard.y, Regard.z), glm::vec3(charactersGestion.getNeutral(j).position().x, charactersGestion.getNeutral(j).position().y + h, charactersGestion.getNeutral(j).position().z)) <= pow(charactersGestion.getNeutral(j).height()*.6, 2))
							targetedAnimal = j;

	    	for(size_t j=0; j<charactersGestion.getNumberOfMonsters(); ++j)
	    		if(targetedMonster < 0)
					for(float h=0; h<=charactersGestion.getMonster(j).height(); h += 0.1)
						if(glm::distance2(glm::vec3(Regard.x, Regard.y, Regard.z), glm::vec3(charactersGestion.getMonster(j).position().x, charactersGestion.getMonster(j).position().y + h, charactersGestion.getMonster(j).position().z)) <= pow(charactersGestion.getMonster(j).height()*.6, 2))
							targetedMonster = j;

	    	int typeBlocQueJeVise = world.getValue(glm::vec3(xPosRegard, yPosRegard, zPosRegard));

	    	if(typeBlocQueJeVise > 0 || targetedAnimal > -1 || targetedMonster > -1){
	    		break;
	    	}
    	}

    	if(targetedMonster > -1){
    		//std::cerr<<"Je tape sur un animal !!!"<<std::endl;
    		charactersGestion.getHero().doAction();
    		//attackSound.play(0);
    		sound.play(0);
    		if(charactersGestion.getMonster(targetedMonster).gainLife(-1.f) == 0){
    			charactersGestion.deleteMonster(targetedMonster);
            	//Obtention d'un matériau lumière (faute de meatboy).
    			charactersGestion.getHero().inventory((int)(rand()%8)+1, (int)((rand()%3) + 1));
    			charactersGestion.getHero().gainLife(1.);
    		}
    		return true;
    	}

    	if(targetedAnimal > -1){
    		//std::cerr<<"Je tape sur un animal !!!"<<std::endl;
    		charactersGestion.getHero().doAction();
    		//attackSound.play(0);
    		sound.play(0);
    		res = true;
    		if(charactersGestion.getNeutral(targetedAnimal).gainLife(-1.f) == 0){
    			charactersGestion.deleteNeutral(targetedAnimal);
            	//Obtention d'un matériau lumière (faute de meatboy).
    			charactersGestion.getHero().inventory(8, 1);
    			charactersGestion.getHero().gainLife(1.);
    		}
    		return true;
    	}

    	int xPosRegard = floor(Regard.x);
    	int yPosRegard = floor(Regard.y);
    	int zPosRegard = floor(Regard.z);
    	int typeOfBlock = world.getValue(glm::vec3(xPosRegard, yPosRegard, zPosRegard));
    	if( typeOfBlock > 0){
    		//TODO : enlever de la solidité au bloc, si le bloc est cassé, le mettre dans l'inventaire.
    		int rightChunk = world.getChuckFromPosition(xPosRegard, zPosRegard);
    		glm::vec3 ici(0, yPosRegard, 0);
    		if(xPosRegard >= 0) ici.x = xPosRegard%16;
    		if(xPosRegard < 0) ici.x = (16+(xPosRegard%16))%16;

    		if(zPosRegard >= 0) ici.z = zPosRegard%16;
    		if(zPosRegard < 0) ici.z = (16+(zPosRegard%16))%16;
    		charactersGestion.getHero().doAction();
    		//constructSound.play(3);
    		sound.play(3);
    		res = true;
    		int blocDur = world.changeDurabilityOfABlock(ici.x, ici.y, ici.z, rightChunk);
    		//std::cerr<<typeOfBlock<<std::endl;
    		if(blocDur == 0){
    			charactersGestion.getHero().inventory(typeOfBlock, 1);
    			iminecraft::Chunk chunk = world.getChunkVector().at(rightChunk);
    			world.refreshMeshChunk(chunk.getXPosition(), chunk.getZPosition(), chunk.getCubeDataVector());
    			world.removePointLight(xPosRegard,yPosRegard,zPosRegard);
    		}
    	}

    	return res;
    }

  	  void ControlCenter::changeMaterial(int index){
  		charactersGestion.getHero().currentMaterial(index);
  		//std::cerr<<charactersGestion.getHero().currentMaterial()<<std::endl;
  	  }

  	 void ControlCenter::changeMaterialUp(){
  		 if(charactersGestion.getHero().currentIndex()<9)
  			 charactersGestion.getHero().currentMaterial(charactersGestion.getHero().currentIndex()+1);
  		 else
  			charactersGestion.getHero().currentMaterial(0);
  	 }

  	 void ControlCenter::changeMaterialDown(){
  		 if(charactersGestion.getHero().currentIndex()>0)
  			 charactersGestion.getHero().currentMaterial(charactersGestion.getHero().currentIndex()-1);
  		 else
  			charactersGestion.getHero().currentMaterial(9);
  	 }

    void ControlCenter::moveFrontHero(){
    	//std::cerr<<charactersGestion.getHero().getDirection().x<<", "<<charactersGestion.getHero().getDirection().y<<", "<<charactersGestion.getHero().getDirection().z<<"\tposition : "<<charactersGestion.getHero().position().x<<", "<<charactersGestion.getHero().position().y<<", "<<charactersGestion.getHero().position().z<<std::endl;
        //Hero& hero = charactersGestion.getHero();
        float factor = charactersGestion.getHero().width()*.5+charactersGestion.getHero().speed();
        glm::vec3 nextPos = charactersGestion.getHero().position() - factor * charactersGestion.getHero().getDirection();
        float width = charactersGestion.getHero().width();
        bool collision = false;
        int blocCollision = 0;
		for(float h = 0; h <= charactersGestion.getHero().height(); h += 0.5)
			if(!collision)
				for(float coefx = -0.5; coefx <= 0.5; coefx += 0.5)
					if(!collision)
						for(float coefz = -0.5; coefz <= 0.5; coefz += 0.5){
							if(!collision && world.getValue(glm::vec3(floor(nextPos.x+(width*coefx)), floor(nextPos.y+h), floor(nextPos.z+(width*coefz)) ))  > 0)
								collision = true;
							else if(world.getValue(glm::vec3(floor(nextPos.x+(width*coefx)), floor(nextPos.y+h), floor(nextPos.z+(width*coefz)) )) == 5){
								blocCollision = 5;
								collision = true;
							}
						}

		if(!collision)
			for(size_t i=0; i < charactersGestion.getNumberOfMonsters(); ++i)
				if(!collision && glm::distance2(charactersGestion.getHero().position(), charactersGestion.getMonster(i).position()) < 10)
					for(float h = 0; h <= charactersGestion.getHero().height(); h += 0.5)
						if(!collision)
							for(float nh = 0; nh <= charactersGestion.getMonster(i).height(); nh += 0.1)
								if(!collision && glm::distance2(glm::vec3(nextPos.x, nextPos.y+h, nextPos.z), glm::vec3(charactersGestion.getMonster(i).position().x, charactersGestion.getMonster(i).position().y + nh, charactersGestion.getMonster(i).position().z)) <  pow((width*0.5+charactersGestion.getMonster(i).width()*0.5), 2))
									collision = true;

		if(!collision)
			for(size_t i=0; i < charactersGestion.getNumberOfNeutrals(); ++i)
				if(!collision && glm::distance2(charactersGestion.getHero().position(), charactersGestion.getNeutral(i).position()) < 10)
					for(float h = 0; h <= charactersGestion.getHero().height(); h += 0.5)
						if(!collision)
							for(float nh = 0; nh <= charactersGestion.getNeutral(i).height(); nh += 0.1)
								if(!collision && glm::distance2(glm::vec3(nextPos.x, nextPos.y+h, nextPos.z), glm::vec3(charactersGestion.getNeutral(i).position().x, charactersGestion.getNeutral(i).position().y + nh, charactersGestion.getNeutral(i).position().z)) <  pow((width*0.5+charactersGestion.getNeutral(i).width()*0.5), 2))
									collision = true;

        if(!collision){
                // nothing in frot of the hero, we can move
                charactersGestion.getHero().moveFront(-1);
                if(SDL_GetTicks()%500 < 50)	sound.play(4);//moveSound.play(4);
        }else if(blocCollision == 5){
        	charactersGestion.getHero().moveFront(-1);
			world.clearAllChunksAndRefreshToOrigin();
			sound.play(11);
			charactersGestion.getHero().die();
        }
    }
    void ControlCenter::moveBackHero(){
           //Hero& hero = charactersGestion.getHero();
            float factor = charactersGestion.getHero().width()*.5+charactersGestion.getHero().speed();
            glm::vec3 nextPos = charactersGestion.getHero().position() + factor * charactersGestion.getHero().getDirection();
            //std::cerr << world.getValue(hero.position()) << std::endl;
            //std::cout << "mmmh, je voudrais aller derriere, je peux ? " << (world.getValue(hero.position() - hero.getSpeed()*hero.getDirection()) < 1) <<std::endl;
            bool collision = false;
            int blocCollision = 0;
            for(float h = 0; h <= charactersGestion.getHero().height(); h += 0.5)
            	if(!collision)
            		for(float coefx = -0.5; coefx <= 0.5; coefx += 0.5)
            			if(!collision)
            				for(float coefz = -0.5; coefz <= 0.5; coefz += 0.5){
								if(!collision && world.getValue(glm::vec3(floor(nextPos.x+(charactersGestion.getHero().width()*coefx)), floor(nextPos.y+h), floor(nextPos.z+(charactersGestion.getHero().width()*coefz)) ))  > 0)
									collision = true;
								else if(world.getValue(glm::vec3(floor(nextPos.x+(charactersGestion.getHero().width()*coefx)), floor(nextPos.y+h), floor(nextPos.z+(charactersGestion.getHero().width()*coefz)) )) == 5){
									blocCollision = 5;
									collision = true;
								}
            				}

            if(!collision)
				for(size_t i=0; i < charactersGestion.getNumberOfNeutrals(); ++i)
					if(!collision && glm::distance2(charactersGestion.getHero().position(), charactersGestion.getNeutral(i).position()) < 10)
						for(float h = 0; h <= charactersGestion.getHero().height(); h += 0.5)
							if(!collision)
								for(float nh = 0; nh <= charactersGestion.getNeutral(i).height(); nh += 0.1)
									if(!collision && glm::distance2(glm::vec3(nextPos.x, nextPos.y+h, nextPos.z), glm::vec3(charactersGestion.getNeutral(i).position().x, charactersGestion.getNeutral(i).position().y + nh, charactersGestion.getNeutral(i).position().z)) <  pow((charactersGestion.getHero().width()*0.5+charactersGestion.getNeutral(i).width()*0.5), 2))
										collision = true;

            if(!collision)
				for(size_t i=0; i < charactersGestion.getNumberOfNeutrals(); ++i)
					if(!collision && glm::distance2(charactersGestion.getHero().position(), charactersGestion.getNeutral(i).position()) < 10)
						for(float h = 0; h <= charactersGestion.getHero().height(); h += 0.5)
							if(!collision)
								for(float nh = 0; nh <= charactersGestion.getNeutral(i).height(); nh += 0.1)
									if(!collision && glm::distance2(glm::vec3(nextPos.x, nextPos.y+h, nextPos.z), glm::vec3(charactersGestion.getNeutral(i).position().x, charactersGestion.getNeutral(i).position().y + nh, charactersGestion.getNeutral(i).position().z)) <  pow((charactersGestion.getHero().width()*0.5+charactersGestion.getNeutral(i).width()*0.5), 2))
										collision = true;


            if(!collision){
            // nothing behind the hero, we can move back
            	charactersGestion.getHero().moveFront(1);
                if(SDL_GetTicks()%500 < 50)	sound.play(4);//moveSound.play(4);
            }else if(blocCollision == 5){
            	charactersGestion.getHero().moveFront(-1);
    			world.clearAllChunksAndRefreshToOrigin();
    			sound.play(11);
    			charactersGestion.getHero().die();
            }

	}
	void ControlCenter::moveLeftHero(){
		//std::cout << "mmmh, je voudrais aller a gauche, je peux ?" << std::endl;
		//Hero& hero = charactersGestion.getHero();
		float factor = charactersGestion.getHero().width()*.5+charactersGestion.getHero().speed();
		glm::vec3 nextPos = charactersGestion.getHero().position() - (factor * charactersGestion.getHero().getLeft());
	 	bool collision = false;
	 	int blocCollision = 0;
		for(float h = 0; h <= charactersGestion.getHero().height(); h += 0.5)
			if(!collision)
				for(float coefx = -0.5; coefx <= 0.5; coefx += 0.5)
					if(!collision)
        				for(float coefz = -0.5; coefz <= 0.5; coefz += 0.5){
							if(!collision && world.getValue(glm::vec3(floor(nextPos.x+(charactersGestion.getHero().width()*coefx)), floor(nextPos.y+h), floor(nextPos.z+(charactersGestion.getHero().width()*coefz)) ))  > 0)
								collision = true;
							else if(world.getValue(glm::vec3(floor(nextPos.x+(charactersGestion.getHero().width()*coefx)), floor(nextPos.y+h), floor(nextPos.z+(charactersGestion.getHero().width()*coefz)) )) == 5){
								blocCollision = 5;
								collision = true;
							}
        				}

        if(!collision)
			for(size_t i=0; i < charactersGestion.getNumberOfNeutrals(); ++i)
				if(!collision && glm::distance2(charactersGestion.getHero().position(), charactersGestion.getNeutral(i).position()) < 10)
					for(float h = 0; h <= charactersGestion.getHero().height(); h += 0.5)
						if(!collision)
							for(float nh = 0; nh <= charactersGestion.getNeutral(i).height(); nh += 0.1)
								if(!collision && glm::distance2(glm::vec3(nextPos.x, nextPos.y+h, nextPos.z), glm::vec3(charactersGestion.getNeutral(i).position().x, charactersGestion.getNeutral(i).position().y + nh, charactersGestion.getNeutral(i).position().z)) <  pow((charactersGestion.getHero().width()*0.5+charactersGestion.getNeutral(i).width()*0.5), 2))
									collision = true;

		if(!collision)
			for(size_t i=0; i < charactersGestion.getNumberOfNeutrals(); ++i)
				if(!collision && glm::distance2(charactersGestion.getHero().position(), charactersGestion.getNeutral(i).position()) < 10)
					for(float h = 0; h <= charactersGestion.getHero().height(); h += 0.5)
						if(!collision)
							for(float nh = 0; nh <= charactersGestion.getNeutral(i).height(); nh += 0.1)
								if(!collision && glm::distance2(glm::vec3(nextPos.x, nextPos.y+h, nextPos.z), glm::vec3(charactersGestion.getNeutral(i).position().x, charactersGestion.getNeutral(i).position().y + nh, charactersGestion.getNeutral(i).position().z)) <  pow((charactersGestion.getHero().width()*0.5+charactersGestion.getNeutral(i).width()*0.5), 2))
									collision = true;

	    if(!collision){
			// nothing in frot of the hero, we can move
			charactersGestion.getHero().moveLeft(1);
            if(SDL_GetTicks()%500 < 50)	sound.play(4);//moveSound.play(4);
		}else if(blocCollision == 5){
        	charactersGestion.getHero().moveFront(-1);
			world.clearAllChunksAndRefreshToOrigin();
			sound.play(11);
			charactersGestion.getHero().die();
		}
	}
	void ControlCenter::moveRightHero(){
		//std::cout << "mmmh, je voudrais aller a droite, je peux ?" << std::endl;
		//Hero& hero = charactersGestion.getHero();
		float factor = charactersGestion.getHero().width()*.5+charactersGestion.getHero().speed();
		glm::vec3 nextPos = charactersGestion.getHero().position() + (factor * charactersGestion.getHero().getLeft());
	 	bool collision = false;
	 	int blocCollision = 0;
		for(float h = 0; h <= charactersGestion.getHero().height(); h += 0.5)
			if(!collision)
				for(float coefx = -0.5; coefx <= 0.5; coefx += 0.5)
					if(!collision)
        				for(float coefz = -0.5; coefz <= 0.5; coefz += 0.5){
							if(!collision && world.getValue(glm::vec3(floor(nextPos.x+(charactersGestion.getHero().width()*coefx)), floor(nextPos.y+h), floor(nextPos.z+(charactersGestion.getHero().width()*coefz)) ))  > 0)
								collision = true;
							else if(world.getValue(glm::vec3(floor(nextPos.x+(charactersGestion.getHero().width()*coefx)), floor(nextPos.y+h), floor(nextPos.z+(charactersGestion.getHero().width()*coefz)) )) == 5){
								blocCollision = 5;
								collision = true;
							}
        				}

        if(!collision)
			for(size_t i=0; i < charactersGestion.getNumberOfNeutrals(); ++i)
				if(!collision && glm::distance2(charactersGestion.getHero().position(), charactersGestion.getNeutral(i).position()) < 10)
					for(float h = 0; h <= charactersGestion.getHero().height(); h += 0.5)
						if(!collision)
							for(float nh = 0; nh <= charactersGestion.getNeutral(i).height(); nh += 0.1)
								if(!collision && glm::distance2(glm::vec3(nextPos.x, nextPos.y+h, nextPos.z), glm::vec3(charactersGestion.getNeutral(i).position().x, charactersGestion.getNeutral(i).position().y + nh, charactersGestion.getNeutral(i).position().z)) <  pow((charactersGestion.getHero().width()*0.5+charactersGestion.getNeutral(i).width()*0.5), 2))
									collision = true;

		if(!collision)
			for(size_t i=0; i < charactersGestion.getNumberOfNeutrals(); ++i)
				if(!collision && glm::distance2(charactersGestion.getHero().position(), charactersGestion.getNeutral(i).position()) < 10)
					for(float h = 0; h <= charactersGestion.getHero().height(); h += 0.5)
						if(!collision)
							for(float nh = 0; nh <= charactersGestion.getNeutral(i).height(); nh += 0.1)
								if(!collision && glm::distance2(glm::vec3(nextPos.x, nextPos.y+h, nextPos.z), glm::vec3(charactersGestion.getNeutral(i).position().x, charactersGestion.getNeutral(i).position().y + nh, charactersGestion.getNeutral(i).position().z)) <  pow((charactersGestion.getHero().width()*0.5+charactersGestion.getNeutral(i).width()*0.5), 2))
									collision = true;

	    if(!collision){
			// nothing in frot of the hero, we can move
			charactersGestion.getHero().moveLeft(-1);
            if(SDL_GetTicks()%500 < 50)	sound.play(4);//moveSound.play(4);
		}else if(blocCollision == 5){
        	charactersGestion.getHero().moveFront(-1);
			world.clearAllChunksAndRefreshToOrigin();
			sound.play(11);
			charactersGestion.getHero().die();
		}
	}

	bool ControlCenter::gravityHero(){
		//std::cout << "mmmh, je voudrais tomber, je peux ?" << std::endl;
		//Hero& hero = charactersGestion.getHero();
		// Vérifier si on peut tomber plus bas
		glm::vec3 oldPosition = charactersGestion.getHero().position();
		bool res = charactersGestion.getHero().gravity();
		if(!res){
			charactersGestion.getHero().jump();
		}
		float widthHero = charactersGestion.getHero().width();
		glm::vec3 newPos = charactersGestion.getHero().position();
		bool collision = false;
		for(float h = 0; h <= charactersGestion.getHero().height(); h += 0.5){
			if(!collision){
				for(float coefx = -0.5; coefx <= 0.5; coefx += 0.5){
					if(!collision){
						for(float coefz = -0.5; coefz <= 0.5; coefz += 0.5){
							if(!collision && world.getValue(glm::vec3(floor(newPos.x+(widthHero*coefx)), floor(newPos.y+h), floor(newPos.z+(widthHero*coefz)) ))  > 0){
								if(world.getValue(glm::vec3(floor(newPos.x+(widthHero*coefx)), floor(newPos.y+h), floor(newPos.z+(widthHero*coefz)))) == 5 ){
									world.clearAllChunksAndRefreshToOrigin();
									sound.play(11);
									charactersGestion.getHero().die();
									return true;
								}else{
									collision = true;
								}
							}
						}
					}
				}
			}
		}

		if(!collision)
			for(size_t i=0; i < charactersGestion.getNumberOfMonsters(); ++i)
				if(!collision && glm::distance2(charactersGestion.getHero().position(), charactersGestion.getMonster(i).position()) < 10)
					for(float h = 0; h <= charactersGestion.getHero().height(); h += 0.5)
						if(!collision)
							for(float nh = 0; nh <= charactersGestion.getMonster(i).height(); nh += 0.1)
								if(!collision && glm::distance2(glm::vec3(newPos.x, newPos.y+h, newPos.z), glm::vec3(charactersGestion.getMonster(i).position().x, charactersGestion.getMonster(i).position().y + nh, charactersGestion.getMonster(i).position().z)) <  pow((charactersGestion.getHero().width()*0.5+charactersGestion.getMonster(i).width()*0.5), 2))
									collision = true;

		if(!collision)
			for(size_t i=0; i < charactersGestion.getNumberOfNeutrals(); ++i)
				if(!collision && glm::distance2(charactersGestion.getHero().position(), charactersGestion.getNeutral(i).position()) < 10)
					for(float h = 0; h <= charactersGestion.getHero().height(); h += 0.5)
						if(!collision)
							for(float nh = 0; nh <= charactersGestion.getNeutral(i).height(); nh += 0.1)
								if(!collision && glm::distance2(glm::vec3(newPos.x, newPos.y+h, newPos.z), glm::vec3(charactersGestion.getNeutral(i).position().x, charactersGestion.getNeutral(i).position().y + nh, charactersGestion.getNeutral(i).position().z)) <  pow((charactersGestion.getHero().width()*0.5+charactersGestion.getNeutral(i).width()*0.5), 2))
									collision = true;

		if(collision){
			if(res)
				charactersGestion.getHero().position(oldPosition);
			if(!res)
				charactersGestion.getHero().position(glm::vec3(oldPosition.x, floor(oldPosition.y), oldPosition.z));
			charactersGestion.getHero().stopJump();
		}
		return res;
	}

	void ControlCenter::jumpHero(){
		//std::cout << "mmmh, je voudrais sauter, je peux ?" << std::endl;
		//Hero& hero = charactersGestion.getHero();
		//TODO : vérifier si il n'est pas déja en l'air
		glm::vec3 oldPosition = charactersGestion.getHero().position();
		//bool isntFalling = gravityHero();
		// the character isn't falling nor jumping
		if(charactersGestion.getHero().position().y >= oldPosition.y && !charactersGestion.getHero().isJumping()){
			charactersGestion.getHero().position(oldPosition);
			glm::vec3 positionHero = charactersGestion.getHero().position();
			float heightHero = charactersGestion.getHero().height();
			float widthHero = charactersGestion.getHero().width();
			if(world.getValue(glm::vec3(floor(positionHero.x+widthHero*.5), floor(positionHero.y+0.12+heightHero), floor(positionHero.z+widthHero*.5))) <1
					&& world.getValue(glm::vec3(floor(positionHero.x-widthHero*.5), floor(positionHero.y+0.12+heightHero), floor(positionHero.z+widthHero*.5))) <1
					&& world.getValue(glm::vec3(floor(positionHero.x+widthHero*.5), floor(positionHero.y+0.12+heightHero), floor(positionHero.z-widthHero*.5))) <1
					&& world.getValue(glm::vec3(floor(positionHero.x-widthHero*.5), floor(positionHero.y+0.12+heightHero), floor(positionHero.z-widthHero*.5))) <1
					&&( world.getValue(glm::vec3(floor(positionHero.x+widthHero*.5), floor(positionHero.y-0.15), floor(positionHero.z+widthHero*.5))) >0
					|| world.getValue(glm::vec3(floor(positionHero.x-widthHero*.5), floor(positionHero.y-0.15), floor(positionHero.z+widthHero*.5))) >0
					|| world.getValue(glm::vec3(floor(positionHero.x+widthHero*.5), floor(positionHero.y-0.15), floor(positionHero.z-widthHero*.5))) >0
					|| world.getValue(glm::vec3(floor(positionHero.x-widthHero*.5), floor(positionHero.y-0.15), floor(positionHero.z-widthHero*.5))) >0))
				charactersGestion.getHero().jump();
				//moveSound.play(5);
			sound.play(5);
		}
	}

	void ControlCenter::moveNeutral(size_t index){
		glm::vec3 oldPos = charactersGestion.getNeutral(index).position();
		if(glm::distance2(glm::vec3(oldPos.x,0,oldPos.z), glm::vec3(charactersGestion.getHero().position().x, 0, charactersGestion.getHero().position().z)) < 8192){
			if(rand()%1000 == 0){
				switch(charactersGestion.getNeutral(index).type()){
					case cow:
						sound.play(6);
						//cowSound.play(6);
						break;

					case sheep:
						sound.play(7);
						//sheepSound.play(7);
						break;

					case pig:
						sound.play(8);
						//pigSound.play(8);
						break;

					default: // Chicken
						sound.play(9);
						//chickenSound.play(9);
						break;
				}
			}
			charactersGestion.getNeutral(index).move();
			bool collision = false;

			glm::vec3 neutralPosition = charactersGestion.getNeutral(index).position();

			for(float h = 0; h <= charactersGestion.getNeutral(index).height(); h += 0.2)
				if(!collision)
					for(float coefx = -0.5; coefx <= 0.5; coefx += 0.5)
						if(!collision)
							for(float coefz = -0.5; coefz <= 0.5; coefz += 0.5)
								if(!collision && world.getValue(glm::vec3(floor(neutralPosition.x+(charactersGestion.getNeutral(index).width()*coefx)), floor(neutralPosition.y+h), floor(neutralPosition.z+(charactersGestion.getNeutral(index).width()*coefz)) ))  > 0)
									collision = true;

			//Test de collision avec le héro
			if(!collision)
				for(float h = 0; h <= charactersGestion.getHero().height(); h += 0.5)
					if(!collision)
						for(float nh = 0; nh <= charactersGestion.getNeutral(index).height(); nh += 0.1)
							if(!collision)
								if(glm::distance2(glm::vec3(neutralPosition.x, neutralPosition.y+nh, neutralPosition.z), glm::vec3(charactersGestion.getHero().position().x, charactersGestion.getHero().position().y + h, charactersGestion.getHero().position().z)) <  pow((charactersGestion.getHero().width()*0.5+charactersGestion.getNeutral(index).width()*0.5), 2))
									collision = true;

			//test avec les monstres
			if(!collision)
				for(size_t i=0; i < charactersGestion.getNumberOfMonsters(); ++i)
					if(!collision)
						for(float h = 0; h <= charactersGestion.getMonster(i).height(); h += 0.1)
							if(!collision)
								for(float nh = 0; nh <= charactersGestion.getNeutral(index).height(); nh += 0.1)
									if(!collision && glm::distance2(glm::vec3(neutralPosition.x, neutralPosition.y+h, neutralPosition.z), glm::vec3(charactersGestion.getMonster(i).position().x, charactersGestion.getMonster(i).position().y + nh, charactersGestion.getMonster(i).position().z)) <  pow((charactersGestion.getNeutral(index).width()*0.5+charactersGestion.getMonster(i).width()*0.5), 2))
										collision = true;

			//test avec les autres neutrals
			if(!collision)
				for(size_t i=0; i < charactersGestion.getNumberOfNeutrals(); ++i)
					if(i != index && !collision)
						for(float h = 0; h <= charactersGestion.getNeutral(i).height(); h += 0.1)
							if(!collision)
								for(float nh = 0; nh <= charactersGestion.getNeutral(index).height(); nh += 0.1)
									if(!collision && glm::distance2(glm::vec3(neutralPosition.x, neutralPosition.y+h, neutralPosition.z), glm::vec3(charactersGestion.getNeutral(i).position().x, charactersGestion.getNeutral(i).position().y + nh, charactersGestion.getNeutral(i).position().z)) <  pow((charactersGestion.getNeutral(index).width()*0.5+charactersGestion.getNeutral(i).width()*0.5), 2))
										collision = true;

			if(collision){
				charactersGestion.getNeutral(index).position(oldPos);
				charactersGestion.getNeutral(index).stopJump();
			}
		}
	}

	void ControlCenter::gravityNeutral(size_t index){

		glm::vec3 oldPos = charactersGestion.getNeutral(index).position();
		if(glm::distance2(glm::vec3(oldPos.x,0,oldPos.z), glm::vec3(charactersGestion.getHero().position().x, 0, charactersGestion.getHero().position().z)) < 16384){

			if(charactersGestion.getNeutral(index).isJumping()){
				charactersGestion.getNeutral(index).jump();
			}

			charactersGestion.getNeutral(index).gravity();

			glm::vec3 neutralPosition = charactersGestion.getNeutral(index).position();

			bool collision = false;
			for(float h = 0; h <= charactersGestion.getNeutral(index).height(); h += 0.5)
				if(!collision)
					for(float coefx = -0.5; coefx <= 0.5; coefx += 0.5)
						if(!collision)
							for(float coefz = -0.5; coefz <= 0.5; coefz += 0.5)
								if(!collision && world.getValue(glm::vec3(floor(neutralPosition.x+(charactersGestion.getNeutral(index).width()*coefx)), floor(neutralPosition.y+h), floor(neutralPosition.z+(charactersGestion.getHero().width()*coefz)) ))  > 0)
									collision = true;

			//test avec les monstres
			if(!collision)
				for(size_t i=0; i < charactersGestion.getNumberOfMonsters(); ++i)
					if(!collision)
						for(float h = 0; h <= charactersGestion.getMonster(i).height(); h += 0.1)
							if(!collision)
								for(float nh = 0; nh <= charactersGestion.getNeutral(index).height(); nh += 0.1)
									if(!collision && glm::distance2(glm::vec3(neutralPosition.x, neutralPosition.y+h, neutralPosition.z), glm::vec3(charactersGestion.getMonster(i).position().x, charactersGestion.getMonster(i).position().y + nh, charactersGestion.getMonster(i).position().z)) <  pow((charactersGestion.getNeutral(index).width()*0.5+charactersGestion.getMonster(i).width()*0.5), 2))
										collision = true;

			//Test de collision avec le héro
			if(!collision)
				for(float h = 0; h <= charactersGestion.getHero().height(); h += 0.5)
					if(!collision)
						for(float nh = 0; nh <= charactersGestion.getNeutral(index).height(); nh += 0.1)
							if(!collision && glm::distance2(glm::vec3(neutralPosition.x, neutralPosition.y+nh, neutralPosition.z), glm::vec3(charactersGestion.getHero().position().x, charactersGestion.getHero().position().y + h, charactersGestion.getHero().position().z)) <  pow((charactersGestion.getHero().width()*0.5+charactersGestion.getNeutral(index).width()*0.5), 2))
								collision = true;

			//test avec les autres neutrals
			if(!collision)
				for(size_t i=0; i < charactersGestion.getNumberOfNeutrals(); ++i)
					if(i != index && !collision)
						for(float h = 0; h <= charactersGestion.getNeutral(i).height(); h += 0.1)
							if(!collision)
								for(float nh = 0; nh <= charactersGestion.getNeutral(index).height(); nh += 0.1)
									if(!collision && glm::distance2(glm::vec3(neutralPosition.x, neutralPosition.y+h, neutralPosition.z), glm::vec3(charactersGestion.getNeutral(i).position().x, charactersGestion.getNeutral(i).position().y + nh, charactersGestion.getNeutral(i).position().z)) <  pow((charactersGestion.getNeutral(index).width()*0.5+charactersGestion.getNeutral(i).width()*0.5), 2))
										collision = true;

			if(collision){
				if(!charactersGestion.getNeutral(index).isJumping()){
					charactersGestion.getNeutral(index).position(glm::vec3(oldPos.x, floor(oldPos.y), oldPos.z));
				}else{
					charactersGestion.getNeutral(index).position(oldPos);
				}
				charactersGestion.getNeutral(index).stopJump();
			}
		}
	}

	void ControlCenter::updatePositionCamera(){
		glm::vec3 direct = glm::normalize(charactersGestion.getHero().getDirection());
		glm::vec3 heroPosition = charactersGestion.getHero().position();
		firstPerson.setPosition(glm::vec3(heroPosition.x - direct.x*0.2,
											heroPosition.y+charactersGestion.getHero().height()*0.8, // position des yeux
											heroPosition.z - direct.z*0.2));
	}

	void ControlCenter::moveFrontMonster(size_t index){
		Monster& monster = charactersGestion.getMonster(index);
        float width = monster.width();
        float factor = monster.speed();
        glm::vec3 nextPos = monster.position() + factor * monster.getDirection();
        bool collision = false;
		for(float h = 0; h <= monster.height(); h += 0.1)
			if(!collision)
				for(float coefx = -0.5; coefx <= 0.5; coefx += 0.5)
					if(!collision)
						for(float coefz = -0.5; coefz <= 0.5; coefz += 0.5)
							if(!collision && world.getValue(glm::vec3(floor(nextPos.x+(width*coefx)), floor(nextPos.y+h), floor(nextPos.z+(width*coefz)) ))  > 0)
								collision = true;

		if(!collision)
			for(size_t i=0; i < charactersGestion.getNumberOfMonsters(); ++i)
				if(i != index && !collision && glm::distance2(nextPos, charactersGestion.getMonster(i).position()) < 10)
					for(float h = 0; h <= monster.height(); h += 0.1)
						if(!collision)
							for(float nh = 0; nh <= charactersGestion.getMonster(i).height(); nh += 0.1)
								if(!collision && glm::distance2(glm::vec3(nextPos.x, nextPos.y+h, nextPos.z), glm::vec3(charactersGestion.getMonster(i).position().x, charactersGestion.getMonster(i).position().y + nh, charactersGestion.getMonster(i).position().z)) <  pow((monster.width()*0.5+charactersGestion.getMonster(i).width()*0.5), 2))
									collision = true;

        //Test de collision avec le héro
        if(!collision)
            for(float h = 0; h <= charactersGestion.getHero().height(); h += 0.5)
                if(!collision)
                    for(float nh = 0; nh <= monster.height(); nh += 0.1)
                        if(!collision && glm::distance2(glm::vec3(nextPos.x, nextPos.y+nh, nextPos.z), glm::vec3(charactersGestion.getHero().position().x, charactersGestion.getHero().position().y + h, charactersGestion.getHero().position().z)) <  pow((charactersGestion.getHero().width()*0.5+monster.width()*0.5), 2))
                            collision = true;
		if(!collision)
			for(size_t i=0; i < charactersGestion.getNumberOfNeutrals(); ++i)
				if(!collision && glm::distance2(nextPos, charactersGestion.getNeutral(i).position()) < 10)
					for(float h = 0; h <= monster.height(); h += 0.2)
						if(!collision)
							for(float nh = 0; nh <= charactersGestion.getNeutral(i).height(); nh += 0.1)
								if(!collision && glm::distance2(glm::vec3(nextPos.x, nextPos.y+h, nextPos.z), glm::vec3(charactersGestion.getNeutral(i).position().x, charactersGestion.getNeutral(i).position().y + nh, charactersGestion.getNeutral(i).position().z)) <  pow((monster.width()*0.5+charactersGestion.getNeutral(i).width()*0.5), 2))
									collision = true;

        if(!collision){
                // nothing in frot of the monster, we can move
                monster.moveFront(1);
        }
	}

	void ControlCenter::gravityMonster(size_t index){

		glm::vec3 oldPos = charactersGestion.getMonster(index).position();
		if(glm::distance2(glm::vec3(oldPos.x,0,oldPos.z), glm::vec3(charactersGestion.getHero().position().x, 0, charactersGestion.getHero().position().z)) < 16384){

			if(charactersGestion.getMonster(index).isJumping()){
				charactersGestion.getMonster(index).jump();
			}

			charactersGestion.getMonster(index).gravity();

			glm::vec3 monsterPosition = charactersGestion.getMonster(index).position();

			bool collision = false;
			for(float coefx = -0.5; coefx <= 0.5; coefx += 0.5)
				if(!collision)
					for(float coefz = -0.5; coefz <= 0.5; coefz += 0.5)
						if(!collision && world.getValue(glm::vec3(floor(monsterPosition.x+(charactersGestion.getMonster(index).width()*coefx)), floor(monsterPosition.y-0.01), floor(monsterPosition.z+(charactersGestion.getMonster(index).width()*coefz)) ))  > 0)
							collision = true;

			//Test de collision avec le héro
			if(!collision)
				for(float h = 0; h <= charactersGestion.getHero().height(); h += 0.5)
					if(!collision)
						for(float nh = 0; nh <= charactersGestion.getMonster(index).height(); nh += 0.1)
							if(!collision && glm::distance2(glm::vec3(monsterPosition.x, monsterPosition.y+nh, monsterPosition.z), glm::vec3(charactersGestion.getHero().position().x, charactersGestion.getHero().position().y + h, charactersGestion.getHero().position().z)) <  pow((charactersGestion.getHero().width()*0.5+charactersGestion.getMonster(index).width()*0.5), 2))
								collision = true;

			//test avec les neutrals
			if(!collision)
				for(size_t i=0; i < charactersGestion.getNumberOfNeutrals(); ++i)
					if(!collision)
						for(float h = 0; h <= charactersGestion.getNeutral(i).height(); h += 0.1)
							if(!collision)
								for(float nh = 0; nh <= charactersGestion.getMonster(index).height(); nh += 0.1)
									if(!collision && glm::distance2(glm::vec3(monsterPosition.x, monsterPosition.y+h, monsterPosition.z), glm::vec3(charactersGestion.getNeutral(i).position().x, charactersGestion.getNeutral(i).position().y + nh, charactersGestion.getNeutral(i).position().z)) <  pow((charactersGestion.getMonster(index).width()*0.5+charactersGestion.getNeutral(i).width()*0.5), 2))
										collision = true;

			//test avec les autres monstres
			if(!collision)
				for(size_t i=0; i < charactersGestion.getNumberOfMonsters(); ++i)
					if(i != index && !collision)
						for(float h = 0; h <= charactersGestion.getMonster(i).height(); h += 0.1)
							if(!collision)
								for(float nh = 0; nh <= charactersGestion.getMonster(index).height(); nh += 0.1)
									if(!collision && glm::distance2(glm::vec3(monsterPosition.x, monsterPosition.y+h, monsterPosition.z), glm::vec3(charactersGestion.getMonster(i).position().x, charactersGestion.getMonster(i).position().y + nh, charactersGestion.getMonster(i).position().z)) <  pow((charactersGestion.getMonster(index).width()*0.5+charactersGestion.getMonster(i).width()*0.5), 2))
										collision = true;

			if(collision){
				if(!charactersGestion.getMonster(index).isJumping()){
					charactersGestion.getMonster(index).position(glm::vec3(oldPos.x, floor(oldPos.y), oldPos.z));
				}else{
					charactersGestion.getMonster(index).position(glm::vec3(oldPos.x, floor(oldPos.y)+0.1, oldPos.z));
				}
				charactersGestion.getMonster(index).stopJump();
			}
		}
	}


	void ControlCenter::jumpMonster(size_t index){
		//std::cout << "mmmh, je voudrais sauter, je peux ?" << std::endl;
		Monster& monster = charactersGestion.getMonster(index);
		//TODO : vérifier si il n'est pas déja en l'air
		glm::vec3 oldPosition = monster.position();
		//bool isntFalling = gravityHero();
		// the character isn't falling nor jumping
		if(monster.position().y >= oldPosition.y && !monster.isJumping()){
			float heightMonster = monster.height();
			float widthMonster = monster.width();
			if(world.getValue(glm::vec3(floor(oldPosition.x+widthMonster*.5), floor(oldPosition.y+0.12+heightMonster), floor(oldPosition.z+widthMonster*.5))) <1
					&& world.getValue(glm::vec3(floor(oldPosition.x-widthMonster*.5), floor(oldPosition.y+0.12+heightMonster), floor(oldPosition.z+widthMonster*.5))) <1
					&& world.getValue(glm::vec3(floor(oldPosition.x+widthMonster*.5), floor(oldPosition.y+0.12+heightMonster), floor(oldPosition.z-widthMonster*.5))) <1
					&& world.getValue(glm::vec3(floor(oldPosition.x-widthMonster*.5), floor(oldPosition.y+0.12+heightMonster), floor(oldPosition.z-widthMonster*.5))) <1
					&&( world.getValue(glm::vec3(floor(oldPosition.x+widthMonster*.5), floor(oldPosition.y-0.15), floor(oldPosition.z+widthMonster*.5))) >0
					|| world.getValue(glm::vec3(floor(oldPosition.x-widthMonster*.5), floor(oldPosition.y-0.15), floor(oldPosition.z+widthMonster*.5))) >0
					|| world.getValue(glm::vec3(floor(oldPosition.x+widthMonster*.5), floor(oldPosition.y-0.15), floor(oldPosition.z-widthMonster*.5))) >0
					|| world.getValue(glm::vec3(floor(oldPosition.x-widthMonster*.5), floor(oldPosition.y-0.15), floor(oldPosition.z-widthMonster*.5))) >0))
				monster.jump();
		}
	}


	void ControlCenter::iaMonster(size_t index){
		// TODO : define pattern for monsters
		if(glm::distance2(glm::vec3(charactersGestion.getMonster(index).position().x, 0, charactersGestion.getMonster(index).position().z), glm::vec3(charactersGestion.getHero().position().x, 0, charactersGestion.getHero().position().z)) <= pow(charactersGestion.getMonster(index).vision() ,2)){
			glm::vec3 heroPos = charactersGestion.getHero().position();
			Monster& monster = charactersGestion.getMonster(index);
			glm::vec3 pos = monster.position();
			monster.reload();
			glm::vec2 abscisse(1., 0.);
			glm::vec2 direction( pos.x - heroPos.x, pos.z - heroPos.z);
			float top = glm::dot(abscisse, direction);

			if(rand()%1000 == 0) 	sound.play(10);//monsterSound.play(10);

			float angle = acos(top/(sqrt(glm::dot(abscisse, abscisse))*sqrt(glm::dot(direction, direction))));
			if(direction.y >= 0)
				angle *= -1;

			monster.direction(angle-M_PI*0.5);
			float factor = (monster.speed()+monster.width()*0.5);
			if(glm::distance2(pos, heroPos) > 4.){
				glm::vec3 nextpos = pos+(factor*monster.getDirection());
				if((world.getValue(glm::vec3(floor(nextpos.x), floor(nextpos.y), floor(nextpos.z))) > 0 || world.getValue(glm::vec3(floor(nextpos.x), floor(nextpos.y+monster.height()), floor(nextpos.z))) > 0 )){
					jumpMonster(index);
				}
				moveFrontMonster(index);
			}else{
				//Attack
				if(monster.canAttack()){
					monster.attack();

					//attackedSound.play(1);
					charactersGestion.getHero().gainLife(-1.);
					if(charactersGestion.getHero().life()<=0){
						world.clearAllChunksAndRefreshToOrigin();
						sound.play(11);
						charactersGestion.getHero().die();
					}else{
						sound.play(1);
					}
				}
			}
		}
	}

	void ControlCenter::processOther(){
		if(changedDay > 0){
			--changedDay;
		}

		gravityHero();

		bool addNeutral = true;
		glm::vec3 heroPos = charactersGestion.getHero().position();

		for(size_t i=0; i <charactersGestion.getNumberOfNeutrals(); ++i){
			moveNeutral(i);
			gravityNeutral(i);
			//addNeutrals ?
			if(glm::distance2(glm::vec3(heroPos.x, 0, heroPos.z), glm::vec3(charactersGestion.getNeutral(i).position().x, 0, charactersGestion.getNeutral(i).position().z) ) < 4096 && addNeutral)
				addNeutral = false;
		}

		if(addNeutral){
        	neutral_type typeOfNeutral = neutral_type((std::rand())%4);
        	int randPosX = heroPos.x + int(std::rand())%32 - 16;
        	int randPosZ = heroPos.z + int(std::rand())%32 - 16;
        	 int y=(heroPos.y + 20 < 30 )? 30 : heroPos.y + 20;
        	 while(world.getValue(glm::vec3(randPosX, y, randPosZ)) == 0 && y > 0){
        	     --y;
        	 }
        	 float posX = randPosX + 0.5;
        	 float posZ = randPosZ + 0.5;
        	 if(y > 0)
        		 charactersGestion.getNeutral(charactersGestion.addNeutral(typeOfNeutral)).position(glm::vec3(posX, y+2 ,posZ));
        	 else
        		 charactersGestion.getNeutral(charactersGestion.addNeutral(typeOfNeutral)).position(glm::vec3(posX, 128 ,posZ));
		}

		bool addMonster = true;

		for(size_t i=0; i <charactersGestion.getNumberOfMonsters(); ++i){
			gravityMonster(i);
			iaMonster(i);
			//std::cerr<<charactersGestion.getMonster(i).position().x<<" "<<charactersGestion.getMonster(i).position().y<<" "<<charactersGestion.getMonster(i).position().z<<"\t\t"<<heroPos.x<<" "<<heroPos.y<<" "<<heroPos.z<<std::endl;
			//addMonsters ?
			if(glm::distance2(glm::vec3(heroPos.x, 0, heroPos.z), glm::vec3(charactersGestion.getMonster(i).position().x, 0, charactersGestion.getMonster(i).position().z) ) < 4096 && addMonster)
				addMonster = false;
		}

		if(addMonster){
        	monster_type typeOfMonster = monster_type((std::rand())%2);
        	int randPosX = heroPos.x + int(std::rand())%64 - 32;
        	int randPosZ = heroPos.z + int(std::rand())%64 - 32;
        	 int y = heroPos.y + 100;
        	 while(world.getValue(glm::vec3(randPosX, y, randPosZ)) <= 0 && y > 0){
        	     --y;
        	 }
        	 float posX = randPosX + 0.5;
        	 float posZ = randPosZ + 0.5;
        	 if(y > 0){
        		 //std::cerr<<"Création d'un monstre position : "<<randPosX<<", "<<y+1<<", "<<randPosZ<<std::endl;
        		 charactersGestion.getMonster(charactersGestion.addMonster(typeOfMonster)).position(glm::vec3(posX, y+1 ,posZ));
        	 }
        	 else
        		 charactersGestion.getMonster(charactersGestion.addMonster(typeOfMonster)).position(glm::vec3(posX, 128 ,posZ));
		}

		world.completeCreationOfChunk(floor(heroPos.x), floor(heroPos.z));
		world.manageChunkVector(floor(heroPos.x), floor(heroPos.z));

		updatePositionCamera();
	}

	void ControlCenter::volumeSound(int v){
		sound.volume(v);
	}

    void ControlCenter::muteSound(){
    	if(mute){
    		sound.volume(0);
	        /*attackedSound.volume(0);
	        attackSound.volume(0);
	        constructSound.volume(0);
	        moveSound.volume(0);
	        cowSound.volume(0);
	        sheepSound.volume(0);
	        pigSound.volume(0);
	        chickenSound.volume(0);
	        monsterSound.volume(0);*/
    	}else{
    		sound.mute();
	        /*attackedSound.mute();
	        attackSound.mute();
	        constructSound.mute();
	        moveSound.mute();
	        cowSound.mute();
	        sheepSound.mute();
	        pigSound.mute();
	        chickenSound.mute();
	        monsterSound.mute();*/
    	}
    	mute = !mute;
    }

	void ControlCenter::saveGame(){
		charactersGestion.getHero().saveHero();
	}

    // destructeur
    ControlCenter::~ControlCenter(){

    }
}
