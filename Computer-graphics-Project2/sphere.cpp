#include <cmath>
#include "glew.h"
#include "glut.h"
#include "FreeImage.h"
#pragma comment(lib,"FreeImage.lib")
#include <Windows.h>
#include <iostream>
#define pi 3.14159265358
using namespace std;
void init();
void lighting();
void init_texture();
void init_texture_m();
void display();
void reshape(int _width, int _height);
void keyboard(unsigned char key, int x, int y);
void idle();
void idle1();
int width = 1000, height = 1000;
int degree = 0;
int button1 = 0;
int button2 = 0;
int swicthp = 0;
int swictho = 0;
double X = 20.0;
double Y = 1;
double year = 365.0;
double degreeero = 0.0;
double degreeere = 0.0;
double degreem = 0;
GLdouble c = pi / 180.0;
GLdouble x, y, z, theata;
GLdouble xone, yone, zone;
GLdouble ph_1;
GLdouble ph_2;
GLdouble theata_earth;
GLdouble th_earth_1, th_earth_2;
GLdouble ph_earth_1, ph_earth_2;
GLdouble th_sun_1, th_sun_2;
GLdouble ph_sun_1, ph_sun_2;
GLdouble phch;
GLdouble thch;
GLdouble theatagl;
float red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
float green[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
float blue[4] = { 0.0f, 0.4f, 1.0f, 1.0f };
float moonn[4] = { 0.3f, 0.3f, 0.3f, 1.0f };
int image_width, image_height;
//int num=10;
unsigned int texture_id;
unsigned int texture_id_m;
const char* pFilename = "earth.jpg";
const char* pFilename_m = "moon.jpg";
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("WindowName");
	glewInit();
	init();
	init_texture();
	init_texture_m();
	lighting();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}

void display()
{
	//ModelView Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0f, 5.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	//Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, width / (GLfloat)height, 0.1, 1000);
	//Viewport Matrix
	glViewport(0, 0, width, height);

	//
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_CULL_FACE);		//remove back face
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);		//normalized normal 
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


