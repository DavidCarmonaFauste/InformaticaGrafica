#include "Scene.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
  glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque) color de fondo de la ventana
  glEnable(GL_DEPTH_TEST);  // enable Depth test 
     
  // lights
  // textures  
  // meshes

  // Graphics objects (entities) of the scene

  //grObjects.push_back(new EjesRGB(200.0)); //crea los ejes de la escena
  
  //Ejercicio 1

  /*
  grObjects.push_back(new Poliespiral(dvec2(0,0), 0, 160, 1, 1, 50));
  grObjects.push_back(new Poliespiral(dvec2(0,0), 0, 72, 30, 0.001, 6)); 
  */
  
  //Ejercicio 2
  
  /*
  grObjects.push_back(new Dragon(3000)); //Ejercicio 2
  grObjects.back()->setModelMat(translate(grObjects.back()->getModelMat(), dvec3(-40, -170, 0)));
  grObjects.back()->setModelMat(scale(grObjects.back()->getModelMat(), dvec3(40, 40, 40)));
  */

  //Ejercicio 3
  
  //grObjects.push_back(new TrianguloRGB(100));

  //Ejercicio 4

  /*
  grObjects.push_back(new RectanguloRGB(200, 100));
  grObjects.back()->setModelMat(rotate(grObjects.back()->getModelMat(), radians(-25.0), dvec3(0, 0, 1))); //No va
  */

  //Ejercicio 5
	
  
  grObjects.push_back(new Poliespiral(dvec2(0, 0), 0, 160, 1, 1, 50));
  grObjects.back()->setModelMat(rotate(grObjects.back()->getModelMat(), radians(-25.0), dvec3(0, 0, 1))); //No va
  grObjects.push_back(new Dragon(3000)); //Ejercicio 2
  grObjects.back()->setModelMat(translate(grObjects.back()->getModelMat(), dvec3(-40, -170, 10)));
  grObjects.back()->setModelMat(scale(grObjects.back()->getModelMat(), dvec3(40, 40, 40)));
  grObjects.push_back(new TrianguloRGB(100));
  grObjects.push_back(new RectanguloRGB(200, 100));
  

}
//-------------------------------------------------------------------------

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
//-------------------------------------------------------------------------

