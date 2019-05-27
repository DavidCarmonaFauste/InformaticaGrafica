#include "EsferaLuz.h"

EsferaLuz::EsferaLuz(GLuint radius, GLuint radius2, glm::dvec3 pos, glm::dvec3 relativePos): Esfera(radius)
{

	qObj2 = gluNewQuadric();

	radio2 = radius2;

	PosicionOriginal = pos;

	MatRelativa = translate(dmat4(1), relativePos);

	luz = new SpotLight();
	luz->setDir(fvec3(0, -1, 0));
	luz->setExp(5.0);
	luz->enable();
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

void EsferaLuz::update()
{
	AnguloUpdate += 1;
	if (AnguloUpdate >= 360)
		AnguloUpdate -= 360;

	


	//AnguloRotacion += 0.5 * DireccionRotacion;
	//if (AnguloRotacion >= topeAngulo) {
	//	AnguloRotacion = topeAngulo;
	//	DireccionRotacion = -1;
	//}
	//else if (AnguloRotacion <= -topeAngulo) {
	//	AnguloRotacion = -topeAngulo;
	//	DireccionRotacion = 1;
	//}


}

void EsferaLuz::uploadLight(dmat4 camMat)
{
	//GLdouble Dato1 = radio2;
	//GLdouble Dato2 = sqrt(4 * 3.14 * radio2 * radio2) / 2;

	GLdouble a = 1 / 2 * 2000;
	GLdouble b = 200;
	GLdouble c = -a;

	dvec3 T = dvec3(a * cos(AnguloUpdate), c * sin(AnguloUpdate)  * sin(AnguloUpdate), c * sin(AnguloUpdate) * cos(AnguloUpdate));

	//dmat4 updateMat = translate(modelMat, dvec3(Dato2 * cos(AnguloUpdate), Dato1 * sin(AnguloUpdate) * sin(AnguloUpdate), -Dato2 * sin(AnguloUpdate) * cos(AnguloUpdate)));

	dmat4 updateMat = translate(modelMat, T);

	mat1 = rotate(updateMat * MatRelativa, radians(AnguloRotacion), dvec3(0, 1.0, 0)) / (updateMat * MatRelativa) * updateMat;
	mat2 = updateMat * MatRelativa;

	luz->upload(camMat * mat1);
}