//earth
	if (button2 == 0)
	{
		double u1 = 0, v1 = 0;
		double u2 = 0, v2 = 0;
		ph_earth_1 = -180;
		ph_earth_2 = 180;
		phch = 1;
		thch = 1;
		glBindTexture(GL_TEXTURE_2D, texture_id);
		glPushMatrix();
		glRotatef(degreeero,  sin(23.5 / 180 * pi) ,  cos(23.5 / 180 * pi), 0.0f);
		for (double pheata = ph_earth_1; pheata <= ph_earth_2;pheata += phch)
		{
			ph_1 = c * pheata;
			ph_2 = c * (pheata + phch);
			glBegin(GL_QUAD_STRIP);
			for (GLdouble theta = -180; theta <= 180;theta += thch)
			{
					theata = c * theta;
					xone = sin(theata)*cos(ph_1) * 1 * Y;
					yone = sin(ph_1) * 1 * Y;
					zone = -cos(theata)*cos(ph_1) * 1 * Y;
					glNormal3d(xone, yone, zone);
					glVertex3d(xone, yone, zone);
					if (0<theta <= 45|| 90 < theta <= 135|| 0 >= theta > -45 || -90 >= theta > -135)glTexCoord2f(1-(v1+180) / 360, (u1+180) / 360);
					else if (90>=theta > 45|| 180 >= theta > 135|| -90 < theta <= -45 || -180 <= theta <= -135)glTexCoord2f((v1 + 180) / 360, (u1 + 180) / 360);
					xone = sin(theata)*cos(ph_2) * 1 * Y;
					yone = sin(ph_2) * 1 * Y;
					zone = -cos(theata)*cos(ph_2) * 1 * Y;
					glNormal3d(xone, yone, zone);
					glVertex3d(xone, yone, zone);
					if (theta <= 45 || 90 < theta <= 135 || 0 >= theta > -45 || -90 >= theta > 135)glTexCoord2f(1-(v1+180+ 1) / 360, ((u1 )+180) / 360);
					else if (90 >= theta > 45 || 180 >= theta > 135 || -90 < theta <= -45 || -180 <= theta <= -135)glTexCoord2f((v1 + 180 + 1) / 360, ((u1)+180) / 360);
				v1 += 1;
			}
			u1 += 2;
			glEnd();
		}
		glPopMatrix();
		//moon

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glPushMatrix();
		glRotatef(degreem, 0.0f, 0.0f, 1.0f);
		glTranslatef(3 * Y, 0.0, 0.0);
		glRotatef(degreem, 3*Y, 1, 0);
		glTranslatef(-3 * Y, 0.0, 0.0);
		glBindTexture(GL_TEXTURE_2D, texture_id_m);
		for (double pheata = -180; pheata <= 180;pheata += 1.5)
		{
			ph_1 = c * pheata;
			ph_2 = c * (pheata + 1.5);
			glBegin(GL_QUAD_STRIP);
			for (GLdouble theta = -180.0; theta <= 180.0;theta += 3)
			{
				theata = c * theta;
				xone = sin(theata)*cos(ph_1) * 1 / 2 * Y + 3 * Y;
				yone = sin(ph_1) * 1 / 2 * Y;
				zone = -cos(theata)*cos(ph_1) * 1 / 2 * Y;
				glNormal3d(xone  - 3*Y, yone, zone);
				glVertex3d(xone, yone, zone);
				if (0 < theta <= 45 || 90 < theta <= 135 || 0 >= theta > -45 || -90 >= theta > -135)glTexCoord2f(1 - (v2 + 180) / 360, (u2 + 180) / 360);
				else if (90 >= theta > 45 || 180 >= theta > 135 || -90 < theta <= -45 || -180 <= theta <= -135)glTexCoord2f((v2 + 180) / 360, (u2 + 180) / 360);
				xone = sin(theata)*cos(ph_2) * 1 / 2 * Y + 3 * Y;
				yone = sin(ph_2) * 1 / 2 * Y;
				zone = -cos(theata)*cos(ph_2) * 1 / 2 * Y;
				glNormal3d(xone - 3*Y, yone, zone);
				glVertex3d(xone, yone, zone);
				if (0 < theta <= 45 || 90 < theta <= 135 || 0 >= theta > -45 || -90 >= theta > -135)glTexCoord2f(1 - (v2 + 180 + 3) / 360, ((u2)+180) / 360);
				else if (90 >= theta > 45 || 180 >= theta > 135 || -90 < theta <= -45 || -180 <= theta <= -135)glTexCoord2f((v2 + 180 + 3) / 360, ((u2)+180) / 360);
				v2 += 3;
			}
			u2 += 3;
			glEnd();
		}

		glPopMatrix();

	}
	else if (button2 == 1)
	{
		double u21 = 0, v21 = 0;
		double u22 = 0, v22 = 0;
		int count = 0;;
		ph_earth_1 = -180;
		ph_earth_2 = 180;
		phch = 90;
		thch = 90;
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glPushMatrix();
		glRotatef(degreeero,  sin(23.5 / 180 * pi) , cos(23.5 / 180 * pi), 0.0f);
		glBindTexture(GL_TEXTURE_2D, texture_id);
			for (int i = 0; i < 4; i++) {
				glBegin(GL_TRIANGLE_STRIP);
				for (int j = 0; j < 2 + 1; j++) {
					xone = sin(j * pi / 2) * cos(i * 2 * pi / 4) * 1 * Y;
					yone = cos(j * pi / 2) * 1 * Y;
					zone = sin(j * pi / 2) * sin(i * 2 * pi / 4) * 1 * Y;
					glNormal3d(xone, yone, zone);
					glVertex3d(xone, yone, zone);
					if (j == 0)u22 = 1;
					else if (j == 1)u22 = 0.5;
					else if (j == 2)u22 = 0;
					if (i == 0)u21 = 0.75;
					else if (i == 1)u21 = 0.5;
					else if (i == 2)u21 = 0.25;
					else if (i == 3)u21 = 0;
					glTexCoord2f(u21, u22);

					xone = sin(j * pi / 2) * cos((i + 1) * 2 * pi / 4) * 1 * Y;
					yone = cos(j * pi / 2) * 1 * Y;
					zone = sin(j * pi / 2) * sin((i + 1) * 2 * pi / 4) * 1 * Y;
					glNormal3d(xone, yone, zone);
					glVertex3d(xone, yone, zone);
					if (j == 0)u22 = 1;
					else if (j == 1)u22 = 0.5;
					else if (j == 2)u22 = 0;
					if (i == 0)u21 = 1;
					else if (i == 1)u21 = 0.75;
					else if (i == 2)u21 = 0.5;
					else if (i == 3)u21 = 0.25;
					glTexCoord2f(u21, u22);
				}
				glEnd();
			}
			glPopMatrix();



		//moon


			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glPushMatrix();
			glRotatef(degreem, 0.0f, 0.0f, 1.0f);
			glTranslatef(3 * Y, 0.0, 0.0);
			glRotatef(degreem, 3 * Y, 1, 0);
			glTranslatef(-3 * Y, 0.0, 0.0);
			glBindTexture(GL_TEXTURE_2D, texture_id_m);
			for (double pheata = -180; pheata <= 180;pheata += 1.5)
			{
				ph_1 = c * pheata;
				ph_2 = c * (pheata + 1.5);
				glBegin(GL_QUAD_STRIP);
				for (GLdouble theta = -180.0; theta <= 180.0;theta += 3)
				{
					theata = c * theta;
					xone = sin(theata)*cos(ph_1) * 1 / 2 * Y + 3 * Y;
					yone = sin(ph_1) * 1 / 2 * Y;
					zone = -cos(theata)*cos(ph_1) * 1 / 2 * Y;
					glNormal3d(xone - 3 * Y, yone, zone);
					glVertex3d(xone, yone, zone);
					if (0 < theta <= 45 || 90 < theta <= 135 || 0 >= theta > -45 || -90 >= theta > -135)glTexCoord2f(1 - (v22 + 180) / 360, (u22 + 180) / 360);
					else if (90 >= theta > 45 || 180 >= theta > 135 || -90 < theta <= -45 || -180 <= theta <= -135)glTexCoord2f((v22 + 180) / 360, (u22 + 180) / 360);
					xone = sin(theata)*cos(ph_2) * 1 / 2 * Y + 3 * Y;
					yone = sin(ph_2) * 1 / 2 * Y;
					zone = -cos(theata)*cos(ph_2) * 1 / 2 * Y;
					glNormal3d(xone - 3 * Y, yone, zone);
					glVertex3d(xone, yone, zone);
					if (theta <= 45 || 90 < theta <= 135 || 0 >= theta > -45 || -90 >= theta > 135)glTexCoord2f(1 - (v22 + 180 + 3) / 360, ((u22)+180) / 360);
					else if (90 >= theta > 45 || 180 >= theta > 135 || -90 < theta <= -45 || -180 <= theta <= -135)glTexCoord2f((v22 + 180 + 3) / 360, ((u22)+180) / 360);
					v22 += 3;
				}
				u22 += 3;
				glEnd();
			}

		glPopMatrix();
	}

	glutSwapBuffers();
}

