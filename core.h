/////////////////////////////////////////////////
//		Core file of project - remder class    //
//		core.h							       //
//		Konkin Artem 2014					   //
/////////////////////////////////////////////////

//_______INCLUDES______//
//#include <windows.h>			// Header File For Windows
//#include <gl\gl.h>			// Header File For The OpenGL32 Library
//#include <gl\glu.h>			// Header File For The GLu32 Library

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

#include <glut.h>

#include "Model.h"

#pragma warning(disable : 4309) //warning C4309: 'argument' : truncation of constant value

//________USING________//
using namespace std;

/////////////////////////////////
//
//          VAR
//
/////////////////////////////////

GLfloat rquad = 1.0f;


GLdouble t_a = 0.0;
GLdouble t_b = -10;

char *name_model = "Normals.fbx";
bool load_state = false;

/*  Initialize color map and fog.  Set screen clear color
*  to end of color ramp.
*/
//#define NUMCOLORS 32
//#define RAMPSTART 16

static GLint fogMode;

//#define x .626731112119133606
//#define z .850650808352039932

static int shoulder = 0, elbow = 0;

static GLdouble spin;

bool close;



const float PI_1 = 3.141592653; //Замечательно число Пи
//const float height_pers = 0; //Высота персонажа, тут нуль, дабы смещения не происходило. 
//double x, y, z; //Положение камеры в пространстве 
//float angleX, angleY; // Углы поворота камеры
//POINT mousexy; // Сюда мы пишем положение мыши на экране.


/////////////////////////////////
//
//          OBJECT_POS
//
/////////////////////////////////

//static GLfloat vdata[12][3] = {
//	{ -x, 0.0, z }, { x, 0.0, z }, { -x, 0.0 - z }, { x, 0.0, -z },
//	{ 0.0, z, x }, { 0.0, z, -x }, { 0.0, -z, x }, { 0.0, -z, -x },
//	{ z, x, 0.0 }, { -z, x, 0.0 }, { z, -x, 0.0 }, { -z, -x, 0.0 }
//};
//static GLuint tindicec[20][3] = {
//	{ 1, 4, 0 }, { 4, 9, 0 }, { 4, 5, 9 }, { 8, 5, 4 }, { 1, 8, 4 },
//	{ 1, 10, 8 }, { 10, 3, 8 }, { 8, 3, 5 }, { 3, 2, 5 }, { 3, 7, 2 },
//	{ 3, 10, 7 }, { 10, 6, 7 }, { 6, 11, 7 }, { 6, 0, 11 }, { 6, 1, 0 },
//	{ 10, 1, 6 }, { 11, 0, 9 }, { 2, 11, 9 }, { 5, 2, 9 }, { 11, 2, 7 }
//};


/////////////////////////////////
//
//          LIGHT
//
/////////////////////////////////


/////////////////////////////////
//
//          CLASS
//
/////////////////////////////////

class CoreGraphicsObjectBind
{
public:
	//Конструктор
	CoreGraphicsObjectBind(char ok)
	{
		//MessageBox(NULL, (LPCWSTR)L"CoreGraphObjectBindClass is loaded.", (LPCWSTR)L"Class message", MB_OK | MB_ICONEXCLAMATION);
		//KillGLWindow();								// Reset The Display

		// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
		//if (MessageBox(NULL, (LPCWSTR)L"CoreGraphObjectBindClass is loaded.", (LPCWSTR)L"Class message", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
		//{
		//	closeWind();
		//}
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
		//GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };	 //Положение

		glLightfv(GL_LIGHT0, GL_AMBIENT, mat_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

		//glLightfv(GL_LIGHT0, GL_POSITION, light_position);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		//glEnable(GL_LIGHT1);
		glEnable(GL_DEPTH_TEST);


		int i;

		for (i = 0; i < NUMCOLORS; i++) 
		{
			GLfloat shade;
			shade = (GLfloat)(NUMCOLORS - i) / (GLfloat)NUMCOLORS;
			//glutSetColor(RAMPSTART + i, shade, shade, shade);
		}

		glEnable(GL_FOG);

		glFogi(GL_FOG_MODE, GL_LINEAR);
		glFogi(GL_FOG_INDEX, NUMCOLORS);
		glFogf(GL_FOG_START, 1.0);
		glFogf(GL_FOG_END, 6.0);
		glHint(GL_FOG_HINT, GL_NICEST);
		//glClearIndex((GLfloat)(NUMCOLORS + RAMPSTART - 1));
	}

	//Render objects
	GLvoid startRendering(
	double x, double y, double z,
	float angleX, float angleY)
	{
		
		const float height_pers = 0;
		
		GLfloat position[] = { 10.0, 0.0, 1.5, 1.0 };	 //Положение источника света (позиционированный)
		
		glPushMatrix();
		//glTranslatef(t_a, 0.0f, t_b);
		glEnable(GL_BLEND);		//Включение смешивания
		glBlendEquation(GL_FUNC_ADD);
		//glBlendEquation(GL_FUNC_SUBTRACT);
		//glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
		//glBlendEquation(GL_MIN);
		//glBlendEquation(GL_MAX);	//Смешивание
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);	//Сглаживание
		glRotated(30, 0.0, 1.0, 0.0);
		glLightfv(GL_LIGHT0, GL_POSITION, position);
		glTranslated(0.0, 0.0, -1.5);
		glDisable(GL_LIGHTING);
		//auxWireCube(0.1);

			Model Models(name_model);

		//Game gameLoad;
		//if (!gameLoad.Load()) {
		//	gameLoad.Shutdown();
		//	return;
		//}
		//gameLoad.Loop();
		//gameLoad.Shutdown();

		//MessageBox(NULL, (LPCWSTR)L"Glew status - err! Close!", (LPCWSTR)L"ERROR", MB_OK | MB_ICONSTOP); //if GLEW init = false 	
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glTranslatef(t_a, 0.0f, t_b);
		glPushMatrix();	

		gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
			auxSolidSphere(0.75);
			glDisable(GL_BLEND);
		glPopMatrix();
	}



	void draw_triangle(void)
	{
		gluLookAt(4.0, 4.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		glColor3f(1, 1, 1);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0.0, 25.0);
		glVertex2f(25.0, -25.0);
		glVertex2f(-25.0, -25.0);
		glEnd();
	}


	void fbx_load_model()
	{
		//Model Model("Normals.fbx");
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
			glVertex3f(iLine, y, fExtent);    // Draw Z lines
			glVertex3f(iLine, y, -fExtent);

			glVertex3f(fExtent, y, iLine);
			glVertex3f(-fExtent, y, iLine);
		}

		glEnd();
	}
};