#version 440 core

#define PLMAX 16


//------------global vars------------
float environment_amb = 0.3f;
float gamma = 2.2; 

//------------input vars------------
in vec3 fragPos;
in vec3 normal;
in vec4 light_space_frag_pos;


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
uniform sampler2D shadow_map;
uniform bool correct_gamma;
uniform bool blinn_phong;
uniform bool lighting;


//-----------output vars----------
out vec4 FragColor;




//************************helper func declare************************
float getShadow(vec3, vec3);
vec3 directionalLight(DirectionalLight, Material);
vec3 pointLight(PointLight, Material);




//************************main function************************
void main(){
	//assign final color to fragment
	vec3 final = vec3(0.0f, 0.0f, 0.0f);
	if(lighting){
		Material mat = {
			material,
			0.8f
		};
		final += directionalLight(dir_light, mat);
		for(int i=0; i<pl_count; ++i){
			final += pointLight(pnt_light[i], mat);
		}
	}else{
		final = material;
	}
	if(correct_gamma){
		FragColor = vec4(pow(final, vec3(1.0/gamma)), 1.0);
	}else{
		FragColor = vec4(final, 1.0);
	}
}



//************************helper func definition************************
float getShadow(vec3 normal, vec3 light_dir){
	float shadow = 0.0f;
	vec3 projection_coords = light_space_frag_pos.xyz / light_space_frag_pos.w * 0.5f +0.5f;
	float current_depth = projection_coords.z;
	if(current_depth<=1.0f){
		//float closest_depth = texture(shadow_map, projection_coords.xy).r;
		vec2 texel_size = 1.0 / textureSize(shadow_map, 0);
		for(int x=-1; x<2; ++x){
			for(int y=-1; y<2; ++y){
				float pcf_depth = texture(shadow_map, projection_coords.xy+vec2(x,y)*texel_size).r;
				shadow += (current_depth-max(0.05*(1.0-dot(normal, light_dir)), 0.005)>pcf_depth) ? 1.0f : 0.0f;
			}
		}
		shadow /= 9.0;
	}
	return shadow;
}

vec3 directionalLight(DirectionalLight light, Material material){

	vec3 ambient = environment_amb * light.ambient * material.color;

	vec3 lightDir = normalize(-light.direction);
	vec3 norm = normalize(normal);
	float diffuseStrength = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diffuseStrength * light.diffuse * material.color;

	vec3 viewDir = normalize(view_pos-fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	vec3 halfway = normalize(viewDir+lightDir);
	float angle = blinn_phong ? dot(norm, halfway) : dot(viewDir, reflectDir);
	float specularStrength = pow(max(angle, 0.0f), 64.0f);
	vec3 specular = specularStrength * light.specular * material.color;

	float shadow = getShadow(norm, lightDir);

	vec3 finalLight = (ambient + (1.0f-shadow)*(diffuse + specular)) * light.intensity; 

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
	float angle = blinn_phong ? dot(norm, halfway) : dot(viewDir, reflectDir);
	float specularStrength = pow(max(angle, 0.0f), 64.0f);
	vec3 specular = specularStrength * light.specular * material.color;

	float distance = length(light.position - fragPos);
	float attenuation = 
		1.0f / (light.attenuation.x + light.attenuation.y*distance + light.attenuation.z * (correct_gamma ? (distance*distance) : distance));

	vec3 finalLight = (ambient + diffuse + specular) * attenuation * light.intensity; 

	//light.intensity is factored into the result differently for different types of casters (i.e. flashlight's intensity will have small effects on ambient factor of a target object, meaning the backside of will stay relatively dark even with a strong light)
	
	return finalLight;	
}
