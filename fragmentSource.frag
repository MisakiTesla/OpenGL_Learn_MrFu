#version 330 core
//in vec4 vertexColor;
in vec2 TexCoord;
in float TestID;
in vec3 FragPos;
in vec3 Normal;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;

};


uniform Material material;
uniform sampler2D ourTexture;
uniform sampler2D ourFaceTexture;
uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 cameraPos;

//uniform vec4 ourColor;
out vec4 FragColor;

void main()
{
	//FragColor = vertexColor;
	//FragColor = texture(ourTexture, TexCoord) * texture(ourFaceTexture, TexCoord) * TestID /10;//GPU Instancing
	//FragColor = vec4(objColor * ambientColor,1.0) * texture(ourTexture, TexCoord) * texture(ourFaceTexture, TexCoord);
	

	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 reflectVec = reflect(-lightDir, Normal);
	vec3 cameraVec = normalize(cameraPos- FragPos);

	//specular
	float specularAmount = pow(max(dot(reflectVec, cameraVec), 0), material.shininess);
	vec3 specular = material.specular * specularAmount * lightColor;
	
	//diffuse
	vec3 diffuse = material.diffuse * max(dot(lightDir, Normal), 0)* lightColor;

	//ambient
	vec3 ambient = material.ambient * ambientColor;
	FragColor = vec4((ambient + diffuse + specular) * objColor,1.0);
}