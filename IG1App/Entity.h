//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Mesh.h"

using namespace glm;
//-------------------------------------------------------------------------

class Entity 
{
public:
	Entity() : modelMat(1.0) { }; 
	virtual ~Entity() { };

	virtual void render(Camera const& cam) = 0;

	virtual void update();

	// modeling matrix
	glm::dmat4 const& getModelMat() const { return modelMat; };

	void setModelMat(glm::dmat4 const& aMat) { modelMat = aMat; }
  
protected:

	Mesh* mesh = nullptr;   // surface mesh
	glm::dmat4 modelMat;    // modeling matrix

	// transfers modelViewMat to the GPU
	virtual void uploadMvM(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class EjesRGB : public Entity 
{
public:
	EjesRGB(GLdouble l);
	~EjesRGB();
	virtual void render(Camera const& cam); 
};

//-------------------------------------------------------------------------

class Poliespiral : public Entity
{
public:
	Poliespiral(dvec2 verIni, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert);
	~Poliespiral();
	virtual void render(Camera const& cam);
};

//-------------------------------------------------------------------------

class Dragon : public Entity
{
public:
	Dragon(GLuint numVert);
	~Dragon();
	virtual void render(Camera const& cam);
};

//-------------------------------------------------------------------------

class TrianguloRGB : public Entity
{
public:
	TrianguloRGB(GLdouble r);
	~TrianguloRGB();
	virtual void render(Camera const& cam);
};

class TrianguloAnimado : public Entity
{
public:
	TrianguloAnimado(GLdouble r);
	~TrianguloAnimado();
	virtual void render(Camera const& cam);
	virtual void update();
private:
	double x, y = 0;
};

class RectanguloRGB : public Entity
{
public:
	RectanguloRGB(GLdouble w, GLdouble h);
	~RectanguloRGB();
	virtual void render(Camera const& cam);
};

//-------------------------------------------------------------------------

class generaEstrella3D : public Entity
{
public:
	generaEstrella3D(GLdouble re, GLdouble np, GLdouble h);
	~generaEstrella3D();
	virtual void render(Camera const& cam);
	virtual void update();
};

class generaContCubo : public Entity
{
public:
	generaContCubo(GLdouble l);
	~generaContCubo();
	virtual void render(Camera const& cam);

protected:
	Mesh* mesh2 = nullptr;   // surface mesh

};

#endif //_H_Entities_H_