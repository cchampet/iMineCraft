#version 330

struct Material{ 
    vec3 Ka, Kd, Ks; // ambiante, diffuse, spéculaire
    float shininess; // brilliance du materiau
};
struct DirectionalLight{
  vec3 direction, intensity;
};
struct PointLight{
  vec3 position, intensity;
};


#define MAX_DIRECTIONAL_LIGHT_COUNT 16
uniform DirectionalLight uDirectionalLights[MAX_DIRECTIONAL_LIGHT_COUNT];
uniform int uDirectionalLightCount = 0;

#define MAX_POINT_LIGHT_COUNT 16
uniform PointLight uPointLights[MAX_POINT_LIGHT_COUNT];
uniform int uPointLightCount = 0;

in vec2 vTexCoords;
in vec3 vNormal;
in vec4 vPosition;

uniform sampler2D uTexture;
uniform sampler2D uTexture2;
uniform int lightActivated = 1;
uniform int isSkybox = 0;
uniform int nightActivated = 0;

out vec4 fFragColor;




uniform Material uMaterial;
uniform DirectionalLight uDirectionalLight;

vec3 getDirectionalLight(){
    vec3 ambientLight = uMaterial.Ka;
    vec3 diffuseLight = uMaterial.Kd*max(dot(vNormal, -normalize(uDirectionalLight.direction)),0.f);
    vec3 specularLight = uMaterial.Ks*pow(
                                            max(
                                                0.0f, 
                                                dot(
                                                    vec3(vPosition), 
                                                    reflect(
                                                            normalize(uDirectionalLight.direction),
                                                            vNormal
                                                            )
                                                    )
                                                ), 
                                            uMaterial.shininess
                                        );
    vec3 L = uDirectionalLight.intensity*(ambientLight + diffuseLight + specularLight);
    return L;
}

vec3 calculPointLight(PointLight pointLight){
    float distanceLumierePoint = pow(vPosition.x-pointLight.position.x, 2) + pow(vPosition.y-pointLight.position.y, 2) + pow(vPosition.z-pointLight.position.z, 2);
    distanceLumierePoint *= 0.1;
    vec3 directionLumierePoint = normalize(vec3(vPosition) - pointLight.position);

    vec3 ambientLight = uMaterial.Ka;
    vec3 diffuseLight = (uMaterial.Kd/ distanceLumierePoint)*max(dot(vNormal, -directionLumierePoint), 0.f);
    vec3 specularLight = (uMaterial.Ks/ distanceLumierePoint)*pow(
                                                    max(
                                                        0.0f, 
                                                        dot(
                                                            vec3(vPosition), 
                                                            reflect(
                                                                    directionLumierePoint,
                                                                    vNormal
                                                                    )
                                                            )
                                                        ), 
                                                    uMaterial.shininess
                                                );
    //vec3 L = pointLight.intensity*(ambientLight + diffuseLight + specularLight);
    
    if(nightActivated > 0){
    	// night
	    if(diffuseLight.x > 0.03) diffuseLight.x = 0.03;
	    if(diffuseLight.y > 0.03) diffuseLight.y = 0.03;
	    if(diffuseLight.z > 0.03) diffuseLight.z = 0.03;
	    if(specularLight.x > 0.03) specularLight.x = 0.03;
	    if(specularLight.y > 0.03) specularLight.y = 0.03;
	    if(specularLight.z > 0.03) specularLight.z = 0.03;
    }else{
    	// day
    	if(diffuseLight.x > 0.02) diffuseLight.x = 0.02;
	    if(diffuseLight.y > 0.02) diffuseLight.y = 0.02;
	    if(diffuseLight.z > 0.02) diffuseLight.z = 0.02;
	    if(specularLight.x > 0.02) specularLight.x = 0.02;
	    if(specularLight.y > 0.02) specularLight.y = 0.02;
	    if(specularLight.z > 0.02) specularLight.z = 0.02;
    }
    vec3 L = pointLight.intensity*(diffuseLight + specularLight);
    return L;
}

void main() {

    // Variable pour Fog
    float density = 0.005;
    const float log2 = 1.442695;
    float z = vPosition.z / vPosition.w;    
    //


	vec4 texture_1 = texture(uTexture, vTexCoords);
	vec4 texture_2 = texture(uTexture2, vTexCoords);
	
	float night = 0;
	
    vec4 factorLight = vec4(1,1,1,1);
	if(lightActivated == 1){
        vec3 sumPointLight = vec3(0.f);
        for(int i=0; i < uPointLightCount; i++){
            sumPointLight += calculPointLight(uPointLights[i]);
        }
		
		if(nightActivated > 0){
			// night
			factorLight = vec4(sumPointLight, 1.f);
		}else{
			// day
			factorLight = vec4(getDirectionalLight() + sumPointLight, 1.f);
		}
	}else{
		if(isSkybox > 0 && nightActivated > 0){
			// skybox
			night = 1;
		}
        density = 0.000005;
    }

    // Calcul pour Fog
    float fogFactor = exp2(-density * density * z * z * log2);
    fogFactor = clamp(fogFactor, 0.0, 1.0);
    vec4 fog_color = vec4(1,1,1,1);
    //	

    fFragColor = mix(fog_color, factorLight*((texture_1*(1-night)) + (texture_2*night)), fogFactor);
}
