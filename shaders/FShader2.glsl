#version 440 core

//------------input vars------------
in vec3 fragPos;
in vec3 normal;


//-----------uniform vars----------
struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
struct DirectionalLight{
	vec3 direction;
	float intensity;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
struct PointLight{
	vec position;
	vec3 attenuation;
	float intensity;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform DirectionalLight dir_light;
uniform DirectionalLight pnt_light;
uniform vec3 view_pos;
float environment_amb = 0.4f;


//-----------uniform vars----------
out vec4 FragColor;




//************************helper func declare************************
vec3 directionalLight(DirectionalLight, Material);
vec3 pointLight(DirectionalLight, Material);



//************************main function************************
void main(){
	//calc final color
	vec3 final = vec3(0.0f, 0.0f, 0.0f);
	//DirectionalLight dl = {

	//};
	Material mat = {
		vec3(0.2,0.2,0.2),
		vec3(0.25,0.3,0.3),
		vec3(0.3,0.4,0.4),
		0.8f
	};
	final += directionalLight(dir_light, mat) + pointLight(pnt_light, mat);

	//assign final color to fragment
	FragColor = vec4(final, 1.0);
}



//************************helper func definition************************
vec3 directionalLight(DirectionalLight light, Material material){

	vec3 ambient = environment_amb * light.ambient * material.ambient;

	vec3 lightDir = normalize(-light.direction);
	vec3 norm = normalize(normal);
	float diffuseStrength = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diffuseStrength * light.diffuse * material.diffuse;

	vec3 viewDir = normalize(view_pos-fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float specularStrength = pow(max(dot(viewDir, reflectDir), 0.0f), 8.0f);
	vec3 specular = specularStrength * light.specular * material.specular;

	vec3 finalLight = (ambient + diffuse + specular) * light.intensity; 

	//light.intensity is factored into the result differently for different types of casters (i.e. flashlight's intensity will have small effects on ambient factor of a target object, meaning the backside of will stay relatively dark even with a strong light)
	
	return finalLight;
}

vec3 pointLight(PointLight light, Material material){

	//implementation

	return vec3(0.0,0.0,0.0);
}
