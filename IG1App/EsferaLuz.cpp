#include "EsferaLuz.h"

EsferaLuz::EsferaLuz(GLuint radius, GLuint radius2, glm::dvec3 pos, glm::dvec3 relativePos) : Esfera(radius)
{

	qObj2 = gluNewQuadric();

	radio2 = radius2;

	PosicionOriginal = pos;

	MatRelativa = translate(modelMat, relativePos);

	luz = new SpotLight();
	luz->setDir(fvec3(0, -1, 0));
	luz->setAng(20.0);
	luz->setExp(0.5);
	luz->uploadLI();
	luz->enable();
	update(); //para que este visible desde el principio
}

EsferaLuz::~EsferaLuz()
{
	delete luz;
}

void EsferaLuz::render(Camera const & cam)
{
	if (qObj != nullptr) {
		dmat4 originalMat = modelMat;

		modelMat = mat1;

		glEnable(GL_CULL_FACE);

		material_.upload();
		gluQuadricDrawStyle(qObj, GLU_LINE);
		gluQuadricTexture(qObj, GL_TRUE);
		gluQuadricNormals(qObj, GLU_SMOOTH);
		gluQuadricOrientation(qObj, GLU_OUTSIDE);

		uploadMvM(cam.getViewMat());

		texture_->bind(GL_MODULATE);
		gluSphere(qObj, radio_, 25, 25);
		texture_->unbind();


		modelMat = mat2;

		material2.upload();
		gluQuadricDrawStyle(qObj2, GLU_FILL);
		gluQuadricTexture(qObj2, GL_TRUE);
		gluQuadricNormals(qObj2, GLU_SMOOTH);
		gluQuadricOrientation(qObj2, GLU_OUTSIDE);

		uploadMvM(cam.getViewMat());

		texture2->bind(GL_MODULATE);
		gluSphere(qObj2, radio2, 100, 100);
		texture2->unbind();


		modelMat = originalMat;

		glDisable(GL_CULL_FACE);
	}
}

void EsferaLuz::setTexture2(Texture * tex)
{
	texture2 = tex;
}

void EsferaLuz::setMaterial2(Material mat)
{
	material2 = mat;
}

void EsferaLuz::update() //animacion del movimiento de la esfera peque�ita, y actualizacion de angulos y las matrices a renderizar
{
	AnguloUpdate += 0.01;
	if (AnguloUpdate >= 360)
		AnguloUpdate -= 360;

	AnguloRotacion += 0.5 * DireccionRotacion;
	if (AnguloRotacion >= topeAngulo) {
		AnguloRotacion = topeAngulo;
		DireccionRotacion = -1;
	}
	else if (AnguloRotacion <= -topeAngulo) {
		AnguloRotacion = -topeAngulo;
		DireccionRotacion = 1;
	}

	GLdouble a = 400; //800 el lado de la superficie, asi que 400
	GLdouble b = radio2; //1/2 altura del objeto, asi la mitad del radio

	dmat4 updateMat = translate(modelMat, dvec3(a * cos(AnguloUpdate), b * sin(AnguloUpdate) * sin(AnguloUpdate), -a * sin(AnguloUpdate) * cos(AnguloUpdate))); //formulita

	mat1 = rotate(updateMat * MatRelativa, radians(AnguloRotacion), dvec3(1.0, 1.0, 1.0)) / (updateMat * MatRelativa) * updateMat; //posiciones relativas
	mat2 = updateMat * MatRelativa;
}

void EsferaLuz::uploadLight(dmat4 camMat) //actualiza la luz
{
	luz->upload(camMat * mat1); //actualizar luz
}
