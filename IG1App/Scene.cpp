#include "Scene.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
  glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque) color de fondo de la ventana	
	  // lights
  // textures  
  // meshes

  // Graphics objects (entities) of the scene

  //grObjects.push_back(new EjesRGB(200.0)); //crea los ejes de la escena

  //Ejercicio 6

  //grObjects.push_back(new generaEstrella3D(100, 6, 50));

  //Ejercicio 7
  //grObjects.push_back(new generaContCubo(50));

  //Animacion

	//grObjects.push_back(new TrianguloAnimado(50));
	//grObjects.back()->setModelMat(translate(grObjects.back()->getModelMat(), dvec3(50, 0, 0)));

  //Ejercicio 8
  //grObjects.push_back(new generaCajaSinTapa(50)); //Cubo con suelo

  //Escena 3D
  grObjects.push_back(new RectangleTexCor(500, 500, 5,5));
  grObjects.back()->setModelMat(rotate(grObjects.back()->getModelMat(), radians(90.0), dvec3(1, 0, 0)));

  
  grObjects.push_back(new generaEstrella3DTex(25, 4, 50));
  grObjects.back()->setModelMat(translate(grObjects.back()->getModelMat(), dvec3(-75 , 100, -75 )));

  grObjects.push_back(new Foto(50,50));
  grObjects.back()->setModelMat(translate(grObjects.back()->getModelMat(), dvec3(0, 10, 0)));
  grObjects.back()->setModelMat(rotate(grObjects.back()->getModelMat(), radians(90.0), dvec3(1, 0, 0)));

  grObjects.push_back(new generaCajaTexCor(50));
  grObjects.back()->setModelMat(translate(grObjects.back()->getModelMat(), dvec3(-75, 50, -75)));

  glAlphaFunc(GL_GREATER, 0);
  grObjects.push_back(new Planta(100));
  grObjects.back()->setModelMat(translate(grObjects.back()->getModelMat(), dvec3(150, 50, -150)));

  //grObjects.push_back(new Cristalera(300));
  //grObjects.back()->setModelMat(rotate(grObjects.back()->getModelMat(), radians(90.0), dvec3(1, 0, 0)));
}

void Scene::init2()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque) color de fondo de la ventana
		
	grObjects.push_back(new Poliespiral(dvec2(0, 0), 0, 160, 1, 1, 50));
	grObjects.back()->setModelMat(translate(grObjects.back()->getModelMat(), dvec3(0, 0, -50))); //No va
	grObjects.push_back(new Dragon(3000)); //Ejercicio 2
	grObjects.back()->setModelMat(translate(grObjects.back()->getModelMat(), dvec3(-40, -170, 10)));
	grObjects.back()->setModelMat(scale(grObjects.back()->getModelMat(), dvec3(40, 40, 40)));
	grObjects.push_back(new TrianguloAnimado(100));
	grObjects.push_back(new RectanguloRGB(200, 100));
}
//------------------------------------------------------------------------

Scene::~Scene()
{ // free memory and resources   
  
  for (Entity* el: grObjects)
  {
	  delete el;  el = nullptr;
  }
}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam)
{
	for (Entity* el: grObjects)
	{
		el->render(cam);
	}
}
void Scene::update()
{
	for (Entity* el : grObjects)
	{
		el->update();
	}
}
void Scene::update(GLuint timeElapsed)
{
	update();
}
void Scene::clear()
{
	while (!grObjects.empty())
	{
		grObjects.pop_back();
	}
}
//-------------------------------------------------------------------------

