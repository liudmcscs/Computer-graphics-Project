
#include "glut.h"
#include <iostream>
#define pi 3.14159
using namespace std;
void lighting();
void display();
void reshape(int _width, int _height);
void keyboard(unsigned char key, int x, int y);
void idle();
void idle1();
int width = 1000, height = 1000;
int degree =0;
int button1=0;
int button2 = 0;
int swicthp = 0;
int swictho = 0;
double X = 100.0;
double Y = 1.0;
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
GLdouble th_earth_1 , th_earth_2;
GLdouble ph_earth_1 , ph_earth_2;
GLdouble th_sun_1, th_sun_2;
GLdouble ph_sun_1, ph_sun_2;
GLdouble phch;
GLdouble thch;
GLdouble theatagl;
float red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
float green[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
float blue[4] = { 0.0f, 0.4f, 1.0f, 1.0f };
float moonn[4] = { 0.3f, 0.3f, 0.3f, 1.0f };


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("WindowName");
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
	gluLookAt(0.0f, 50.0f, 50.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
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

	//sun
	glPushMatrix();
	ph_sun_1 = -178.5;//240
	ph_sun_2 = 178.5;
	phch = 1.5;
	thch = 3;//60
	for (double pheata = ph_sun_1; pheata <= ph_sun_2;pheata += phch)
	{
		ph_1 = c * pheata;
		ph_2 = c * (pheata + phch);
		glBegin(GL_QUAD_STRIP);
		for (GLdouble theta = -180.0; theta <= 180.0;theta += thch)
		{
			theata = c * theta;
			x = sin(theata)*cos(ph_1)*6*Y;
			y = cos(theata)*cos(ph_1) * 6 * Y;
			z = sin(ph_1) * 6 * Y;
			glNormal3d(x, y, z);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
			glVertex3d(x, y, z);
			x = sin(theata)*cos(ph_2) * 6 * Y;
			y = cos(theata)*cos(ph_2) * 6 * Y;
			z = sin(ph_2) * 6 * Y;
			glNormal3d(x, y, z);	
			glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
			glVertex3d(x, y, z);
		}
		glEnd();
	}
	glBegin(GL_TRIANGLE_FAN);
	glNormal3d(x, y, z);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
	glVertex3d(0.0, 0.0, 6*Y);
	theatagl = c * ph_sun_2;
	z = sin(theatagl);

	for (GLdouble theta = -180.0; theta <= 180;theta += thch)
	{
		theata = c * theta;
		x = sin(theata)*cos(theatagl) * 6 * Y;
		y = cos(theata)*cos(theatagl) * 6 * Y;
		glNormal3d(x, y, z);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
		glVertex3d(x, y, z);
	}
	glEnd();
	//south
	glBegin(GL_TRIANGLE_FAN);
	glNormal3d(x, y, z);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
	glVertex3d(0.0, 0.0, -6*Y);
	z = -sin(theatagl);
	for (GLdouble theta = -180.0; theta <= 180.0;theta += thch)
	{
		theata = c * theta;
		x = sin(theata)*cos(theatagl) * 6 * Y;
		y = cos(theata)*cos(theatagl) * 6 * Y;
		glNormal3d(x, y, z);		
		glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
		glVertex3d(x, y, z);
	}
	glEnd();
	glPopMatrix();



	//spin axis
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glRotatef(degreeere, 0.0f, 1.0f, 0.0f);
	glLineWidth(5);
	glBegin(GL_LINES);
	glColor3f(0,0,3);
	glVertex3d( 20+2*Y* sin(23.5 / 180 * pi)*1, 1*2*Y*cos(23.5 / 180 * pi), 0);
	glVertex3d( 20-2*Y* sin(23.5 / 180 * pi)*1, 1*-2*Y*cos(23.5 / 180 * pi), 0);
	glEnd();
	glPopMatrix();



	//earth
	if (button2 == 0)
	{
		ph_earth_1 = -179;
		ph_earth_2 = 179;
		phch = 1;
		thch = 1;
		glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0);
		glRotatef(degreeere, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0, 0.0, 0.0);
		glTranslatef(20.0, 0.0, 0.0);
		glRotatef(degreeero, 4 * Y* sin(23.5 / 180 * pi) * 100, 100 * 4 * Y*cos(23.5 / 180 * pi), 0.0f);
		glTranslatef(-20.0, 0.0, 0.0);

		for (double pheata = ph_earth_1; pheata <= ph_earth_2;pheata += phch)
		{
			ph_1 = c * pheata;
			ph_2 = c * (pheata + phch);
			glBegin(GL_QUAD_STRIP);
			for (GLdouble theta = -180.0; theta <= 180.0;theta += thch)
			{
				theata = c * theta;
				xone = sin(theata)*cos(ph_1) * 2 * Y + 20;
				yone = cos(theata)*cos(ph_1) * 2 * Y;
				zone = sin(ph_1) * 2 * Y;
				glNormal3d(xone - 20, yone, zone);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
				glVertex3d(xone, yone, zone);
				xone = sin(theata)*cos(ph_2) * 2 * Y + 20;
				yone = cos(theata)*cos(ph_2) * 2 * Y;
				zone = sin(ph_2) * 2 * Y;
				glNormal3d(xone - 20, yone, zone);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
				glVertex3d(xone, yone, zone);
			}
			glEnd();
		}
		//north
		glBegin(GL_TRIANGLE_FAN);
		glNormal3d(20, 0, 0);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
		glVertex3d(20, 0.0, 2*Y);
		zone = sin(theatagl);
		for (GLdouble theta = -180.0; theta <= 180;theta +=thch)
		{
			theata = c * theta;
			xone = sin(theata)*cos(theatagl) * 2 * Y + 20;
			yone = cos(theata)*cos(theatagl) * 2 * Y;
			glNormal3d(xone-20 , yone, zone);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
			glVertex3d(xone, yone, zone);
		}
		glEnd();
		//south
		glBegin(GL_TRIANGLE_FAN);
		glNormal3d(20, 0, 0);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
		glVertex3d(20, 0.0, -2*Y);
		zone = -sin(theatagl);
		for (GLdouble theta = -180.0; theta <= 180.0;theta += thch)
		{
			theata = c * theta;
			xone = sin(theata)*cos(theatagl) * 2 * Y + 20;
			yone = cos(theata)*cos(theatagl) * 2 * Y;
			glNormal3d(xone - 20, yone, zone);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
			glVertex3d(xone, yone, zone);
		}
		glEnd();


	
		//moon

		glTranslatef(20.0, 0.0, 0.0);
		glRotatef(degreem,20,1,0);
		glTranslatef(-20.0, 0.0, 0.0);


		for (double pheata = -178.5; pheata <= 178.5;pheata += 1.5)
		{
			ph_1 = c * pheata;
			ph_2 = c * (pheata + 1.5);
			glBegin(GL_QUAD_STRIP);
			for (GLdouble theta = -180.0; theta <= 180.0;theta += 3)
			{
				theata = c * theta;
				xone = sin(theata)*cos(ph_1) * 1 * Y + 20+3;
				yone = cos(theata)*cos(ph_1) * 1 * Y;
				zone = sin(ph_1) * 1 * Y;
				glNormal3d(xone-20-3, yone, zone);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, moonn);
				glVertex3d(xone, yone, zone);
				xone = sin(theata)*cos(ph_2) * 1 * Y + 20+3;
				yone = cos(theata)*cos(ph_2) * 1 * Y;
				zone = sin(ph_2) * 1 * Y;
				glNormal3d(xone - 20 - 3, yone, zone);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, moonn);
				glVertex3d(xone, yone, zone);
			}
			glEnd();
		}
		//north
		glBegin(GL_TRIANGLE_FAN);
		glNormal3d(20+3, 0, 0);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, moonn);
		glVertex3d(20+3, 0.0, 1 * Y);
		zone = sin(theatagl);
		for (GLdouble theta = -180; theta <= 180;theta += 3)
		{
			theata = c * theta;
			xone = sin(theata)*cos(theatagl) * 1 * Y + 20+3;
			yone = cos(theata)*cos(theatagl) * 1 * Y;
			glNormal3d(xone - 20 - 3, yone, zone);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, moonn);
			glVertex3d(xone, yone, zone);
		}
		glEnd();
		//south
		glBegin(GL_TRIANGLE_FAN);
		glNormal3d(20+3, 0, 0);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, moonn);
		glVertex3d(20+3, 0.0, -1 * Y);
		zone = -sin(theatagl);
		for (GLdouble theta = -180; theta <= 180;theta += 3)
		{
			theata = c * theta;
			xone = sin(theata)*cos(theatagl) * 1 * Y + 20+3;
			yone = cos(theata)*cos(theatagl) * 1 * Y;
			glNormal3d(xone - 20 - 3, yone, zone);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, moonn);
			glVertex3d(xone, yone, zone);
		}
		glEnd();
		glPopMatrix();
	}
	else if (button2 == 1)
	{
		ph_earth_1 = -90;
		ph_earth_2 = 90;
		phch = 90;
		thch = 90;

		glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0);
		glRotatef(degreeere, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0, 0.0, 0.0);
		glTranslatef(20.0, 0.0, 0.0);
		glRotatef(degreeero, 4 * Y* sin(23.5 / 180 * pi) * 100, 100 * 4 * Y*cos(23.5 / 180 * pi), 0.0f);
		glTranslatef(-20.0, 0.0, 0.0);

		for (double pheata = ph_earth_1; pheata <= ph_earth_2;pheata += phch)
		{
			ph_1 = c * pheata;
			ph_2 = c * (pheata + phch);
			glBegin(GL_QUAD_STRIP);
			for (GLdouble theta = -180.0; theta <= 180.0;theta += thch)
			{
				theata = c * theta;
				xone = sin(theata)*cos(ph_1) * 2 * Y + 20;
				yone = cos(theata)*cos(ph_1) * 2 * Y;
				zone = sin(ph_1) * 2 * Y;
				glNormal3d(xone - 20, yone, zone);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
				glVertex3d(xone, yone, zone);
				xone = sin(theata)*cos(ph_2) * 2 * Y + 20;
				yone = cos(theata)*cos(ph_2) * 2 * Y;
				zone = sin(ph_2) * 2 * Y;
				glNormal3d(xone - 20, yone, zone);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
				glVertex3d(xone, yone, zone);
			}
			glEnd();
		}
		//north
		glBegin(GL_TRIANGLE_FAN);
		glNormal3d(20, 0, 0);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
		glVertex3d(20, 0.0, 2 * Y);
		zone = sin(theatagl);
		for (GLdouble theta = -180.0; theta <= 180;theta += thch)
		{
			theata = c * theta;
			xone = sin(theata)*cos(theatagl) * 2 * Y + 20;
			yone = cos(theata)*cos(theatagl) * 2 * Y;
			glNormal3d(xone - 20, yone, zone);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
			glVertex3d(xone, yone, zone);
		}
		glEnd();
		//south
		glBegin(GL_TRIANGLE_FAN);
		glNormal3d(20, 0, 0);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
		glVertex3d(20, 0.0, -2 * Y);
		zone = -sin(theatagl);
		for (GLdouble theta = -180.0; theta <= 180.0;theta += thch)
		{
			theata = c * theta;
			xone = sin(theata)*cos(theatagl) * 2 * Y + 20;
			yone = cos(theata)*cos(theatagl) * 2 * Y;
			glNormal3d(xone - 20, yone, zone);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
			glVertex3d(xone, yone, zone);
		}
		glEnd();




		//moon
		glTranslatef(20.0, 0.0, 0.0);
		glRotatef(degreem, 20, 1, 0);
		glTranslatef(-20.0, 0.0, 0.0);


		for (double pheata = -178.5; pheata <= 178.5;pheata += 1.5)
		{
			ph_1 = c * pheata;
			ph_2 = c * (pheata + 1.5);
			glBegin(GL_QUAD_STRIP);
			for (GLdouble theta = -180.0; theta <= 180.0;theta += 3)
			{
				theata = c * theta;
				xone = sin(theata)*cos(ph_1) * 1 * Y + 20 + 3;
				yone = cos(theata)*cos(ph_1) * 1 * Y;
				zone = sin(ph_1) * 1 * Y;
				glNormal3d(xone - 20 - 3, yone, zone);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, moonn);
				glVertex3d(xone, yone, zone);
				xone = sin(theata)*cos(ph_2) * 1 * Y + 20 + 3;
				yone = cos(theata)*cos(ph_2) * 1 * Y;
				zone = sin(ph_2) * 1 * Y;
				glNormal3d(xone - 20 - 3, yone, zone);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, moonn);
				glVertex3d(xone, yone, zone);
			}
			glEnd();
		}
		//north
		glBegin(GL_TRIANGLE_FAN);
		glNormal3d(20 + 3, 0, 0);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, moonn);
		glVertex3d(20 + 3, 0.0, 1 * Y);
		zone = sin(theatagl);
		for (GLdouble theta = -178.5; theta <= 178.5;theta += 1.5)
		{
			theata = c * theta;
			xone = sin(theata)*cos(theatagl) * 1 * Y + 20 + 3;
			yone = cos(theata)*cos(theatagl) * 1 * Y;
			glNormal3d(xone - 20 - 3, yone, zone);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, moonn);
			glVertex3d(xone, yone, zone);
		}
		glEnd();
		//south
		glBegin(GL_TRIANGLE_FAN);
		glNormal3d(20 + 3, 0, 0);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, moonn);
		glVertex3d(20 + 3, 0.0, -1 * Y);
		zone = -sin(theatagl);
		for (GLdouble theta = -178.5; theta <= 178.5;theta += 1.5)
		{
			theata = c * theta;
			xone = sin(theata)*cos(theatagl) * 1 * Y + 20 + 3;
			yone = cos(theata)*cos(theatagl) * 1 * Y;
			glNormal3d(xone - 20 - 3, yone, zone);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, moonn);
			glVertex3d(xone, yone, zone);
		}
		glEnd();
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
	degree =1* ((degree +1) % 360);
	degreeere = degreeere +(double)(X/365);
	degreeero = degreeero + X;
	degreem = degreem + (double)(X / 28);

	glutPostRedisplay();
}
void idle1() {

	degree = degree;
	degreeere = degreeere;
	degreeero = degreeero ;
	degreem = degreem ;

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
