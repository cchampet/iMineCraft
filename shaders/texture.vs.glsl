#version 330

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aTexCoords;

uniform mat4 uProjectionMatrix = mat4(1.f);  
uniform mat4 uModelViewMatrix = mat4(1.f);
uniform mat3 uNormalMatrix = mat3(1.f);

out vec2 vTexCoords;
out vec3 vNormal;
out vec4 vPosition;

void main() {
	vTexCoords = aTexCoords;

	vNormal = normalize(uNormalMatrix * aVertexNormal);
	vPosition = uModelViewMatrix * vec4(aVertexPosition, 1.f);
	gl_Position =  uProjectionMatrix * vPosition;
}
