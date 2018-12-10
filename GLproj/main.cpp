


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
GLuint VAO,vertexbuffer, indexbuffer, texturecoordbuffer, normalbuffer;
GLushort * indeces;
GLfloat * vertexes;
GLuint texture;
GLfloat xangle = 0, yangle = 0;
GLfloat langle = 0;
GLfloat langle2 = 0;
GLfloat mx = 0, my = 0 , mz = 0;
void Init(void)
{
	glClearColor(0, 0, 0, 1.0f);

	glEnable(GL_COLOR_MATERIAL);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_LIGHTING);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT1);
	texture= SOIL_load_OGL_texture("cat_diff.tga", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_INVERT_Y);
	bool succes = obj_loader.LoadFile("cat.obj");
	if (succes) {
		size_t sz = obj_loader.LoadedVertices.size() * 11;
		size_t sz_indces = obj_loader.LoadedIndices.size();
		vertexes = new GLfloat[sz];
		indeces = new GLushort[sz_indces];
		int ind = 0;
		for (size_t i = 0; i < sz; i+=11)
		{
			vertexes[i] = obj_loader.LoadedVertices[ind].Position.X;
			vertexes[i+1] = obj_loader.LoadedVertices[ind].Position.Y;
			vertexes[i+2] = obj_loader.LoadedVertices[ind].Position.Z;
			vertexes[i+3] = obj_loader.LoadedVertices[ind].Normal.X;
			vertexes[i+4] = obj_loader.LoadedVertices[ind].Normal.Y;
			vertexes[i+5] = obj_loader.LoadedVertices[ind].Normal.Z;
			vertexes[i + 6] = (double)rand() / RAND_MAX;
			vertexes[i + 7] = (double)rand() / RAND_MAX;
			vertexes[i + 8] = (double)rand() / RAND_MAX;
			vertexes[i + 9] = obj_loader.LoadedVertices[ind].TextureCoordinate.X;
			vertexes[i + 10] = obj_loader.LoadedVertices[ind].TextureCoordinate.Y;


			ind++;
		}
		for (size_t i = 0; i < sz_indces; i++)
		{
			indeces[i] = obj_loader.LoadedIndices[i];
		}

		glVertexPointer(3, GL_FLOAT, sizeof(GLfloat) * 11, vertexes);
		glNormalPointer(GL_FLOAT, sizeof(GLfloat) * 11, vertexes + 3);
		glColorPointer(3, GL_FLOAT, sizeof(GLfloat) * 11, vertexes + 6);
		glTexCoordPointer(2, GL_FLOAT, sizeof(GLfloat) * 11, vertexes + 9);
		
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
	gluPerspective(90, (GLdouble)w / h, 0.05, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-3, 0, 0, 0, 0, 0, 0, 0, 1);

}



void Update(void) {
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	


	glPushMatrix();
	glTranslatef(mx, my, mz);
	glRotatef(xangle, 0, 0, 1);
	glRotatef(yangle, 1, 0, 0);
	
	glEnableClientState(GL_NORMAL_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//glColor3f(0, 0, 1);
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_TEXTURE_2D);
	glDrawElements(GL_TRIANGLES,obj_loader.LoadedVertices.size(), GL_UNSIGNED_SHORT, indeces);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	auto er = glGetError();
	glPopMatrix();


	glPushMatrix();

	glRotatef(langle, 0, 0, 1);
	glRotatef(langle2, 1, 0, 0);
	GLfloat light_diffuse[4]{ 1,1,1,1 };
	GLfloat light_ambient[4]{ 0.1f,0.1f,0.1f,1 };
	GLfloat light_position[4]{ 0,10,10,1 };
	GLfloat light_spot_direction[3];



	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_diffuse);
	//glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 50);
	//glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 5);
	//glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_spot_direction);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 3);

	glTranslatef(0, 1, 1);
	//glPushAttrib(GL_LIGHTING_BIT);
	//glMaterialfv(GL_FRONT, GL_EMISSION, light_diffuse);
	//glutSolidSphere(0.1, 10, 10);

	//glPopAttrib();
	glPopMatrix();



	glFlush();
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)	
{
	float translate_dif = 0.1;
	float ang_dif = 5;
	switch (key)
	{
	case 'a':	// A
		xangle +=ang_dif;
		break;
	case 'd':	// D
		xangle -= ang_dif;
		break;
	case 'w':	// W
		yangle += ang_dif;
		break;
	case 's':	// S	
		yangle -= ang_dif;
		break;
	case 'r': 
		mx += translate_dif;
		break;
	case 'f':
		mx -= translate_dif;
		break;
	case 't':
		my += translate_dif;
		break;
	case 'g':
		my -= translate_dif;
		break;
	case 'y':
		mz += translate_dif;
		break;
	case 'h':
		mz -= translate_dif;
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
		langle += 5;
		break;

	case GLUT_KEY_DOWN:
		langle -= 5;
		break;

	case GLUT_KEY_LEFT:
		langle2 += 5;
		break;

	case GLUT_KEY_RIGHT:
		langle2 -= 5;
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