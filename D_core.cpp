#include <windows.h>		// Header File For Windows
//#include <gl\gl.h>			// Header File For The OpenGL32 Library
//#include <gl\glu.h>			// Header File For The GLu32 Library
//#include <gl\glaux.h>		// Header File For The Glaux Library
#include "core.h"
#include <glew.h>
#include <iostream>

//________GLEW_________//
#ifdef	_WIN32
#include	<wglew.h>
#else
#include	<glxew.h>
#endif

#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

#include "Model.h"


const float PI = 3.141592653; //Замечательно число Пи
const float height_pers = 0; //Высота персонажа, тут нуль, дабы смещения не происходило. 
double x, y, z; //Положение камеры в пространстве 
float angleX, angleY; // Углы поворота камеры
POINT mousexy; // Сюда мы пишем положение мыши на экране.


//________USING________//
using namespace std;

SDL_Window *window; // задаем окно для SDL

const int width = 640; // ширина окна
const int height = 480; // высота окна

GLvoid ReSizeGLScene()		// Resize And Initialize The GL Window
{
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix

}

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	ReSizeGLScene();

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.105f, 0.105f, 0.105f, 0.105f);				// Black Background

	
	/*GLEW initialize*/
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		MessageBox(NULL, (LPCWSTR)L"Glew status - err! Close!", (LPCWSTR)L"ERROR", MB_OK | MB_ICONSTOP); //if GLEW init = false 
	}
	/*_______________*/


	// Core graphics functions
	CoreGraphicsObjectBind bindFuncCall('OK');
	//bindFuncCall.key();

	glBlendFunc(GL_ONE, GL_ONE);

	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	return TRUE;										// Initialization Went OK
}

int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	
	// Core graphics functions
	CoreGraphicsObjectBind bindFuncCall('OK');

	bindFuncCall.lightRender();
	bindFuncCall.startRendering(x,y,z,angleX,angleY);
	
	glLoadIdentity();									// Reset The Current Modelview Matrix
	
	return TRUE;										// Everything Went OK
}

void init(){

	// Инициализация SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		cout << "Unable to init SDL, error: " << SDL_GetError() << endl;
		exit(1);
	}
	// Включаем двойной буфер, настраиваем цвета
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	// Создаем окно с заголовком "Cube", размером 640х480 и расположенным по центру экрана.
	window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	SDL_GLContext glcontext = SDL_GL_CreateContext(window); // создаем контекст OpenGL

	if (window == NULL){ // если не получилось создать окно, то выходим 
		exit(1);
	}

	InitGL();
}

int main(int argc, char *argv[]){

	CoreGraphicsObjectBind bindFuncCall('OK');

	init(); // инициализация

	bool running = true;

	float xrf = 0, yrf = 0, zrf = 0; // углы поворота

	while (running){

		SDL_Event event; // события SDL

		while (SDL_PollEvent(&event)){ // начинаем обработку событий
			switch (event.type){ // смотрим:
			case SDL_QUIT: // если произошло событие закрытия окна, то завершаем работу программы
				running = false;
				break;

			case SDL_KEYDOWN: // если нажата клавиша
				switch (event.key.keysym.sym){ // смотрим какая
				case SDLK_ESCAPE: // клавиша ESC
					running = false; // завершаем работу программы
					break;

				case SDLK_w: // клавиша W
				{
								 t_b -= 0.1;
								 glFlush();
								 SDL_GL_SwapWindow(window);
								 break;
				}
				case SDLK_s: // клавиша S
				{
								 t_b += 0.1;
								 glFlush();
								 SDL_GL_SwapWindow(window);
								 break;
				}
				case SDLK_d: // клавиша D
				{
								 t_a += 0.1;
								 glFlush();
								 SDL_GL_SwapWindow(window);
								 break;
				}
				case SDLK_a: // клавиша A
				{
								 t_a -= 0.1;
								 glFlush();
								 SDL_GL_SwapWindow(window);
								 break;
				}
				case SDLK_z: // клавиша Z
				{
								 fogMode = GL_LINEAR;
								 glFlush();
								 SDL_GL_SwapWindow(window);
								 break;
				}
				case SDLK_x: // клавиша X
				{
								 fogMode = GL_EXP2;
								 glFlush();
								 SDL_GL_SwapWindow(window);
								 break;
				}
				case SDLK_c: // клавиша C
				{
								 fogMode = GL_EXP;
								 glFlush();
								 SDL_GL_SwapWindow(window);
								 break;
				}
				case SDLK_l: // клавиша "L" - Load FBX model 
				{
								 break;
				}
					glFogi(GL_FOG_MODE, fogMode);
				}
				break;
			}
		}

		// пока программа запущена изменяем углы поворота, тем самым вращая куб
		DrawGLScene();

		// обновляем экран
		gluPerspective(60.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f); //GLU prspective

		glFlush();
		SDL_GL_SwapWindow(window);
	}

	SDL_Quit(); // завершаем работу SDL и выходим
	return 0;
}

