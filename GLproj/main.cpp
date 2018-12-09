


#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/glut.h>
#include <SOIL2.h>
#include <cmath>
#include <utility>
#include <iostream>
#include "OBJ_Loader.h"

int w = 0, h = 0;
objl::Loader obj_loader;
GLuint vertexbuffer, indexbuffer, texturecoordbuffer, normalbuffer;

void Init(void)
{
	glClearColor(0, 0, 0, 1.0f);
	glEnable(GL_LIGHTING);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	// автоматическое приведение нормалей к
	// единичной длине
	glEnable(GL_NORMALIZE);

	

	bool succes = obj_loader.LoadFile("torus.obj");
	if (succes) {
		glGenBuffers(1, &vertexbuffer);

	}


}

void Reshape(int x, int y)
{
	if (y == 0 || x == 0) return;

	w = x;
	h = y;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, (GLdouble)w / h, 0.1, 50);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(-10, 0, 0, 0, 0, 0, 0, 0, 1);

}



void Update(void) {
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glFlush();
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)	
{
	switch (key)
	{
	case 'a':	// A
		
		break;
	case 'd':	// D
		
		break;
	case 'w':	// W
		
		break;
	case 's':	// S	
		
		break;
	case 'q': 
		
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
	switch (key)
	{ 
	case GLUT_KEY_PAGE_UP:
		
		break;
	case GLUT_KEY_PAGE_DOWN:
		
		break;
	case GLUT_KEY_UP:
		
		break;

	case GLUT_KEY_DOWN:
		
		break;

	case GLUT_KEY_LEFT:
		
		break;

	case GLUT_KEY_RIGHT:
		
		break;
	default:
		break;
	
	}


	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);

	glutCreateWindow("OpenGL");
	glEnable(GL_DEPTH_TEST);

	
	glutDisplayFunc(Update);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeys);
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		std::cout << glewGetErrorString(err) << std::endl;

	}
	Init();
	glutMainLoop();
	return 0;         
}