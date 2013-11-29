#ifndef _IMINECRAFT_MONSTER_HPP_
#define _IMINECRAFT_MONSTER_HPP_

#include "iminecraft/characters/Character.hpp"
#include "iminecraft/characters/Hero.hpp"

namespace iminecraft {
	enum monster_type {meatboy, zombie, skeleton};

	class Monster : public iminecraft::Character{
	    private:
	    	// limite à partir de laquelle un monstre réagit ou pas à la présence de Steve
	    	float vision_reaction;
	    	monster_type m_type;
	    	int m_AS; // attack speed
	    	int waitAttack;

	    public:
	    	Monster(monster_type type = meatboy);
	    	~Monster();

	    	inline const float vision() {return vision_reaction;};
	    	inline void vision(float new_vision) { vision_reaction = new_vision;};
	    	inline const monster_type type() {return m_type;}

	    	inline bool canAttack(){return (waitAttack == 0);};
	    	inline void attack(){waitAttack = m_AS;};
	    	void reload();

	    	virtual void jump();

	    	/*void IA_gestion(Hero &Steve);
	    	void IA_attack(Hero &Steve);
	    	void IA_walkAround();*/


	};
}

#endif
