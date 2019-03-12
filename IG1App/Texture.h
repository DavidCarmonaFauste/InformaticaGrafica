#pragma once
#include <GL/freeglut.h>  // Free OpenGL Utility Toolkit for creating windows, initializing OpenGL contexts, and handling input events
#include <glm.hpp>  // OpenGL Mathematics. A C++ mathematics library for graphics programming 
#include "Pixmap32RGBA.h"

class Texture// utiliza la clase PixMap32RGBA para el método load 
{  
public: 
	Texture(): w(0), h(0), id(0) {}; 
	~Texture() {if(id !=0 ) glDeleteTextures(1, &id);}; 
	void load(const std::string & BMP_Name,GLubyte alpha= 255); // cargary transferira GPU 
	void load(const std::string & BMP_Name, PixMap32RGBA::rgba_color color, GLubyte alpha);
	void bind(GLint modo = GL_REPLACE);   // para mezcla de colores 
	void unbind() { glBindTexture(GL_TEXTURE_2D, 0); }; 
	void loadColorBuffer();
	void save(const std::string & BMP_Name);
protected: 
	GLuint w, h;  // dimensiones de la imagen 
	GLuint id;     // identificador interno (GPU) de la textura 
	void init(); 
};

