#include <cmath>
#include "glew.h"
#include "glut.h"
#include "FreeImage.h"
#pragma comment(lib,"FreeImage.lib")
#include "shader.h"
#include <Windows.h>
#include <iostream>
#define pi 3.14159265358
using namespace std;

struct VertexAttribute {
	GLfloat position[3];
	GLfloat normal[3];
	GLfloat texcoord[2];
};

int windowSize[2] = { 1000, 1000 };

GLuint program;
GLuint vboName;
int trisize =388800;
bool start;
unsigned int textObj;
unsigned int texture_id_normal, texture_id_specular;
VertexAttribute *drawPlane();
void display();
void reshape(GLsizei w, GLsizei h);
void init();
void LoadTexture(char* pFilename);
void LoadTexture1(char* pFilename);
void LoadTexture2(char* pFilename);
void keyboard(unsigned char key, int x, int y);
void idle();
void idle1();
double X = 0.7;
double Y = 1;
double degreeero = 0.0;
double degreeeli = 0.0;
int button1 = 0;
int button2 = 1;
int button3 = 1;
int button4 = 1;
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowSize[0], windowSize[1]);
	glutCreateWindow("ComputerGraphicsDemo");
	glutInitWindowPosition(0, 0);
	glewInit();

	init();

	glGenTextures(1, &textObj);
	LoadTexture("earth_texture_map.jpg");

	glGenTextures(2, &texture_id_normal);
	LoadTexture1("earth_normal_map.tif");
	glGenTextures(3, &texture_id_specular);
	LoadTexture2("earth_specular_map.tif");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMainLoop();

	return 0;
}

void init() {
	GLuint vert = createShader("Shaders/example.vert", "vertex");
	GLuint geom = createShader("Shaders/example.geom", "geometry");
	GLuint frag = createShader("Shaders/example.frag", "fragment");
	program = createProgram(vert, geom, frag);

	glGenBuffers(1, &vboName);
	glBindBuffer(GL_ARRAY_BUFFER, vboName);

	VertexAttribute *vertices;
	vertices = drawPlane();
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexAttribute) * trisize, vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)(offsetof(VertexAttribute, position)));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)(offsetof(VertexAttribute, normal)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)(offsetof(VertexAttribute, texcoord)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display()
{
	// viewing and modeling transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);// up
	
	// projection transformation
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//Clear the buffer
	
	gluPerspective(45, (GLfloat)512 / (GLfloat)512, 1, 500);
	//Viewport Matrix
	glViewport(0, 0, windowSize[0], windowSize[1]);

	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_CULL_FACE);  //remove back face
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);  //normalized normal 
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	GLfloat pmtx[16];
	GLfloat mmtx[16];
	GLfloat litx[16];

	glGetFloatv(GL_PROJECTION_MATRIX, pmtx);
	GLint pmatLoc = glGetUniformLocation(program, "Projection");
	GLint mmatLoc = glGetUniformLocation(program, "ModelView");
	GLint ligtLoc = glGetUniformLocation(program, "ligthModelView");
	GLint texLoc = glGetUniformLocation(program, "TextureMap");
	GLint tex_nor_Loc = glGetUniformLocation(program, "TextureMap_nor");
	GLint tex_spe_Loc = glGetUniformLocation(program, "TextureMap_spe");
	GLint bu1Loc = glGetUniformLocation(program, "button1");
	GLint b1 = button2;
	GLint bu2Loc = glGetUniformLocation(program, "button2");
	GLint b2 = button3;
	GLint bu3Loc = glGetUniformLocation(program, "button3");
	GLint b3 = button4;

		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glUseProgram(program);


		glUniform1f(bu1Loc, b1);
		glUniform1f(bu2Loc, b2);
		glUniform1f(bu3Loc, b3);
		glRotatef(degreeero, -sin(23.5 / 180 * pi), -cos(23.5 / 180 * pi), 0.0f);
		glGetFloatv(GL_MODELVIEW_MATRIX, mmtx);
		glUniformMatrix4fv(pmatLoc, 1, GL_FALSE, pmtx);
		glUniformMatrix4fv(mmatLoc, 1, GL_FALSE, mmtx);
		glRotatef(-degreeero, -sin(23.5 / 180 * pi), -cos(23.5 / 180 * pi), 0.0f);
		glRotatef(degreeeli, 0, 1, 0.0f);
		glGetFloatv(GL_MODELVIEW_MATRIX, litx);
		glUniformMatrix4fv(ligtLoc, 1, GL_FALSE, litx);
		
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textObj);
			glUniform1i(texLoc, 0);
		
		
			glActiveTexture(GL_TEXTURE0+1);
			glBindTexture(GL_TEXTURE_2D, texture_id_normal);
			glUniform1i(tex_nor_Loc, 1);
		
		
		
			glActiveTexture(GL_TEXTURE0+2);
			glBindTexture(GL_TEXTURE_2D, texture_id_specular);
			glUniform1i(tex_spe_Loc, 2);
		

		glDrawArrays(GL_TRIANGLES, 0, trisize);
		glBindTexture(GL_TEXTURE_2D, NULL);
		glUseProgram(0);
		glPopMatrix();

	glutSwapBuffers();

}

