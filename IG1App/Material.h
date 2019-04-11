#pragma once

#include <GL/freeglut.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>


class Material
{
	glm::fvec4 ambient, diffuse, specular;
	// coeficientes de reflexión
	GLfloat expF;
	// exponente especular
	GLuint face = GL_FRONT_AND_BACK;
	// ambos lados
	GLuint sh = GL_SMOOTH;
	// smooth / flat shading

public:
	void setCooper();
	virtual	void upload() {
		glShadeModel(sh);
		glMaterialfv(face, GL_AMBIENT, glm::value_ptr(ambient));
		glMaterialfv(face, GL_DIFFUSE, glm::value_ptr(diffuse));
		glMaterialfv(face, GL_SPECULAR, glm::value_ptr(specular));
		glMaterialf(face, GL_SHININESS, expF);
	};
};

