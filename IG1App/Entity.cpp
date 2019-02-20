#include "Entity.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Entity::update()
{
}

void Entity::update(GLuint timeElapsed)
{
}

void Entity::uploadMvM(dmat4 const& modelViewMat) const
{ 
	dmat4 aMat = modelViewMat * modelMat;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(aMat));
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l): Entity() 
{
  mesh = Mesh::createRGBAxes(l);
}
//-------------------------------------------------------------------------

EjesRGB::~EjesRGB() 
{ 
	delete mesh; mesh = nullptr; 
};
//-------------------------------------------------------------------------

void EjesRGB::render(Camera const& cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat()); 
		glLineWidth(2);
		mesh->render();
		glLineWidth(1);
	}
}
//-------------------------------------------------------------------------

Poliespiral::Poliespiral(dvec2 verIni, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert)
{
	mesh = Mesh::generaPoliespiral(verIni, angIni, incrAng, ladoIni, incrLado, numVert);
}

Poliespiral::~Poliespiral()
{
	delete mesh; 
	mesh = nullptr;
}

void Poliespiral::render(Camera const & cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		glColor3d(0.0,0.0,1.0);
		glLineWidth(2);
		mesh->render();
		glLineWidth(1);
	}
}

Dragon::Dragon(GLuint numVert)
{
	mesh = Mesh::generaDragon(numVert);
}

Dragon::~Dragon()
{
	delete mesh;
	mesh = nullptr;
}

void Dragon::render(Camera const & cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		glColor3d(0.0, 0.0, 1.0);
		glLineWidth(2);
		mesh->render();
		glLineWidth(1);
	}
}

TrianguloRGB::TrianguloRGB(GLdouble r)
{
	mesh = Mesh::generaTrianguloRGB(r);
}

TrianguloRGB::~TrianguloRGB()
{
	delete mesh;
	mesh = nullptr;
}

void TrianguloRGB::render(Camera const & cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		glColor3d(0.0, 0.0, 1.0);
		glLineWidth(2);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Sin relleno
		//glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); //Solo v�rtices
		//glPolygonMode(GL_FRONT, GL_FILL); //Con relleno
		glPolygonMode(GL_BACK, GL_LINE); //Tiene relleno por una cara
		mesh->render();
		glLineWidth(1);
	}
}

RectanguloRGB::RectanguloRGB(GLdouble w, GLdouble h)
{
	mesh = Mesh::generaRectanguloRGB(w,h);

}

RectanguloRGB::~RectanguloRGB()
{
	delete mesh;
	mesh = nullptr;
}

void RectanguloRGB::render(Camera const & cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		glColor3d(0.0, 0.0, 1.0);
		glLineWidth(2);
		mesh->render();
		glLineWidth(1);
	}
}

generaEstrella3D::generaEstrella3D(GLdouble re, GLdouble np, GLdouble h)
{
	mesh = Mesh::generaEstrella3D(re, np, h);

}

generaEstrella3D::~generaEstrella3D()
{
	delete mesh;
	mesh = nullptr;
}

void generaEstrella3D::render(Camera const & cam)
{
	if (mesh != nullptr) {

		aux = this->getModelMat();

		this->setModelMat(rotate(aux, radians(ang1), dvec3(0, 1, 0)));
		this->setModelMat(rotate(this->getModelMat(), radians(ang2), dvec3(0, 0, 1)));

		uploadMvM(cam.getViewMat());
		glColor3d(0.0, 0.0, 1.0);
		glLineWidth(2);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Sin relleno
		mesh->render();

		this->setModelMat(rotate(this->getModelMat(), radians(180.0), dvec3(0, 1, 0)));
		uploadMvM(cam.getViewMat());
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Sin relleno
		mesh->render();

		this->setModelMat(rotate(this->getModelMat(), radians(-180.0), dvec3(0, 1, 0)));
		//mesh->render();

		glLineWidth(1);

		this->setModelMat(aux);

	}
}

void generaEstrella3D::update()
{
	ang1 += 3;
	ang2 += 3;
}

generaContCubo::generaContCubo(GLdouble l)
{
	mesh = Mesh::generaContCubo(l);
}

generaContCubo::~generaContCubo()
{
	delete mesh;
	mesh = nullptr;
}

void generaContCubo::render(Camera const & cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		glColor3d(0.0, 0.0, 1.0);
		glLineWidth(2);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Sin relleno
		mesh->render();
		glLineWidth(1);
	}
}

TrianguloAnimado::TrianguloAnimado(GLdouble r)
{
	mesh = Mesh::generaTrianguloRGB(r);
}

TrianguloAnimado::~TrianguloAnimado()
{
	delete mesh;
	mesh = nullptr;
}

void TrianguloAnimado::render(Camera const & cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		glColor3d(0.0, 0.0, 1.0);
		glLineWidth(2);
		mesh->render();
		glLineWidth(1);
	}
}

void TrianguloAnimado::update()
{
	this->setModelMat(translate(this->getModelMat(), dvec3(sin(radians(15.0)), cos(radians(15.0)), 0)));
	this->setModelMat(rotate(this->getModelMat(), radians(15.0), dvec3(0, 0, 1)));
	this->setModelMat(translate(this->getModelMat(), dvec3(-sin(radians(15.0)), -cos(radians(15.0)), 0)));


	x = 50 * cos(radians(15.0));
	y = 50 * sin(radians(15.0));

	this->setModelMat(translate(this->getModelMat(), dvec3(x,y, 0)));

}

generaCajaSinTapa::generaCajaSinTapa(GLdouble l)
{
	l_ = l;
	mesh = Mesh::generaContCubo(l);
	mesh2 = Mesh::generaRectanguloRGB(l, l);
}

generaCajaSinTapa::~generaCajaSinTapa()
{
	delete mesh;
	delete mesh2;
	mesh = nullptr;
	mesh2 = nullptr;
}

void generaCajaSinTapa::render(Camera const & cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		glColor3d(0.0, 0.0, 1.0);
		glLineWidth(2);
		mesh->render();

		this->setModelMat(translate(this->getModelMat(), dvec3(-0.5 * l_, -l_/2, -l_ / 2)));
		this->setModelMat(rotate(this->getModelMat(), radians(-90.0), dvec3(1, 0, 0)));
		//this->setModelMat(translate(this->getModelMat(), dvec3(-100, 50, -30)));
		uploadMvM(cam.getViewMat());

		mesh2->render();

		this->setModelMat(rotate(this->getModelMat(), radians(90.0), dvec3(1, 0, 0)));
		this->setModelMat(translate(this->getModelMat(), dvec3(0.5 * l_, l_/2, l_/2)));

		glLineWidth(1);
	}
}