void reshape(int _width, int _height) {
	width = _width;
	height = _height;
}


void keyboard(unsigned char key, int x, int y)
{
	if (key == 'p')
	{
		if (button1 == 0)button1 = 1;
		else if (button1 == 1)button1 = 0;
		if (button1 == 0)
		{
			glutIdleFunc(idle);
		}
		else if (button1 == 1)
		{
			glutIdleFunc(idle1);
		}

	}
	if (key == 'o')
	{
		if (button2 == 0)button2 = 1;
		else if (button2 == 1)button2 = 0;

	}

}


void idle() {
	if (degreeere >= 360)degreeere = 0;
	if (degreeero >= 360)degreeero = 0;
	if (degreem >= 360)degreem = 0;
	degree = 1 * ((degree + 1) % 360);
	degreeere = degreeere + (double)(X / 365);
	degreeero = degreeero + X;
	degreem = degreem + (double)(X / 28);

	glutPostRedisplay();
}
void idle1() {

	degree = degree;
	degreeere = degreeere;
	degreeero = degreeero;
	degreem = degreem;

	glutPostRedisplay();
}
void lighting()
{
	// enable lighting
	glEnable(GL_LIGHTING);
	//Add directed light
	GLfloat diffuse_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat ambient_color[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat position[] = { 0.0f, 10.0f, 0.0f };
	glEnable(GL_LIGHT0);								//open light0
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_color);	//set diffuse color of light0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_color);	//set ambient color of light0
	glLightfv(GL_LIGHT0, GL_POSITION, position);		//set position of light 0

}


void init_texture()
{
	FIBITMAP * pImage = FreeImage_Load(FreeImage_GetFileType("./earth.jpg", 0), "./earth.jpg");
	FIBITMAP *p32BitsImage = FreeImage_ConvertTo32Bits(pImage);
	int image_width = FreeImage_GetWidth(p32BitsImage);
	int image_height = FreeImage_GetHeight(p32BitsImage);
	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image_width, image_height, 0, GL_BGRA, GL_UNSIGNED_BYTE,(void*)FreeImage_GetBits(p32BitsImage));


	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture(GL_TEXTURE_2D, 0);
}
void init_texture_m()
{
	FIBITMAP * pImage = FreeImage_Load(FreeImage_GetFileType("./moon.jpg", 0), "./moon.jpg");
	FIBITMAP *p32BitsImage = FreeImage_ConvertTo32Bits(pImage);
	int image_width = FreeImage_GetWidth(p32BitsImage);
	int image_height = FreeImage_GetHeight(p32BitsImage);
	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &texture_id_m);
	glBindTexture(GL_TEXTURE_2D, texture_id_m);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image_width, image_height, 0, GL_BGRA, GL_UNSIGNED_BYTE, /*data*/(void*)FreeImage_GetBits(p32BitsImage));


	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture(GL_TEXTURE_2D, 0);
}
void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
}