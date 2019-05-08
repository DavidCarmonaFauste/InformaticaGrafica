#pragma once
#include "Mesh.h"
class IndexMesh :	public Mesh
{
public:
	IndexMesh();
	virtual ~IndexMesh();
	virtual void render();
	static	IndexMesh* generateGridTex(GLdouble lado, GLuint numDiv);
	static	IndexMesh*  generatePlanoCurvado(GLdouble  lado, GLuint	numDiv, GLdouble curvatura);
protected:
	GLuint* indices = nullptr;
	GLuint  numIndices = 0;
	glm::dvec2* texCoords;
};

