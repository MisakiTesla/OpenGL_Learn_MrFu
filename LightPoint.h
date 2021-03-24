#pragma once

#include <glm.hpp>
#include <gtx/rotate_vector.hpp>

class LightPoint
{
public:
	LightPoint(glm::vec3 position, glm::vec3 angles, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightPoint();
	glm::vec3 position;
	glm::vec3 angles;
	glm::vec3 direction;
	glm::vec3 color;

	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;
};

