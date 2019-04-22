#include "EsferaLuz.h"

EsferaLuz::EsferaLuz(GLuint radius, glm::dvec3 pos): Esfera(radius)
{
	luz = new SpotLight();
	luz->setDir(fvec3(0, -1, 0));
	luz->setPos(pos);
	luz->setAng(180.0);
	luz->uploadLI();
	luz->enable();
}

EsferaLuz::~EsferaLuz()
{
	delete luz;
}
