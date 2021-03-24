#include "LightDirectional.h"

LightDirectional::LightDirectional(glm::vec3 position, glm::vec3 angles, glm::vec3 color):
	position(position),
	angles(angles),
	color(color)
{
	UpdateDirection();
}

LightDirectional::~LightDirectional()
{
}

void LightDirectional::UpdateDirection()
{
	direction = glm::vec3(0, 0, 1.0f);//pointing to z(forward)
	direction = glm::rotateZ(direction, angles.z);
	direction = glm::rotateX(direction, angles.x);
	direction = glm::rotateY(direction, angles.y);
	direction = -1.0f * direction;
}
