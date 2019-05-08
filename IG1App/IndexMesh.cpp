#include "IndexMesh.h"



IndexMesh::IndexMesh()
{
}


IndexMesh::~IndexMesh()
{
}

void IndexMesh::render()
{
		if (vertices != nullptr) {
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_DOUBLE, 0, vertices);  // number of coordinates per vertex, type of each coordinate, stride, pointer 
			if (colors != nullptr) {
				glEnableClientState(GL_COLOR_ARRAY);
				glColorPointer(4, GL_DOUBLE, 0, colors);   // number of coordinates per color, type of each coordinate, stride, pointer 
			}
			if (textureData != nullptr)
			{
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glTexCoordPointer(2, GL_DOUBLE, 0, textureData);
			}
			if (normals != nullptr)
			{
				glEnableClientState(GL_INDEX_ARRAY);
				glIndexPointer(GL_UNSIGNED_INT, 0, indices);
			}

			glDrawElements(primitive, numIndices, GL_UNSIGNED_INT, indices);   // primitive graphic, first index and number of elements to be rendered

			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glDisableClientState(GL_COLOR_ARRAY);
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_INDEX_ARRAY);
		}
}

IndexMesh * IndexMesh::generateGridTex(GLdouble lado, GLuint numDiv)
{	// Grid cuadrado de lado*lado, centrado en el plano Y = 0,
	// dividido en numDiv*numDiv celdas (cada celda son 2 triángulos)
		
	IndexMesh* m = new IndexMesh();
	m->primitive = GL_TRIANGLES;

	GLdouble incr = lado / numDiv;	// incremento para la coordenada x, y la c. z
	GLuint numFC = numDiv + 1;	// número de vértices por filas y columnas
	
	// generar vértices
	m-> numVertices = numFC * numFC;


	// número de vértices 
	m->	vertices = new glm::dvec3[m->numVertices];

	// ->
	GLdouble z = -lado / 2;
	GLdouble x = -lado / 2;
	
	for (int i = 0; i < numDiv; i++) {
		for (int j = 0; j < numDiv; j++) {
			m->vertices[i * numFC + j] = glm::dvec3(x + j * incr, 0, z + i * incr);
		}
	}

	// generar índices

	m->	numIndices = numDiv * numDiv * 6;
	
	// número de índices 
	m-> indices = new GLuint[m->numIndices];
	
	// ->
	int a = 0;
	GLuint iv;

	for (int h = 0; h < numDiv; h++) {
		for (int k = 0; k < numDiv; k++) {
			iv = h * numFC + k;
			m->indices[a++] = iv;
		}
	}

	//Texturas
	m->texCoords = new glm::dvec2[m->numVertices];

	int s = 0;
	int t = 1;
		
	for (int b = 0; b < numDiv; b++) {
		for (int n = 0; n < numDiv; n++) {
			m->texCoords[b * numFC + n] = glm::dvec2(s + 1/b, t - 1/n);
		}
	}

	
	
	return m;
}

IndexMesh * IndexMesh::generatePlanoCurvado(GLdouble lado, GLuint numDiv, GLdouble curvatura)
{
	IndexMesh* m = generateGridTex(lado, numDiv);

	for (int i = 0; i < m->vertices; i++)
	{
		f(x, z) = lado * curvatura / 2 – curvatura / lado * (x*x) – curvatura / lado * (z*z);

		n(x, z) = (2 * curvatura / lado * x, 1, 2 * curvatura / lado * z);
	}
}
