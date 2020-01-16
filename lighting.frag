#version 330 core
struct Material 
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D tex;
uniform float sample;
uniform float sampleCount;
uniform float textureWidth;

// Lighting
uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;  

void main()
{
	// Ambient
    vec3 ambient = material.ambient * light.ambient;

	// Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (material.diffuse * diff) * light.diffuse;

	// Specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * material.specular);  

	vec3 texColor = vec3(texture(tex, vec2(TexCoord.x/sampleCount + (sample-1)/sampleCount, TexCoord.y)));
	vec3 result = (ambient + diffuse + specular) * texColor;
	FragColor = vec4(result, 1.0);

	// FragColor = texture(tex, vec2(TexCoord.x/sampleCount + (sample-1)/sampleCount, TexCoord.y));
}