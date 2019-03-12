//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Mesh.h"
#include "Texture.h"

using namespace glm;
//-------------------------------------------------------------------------

class Entity 
{
public:
	Entity() : modelMat(1.0) { }; 
	virtual ~Entity() { };

	virtual void render(Camera const& cam) = 0;

	virtual void update();
	void update(GLuint timeElapsed);
	// modeling matrix
	glm::dmat4 const& getModelMat() const { return modelMat; };

	void setModelMat(glm::dmat4 const& aMat) { modelMat = aMat; }
  
protected:

	Mesh* mesh = nullptr;   // surface mesh
	glm::dmat4 modelMat;    // modeling matrix
	Texture texture;    // w, h, id  
					   // transfers modelViewMat to the GPU
	virtual void uploadMvM(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class RectangleTex : public Entity
{
public:
	RectangleTex(GLdouble w, GLdouble h);
	~RectangleTex();
	void render(Camera const& cam);
};

class RectangleTexCor : public Entity
{
public:
	RectangleTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	~RectangleTexCor();
	void render(Camera const& cam);
};

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
	double radio;
	double ang;
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
private:
	GLdouble ang1 = 0;
	GLdouble ang2 = 0;
	dmat4 aux;
};

class generaContCubo : public Entity
{
public:
	generaContCubo(GLdouble l);
	~generaContCubo();
	virtual void render(Camera const& cam);
};

class generaCajaSinTapa : public Entity
{
public:
	generaCajaSinTapa(GLdouble l);
	~generaCajaSinTapa();
	virtual void render(Camera const& cam);

protected:
	Mesh* mesh2 = nullptr;
	GLdouble l_;
};

class generaEstrella3DTex : public Entity
{
public:
	generaEstrella3DTex(GLdouble re, GLdouble np, GLdouble h);
	~generaEstrella3DTex();
	virtual void render(Camera const& cam);
	virtual void update();
private:
	GLdouble ang1 = 0;
	GLdouble ang2 = 0;
	dmat4 aux;
};

class generaCajaTexCor : public Entity
{
public:
	generaCajaTexCor(GLdouble l);
	~generaCajaTexCor();
	virtual void render(Camera const& cam);

protected:
	Mesh* mesh2 = nullptr;
	GLdouble l_;
	Texture texture2;
};

class Foto : public Entity
{
public:
	Foto(GLdouble w, GLdouble h);
	~Foto();
	virtual void render(Camera const& cam);
	virtual void update();

};

class Cristalera : public Entity
{
public:
	Cristalera(GLdouble l);
	~Cristalera();
	virtual void render(Camera const& cam);
protected:
	Mesh* mesh2;
	Texture text2;
	GLdouble l_;
};

class Planta : public Entity
{
public:
	Planta(GLdouble l);
	~Planta();
	virtual void render(Camera const& cam);
protected:
	Mesh* mesh2;
	Texture text2;
	GLdouble l_;
};

#endif //_H_Entities_H_