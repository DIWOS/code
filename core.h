/////////////////////////////////////////////////
//		Core file of project - remder class    //
//		core.h							       //
//		Konkin Artem 2014					   //
/////////////////////////////////////////////////

//_______INCLUDES______//
#include <cmath>
#include <glew.h>
#include <gl\glaux.h>			// Header File For The Glaux Library
#include <iostream>
//________GLEW_________//
#ifdef	_WIN32
#include	<wglew.h>
#else
#include	<glxew.h>
#endif
//_________SDL_________//
#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif
//_________GLUT_________//
#ifdef __APPLE__
#include <glut.h>
#else
#include <glut.h>
#endif
#include "Model.h"

#pragma warning(disable : 4309) //warning C4309: 'argument' : truncation of constant value

//________USING________//
using namespace std;

/////////////////////////////////
//
//          VAR
//
/////////////////////////////////

GLdouble t_a = 0.0;
GLdouble t_b = -10;

char *name_model = "cube.fbx";
bool load_state = false;
static GLint fogMode;
static int shoulder = 0, elbow = 0;
static GLdouble spin;
bool close;
const float PI_1 = 3.141592653; //Замечательно число Пи


class CoreGraphicsObjectBind
{
public:
	//Конструктор
	CoreGraphicsObjectBind(char ok)
	{
		DrawGround();
	}
										//RENDER//
	//Light render
	GLvoid lightRender(void)
	{		
		

		GLfloat mat_ambient[] = { 0.3, 0.3, 0.0, 1.0 };		//Цвет фонового освещения
		GLfloat mat_diffuse[] = {1.0,1.0,1.0,1.0};		//Цвет рассеянного освещения
		GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };	 //Цвет отраженного света
		GLfloat mat_shininess[] = { 60.0 };		//Степень отражения от материала

		glLightfv(GL_LIGHT0, GL_AMBIENT, mat_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		glEnable(GL_DEPTH_TEST);

		int i;
		for (i = 0; i < NUMCOLORS; i++) 
		{
			GLfloat shade;
			shade = (GLfloat)(NUMCOLORS - i) / (GLfloat)NUMCOLORS;
		}

		glEnable(GL_FOG);
		glFogi(GL_FOG_MODE, GL_LINEAR);
		glFogi(GL_FOG_INDEX, NUMCOLORS);
		glFogf(GL_FOG_START, 1.0);
		glFogf(GL_FOG_END, 6.0);
		glHint(GL_FOG_HINT, GL_NICEST);
	}

	//Render objects
	GLvoid startRendering(
	double x, double y, double z,
	float angleX, float angleY)
	{
		GLfloat position[] = { 10.0, 0.0, 1.5, 1.0 };	 //Положение источника света (позиционированный)
		
		glPushMatrix();
			glEnable(GL_BLEND);		//Включение смешивания
			glBlendEquation(GL_FUNC_ADD);
			glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);	//Сглаживание
			glRotated(30, 0.0, 1.0, 0.0);
			glLightfv(GL_LIGHT0, GL_POSITION, position);
			glTranslated(0.0, 0.0, -1.5);
			glDisable(GL_LIGHTING);
			Model Models(name_model);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glTranslatef(t_a, 0.0f, t_b);
		glPushMatrix();	
			gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
			//auxSolidSphere(0.75);
			glDisable(GL_BLEND);
		glPopMatrix();
	}

private:

	void DrawGround(void)
	{
		GLfloat fExtent = 20.0f;
		GLfloat fStep = 1.0f;
		GLfloat y = -0.4f;
		GLint iLine;

		glBegin(GL_LINES);
		for (iLine = -fExtent; iLine <= fExtent; iLine += fStep)
		{
			glVertex3f(iLine, y, fExtent);   
			glVertex3f(iLine, y, -fExtent);
			glVertex3f(fExtent, y, iLine);
			glVertex3f(-fExtent, y, iLine);
		}

		glEnd();
	}
};