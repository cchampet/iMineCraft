#include "iminecraft/characters/Monster.hpp"

namespace iminecraft {

	Monster::Monster(monster_type type):Character(glm::vec3(5.,87.,0.)) {

		m_type = type;
		switch(type){
			case zombie:
				m_maxLife = 5;
				m_currentLife = m_maxLife;
				m_AS = 80;
				vision_reaction = 32.;
				m_Speed = 0.02;
				break;

			default:
				m_maxLife = 3;
				m_currentLife = m_maxLife;
				m_AS = 40; // about 1 second (in frames time)
				vision_reaction = 8.;
				m_Speed = 0.1;
				m_height = 0.5;
				m_width = 0.5;
				break;
		}
		waitAttack = 0;

	}

	Monster::~Monster() {

	}

	void Monster::reload(){
    	if(waitAttack > 0){
    		--waitAttack;
    		if(waitAttack >= m_AS*0.5)
    			m_height -= 0.001;
    		else
    			m_height += 0.001;
    	}
	}

	void Monster::jump(){
		if(m_type == meatboy){
			Character::jump();
		}
	}

}
