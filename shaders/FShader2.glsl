#version 440 core

#define PLMAX 16


//------------global vars------------
float environment_amb = 0.3f;
float gamma = 2.2; 

//------------input vars------------
in vec3 fragPos;
in vec3 normal;


//-----------uniform vars----------
struct Material{
	vec3 color;
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
	vec3 position;
	vec3 attenuation;
	float intensity;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform DirectionalLight dir_light;
uniform PointLight pnt_light[PLMAX];
uniform int pl_count;
uniform vec3 view_pos;
uniform vec3 material;
uniform bool correct_gamma;


//-----------output vars----------
out vec4 FragColor;




//************************helper func declare************************
vec3 directionalLight(DirectionalLight, Material);
vec3 pointLight(PointLight, Material);



//************************main function************************
void main(){
	//calc final color
	vec3 final = vec3(0.0f, 0.0f, 0.0f);
	Material mat = {
		material,
		0.8f
	};
	final += directionalLight(dir_light, mat);
	for(int i=0; i<pl_count; ++i){
		final += pointLight(pnt_light[i], mat);
	}

	//assign final color to fragment
	if(correct_gamma){
		FragColor = vec4(pow(final, vec3(1.0/gamma)), 1.0);
	}else{
		FragColor = vec4(final, 1.0);
	}
}



//************************helper func definition************************
vec3 directionalLight(DirectionalLight light, Material material){

	vec3 ambient = environment_amb * light.ambient * material.color;

	vec3 lightDir = normalize(-light.direction);
	vec3 norm = normalize(normal);
	float diffuseStrength = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diffuseStrength * light.diffuse * material.color;

	vec3 viewDir = normalize(view_pos-fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	vec3 halfway = normalize(viewDir+lightDir);
	//float specularStrength = pow(max(dot(viewDir, reflectDir), 0.0f), 32.0f);
	float specularStrength = pow(max(dot(norm, halfway), 0.0f), 64.0f);
	vec3 specular = specularStrength * light.specular * material.color;

	vec3 finalLight = (ambient + diffuse + specular) * light.intensity; 

	//light.intensity is factored into the result differently for different types of casters (i.e. flashlight's intensity will have small effects on ambient factor of a target object, meaning the backside of will stay relatively dark even with a strong light)
	
	return finalLight;
}

vec3 pointLight(PointLight light, Material material){

	vec3 ambient = environment_amb * light.ambient * material.color;

	vec3 lightDir = normalize(light.position-fragPos);
	vec3 norm = normalize(normal);
	float diffuseStrength = max(dot(norm, lightDir), 0.0f);
	//vec3 diffuse = diffuseStrength * light.diffuse * pow(material.color, gamma);
	vec3 diffuse = diffuseStrength * light.diffuse * material.color;

	vec3 viewDir = normalize(view_pos-fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	vec3 halfway = normalize(lightDir+viewDir);
	//float specularStrength = pow(max(dot(viewDir, reflectDir), 0.0f), 32.0f);
	float specularStrength = pow(max(dot(norm, halfway), 0.0f), 64.0f);
	vec3 specular = specularStrength * light.specular * material.color;

	float distance = length(light.position - fragPos);
	float attenuation = 1.0f / (light.attenuation.x + light.attenuation.y*distance + light.attenuation.z * (correct_gamma ? (distance*distance) : distance));

	vec3 finalLight = (ambient + diffuse + specular) * attenuation * light.intensity; 

	//light.intensity is factored into the result differently for different types of casters (i.e. flashlight's intensity will have small effects on ambient factor of a target object, meaning the backside of will stay relatively dark even with a strong light)
	
	return finalLight;	
}
