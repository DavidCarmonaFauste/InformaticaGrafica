#include "Mesh.h"

using namespace glm;

//-------------------------------------------------------------------------

Mesh ::~Mesh(void) 
{
  delete[] vertices;  vertices = nullptr;
  delete[] colors;    colors = nullptr;
}
//-------------------------------------------------------------------------

void Mesh::render()
{
  if (vertices != nullptr) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vertices);  // number of coordinates per vertex, type of each coordinate, stride, pointer 
    if (colors != nullptr) {
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0, colors);   // number of coordinates per color, type of each coordinate, stride, pointer 
    }
	
    glDrawArrays(primitive, 0, numVertices);   // primitive graphic, first index and number of elements to be rendered

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
  }
}
//-------------------------------------------------------------------------

Mesh * Mesh::createRGBAxes(GLdouble l)
{
  Mesh* m = new Mesh();
  m->primitive = GL_LINES;
  m->numVertices = 6;

  m->vertices = new dvec3[m->numVertices];
  // X axis vertices
  m->vertices[0] = dvec3(0.0, 0.0, 0.0);   
  m->vertices[1] = dvec3(l, 0.0, 0);
  // Y axis vertices
  m->vertices[2] = dvec3(0, 0.0, 0.0);
  m->vertices[3] = dvec3(0.0, l, 0.0); 
  // Z axis vertices
  m->vertices[4] = dvec3(0.0, 0.0, 0.0);
  m->vertices[5] = dvec3(0.0, 0.0, l);

  m->colors = new dvec4[m->numVertices];
  // X axis color: red  ( Alpha = 1 : fully opaque)
  m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
  m->colors[1] = dvec4(1.0, 0.0, 0.0, 1.0);
  // Y axis color: green
  m->colors[2] = dvec4(0.0, 1.0, 0.0, 1.0);
  m->colors[3] = dvec4(0.0, 1.0, 0.0, 1.0);
  // Z axis color: blue
  m->colors[4] = dvec4(0.0, 0.0, 1.0, 1.0);
  m->colors[5] = dvec4(0.0, 0.0, 1.0, 1.0);
 
  return m; 
}

//-------------------------------------------------------------------------

Mesh * Mesh::generaPoliespiral(dvec2 verIni, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert)
{
	Mesh* m = new Mesh();
	m->primitive = GL_LINE_STRIP;
	m->numVertices = numVert;

	m->vertices = new dvec3[m->numVertices];
	double x = verIni.x;
	double y = verIni.y;
	//m->vertices[0] = dvec3(verIni.x, verIni.y, 0);

	for (int i = 0; i < numVert; i++) {
		m->vertices[i] = dvec3(x, y, 0);

		x = x + (ladoIni + incrLado * i) * cos(radians(angIni + incrAng * i));
		y = y + (ladoIni + incrLado * i) * sin(radians(angIni + incrAng * i));
	}
	return m;
}

//-------------------------------------------------------------------------

Mesh * Mesh::generaDragon(GLuint numVert)
{
	Mesh* m = new Mesh();
	m->primitive = GL_POINTS;
	m->numVertices = numVert;

	m->vertices = new dvec3[m->numVertices];
	double x = 0;
	double y = 0;
	double xAux = 0;
	double yAux = 0;

	double PR1 = 0.787473;
	//m->vertices[0] = dvec3(verIni.x, verIni.y, 0);

	for (int i = 0; i < numVert; i++) {
		m->vertices[i] = dvec3(x, y, 0);

		xAux = x;
		yAux = y;

		double azar =rand()/double(RAND_MAX);
		if (azar <	PR1)
		{		
			x = 0.824074 * xAux + 0.281482 * yAux - 0.882290;
			y = -0.212346 * xAux + 0.864198 * yAux - 0.110607;
		}
		else
		{
			x = 0.088272 * xAux + 0.520988 * yAux + 0.785360;
			y = -0.463889 * xAux - 0.377778 * yAux + 8.095795;
		}
	}

	return m;
}


