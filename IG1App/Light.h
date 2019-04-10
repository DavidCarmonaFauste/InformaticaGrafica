#pragma once
#include <GL/freeglut.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>


class Light
{
protected:
	static GLuint cont;
	GLuint id = GL_LIGHT0 + GL_MAX_LIGHTS;

	glm::fvec4	ambient = { 0.1, 0.1, 0.1, 1 };
	glm::fvec4	diffuse = { 0.5, 0.5, 0.5, 1 };
	glm::fvec4	specular = { 0.5, 0.5, 0.5, 1 };

public:
	Light() {
		if(cont < GL_MAX_LIGHTS)
			id = GL_LIGHT0 + cont;
		++cont;
    enable();
	}
	virtual ~Light() {
		disable();
	}
	virtual void uploadLI();
	virtual void upload(glm::dmat4 const& modelViewMat) = 0;
	void disable() {
		if (id < GL_LIGHT0 + GL_MAX_LIGHTS) { glDisable(id); }
	};
	void enable() {
		if (id < GL_LIGHT0 + GL_MAX_LIGHTS) { glEnable(id); }
	};

	void setAmb(glm::fvec4 amb) {
		ambient = amb;
	};
};


