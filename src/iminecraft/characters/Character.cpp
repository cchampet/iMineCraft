#include "iminecraft/characters/Character.hpp"

namespace iminecraft {
    /* Constructeur
    Character::Character(){
    	m_Position = glm::vec3(0.f, 128.f, 0.f);
    	m_maxLife = 10.f;
    	m_currentLife = m_maxLife;

    	m_Alpha = M_PI;

    	m_Speed = 1.f;
    }*/

    float Character::gainLife(float points){
	    m_currentLife += points;
	    m_currentLife = (m_currentLife > m_maxLife) ? m_maxLife : ((m_currentLife < 0) ? 0 : m_currentLife);
	    return m_currentLife;
	}

	void Character::moveFront(int coeff){
		m_Position += m_Speed*coeff*m_FrontVec;
	}
	void Character::moveLeft(int coeff){
		m_Position -= m_Speed*coeff*m_LeftVec;
	}

	bool Character::isJumping(){
		if(m_Jump > 0)
			return true;
		return false;
	}

	void Character::stopJump(){
		m_Jump = 0;
	}

	void Character::jump(){
		m_Jump = (m_Jump>22)? 0 : m_Jump + 1;
		if(m_Jump <= 20 && m_Jump > 0){
			m_Position.y += .12;
		}
	}

    // destructeur
    Character::~Character(){

    }
}
