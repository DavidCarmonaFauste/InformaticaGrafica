#pragma once
#include "Entity.h"
#include "Material.h"

class EntityMaterial :
	public Entity
{
public:
	EntityMaterial();
	void setTExture(Texture* tex);
	void setMaterial(Material material);
	virtual ~EntityMaterial();
protected:
	Texture* texture_;
	Material material_;
};

class Esfera : public EntityMaterial
{
public:
	Esfera(GLdouble radio);
	Esfera(GLdouble radio, glm::dvec3 pos);
	Esfera(GLdouble radio, GLint x, GLint y, Texture* text, Material m);
	~Esfera();
	virtual void render(Camera const& cam);
protected:
	GLUquadric* qObj;
	GLdouble radio_;
};

class Superficie : public EntityMaterial
{
public:
	Superficie(GLdouble lado, GLdouble numdiv, GLdouble curvatura, Texture* text, Material m);
	~Superficie();
	void render(Camera const& cam);
protected:
	IndexMesh* indexMesh_; //ponerlo como atributo base a Mesh?
};

