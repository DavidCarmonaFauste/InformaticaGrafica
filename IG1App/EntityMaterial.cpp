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

Esfera::Esfera(GLdouble radio, glm::dvec3 pos)
{
	Esfera::Esfera(radio);
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

Superficie::Superficie(GLdouble lado, GLdouble numdiv, GLdouble curvatura, Texture* text, Material m)
{
	indexMesh_ = IndexMesh::generatePlanoCurvado(lado, numdiv, curvatura);
	texture_ = text;
	material_ = m;

}

Superficie::~Superficie()
{
	delete indexMesh_;
}

void Superficie::render(Camera const & cam)
{
	if (indexMesh_ != nullptr) {

		texture.bind();
		uploadMvM(cam.getViewMat());


		/*this->setModelMat(rotate(this->getModelMat(), radians(-90.0), dvec3(0, 1, 0)));
		uploadMvM(cam.getViewMat());
		this->setModelMat(rotate(this->getModelMat(), radians(90.0), dvec3(0, 1, 0)));*/


		indexMesh_->render();

		//this->setModelMat(translate(this->getModelMat(), dvec3(0, l_ / 2, 0)));
		//glColor3d(0.0, 0.0, 1.0);
		glLineWidth(2);

		//this->setModelMat(translate(this->getModelMat(), dvec3(0, -l_ / 2, 0)));
		//this->setModelMat(rotate(this->getModelMat(), radians(90.0), dvec3(1, 0, 0)));
		//this->setModelMat(translate(this->getModelMat(), dvec3(-100, 50, -30)));
	}
}
