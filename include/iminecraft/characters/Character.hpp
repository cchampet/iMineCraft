#ifndef _IMINECRAFT_CHARACTER_HPP_
#define _IMINECRAFT_CHARACTER_HPP_

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace iminecraft {
	class Character{
	    protected:
	    	glm::vec3 m_Position;
	    	float m_maxLife;
	    	float m_currentLife;

	    	glm::vec3 m_FrontVec;
	    	glm::vec3 m_LeftVec;

	    	float m_Alpha;
	    	float m_Speed;
            
            float m_width;
            float m_height;

	    	// saute pendant 1 sec => value entre 0 et 40
	    	// à  terre à 0, ne pas appliquer de gravité tant que > 0
	    	// ne bouge plus en hauteur entre 60 et 90 mais reste déplaçable.
	    	size_t m_Jump;

	    public:
	        inline Character(const glm::vec3 &pos = glm::vec3(3.f, 128.f, 3.f), float angle = M_PI, float cLife = 10.f, float speed = .1f, float mLife = 10.f){
	            m_Position = pos;
	            m_Alpha = angle;
	            m_currentLife = cLife;
	            m_maxLife = mLife;
	            m_Speed = speed;
	            m_Jump = 0;
	            m_width = 0.5;
	            m_height = 1.5;
	            computeVectors();
	        }

	        virtual ~Character();

	        float gainLife(float points = 0.f);

	        inline const glm::vec3 position(){return m_Position;};
	        inline void position(const glm::vec3 &pos){m_Position = pos;};
	        inline const float life(){return m_currentLife;};
	        inline void life(const float l){m_currentLife = l;};
	        inline const float maxLife(){return m_maxLife;};
	        inline void maxLife(const float l){m_maxLife = l;};
	        inline const float direction(){return m_Alpha;};
	        inline void direction(const float phi){m_Alpha = phi; computeVectors();};
	        inline const float speed(){return m_Speed;};
	        inline void speed(const float s){m_Speed = s;};
            inline const float width(){return m_width;};
            inline void height(const float h){m_height = h;};
            inline const float height(){return m_height;};
            inline void width(const float w){m_width = w;};

	        // de base à 0, 0, -1
            inline void computeVectors(){m_FrontVec = compute(m_Alpha); m_LeftVec = compute(m_Alpha + M_PI*.5f);};
	        inline glm::vec3 compute(float angle){return glm::vec3(sin(angle), 0., cos(angle));};

	        inline glm::vec3 getDirection(){return m_FrontVec;};
	        inline glm::vec3 getLeft(){return m_LeftVec;};

	        //angle en degrés
	        inline void rotateLeft(float angle){m_Alpha += (angle*M_PI/180.f); computeVectors();};

	        virtual void jump();
	        void stopJump();
	        bool isJumping();

	        inline bool gravity(){
	        	if(!isJumping())	{m_Position.y -= .15f; return true;}
	        	return false;
	        };

	        // coeff = -1 or 1
	        void moveFront(int coeff);
	        void moveLeft(int coeff);
	};
}

#endif
