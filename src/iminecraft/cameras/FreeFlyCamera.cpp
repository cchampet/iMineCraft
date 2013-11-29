/*
 * FreeFlyCamera.cpp
 *
 *  Created on: 5 déc. 2012
 *      Author: florent
 */

#include "iminecraft/cameras/FreeFlyCamera.hpp"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace iminecraft {

	FreeFlyCamera::FreeFlyCamera() {
		// TODO Auto-generated constructor stub
		m_Position = glm::vec3(0., 0., 0.);
		m_fPhi = M_PI;
		m_fTheta = 0.;
		computeDirectionVectors();
	}

	FreeFlyCamera::FreeFlyCamera(const FreeFlyCamera &FFC){
		this->m_Position = FFC.m_Position;
		this->m_fPhi = FFC.m_fPhi;
		this->m_fTheta = FFC.m_fTheta;
		computeDirectionVectors();
	}

	void FreeFlyCamera::computeDirectionVectors(){
		m_FrontVector = glm::vec3(cos(m_fTheta)*sin(m_fPhi), sin(m_fTheta), cos(m_fTheta)*cos(m_fPhi));
		m_LeftVector = glm::vec3(sin(m_fPhi+M_PI*0.5), 0., cos(m_fPhi+M_PI*0.5));
		m_UpVector = glm::cross(m_LeftVector, m_FrontVector);
	}

	void FreeFlyCamera::moveLeft(float t){
		m_Position += t*m_LeftVector;
	}

	void FreeFlyCamera::moveFront(float t){
		m_Position += t*m_FrontVector;
	}

	glm::vec3 FreeFlyCamera::getFrontVector(){
		return m_FrontVector;
	}

	void FreeFlyCamera::rotateLeft(float alpha){
		alpha = (alpha > M_PI*.49) ? M_PI*.49 : (alpha < -M_PI*0.49) ? -M_PI*.49 : alpha ;
		alpha *= (M_PI/180.);
		m_fPhi += alpha;
		computeDirectionVectors();
	}

	void FreeFlyCamera::rotateUp(float alpha){
		alpha = (alpha > M_PI*.49) ? M_PI*.49 : (alpha < -M_PI*0.49) ? -M_PI*.49 : alpha ;
		alpha *= (M_PI/180.);
		m_fTheta += alpha;
		computeDirectionVectors();
	}

	glm::mat4 FreeFlyCamera::getViewMatrix() const{
		return glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
	}

	FreeFlyCamera::~FreeFlyCamera() {
		// TODO Auto-generated destructor stub
	}

}
