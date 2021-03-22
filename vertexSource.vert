#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 transform;//变换矩阵
uniform mat4 modelMat;//M
uniform mat4 viewMat;//V
uniform mat4 projMat;//P

//GPU Instancing
uniform mat4 instanceModelMat[10];

out vec4 vertexColor;
out vec2 TexCoord;
out float TestID;
void main()
{
	//gl_Position = projMat * viewMat * modelMat * vec4(aPos.x, aPos.y, aPos.z, 1.0); //最后一位齐次坐标 -> 1-标量，0-向量
	gl_Position = projMat * viewMat * instanceModelMat[gl_InstanceID] * vec4(aPos.x, aPos.y, aPos.z, 1.0); //最后一位齐次坐标 -> 1-标量，0-向量
	vertexColor = vec4(aColor.x, aColor.y, aColor.z, 1.0);
	TexCoord = aTexCoord;
	TestID = gl_InstanceID;
}
