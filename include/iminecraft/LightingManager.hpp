#ifndef _IMINECRAFT_LIGHTINGMANAGER_HPP_
#define _IMINECRAFT_LIGHTINGMANAGER_HPP_

#include <glm/glm.hpp>
#include <cstdlib>
#include <iostream>
#include <GL/glew.h>
#include <string>
#include <sstream>
#include <vector>

#include <iminecraft/lighting.hpp>

using namespace std;

namespace iminecraft {
    class LightingManager{
        private:
        	int maxPointLightsCount;
        	int maxDistancePlayer;
            vector<PointLight> pointLightsVector;

        public:
            LightingManager(int maxPLCount, int maxDP){
            	maxPointLightsCount = maxPLCount;
            	maxDistancePlayer = maxDP;
            };
            ~LightingManager(){};

            void addPointLight(PointLight PL);
            void managePointLights(int xPositionPlayer, int yPositionPlayer, int zPositionPlayer);

            void sendPointLights(GLuint Program, glm::mat4 viewMatrix);
            void removePointLight(int xPosRegard, int yPosRegard, int zPosRegard);
    };
}

#endif
