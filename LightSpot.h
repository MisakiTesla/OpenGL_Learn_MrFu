#pragma once

#include <glm.hpp>
#include <gtx/rotate_vector.hpp>

#include "LightPoint.h"

class LightSpot : public LightPoint
{
public:
	LightSpot(glm::vec3 position, glm::vec3 angles, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightSpot();

	float cosPhyInner = 0.9f;
	float cosPhyOutter = 0.89f;
};

