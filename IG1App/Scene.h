//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Entity.h"
#include "EntityMaterial.h"
#include "DirLight.h"
//#include "Mesh.h"

#include <vector>

//-------------------------------------------------------------------------

class Scene	
{ 
public:
    Scene() { };
	~Scene();
    void init();
	void init2();
  void init3();

    void render(Camera const& cam);

	void update();
	void update(GLuint timeElapsed);

	void clear();
protected:

	  std::vector<Entity*> grObjects;  // Entities (graphics objects) of the scene
	  std::vector<Texture*> grTextures;

	  DirLight luzDireccional;
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_

