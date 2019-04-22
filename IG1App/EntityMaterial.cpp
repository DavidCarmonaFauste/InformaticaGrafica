#include "EntityMaterial.h"



EntityMaterial::EntityMaterial()
{
}

void EntityMaterial::setTExture(Texture * tex)
{
	texture_ = tex;
}

void EntityMaterial::setMaterial(Material material)
{
	material_ = material;
}


EntityMaterial::~EntityMaterial()
{
}

Esfera::Esfera(GLdouble radio)
{
	qObj = gluNewQuadric();
	radio_ = radio;
}

Esfera::Esfera(GLdouble radio, GLint x, GLint y, Texture* text, Material m)
{
	qObj = gluNewQuadric();
	radio_ = radio;
	setTExture(text);
	setMaterial(m);
}

Esfera::~Esfera()
{
	gluDeleteQuadric(qObj);
}

void Esfera::render(Camera const & cam)
{
	glEnable(GL_CULL_FACE);
	material_.upload();
	gluQuadricDrawStyle(qObj, GLU_FILL);
	gluQuadricTexture(qObj, GL_TRUE);
	texture_->bind(GL_MODULATE);
	uploadMvM(cam.getViewMat());
	glLineWidth(2);
	gluSphere(qObj, radio_, 50, 50);
	texture_->unbind();
	glDisable(GL_CULL_FACE);

	//gluQuadricNormals(qObj, GLU_SMOOTH);
	//gluQuadricOrientation(qObj, GLU_OUTSIDE);
}

