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
  
  grObjects.push_back(new generaEstrella3DTex(25, 4, 50));
  grObjects.back()->setModelMat(translate(grObjects.back()->getModelMat(), dvec3(-75 , 100, -75 )));

  grObjects.push_back(new Foto(50,50));
  grObjects.back()->setModelMat(translate(grObjects.back()->getModelMat(), dvec3(0, 10, 0)));
  grObjects.back()->setModelMat(rotate(grObjects.back()->getModelMat(), radians(90.0), dvec3(1, 0, 0)));

  grObjects.push_back(new generaCajaTexCor(50));
  grObjects.back()->setModelMat(translate(grObjects.back()->getModelMat(), dvec3(-75, 50, -75)));

  glAlphaFunc(GL_GREATER, 0);

  grObjects.push_back(new Planta(100));
  grObjects.back()->setModelMat(translate(grObjects.back()->getModelMat(), dvec3(75, 50, 75)));

  grObjects.push_back(new Cristalera(300));
  grObjects.back()->setModelMat(rotate(grObjects.back()->getModelMat(), radians(90.0), dvec3(1, 0, 0)));
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

void Scene::init3()
{
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glClearColor(0.0, 0.0, 0.05, 1.0);  // background color (alpha=1 -> opaque) color de fondo de la ventana
	glEnable(GL_DEPTH_TEST);  // enable Depth test
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_FLAT);

  //Materiales
  Material m;
  m.setCooper();


  //Texturas
  for (int i = 0; i < grTexturesStrings.size(); i++)
  {
	  Texture* t = new Texture();
	  t->load(grTexturesStrings.at(i));
	  grTextures.push_back(t);
  }


  luzDireccional = new DirLight();
  luzDireccional->enable();
  luzDireccional->setDir(fvec3(0, 0.25, 1));
  luzDireccional->setAmb(fvec4(1, 1, 1,1));
  luzDireccional->uploadLI();
  
  luzCamara = new SpotLight();
  luzCamara->setAng(1.0);
  luzCamara->uploadLI();
  luzCamara->enable();


  grObjects.push_back(new EjesRGB(200.0)); //crea los ejes de la escena
  grObjects.push_back(new RectangleTexCor(500,500, 5, 5)); //crea los ejes de la escena
  grObjects.back()->setModelMat(rotate(grObjects.back()->getModelMat(), radians(90.0), dvec3(1, 0, 0)));


  grObjects.push_back(new Esfera(25, 0, 0, grTextures.front(), m)); 
  grObjects.back()->setModelMat(translate(grObjects.back()->getModelMat(), dvec3(50, 100, 50)));

  //MARTE
  grObjects.push_back(new Esfera(35, 0, 0, grTextures.at(11), m)); 
  grObjects.back()->setModelMat(translate(grObjects.back()->getModelMat(), dvec3(75, 100, -50)));

  //LUNA
  grObjects.push_back(new Esfera(15, 0, 0, grTextures.at(12), m)); 
  grObjects.back()->setModelMat(translate(grObjects.back()->getModelMat(), dvec3(125, 100, -200)));

  //VENUS
  grObjects.push_back(new Esfera(60, 0, 0, grTextures.at(15), m));
  grObjects.back()->setModelMat(translate(grObjects.back()->getModelMat(), dvec3(-100, -100, 50)));

  esferaLuz = new EsferaLuz(75, dvec3(0, 0, 0));
  esferaLuz->setTExture(grTextures.at(14));
  esferaLuz->setMaterial(m);
  grObjects.push_back(esferaLuz);
  grObjects.back()->setModelMat(translate(grObjects.back()->getModelMat(), dvec3(-50, 100, 100)));
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
	if (luzDireccional != nullptr)
	luzDireccional->upload(cam.getViewMat());

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

