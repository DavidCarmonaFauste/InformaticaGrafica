#pragma once
#include "EntityMaterial.h"
#include "SpotLight.h"

class EsferaLuz: public Esfera
{
public:
	EsferaLuz(GLuint radius, GLuint radius2, glm::dvec3 pos);
	~EsferaLuz();

	SpotLight* luz;
	Esfera* sphere;
};