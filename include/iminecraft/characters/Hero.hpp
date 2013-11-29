#ifndef _IMINECRAFT_HERO_HPP_
#define _IMINECRAFT_HERO_HPP_

#include "iminecraft/characters/Character.hpp"
#include <SDL/SDL.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

namespace iminecraft {
	class Hero : public iminecraft::Character{
	    private:
			int m_InventoryType[10];
			int m_InventoryQty[10];
			size_t m_Index;

			// Va de 0 =< pas d'action à 20, les différents moments de l'action.
			size_t m_Action;

	    public:
	    	Hero(glm::vec3 position = glm::vec3(0., 64., 0.));
	    	virtual ~Hero();

	    	void saveHero();

	    	bool inventory(int type, int qte = 1){
	    		size_t index = 0;
	    		while(m_InventoryType[index] != type && index < 9 ){
	    			++ index;
	    		}
	    		if(m_InventoryType[index] == type){
	    			//std::cerr<<"Ajout dans l'inventaire position : "<<index<<std::endl;
	    			if((m_InventoryQty[index] + qte) > 0){
	    				m_InventoryQty[index] += qte;
	    				return true;
	    			}else if((m_InventoryQty[index] + qte) == 0){
	    				m_InventoryType[index] = 0;
	    				m_InventoryQty[index] = 0;
	    				return true;
	    			}else{
	    				return false;
	    			}
	    		} else if(qte>0){
	    			size_t index = 0;
	    			while(m_InventoryType[index] != 0 && index < 9){
	    				++ index;
	    			}
	    			if(m_InventoryType[index] == 0){
	    				//std::cerr<<index<<std::endl;
	    				m_InventoryType[index] = type;
	    				m_InventoryQty[index] = qte;
	    			}
	    		}
	    		return false;
	    	}

	    	const size_t currentMaterial();
	    	void currentMaterial(const size_t index);
	    	const size_t currentIndex();

	    	void swapInvetory(size_t indexA, size_t indexB);
	    	size_t getFromInventory(size_t index);

	    	size_t getQuantityOf(size_t index);

	    	void die();
	    	void clearInventory();

	    	//virtual void jump();

	    	void doAction();
	    	bool isDoingAction();
	    	size_t getAction();
	};
}

#endif
