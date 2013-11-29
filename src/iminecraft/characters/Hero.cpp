#include "iminecraft/characters/Hero.hpp"

using namespace std;

namespace iminecraft {
	Hero::Hero(glm::vec3 position): Character(position){
		for(size_t i=0; i< 10; ++i){
			m_InventoryQty[i] = 0;
			m_InventoryType[i] = 0;
			m_Index = 0;
		}

		m_InventoryQty[9] = 10;
		m_InventoryType[9] = 8;

		ifstream file("files/hero.sav");
		size_t tempType, tempQty;
		size_t i = 0;
		float x, y, z;
		float life;

		if(file){
			file >> x;
			file >> y;
			file >> z;
			m_Position = glm::vec3(x, y, z);

			file >> life;
			if(life > 0 && life <= 10)
				m_currentLife = life;

			while(file >> tempType && i < 10){
				file >> tempQty;
				m_InventoryQty[i] = tempQty;
				m_InventoryType[i] = tempType;
				++ i;
			}
		}

	}

	void Hero::saveHero(){
		ofstream file("files/hero.sav");

		if(!file.good()) {
			cerr<<"Impossible de créer le fichier de sauvegarde."<<endl;
			throw ofstream::failure("Save Hero: fail to create file.");
		}

		file << m_Position.x << " " << m_Position.y << " " << m_Position.z << endl;
		file << m_currentLife <<std::endl;
		for(size_t i = 0; i < 10 ; ++i){
			file << m_InventoryType[i] << " " << m_InventoryQty[i] << endl;
		}
		file.close();
	}

	const size_t Hero::currentMaterial(){
		return m_InventoryType[m_Index];
	}

	void Hero::currentMaterial(const size_t index){
		m_Index = index;
	}

	const size_t Hero::currentIndex(){
		return m_Index;
	}

	void Hero::swapInvetory(size_t indexA, size_t indexB){
		size_t tmpQty = m_InventoryQty[indexA];
		size_t tmpType = m_InventoryType[indexA];
		m_InventoryQty[indexA] = m_InventoryQty[indexB];
		m_InventoryType[indexA] = m_InventoryType[indexB];
		m_InventoryQty[indexB] = tmpQty;
		m_InventoryType[indexB] = tmpType;
	}

	size_t Hero::getFromInventory(size_t index){
		if(m_InventoryQty[index] > 0)
			return m_InventoryType[index];

		return 0;
	}

	size_t Hero::getQuantityOf(size_t index){
		return m_InventoryQty[index];
	}

	void Hero::doAction(){
		m_Action = (m_Action > 9) ? 0 : m_Action + 1;
	}

	bool Hero::isDoingAction(){
		if(m_Action > 0)	return true;
		return false;
	}

	size_t Hero::getAction(){
		if(m_Action > 0)	doAction();
		return m_Action;
	}

	/*void Hero::jump(){
		this->Character::jump();
	}*/

	void Hero::die(){
		clearInventory();
		SDL_Delay(1000);
		m_currentLife = m_maxLife;
		m_Position = glm::vec3(0., 100., 0.);
	}

	void Hero::clearInventory(){
		for(size_t i=0; i < 10; ++i){
			if(m_InventoryType[i] != 8){
				m_InventoryType[i] = 0;
				m_InventoryQty[i] = 0;
			}
		}
	}

	Hero::~Hero(){

	}
}
