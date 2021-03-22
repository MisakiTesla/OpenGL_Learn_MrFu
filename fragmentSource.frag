#version 330 core
out vec4 FragColor;
in vec4 vertexColor;
in vec2 TexCoord;
in float TestID;
uniform sampler2D ourTexture;
uniform sampler2D ourFaceTexture;

//uniform vec4 ourColor;

void main()
{
	//FragColor = vertexColor;
	FragColor = texture(ourTexture, TexCoord) * texture(ourFaceTexture, TexCoord) * TestID /10;
}