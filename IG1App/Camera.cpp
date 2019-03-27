#include "Camera.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

//-------------------------------------------------------------------------

void Camera::set2D() 
{
	ang = 270;

	eye= dvec3(0, 0, 500);
	look= dvec3(0, 0, 0);
	up= dvec3(0, 1, 0);

//	setVm();
	viewMat = lookAt(eye, look, up);
}
//-------------------------------------------------------------------------

void Camera::set3D() 
{
	ang = 315;

	eye= dvec3(500, 500, 500);
	look= dvec3(0, 10, 0);
	up= dvec3(0, 1, 0);

	//	setVm();
	viewMat = lookAt(eye, look, up);
}
//-------------------------------------------------------------------------

void Camera::uploadVM() const
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(viewMat));
}
//-------------------------------------------------------------------------

/*void Camera::pitch(GLdouble a) 
{  
	viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(1.0, 0, 0));
}
//-------------------------------------------------------------------------
void Camera::yaw(GLdouble a)
{
	viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 1.0, 0));
}
//-------------------------------------------------------------------------
void Camera::roll(GLdouble a)
{
	viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 0, 1.0));
}*/

void Camera::setAxes()
{
	right = row(viewMat, 0);
	upward = row(viewMat, 1);
	front = -row(viewMat, 2);
}
void Camera::setVm()
{
	viewMat = lookAt(eye, look, up); 
	setAxes();
}
//-------------------------------------------------------------------------

void Camera::uploadSize(GLdouble aw, GLdouble ah)
{
	xRight = aw / 2.0;
	xLeft = -xRight;
	yTop = ah / 2.0;
	yBot = -yTop;

	projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);

	uploadPM();
}
//-------------------------------------------------------------------------

void Camera::uploadScale(GLdouble s)
{
	factScale -= s;
	if (factScale < 0) factScale = 0.01;
	projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);

	uploadPM();
}
void Camera::moveLR(GLdouble cs)
{
	eye += right * cs;
	look += right * cs;
	setVm();
}
void Camera::moveFB(GLdouble cs)
{
	eye += front * cs;
	look += front * cs;
	setVm();
}
void Camera::moveUD(GLdouble cs)
{
	eye += upward * cs;
	look += upward * cs;
	setVm();
}

void Camera::orbit(GLdouble incAng, GLdouble incY)
{
	ang += incAng;
	eye.x = look.x + cos(radians(ang)) * radio;
	eye.z = look.z - sin(radians(ang)) * radio;
	eye.y += incY;
	setVm();
}
//-------------------------------------------------------------------------

void Camera::uploadPM() const
{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(value_ptr(projMat));
	glMatrixMode(GL_MODELVIEW);
}
//-------------------------------------------------------------------------


