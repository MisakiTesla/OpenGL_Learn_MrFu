#include "Material.h"

Material::Material(Shader* shader, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 ambient, float shininess):
	shader(shader),
	diffuse(diffuse),
	specular(specular),
	ambient(ambient),
	shininess(shininess)
{
}

Material::~Material()
{
}
