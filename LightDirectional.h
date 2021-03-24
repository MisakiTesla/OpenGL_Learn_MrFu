#pragma once

#include <glm.hpp>
#include <gtx/rotate_vector.hpp>

class LightDirectional
{
public:
	LightDirectional(glm::vec3 position, glm::vec3 angles, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightDirectional();
	glm::vec3 position;
	glm::vec3 angles;
	glm::vec3 lightDir;
	glm::vec3 color;
	void UpdateDirection();
};

