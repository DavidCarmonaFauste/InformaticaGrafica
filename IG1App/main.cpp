//#include <Windows.h>
//#include <gl/GL.h>    // OpenGL
//#include <gl/GLU.h>   // OpenGL Utility Library
//#include <GL/glut.h>  // OpenGL Utility Toolkit

#include <GL/freeglut.h>  // Free OpenGL Utility Toolkit for creating windows, initializing OpenGL contexts, and handling input events
#include <glm.hpp>  // OpenGL Mathematics. A C++ mathematics library for graphics programming 

#include "Viewport.h"
#include "Camera.h"
#include "Scene.h"

#include <iostream>

using namespace std;

//---------- Global variables -------------------------------------------------------------

// Viewport position and size
Viewport viewPort(800, 600);   

// Camera position, view volume and projection
Camera camera(&viewPort);    

// Graphics objects of the scene
Scene scene;

bool animation = false;
bool sceneBool = true;

GLuint last_update_tick = 0;

dvec2 mCoord;

GLint mBot;

//----------- Callbacks ----------------------------------------------------

void display();
void resize(int newWidth, int newHeight);
void key(unsigned char key, int x, int y);
void specialKey(int key, int x, int y);
void update();
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void mouseWheel(int n, int d, int x, int y);
//-------------------------------------------------------------------------

int main(int argc, char *argv[])
{
  cout << "Starting console..." << '\n';

  // Initialization
  glutInit(&argc, argv);

  glutInitContextVersion(3, 3);	//versión de openGL
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);  // GLUT_CORE_PROFILE		//Modo: compatibilidad con versiones antiguas
  glutInitContextFlags(GLUT_DEBUG);   // GLUT_FORWARD_COMPATIBLE
 
  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS); //que acabe la ejecución cuando se cierre la ventana
  
  glutInitWindowSize(800, 600);   // window size
  //glutInitWindowPosition (140, 140);

  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH /*| GLUT_STENCIL*/); // RGBA colors, double buffer (para que los frames se dibujen de una vez), depth buffer and stencil buffer   
  
  int win = glutCreateWindow("IG1App");  // window's identifier
  
  // Callback registration
  glutReshapeFunc(resize);		// cambios de tamaño de la ventana
  glutKeyboardFunc(key);		//eventos de teclado
  glutSpecialFunc(specialKey);
  glutDisplayFunc(display);		//como se dibuja el contenido de la ventana
  glutIdleFunc(update);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutMouseWheelFunc(mouseWheel);

  cout << glGetString(GL_VERSION) << '\n';
  cout << glGetString(GL_VENDOR) << '\n';

  // after creating the context	(los objetos de la escena)
  camera.set2D();
  scene.init2();    
  
  glutMainLoop(); //bucle automático, no lo vamos a implementar (responde a eventos repinta)
    
  //cin.ignore(INT_MAX, '\n');  cin.get();  
  glutDestroyWindow(win);  // Destroy the context 
 
  return 0;
}
//-------------------------------------------------------------------------

void display()   // double buffering
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
  
  scene.render(camera);   
    
  glutSwapBuffers();  
}
//-------------------------------------------------------------------------

void resize(int newWidth, int newHeight)
{
  // Resize Viewport 
  viewPort.uploadSize(newWidth, newHeight);  
  
  // Resize Scene Visible Area 
  camera.uploadSize(viewPort.getW(), viewPort.getH());    // scale unchanged
}
//-------------------------------------------------------------------------

void key(unsigned char key, int x, int y)
{
  bool need_redisplay = true;

  switch (key) {
  case 27:  // Escape key 
    glutLeaveMainLoop();  // Freeglut's sentence for stopping glut's main loop 
    break;
  case '+': 
    camera.uploadScale(+0.01);   // zoom in  (increases the scale)
    break;
  case '-':
    camera.uploadScale(-0.01);   // zoom out (decreases the scale)
    break;
  case 'l':
	camera.set3D(); 
	break;
  case 'o':
	camera.set2D();
	break;
  case 'f':

	  break;
  case 'u':
	  if (animation)
		  animation = false;
	  else
		  animation = true;
	  break;
  case 'a':
	  camera.moveLR(-5);
	  break;
  case 'd':
	  camera.moveLR(5);
	  break;
  case 'w':
	  camera.moveUD(5);
	  break;
  case 's':
	  camera.moveUD(-5);
	  break;
  case 'q':
	  camera.moveFB(-5);
	  break;
  case 'e':
	  camera.moveFB(5);
	  break;
  case '3':
	  scene.clear();

	  if (sceneBool)
	  {
		  glEnable(GL_DEPTH_TEST);  // enable Depth test 
		  glEnable(GL_TEXTURE_2D);
		  glEnable(GL_BLEND);
		  glEnable(GL_ALPHA_TEST);
		  scene.init();
		  sceneBool = false;
	  }
	  else
	  {
		 glDisable(GL_DEPTH_TEST);  // enable Depth test 
		 glDisable(GL_TEXTURE_2D);
		 glDisable(GL_BLEND);
		 glDisable(GL_ALPHA_TEST);
		 scene.init2();
		 sceneBool = true;
	  }
	  glutPostRedisplay();
  default:
	need_redisplay = false;
    break;
  } //switch

  if (need_redisplay)
    glutPostRedisplay();
}
//-------------------------------------------------------------------------

void specialKey(int key, int x, int y)
{
  bool need_redisplay = true;

  switch (key) {
  case GLUT_KEY_RIGHT:
	  camera.moveLR(5);
	  break;
  case GLUT_KEY_LEFT:
	  camera.moveLR(-5);
	  break;
  case GLUT_KEY_UP:
	  camera.moveUD(5);
	  break;
  case GLUT_KEY_DOWN:
	  camera.moveUD(-5);
    break;
  default:
    need_redisplay = false;
    break;
  }//switch

  if (need_redisplay)
    glutPostRedisplay();
}
//-------------------------------------------------------------------------

void update()
{	
	if (glutGet(GLUT_ELAPSED_TIME) > (last_update_tick + 16))
	{
		if (animation)
		{
			//cout << glutGet(GLUT_ELAPSED_TIME);
			scene.update();
			glutPostRedisplay();
			last_update_tick = glutGet(GLUT_ELAPSED_TIME);
		}
	}
}

void mouse(int button, int state, int x, int y)
{
	mCoord = dvec2(x, y);

	if (state == GLUT_DOWN)
		mBot = button;

	else if (state == GLUT_UP)
		mBot = -1;
}

void motion(int x, int y)
{
	dvec2 mp = mCoord; // guardar la anterior posición en var. temp.
	mCoord = dvec2(x, y); // Guardamos la posición actual
	mp = (mCoord - mp); // desplazamiento realizado	
		
		if (mBot == GLUT_LEFT_BUTTON) 
		{
			camera.orbit(mp.x * -0.05, mp.y * 0.05); 
			glutPostRedisplay();
		}
		else if (mBot == GLUT_RIGHT_BUTTON) 
		{
			camera.moveLR(mp.x * -0.05); 
			camera.moveUD(mp.y * 0.05);
			glutPostRedisplay();
		}
}

void mouseWheel(int n, int d, int x, int y)
{
	int m = glutGetModifiers();	//returns any special key that is pressed (CTRL, ALT, SHIFT)

		if (m == 0) // none of those special keys is pressed
		{
			camera.moveFB(5 * d);


			glutPostRedisplay();
		}
		else if (m == GLUT_ACTIVE_CTRL) {

			camera.uploadScale(+0.01 * d);
			glutPostRedisplay();
		}
}
