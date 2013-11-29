#include "iminecraft/lighting.hpp"

MaterialUniform getMaterialLocations(const char* uniform, GLuint program){
    MaterialUniform uMaterial;
    uMaterial.KaLocation = glGetUniformLocation(program, (std::string(uniform) + ".Ka").c_str());
    uMaterial.KdLocation = glGetUniformLocation(program, (std::string(uniform) + ".Kd").c_str());
    uMaterial.KsLocation = glGetUniformLocation(program, (std::string(uniform) + ".Ks").c_str());
    uMaterial.shininessLocation = glGetUniformLocation(program, (std::string(uniform) + ".shininess").c_str());

    return uMaterial;
}
void sendMaterial(const Material& material, const MaterialUniform& materialUniform){
    glUniform3f(materialUniform.KaLocation, material.Ka.x, material.Ka.y, material.Ka.z);
    glUniform3f(materialUniform.KdLocation, material.Kd.x, material.Kd.y, material.Kd.z);
    glUniform3f(materialUniform.KsLocation, material.Ks.x, material.Ks.y, material.Ks.z);
    glUniform1i(materialUniform.shininessLocation, material.shininess);
}


DirectionalLightUniform getDirectionalLightLocations(const char* uniform, GLuint program){
    DirectionalLightUniform uDirectionalLight;
    uDirectionalLight.directionLocation = glGetUniformLocation(program, (std::string(uniform) + ".direction").c_str());
    uDirectionalLight.intensityLocation = glGetUniformLocation(program, (std::string(uniform) + ".intensity").c_str());
    return uDirectionalLight;
}
void sendDirectionalLight(const DirectionalLight& directionalLight, const DirectionalLightUniform& directionalLightUniform){
    glUniform3f(directionalLightUniform.directionLocation, directionalLight.direction.x, directionalLight.direction.y, directionalLight.direction.z);
    glUniform3f(directionalLightUniform.intensityLocation, directionalLight.intensity.x, directionalLight.intensity.y, directionalLight.intensity.z);
}


PointLightUniform getPointLightLocations(const char* uniform, GLuint program){
    PointLightUniform uPointLight;
    uPointLight.positionLocation = glGetUniformLocation(program, (std::string(uniform) + ".position").c_str());
    uPointLight.intensityLocation = glGetUniformLocation(program, (std::string(uniform) + ".intensity").c_str());
    return uPointLight;
}
void sendPointLight(const PointLight& pointLight, const PointLightUniform& pointLightUniform){
    glUniform3f(pointLightUniform.positionLocation, pointLight.position.x, pointLight.position.y, pointLight.position.z);
    glUniform3f(pointLightUniform.intensityLocation, pointLight.intensity.x, pointLight.intensity.y, pointLight.intensity.z);
}
