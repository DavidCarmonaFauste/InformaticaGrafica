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
		//glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); //Solo vértices
		//glPolygonMode(GL_FRONT, GL_FILL); //Con relleno
		//glPolygonMode(GL_BACK, GL_LINE); //Tiene relleno por una cara
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
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //Sin relleno
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
	radio = r;
	ang = 0;
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
	x = 2 * radio * cos(radians(ang));
	y = 2 * radio * sin(radians(ang));

	ang += 10;

	modelMat = dmat4(1);

	this->setModelMat(translate(this->getModelMat(), dvec3(x, y, 0)));
	this->setModelMat(rotate(this->getModelMat(), radians(ang), dvec3(0, 0, 1)));
	//this->setModelMat(translate(this->getModelMat(), dvec3(-x, -y, 0)));
	

	//this->setModelMat(translate(this->getModelMat(), dvec3(x,y, 0)));
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

		this->setModelMat(translate(this->getModelMat(), dvec3(0, -l_/2, 0)));
		this->setModelMat(rotate(this->getModelMat(), radians(-90.0), dvec3(1, 0, 0)));
		//this->setModelMat(translate(this->getModelMat(), dvec3(-100, 50, -30)));
		uploadMvM(cam.getViewMat());

		mesh2->render();

		this->setModelMat(rotate(this->getModelMat(), radians(90.0), dvec3(1, 0, 0)));
		this->setModelMat(translate(this->getModelMat(), dvec3(0, l_/2, 0)));

		glLineWidth(1);
	}
}

RectangleTex::RectangleTex(GLdouble w, GLdouble h)
{
	mesh = Mesh::generateRectangleTex(w, h);// con coord. de textura 
	texture.load("..\\Bmps\\Zelda.bmp");  // cargamos la imagen 
}

RectangleTex::~RectangleTex()
{
	delete mesh;
	mesh = nullptr;
}

void RectangleTex::render(Camera const& cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		glColor3d(0.0, 0.0, 1.0);
		glLineWidth(2);
		texture.bind();
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Sin relleno
		//glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); //Solo vértices
		glPolygonMode(GL_FRONT, GL_FILL); //Con relleno
		//glPolygonMode(GL_BACK, GL_LINE); //Tiene relleno por una cara
		mesh->render();
		glLineWidth(1);
	}
}

RectangleTexCor::RectangleTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
	mesh = Mesh::generaRectanguloTexCor(w, h, rw, rh);// con coord. de textura 
	texture.load("..\\Bmps\\baldosaC.bmp");  // cargamos la imagen 
}

RectangleTexCor::~RectangleTexCor()
{
	delete mesh;
	mesh = nullptr;
}

void RectangleTexCor::render(Camera const & cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		glColor3d(0.0, 0.0, 1.0);
		glLineWidth(2);
		texture.bind();
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Sin relleno
		//glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); //Solo vértices
		glPolygonMode(GL_FRONT, GL_FILL); //Con relleno
		GL_REPEAT;
		//glPolygonMode(GL_BACK, GL_LINE); //Tiene relleno por una cara
		mesh->render();
		glLineWidth(1);
	}
}

generaEstrella3DTex::generaEstrella3DTex(GLdouble re, GLdouble np, GLdouble h)
{
	mesh = Mesh::generaEstrellaTexCor(re, np, h);
	texture.load("..\\Bmps\\baldosaP.bmp");  // cargamos la imagen 
}

generaEstrella3DTex::~generaEstrella3DTex()
{
	delete mesh;
	mesh = nullptr;
}

