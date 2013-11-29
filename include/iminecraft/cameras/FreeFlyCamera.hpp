/*
 * FreeFlyCamera.hpp
 *
 *  Created on: 5 déc. 2012
 *      Author: florent
 */

#ifndef FREEFLYCAMERA_HPP_
#define FREEFLYCAMERA_HPP_

#include <glm/glm.hpp>

namespace iminecraft {

	class FreeFlyCamera {
		protected :
			glm::vec3 m_Position;

			glm::vec3 m_FrontVector;
			glm::vec3 m_LeftVector;
			glm::vec3 m_UpVector;

			float m_fPhi;
			float m_fTheta;

		public:
			FreeFlyCamera();
			FreeFlyCamera(const FreeFlyCamera &FFC);

			void computeDirectionVectors();

			virtual void moveLeft(float t);
			virtual void moveFront(float t);

			virtual void rotateLeft(float alpha);
			virtual void rotateUp(float alpha);

			glm::vec3 getFrontVector();

			inline glm::vec3 getPosition(){ return m_Position; };
			inline glm::vec2 getAngles(){ return glm::vec2(m_fPhi, m_fTheta); };

			inline void setPosition(const glm::vec3 &pos){ m_Position = pos; };
			inline void setAngles(float phi, float theta){ m_fPhi = phi; m_fTheta = theta; computeDirectionVectors(); };
			inline void setCamera(glm::vec3 pos, float phi, float theta){this->setPosition(pos); this->setAngles(phi, theta);};

			glm::mat4 getViewMatrix() const;

			virtual ~FreeFlyCamera();
	};

}

#endif /* FREEFLYCAMERA_HPP_ */
