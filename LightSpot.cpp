#include "LightSpot.h"

LightSpot::LightSpot(glm::vec3 position, glm::vec3 angles, glm::vec3 color) :
	position(position),
	angles(angles),
	color(color)
{
	UpdateDirection();
}

LightSpot::~LightSpot()
{
}

void LightSpot::UpdateDirection()
{
	lightDir = glm::vec3(0, 0, 1.0f);//pointing to z(forward)
	lightDir = glm::rotateZ(lightDir, angles.z);
	lightDir = glm::rotateX(lightDir, angles.x);
	lightDir = glm::rotateY(lightDir, angles.y);
	lightDir = -1.0f * lightDir;
}