void generaEstrella3DTex::render(Camera const & cam)
{
	if (mesh != nullptr) {

		aux = this->getModelMat();

		this->setModelMat(rotate(aux, radians(ang1), dvec3(0, 1, 0)));
		this->setModelMat(rotate(this->getModelMat(), radians(ang2), dvec3(0, 0, 1)));

		uploadMvM(cam.getViewMat());
		glColor3d(0.0, 0.0, 1.0);
		glLineWidth(2);
		texture.bind();
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Sin relleno
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

void generaEstrella3DTex::update()
{
	ang1 += 3;
	ang2 += 3;
}

generaCajaTexCor::generaCajaTexCor(GLdouble l)
{
	l_ = l;
	mesh = Mesh::generaCajaTexCor(l);
	mesh2 = Mesh::generaRectanguloTexCor(l, l, 1, 1);
	texture.load("..\\Bmps\\BaldosaC.bmp");  // cargamos la imagen 
	texture2.load("..\\Bmps\\CristalTri.bmp");  // cargamos la imagen 

}

generaCajaTexCor::~generaCajaTexCor()
{
	delete mesh;
	delete mesh2;
}

void generaCajaTexCor::render(Camera const & cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		//glColor3d(0.0, 0.0, 1.0);
		glLineWidth(2);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		mesh->render();

		texture.unbind();
		texture2.bind();

		glCullFace(GL_BACK);
		uploadMvM(cam.getViewMat());
		mesh->render();

		this->setModelMat(translate(this->getModelMat(), dvec3(0, -l_ / 2, 0)));
		this->setModelMat(rotate(this->getModelMat(), radians(90.0), dvec3(1, 0, 0)));
		//this->setModelMat(translate(this->getModelMat(), dvec3(-100, 50, -30)));


		texture2.unbind();
		texture.bind();

		uploadMvM(cam.getViewMat());
		glCullFace(GL_FRONT);
		mesh2->render();

		texture.unbind();
		texture2.bind();

		glCullFace(GL_BACK);
		uploadMvM(cam.getViewMat());
		mesh2->render();

		this->setModelMat(rotate(this->getModelMat(), radians(-90.0), dvec3(1, 0, 0)));
		this->setModelMat(translate(this->getModelMat(), dvec3(0, l_ / 2, 0)));

		texture2.unbind();
		texture.bind();

		glDisable(GL_CULL_FACE);
	}
}

Foto::Foto(GLdouble w, GLdouble h)
{
	mesh = Mesh::generateRectangleTex(w, h);// con coord. de textura 
	texture.loadColorBuffer();
}

Foto::~Foto()
{
}

void Foto::render(Camera const & cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		glColor3d(0.0, 0.0, 1.0);
		glLineWidth(2);
		texture.bind();
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Sin relleno
		//glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); //Solo vértices
		glPolygonMode(GL_FRONT, GL_FILL); //Con relleno
		GL_REPEAT;
		//glPolygonMode(GL_BACK, GL_LINE); //Tiene relleno por una cara
		mesh->render();
		glLineWidth(1);
	}
}

void Foto::update()
{
	texture.loadColorBuffer();
}

Cristalera::Cristalera(GLdouble l)
{
	l_ = l;
	mesh = Mesh::generaCajaTexCor(l);
	mesh2 = Mesh::generateRectangleTex(l, l);
	texture.load("..\\Bmps\\cristalTri.bmp", 185);  // cargamos la imagen 
	text2.load("..\\Bmps\\BaldosaC.bmp", 255);  // cargamos la imagen 
}

Cristalera::~Cristalera()
{
	delete mesh;
	delete mesh2;
}

void Cristalera::render(Camera const & cam)
{
	if (mesh != nullptr) {

		text2.bind();
		uploadMvM(cam.getViewMat());

		mesh2->render();

		this->setModelMat(rotate(this->getModelMat(), radians(-90.0), dvec3(1, 0, 0)));
		this->setModelMat(translate(this->getModelMat(), dvec3(0, l_ / 2, 0)));

		text2.unbind();
		texture.bind();

		glDepthMask(GL_FALSE);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		uploadMvM(cam.getViewMat());
		//glColor3d(0.0, 0.0, 1.0);
		glLineWidth(2);
		texture.bind();
		mesh->render();

		this->setModelMat(translate(this->getModelMat(), dvec3(0, -l_ / 2, 0)));
		this->setModelMat(rotate(this->getModelMat(), radians(90.0), dvec3(1, 0, 0)));
		//this->setModelMat(translate(this->getModelMat(), dvec3(-100, 50, -30)));
		
		texture.unbind();
		text2.bind();

		glDepthMask(GL_TRUE);
	}
}

Planta::Planta(GLdouble l)
{
	mesh = Mesh::generateRectangleTex(l, l);
	mesh2 = Mesh::generateRectangleTex(l, l);
	texture.load("..\\Bmps\\grass.bmp", { 0,0,0,0 }, 0);  // cargamos la imagen 
}

Planta::~Planta()
{
	delete mesh;
	delete mesh2;
}

void Planta::render(Camera const & cam)
{
	if (mesh != nullptr) {

		texture.bind();
		uploadMvM(cam.getViewMat());

		mesh->render();

		this->setModelMat(rotate(this->getModelMat(), radians(-90.0), dvec3(0, 1, 0)));
		uploadMvM(cam.getViewMat());

		mesh2->render();

		//this->setModelMat(rotate(this->getModelMat(), radians(-90.0), dvec3(1, 0, 0)));
		//this->setModelMat(translate(this->getModelMat(), dvec3(0, l_ / 2, 0)));
		//glColor3d(0.0, 0.0, 1.0);
		glLineWidth(2);

		//this->setModelMat(translate(this->getModelMat(), dvec3(0, -l_ / 2, 0)));
		//this->setModelMat(rotate(this->getModelMat(), radians(90.0), dvec3(1, 0, 0)));
		//this->setModelMat(translate(this->getModelMat(), dvec3(-100, 50, -30)));
	}
}
