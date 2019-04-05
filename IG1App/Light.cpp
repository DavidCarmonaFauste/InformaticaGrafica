#include "Light.h"

GLuint Light::cont = 0;

void Light::uploadLI()
{
	glLightfv(id, GL_AMBIENT, value_ptr(ambient));
	glLightfv(id, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(id, GL_SPECULAR,value_ptr(specular));
}
