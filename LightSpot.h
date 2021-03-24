#pragma once

#include <glm.hpp>
#include <gtx/rotate_vector.hpp>

class LightSpot
{
public:
	LightSpot(glm::vec3 position, glm::vec3 angles, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightSpot();

	void UpdateDirection();

	glm::vec3 position;
	glm::vec3 angles;
	glm::vec3 lightDir;
	glm::vec3 color;

	float constant = 1.0f;
	float linear = 0.1f;
	float quadratic = 0.001f;

	float cosPhyInner = 0.9f;
	float cosPhyOutter = 0.89f;
};

