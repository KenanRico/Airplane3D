#version 440 core

#define PLMAX 16


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
	vec3 position;
	vec3 attenuation;
	float intensity;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform DirectionalLight dir_light;
uniform PointLight pnt_light[PLMAX];
uniform int pl_count;
uniform vec3 view_pos;
float environment_amb = 0.4f;


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
		vec3(0.03,0.1,0.1),
		vec3(0.03,0.1,0.1),
		vec3(0.03,0.1,0.1),
		0.8f
	};
	final += directionalLight(dir_light, mat);
	for(int i=0; i<pl_count; ++i){
		final += pointLight(pnt_light[i], mat);
	}

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
	float specularStrength = pow(max(dot(viewDir, reflectDir), 0.0f), 4.0f);
	vec3 specular = specularStrength * light.specular * material.specular;

	vec3 finalLight = (ambient + diffuse + specular) * light.intensity; 

	//light.intensity is factored into the result differently for different types of casters (i.e. flashlight's intensity will have small effects on ambient factor of a target object, meaning the backside of will stay relatively dark even with a strong light)
	
	return finalLight;
}

vec3 pointLight(PointLight light, Material material){

	vec3 material_ambient_sum = vec3(0.0f, 0.0f, 0.0f);
	vec3 ambient = environment_amb * light.ambient * material.ambient;

	vec3 lightDir = normalize((light.position-fragPos));
	vec3 norm = normalize(normal);
	float diffuseStrength = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diffuseStrength * light.diffuse * material.ambient;

	vec3 viewDir = normalize(view_pos-fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float specularStrength = pow(max(dot(viewDir, reflectDir), 0.0f), 32.0f);
	vec3 specular = specularStrength * light.specular * material.specular;

	float distance = length(light.position - fragPos);
	float attenuation = 1.0f / (light.attenuation.x + light.attenuation.y*distance + light.attenuation.z*(distance*distance));

	vec3 finalLight = (ambient + diffuse + specular) * attenuation * light.intensity; 

	//light.intensity is factored into the result differently for different types of casters (i.e. flashlight's intensity will have small effects on ambient factor of a target object, meaning the backside of will stay relatively dark even with a strong light)
	
	return finalLight;	
}
