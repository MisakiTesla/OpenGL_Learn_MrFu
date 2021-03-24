#version 330 core
//in vec4 vertexColor;
in float TestID;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

struct Material
{
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct LightPoint
{
	float constant;
	float linear;
	float quadratic;
};

uniform Material material;
uniform LightPoint lightPoint;
uniform sampler2D ourTexture;
uniform sampler2D ourFaceTexture;
uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightDirUniform;//Æ½ÐÐ¹â
uniform vec3 lightColor;
uniform vec3 cameraPos;

//uniform vec4 ourColor;
out vec4 FragColor;

void main()
{
	//FragColor = vertexColor;
	//FragColor = texture(ourTexture, TexCoord) * texture(ourFaceTexture, TexCoord) * TestID /10;//GPU Instancing
	//FragColor = vec4(objColor * ambientColor,1.0) * texture(ourTexture, TexCoord) * texture(ourFaceTexture, TexCoord);
	float dist = length(lightPos - FragPos);
	float attenuation = 1.0f / (lightPoint.constant + lightPoint.linear * dist + lightPoint.quadratic * (dist * dist));

	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 reflectVec = reflect(-lightDir, Normal);
	vec3 cameraVec = normalize(cameraPos- FragPos);

	//specular
	float specularAmount = pow(max(dot(reflectVec, cameraVec), 0), material.shininess);
	vec3 specular = texture(material.specular, TexCoord).rgb * specularAmount * lightColor;
	
	//diffuse
	//vec3 diffuse = material.diffuse * max(dot(lightDir, Normal), 0)* lightColor;
	vec3 diffuse = texture(material.diffuse, TexCoord).rgb * max(dot(lightDir, Normal), 0)* lightColor;

	//ambient
	vec3 ambient = texture(material.diffuse, TexCoord).rgb * ambientColor;
	FragColor = vec4((ambient + (diffuse + specular) * attenuation) * objColor,1.0);
}