VertexAttribute *drawPlane() {
	VertexAttribute *vertices;
	vertices = new VertexAttribute[trisize];
	int direction[4][2] = { { 0, 0 },{ 1, 0 },{ 0, 1 },{ 1, 1 } };
	int index[6] = { 0, 1, 2, 1, 3, 2 };
	int slice = 360, stack = 180, count = 0;
	float slice_step = 2 * pi / slice, stack_step = pi / stack;
	for (int i = 0; i < slice; i++) {
		for (int j = 0; j < stack; j++) {
			VertexAttribute quad_vertices[4];
			for (int k = 0; k < 4; k++) {
				quad_vertices[k].position[0] = quad_vertices[k].normal[0] = sin((j + direction[k][1]) * stack_step) * cos((i + direction[k][0])*slice_step);
				quad_vertices[k].position[1] = quad_vertices[k].normal[1] = cos((j + direction[k][1]) * stack_step);
				quad_vertices[k].position[2] = quad_vertices[k].normal[2] = sin((j + direction[k][1]) * stack_step) * sin((i + direction[k][0])*slice_step);
				quad_vertices[k].texcoord[0] = 1 - float(i + direction[k][0]) / slice;
				quad_vertices[k].texcoord[1] = 1 - float(j + direction[k][1]) / stack;
			}
			for (int k = 0; k < 6; k++) {
				vertices[count].position[0] = quad_vertices[index[k]].position[0];
				vertices[count].position[1] = quad_vertices[index[k]].position[1];
				vertices[count].position[2] = quad_vertices[index[k]].position[2];
				vertices[count].normal[0] = quad_vertices[index[k]].normal[0];
				vertices[count].normal[1] = quad_vertices[index[k]].normal[1];
				vertices[count].normal[2] = quad_vertices[index[k]].normal[2];
				vertices[count].texcoord[0] = quad_vertices[index[k]].texcoord[0];
				vertices[count].texcoord[1] = quad_vertices[index[k]].texcoord[1];
				count++;
			}
		}
	}
	return vertices;
}

void reshape(GLsizei w, GLsizei h)
{
	windowSize[0] = w;
	windowSize[1] = h;
}

void LoadTexture(char* pFilename) {
	FIBITMAP* pImage = FreeImage_Load(FreeImage_GetFileType(pFilename, 0), pFilename);
	FIBITMAP *p32BitsImage = FreeImage_ConvertTo32Bits(pImage);
	int iWidth = FreeImage_GetWidth(p32BitsImage);
	int iHeight = FreeImage_GetHeight(p32BitsImage);

	glBindTexture(GL_TEXTURE_2D, textObj);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, iWidth, iHeight,0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(p32BitsImage));
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	float fLargest;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);

	FreeImage_Unload(p32BitsImage);
	FreeImage_Unload(pImage);
}
void LoadTexture1(char* pFilename) {
	FIBITMAP* pImage = FreeImage_Load(FreeImage_GetFileType(pFilename, 0), pFilename);
	FIBITMAP *p32BitsImage = FreeImage_ConvertTo32Bits(pImage);
	int iWidth = FreeImage_GetWidth(p32BitsImage);
	int iHeight = FreeImage_GetHeight(p32BitsImage);

	glBindTexture(GL_TEXTURE_2D, texture_id_normal);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, iWidth, iHeight,
		0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(p32BitsImage));
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	float fLargest;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);

	FreeImage_Unload(p32BitsImage);
	FreeImage_Unload(pImage);
}
void LoadTexture2(char* pFilename) {
	FIBITMAP* pImage = FreeImage_Load(FreeImage_GetFileType(pFilename, 0), pFilename);
	FIBITMAP *p32BitsImage = FreeImage_ConvertTo32Bits(pImage);
	int iWidth = FreeImage_GetWidth(p32BitsImage);
	int iHeight = FreeImage_GetHeight(p32BitsImage);

	glBindTexture(GL_TEXTURE_2D, texture_id_specular);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, iWidth, iHeight,
		0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(p32BitsImage));
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	float fLargest;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);

	FreeImage_Unload(p32BitsImage);
	FreeImage_Unload(pImage);
}
void idle() {
	if (degreeero >= 360)degreeero = 0;
	degreeero = degreeero + X;
	if (degreeeli >= 360)degreeeli = 0;
	degreeeli = degreeeli + (double)(X/10);
	glutPostRedisplay();
}
void idle1() {
	degreeero = degreeero;
	degreeeli = degreeeli;
	glutPostRedisplay();
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
	if (key == '1')
	{
		if (button2 == 0)button2 = 1;
		else if (button2 == 1)button2 = 0;
	}
	if (key == '2')
	{
		if (button3 == 0)button3 = 1;
		else if (button3 == 1)button3 = 0;
	}
	if (key == '3')
	{
		if (button4 == 0)button4 = 1;
		else if (button4 == 1)button4 = 0;
	}
}