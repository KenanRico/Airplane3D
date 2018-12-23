#version 440 core

in vec3 fragPos;

uniform samplerCube skybox;

out vec4 FragColor;

void main(){
	FragColor = texture(skybox, fragPos);
}
