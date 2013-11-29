#include <cstdlib>
#include <iostream>

#include "iminecraft/characters/Neutral.hpp"

namespace iminecraft {

	Neutral::Neutral(neutral_type type):Character(glm::vec3(0.,128.,0.)){
		m_type = type;
		switch(m_type){
		case pig :
			m_width = 0.8;
			m_height = 0.9;
			m_Speed = 0.01;
			m_maxLife = 7;
			//std::cerr<<"Création d'un cochon."<<std::endl;
			break;

		case sheep:
			m_width = 0.5;
			m_height = 0.6;
			m_Speed = 0.05;
			m_maxLife = 3;
			//std::cerr<<"Création d'un mouton."<<std::endl;
			break;

		case cow:
			m_width = 1.;
			m_height = 1.3;
			m_Speed = 0.01;
			m_maxLife = 5;
			//std::cerr<<"Création d'une vache."<<std::endl;
			break;

		default: //Chicken
			m_width = 0.2;
			m_height = 0.3;
			m_Speed = 0.02;
			m_maxLife = 1;
			//std::cerr<<"Création d'un poulet."<<std::endl;
			break;
		}
		m_currentLife = m_maxLife;
	}

	void Neutral::jump(){
		switch(m_type){
			case sheep :
				Character::jump();
				break;

			case chicken :
				Character::jump();
				break;

			case cow :
				m_Jump = (m_Jump>12)? 0 : m_Jump + 1;
				if(m_Jump <= 10 && m_Jump > 0){
					m_Position.y += .08;
				}
				break;

			default:
				break;
		}
	}

	void Neutral::move() {

		// mouvement front (90%)
		moveFront(1);

		// mouvement rotate left (20%)
		if (rand()%(100) == 1) {
			int degres = (rand()%(180))-90;
			rotateLeft(degres);
		}
		// jump (0,01%)
		if(rand()%(1000) == 1) jump();
	}
}
