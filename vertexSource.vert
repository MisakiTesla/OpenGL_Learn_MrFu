#version 330 core
layout(location = 0) in vec3 aPos;
//layout(location = 1) in vec3 aColor;//顶点色
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

uniform mat4 transform;//变换矩阵
uniform mat4 modelMat;//M
uniform mat4 viewMat;//V
uniform mat4 projMat;//P

//GPU Instancing
uniform mat4 instanceModelMat[10];

//out vec4 vertexColor;
out vec2 TexCoord;
out float TestID;
out vec3 FragPos;
out vec3 Normal;
void main()
{
	//gl_Position = projMat * viewMat * modelMat * vec4(aPos.x, aPos.y, aPos.z, 1.0); //最后一位齐次坐标 -> 1-标量，0-向量
	gl_Position = projMat * viewMat * instanceModelMat[gl_InstanceID] * vec4(aPos.xyz, 1.0); //最后一位齐次坐标 -> 1-标量，0-向量
	//Normal = mat3(modelMat) * aNormal;
	//FragPos = (modelMat * vec4(aPos.xyz, 1.0)).xyz;
	FragPos = (instanceModelMat[gl_InstanceID] * vec4(aPos.xyz, 1.0)).xyz;
	//Normal = mat3(instanceModelMat[gl_InstanceID]) * aNormal;
	//使用原来变换矩阵的逆转置矩阵得到正确的世界空间法线
	Normal = mat3(transpose(inverse(instanceModelMat[gl_InstanceID]))) * aNormal;

	//vertexColor = vec4(aColor.x, aColor.y, aColor.z, 1.0);
	TexCoord = aTexCoord;
	TestID = gl_InstanceID;

}