//-------------------------------------------------------------------------

Mesh * Mesh::generaTrianguloRGB(GLdouble r)
{
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLES;
	m->numVertices = r;

	m->vertices = new dvec3[m->numVertices];

	double x = 0, y = 0;

	double ang = 90; //Para que salga hacia arriba, y se creen en el orden

	double angA = 120;

	for (int i = 0; i < 3; i++) {
		
		x = 0 + r * cos(radians(ang + angA * i));
		y = 0 + r * sin(radians(ang + angA * i));
		
		m->vertices[i] = dvec3(x, y, 0);
	}

	m->colors = new dvec4[m->numVertices];

	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0); //Rojo
	m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0); //Verde
	m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0); //Azul

	return m;
}

Mesh * Mesh::generaRectangulo(GLdouble w, GLdouble h)
{
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLE_STRIP;
	m->numVertices = 4;

	m->vertices = new dvec3[m->numVertices];

	m->vertices[0] = dvec3(0, 0, 0); //V0
	m->vertices[2] = dvec3(w, 0, 0); //V2
	m->vertices[1] = dvec3(0, -h, 0); // V1
	m->vertices[3] = dvec3(w, -h, 0); // V3


	return m;
}
//-------------------------------------------------------------------------
Mesh * Mesh::generaRectanguloRGB(GLdouble w, GLdouble h)
{
	Mesh* m = generaRectangulo(w, h);

	m->colors = new dvec4[m->numVertices];

	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0); //Rojo
	m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0); //Verde
	m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0); //Azul
	m->colors[3] = dvec4(1.0, 1.0, 1.0, 1.0); //Blanco

	return m;
}
//-------------------------------------------------------------------------
Mesh * Mesh::generaEstrella3D(GLdouble re, GLdouble np, GLdouble h)
{
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLE_FAN;
	m->numVertices = 2*np+2;

	m->vertices = new dvec3[m->numVertices];

	double x = 0, y = 0, z = 0;

	double ang = 90; //Para que salga hacia arriba, y se creen en el orden

	double angA = 30;

	m->vertices[0] = dvec3(x, y, z);

	bool grande = false;

	for (int i = 1; i < (2 * np + 1); i++) {

		x = 0 + re * cos(radians(ang + angA * i));
		y = 0 + re * sin(radians(ang + angA * i));

		if (!grande)
		{
			x = x / 2;
			y = y / 2;

			grande = true;
		}

		else
		{
			grande = false;
		}

		m->vertices[i] = dvec3(x, y, h);
	}

	m->vertices[m->numVertices-1] = m->vertices[1];

	return m;
}

Mesh * Mesh::generaContCubo(GLdouble l)
{
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLE_STRIP;
	m->numVertices = 12;

	m->vertices = new dvec3[m->numVertices];

	m->vertices[0] = dvec3(-l/2, l / 2, l / 2);
	m->vertices[1] = dvec3(-l  / 2, -l/ 2, l / 2);
	m->vertices[2] = dvec3(l / 2, l / 2, l / 2);
	m->vertices[3] = dvec3(l / 2, -l / 2, l / 2);
	m->vertices[4] = dvec3(l / 2, l / 2, -l / 2);
	m->vertices[5] = dvec3(l / 2, -l / 2, -l / 2);
	m->vertices[6] = dvec3(-l / 2, l / 2, -l / 2);
	m->vertices[7] = dvec3(-l / 2, -l / 2, -l / 2);
	m->vertices[8] = m->vertices[0];
	m->vertices[9] = m->vertices[1];
	//m->vertices[10] = m->vertices[3];
	//m->vertices[11] = m->vertices[5];

	
	return m;
}

Mesh * Mesh::generaCajaSinTapa(GLdouble l)
{
	return nullptr;
}

//-------------------------------------------------------------------------