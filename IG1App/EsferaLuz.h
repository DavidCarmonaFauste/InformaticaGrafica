#pragma once
#include "EntityMaterial.h"
#include "SpotLight.h"

class EsferaLuz: public Esfera
{
public:
	EsferaLuz(GLuint radius, GLuint radius2, glm::dvec3 pos, glm::dvec3 relativePos);
	~EsferaLuz();
	virtual void render(Camera const& cam);
	void setTexture2(Texture* tex);
	void setMaterial2(Material mat);
	virtual void update();
	void uploadLight(dmat4 camMat);

	SpotLight* luz;
	Texture* texture2;
	Material material2;

	GLUquadricObj* qObj2;
	GLuint radio2;

	dvec3 PosRelativa;
	dvec3 PosicionOriginal;
		

	GLdouble AnguloUpdate = 0;
	GLdouble AnguloRotacion = 0;

	GLint DireccionRotacion = 1;
	GLint topeAngulo = 45;



	dmat4 MatRelativa;
	dmat4 MatUpdate;
	dmat4 mat1;
	dmat4 mat2;
};