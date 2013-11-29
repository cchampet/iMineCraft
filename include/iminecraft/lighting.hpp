#ifndef _IMINECRAFT_LIGHTING_HPP_
#define _IMINECRAFT_LIGHTING_HPP_

#include <glm/glm.hpp>
#include <cstdlib>
#include <GL/glew.h>
#include <string>


/**
 * Structure Material - define the material of each object we will render
 */
struct Material{
    glm::vec3 Ka, Kd, Ks; // ambiante, diffuse, spéculaire
    float shininess; // brilliance du materiau
};
struct MaterialUniform{
	GLint KaLocation, KdLocation, KsLocation, shininessLocation;
};
MaterialUniform getMaterialLocations(const char* uniform, GLuint program);
void sendMaterial(const Material& material, const MaterialUniform& materialUniform);

/**
 * Directional Light - define a directional Light (no position, only direction)
 */
struct DirectionalLight{
    glm::vec3 direction, intensity;
};
struct DirectionalLightUniform{
	GLint directionLocation, intensityLocation;
};
DirectionalLightUniform getDirectionalLightLocations(const char* uniform, GLuint program);
void sendDirectionalLight(const DirectionalLight& directionalLight, const DirectionalLightUniform& directionalLightUniform);

/**
 * Point Light - define a Point Light with a position but no direction, only intensity
 */
struct PointLight{
    glm::vec3 position, intensity;
};
struct PointLightUniform{
	GLint positionLocation, intensityLocation;
};
PointLightUniform getPointLightLocations(const char* uniform, GLuint program);
void sendPointLight(const PointLight& pointLight, const PointLightUniform& pointLightUniform);

#endif
