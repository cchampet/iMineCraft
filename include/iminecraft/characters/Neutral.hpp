#ifndef _IMINECRAFT_NEUTRAL_HPP_
#define _IMINECRAFT_NEUTRAL_HPP_

#include "iminecraft/characters/Character.hpp"

namespace iminecraft {
	enum neutral_type {cow, sheep, pig, chicken};

	class Neutral : public iminecraft::Character{
	    private:
	    	neutral_type m_type;
	    public:

	    	Neutral(neutral_type type = chicken);

	    	inline const neutral_type type() {return m_type;}

	    	void move();
	    	virtual void jump();

	    	virtual ~Neutral(){};

	};
}

#endif
