/*
 * FirstPersonCamera2.hpp
 *
 *  Created on: 6 déc. 2012
 *      Author: florent
 */

#ifndef FIRSTPERSONCAMERA_HPP_
#define FIRSTPERSONCAMERA_HPP_

#include "FreeFlyCamera.hpp"

namespace iminecraft {

	class FirstPersonCamera : public FreeFlyCamera {

		public:
			inline FirstPersonCamera() : FreeFlyCamera(){};

			//FirstPersonCamera replace(const FreeFlyCamera &fpc);

			void moveUp(float t); // utiliser pour les sauts (fonction de y)
			virtual void moveFront(float t);

			virtual void rotateUp(float alpha);

			virtual ~FirstPersonCamera();
	};

}

#endif /* FIRSTPERSONCAMERA2_HPP_ */
