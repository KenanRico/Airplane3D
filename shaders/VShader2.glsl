#version 440 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 light_space_matrix;

out vec3 fragPos;
out vec3 normal;
out vec4 light_space_frag_pos;

void main(){
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	fragPos = vec3(model * vec4(aPos, 1.0f));
	normal = vec3(model * vec4(aNormal, 0.0f));
	light_space_frag_pos = light_space_matrix * vec4(fragPos, 1.0);
}

//out vec3 fragPos;
//out vec3 normal;
//out vec2 texCoord;

//void main(){
//	gl_Position = projection * view * model * vec4(aPos, 1.0f);
//	fragPos = vec3(model * vec4(aPos, 1.0f));
//	normal = vec3(model * vec4(aNormal, 0.0f));
//	texCoord = aTex;
//}
