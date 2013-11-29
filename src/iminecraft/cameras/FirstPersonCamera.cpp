/*
 * FirstPersonCamera2.cpp
 *
 *  Created on: 6 déc. 2012
 *      Author: florent
 */

#include "iminecraft/cameras/FirstPersonCamera.hpp"

namespace iminecraft{

	/*FirstPersonCamera FirstPersonCamera::replace(const FreeFlyCamera &fpc){
		FirstPersonCamera FPcam;
		FPcam.m_FrontVector = fpc.m_FrontVector;
		FPcam.m_LeftVector = fpc.m_LeftVector;
		FPcam.m_Position = fpc.m_Position;
		FPcam.m_UpVector = fpc.m_UpVector;
		FPcam.m_fPhi = fpc.m_fPhi;
		FPcam.m_fTheta = fpc.m_fTheta;
		return FPcam;
	}*/

	void FirstPersonCamera::moveUp(float t){
		m_Position.y += t*m_UpVector.y;
	}

	void FirstPersonCamera::moveFront(float t){
		m_Position.x += t*m_FrontVector.x;
		m_Position.z += t*m_FrontVector.z;
	}

	void FirstPersonCamera::rotateUp(float alpha){
		alpha *= (M_PI/180.);
		m_fTheta = (alpha + m_fTheta > M_PI*1.5 - 0.01 ) ? M_PI*1.5 - 0.01 : (alpha + m_fTheta < M_PI*0.5 -0.01 ) ? M_PI*0.5 -0.01 : alpha + m_fTheta ;
		computeDirectionVectors();
	}

	FirstPersonCamera::~FirstPersonCamera() {
		// TODO Auto-generated destructor stub
	}
}
