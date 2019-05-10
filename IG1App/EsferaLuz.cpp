#include "EsferaLuz.h"

EsferaLuz::EsferaLuz(GLuint radius, GLuint radius2, glm::dvec3 pos): Esfera(radius)
{
	luz = new SpotLight();
	luz->setDir(fvec3(0, -1, 0));
	luz->setPos(pos);
	luz->setAng(180.0);
	luz->uploadLI();
	luz->enable();
	sphere = new Esfera(radius2);
}

EsferaLuz::~EsferaLuz()
{
	delete luz;
}
