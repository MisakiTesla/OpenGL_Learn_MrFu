#include "LightPoint.h"

LightPoint::LightPoint(glm::vec3 position, glm::vec3 angles, glm::vec3 color):LightDirectional(position, angles, color)
{
}

LightPoint::~LightPoint()
{
}
