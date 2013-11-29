#include "iminecraft/LightingManager.hpp"

namespace iminecraft {
    void LightingManager::addPointLight(PointLight PL){
        if(pointLightsVector.size() < (unsigned int)maxPointLightsCount){
            pointLightsVector.push_back(PL);
        }else{
            cout << "Nombre de lumières max atteint" << endl;
        }
    }

    void LightingManager::managePointLights(int xPositionPlayer, int yPositionPlayer, int zPositionPlayer){
        for (unsigned int i = 0; i < pointLightsVector.size(); ++i){
            float distanceLightPlayer = abs(pointLightsVector.at(i).position.x - xPositionPlayer) + abs(pointLightsVector.at(i).position.y - yPositionPlayer) + abs(pointLightsVector.at(i).position.z - zPositionPlayer);
            if(distanceLightPlayer > maxDistancePlayer){
                pointLightsVector.erase(pointLightsVector.begin()+i);
                break;
            }
        }
    }

    void LightingManager::sendPointLights(GLuint Program, glm::mat4 viewMatrix){
        for(unsigned int i = 0; i < pointLightsVector.size(); ++i){
            stringstream ss_position;
            ss_position << "uPointLights[" << i << "].position";
            glm::vec3 positionLight = glm::vec3(viewMatrix*glm::vec4(pointLightsVector.at(i).position.x,pointLightsVector.at(i).position.y,pointLightsVector.at(i).position.z,1.f));
            glUniform3f(glGetUniformLocation(Program, ss_position.str().c_str()), positionLight.x, positionLight.y, positionLight.z);
            stringstream ss_intensity;
            ss_intensity << "uPointLights[" << i << "].intensity";
            glUniform3f(glGetUniformLocation(Program, ss_intensity.str().c_str()), pointLightsVector.at(i).intensity.x, pointLightsVector.at(i).intensity.x, pointLightsVector.at(i).intensity.x);
        }

        glUniform1i(glGetUniformLocation(Program, "uPointLightCount"), pointLightsVector.size());
    }

    void LightingManager::removePointLight(int xPosRegard, int yPosRegard, int zPosRegard){
        for(unsigned int i = 0; i < pointLightsVector.size(); ++i){
            if(pointLightsVector.at(i).position.x == xPosRegard+0.5f 
                && pointLightsVector.at(i).position.y == yPosRegard+0.5f
                && pointLightsVector.at(i).position.z == zPosRegard+0.5f){
                pointLightsVector.erase(pointLightsVector.begin()+i);
                break;
            }
        }
    }
}
