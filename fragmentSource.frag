#version 330 core
out vec4 FragColor;
//in vec4 vertexColor;
in vec2 TexCoord;
in float TestID;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D ourTexture;
uniform sampler2D ourFaceTexture;
uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 cameraPos;

//uniform vec4 ourColor;

void main()
{
	//FragColor = vertexColor;
	//FragColor = texture(ourTexture, TexCoord) * texture(ourFaceTexture, TexCoord) * TestID /10;//GPU Instancing
	//FragColor = vec4(objColor * ambientColor,1.0) * texture(ourTexture, TexCoord) * texture(ourFaceTexture, TexCoord);
	

	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 reflectVec = reflect(-lightDir, Normal);
	vec3 cameraVec = normalize(cameraPos- FragPos);

	float specularAmount = max(dot(reflectVec, cameraVec), 0);
	vec3 specular = pow(specularAmount, 32)* lightColor;
	
	vec3 diffuse = max(dot(lightDir, Normal), 0)* lightColor;
	//FragColor = vec4(objColor * ambientColor,1.0);
	FragColor = vec4((ambientColor + diffuse + specular) * objColor,1.0);
}