#include "stdafx.h"
// File:        colorcube.cpp
// Author:      Matt Daisley
// Created:     4/25/2012
// Project:     Source code for Make a Cube in OpenGL
// Description: Creates an OpenGL window and draws a 3D cube
//              That the user can rotate using the arrow keys
// 
// Controls:    Left Arrow  - Rotate Left
//              Right Arrow - Rotate Right
//              Up Arrow    - Rotate Up
//              Down Arrow  - Rotate Down     

// ----------------------------------------------------------
// Includes
// ----------------------------------------------------------
//#include <stdio.h>
//#include <stdarg.h>
#include <math.h>
//#define GL_GLEXT_PROTOTYPES

#include <GL/glut.h>


// ----------------------------------------------------------
// Function Prototypes
// ----------------------------------------------------------
void display();
void specialKeys();

// ----------------------------------------------------------
// Global Variables
// ----------------------------------------------------------
double rotate_y = 0;
double rotate_x = 0;
#define M_PI 3.14159265357

GLfloat vertices[][3] = { { -0.5, -0.5, -0.5 },{ 0.5, -0.5, -0.5 },
{ 0.5, 0.5, -0.5 },{ -0.5, 0.5, -0.5 },{ -0.5, -0.5, 0.5 },
{ 0.5, -0.5, 0.5 },{ 0.5, 0.5, 0.5 },{ -0.5, 0.5, 0.5 } };

GLfloat colors[][3] = { { 0.0, 0.0, 0.0 },{ 1.0, 0.0, 0.0 },
{ 1.0, 1.0, 0.0 },{ 0.0, 1.0, 0.0 },{ 0.0, 0.0, 1.0 },
{ 1.0, 0.0, 1.0 },{ 1.0, 1.0, 1.0 },{ 0.0, 1.0, 1.0 } };

GLubyte cubeIndices[24] = { 0, 3, 2, 1, 2, 3, 7, 6,
0, 4, 7, 3, 1, 2, 6, 5, 4, 5, 6, 7, 0, 1, 5, 4 };


// ----------------------------------------------------------
// display() Callback function
// ----------------------------------------------------------


void colorcube1()
{
	//Multi-colored side - FRONT
	glBegin(GL_POLYGON);

	glColor3f(1.0, 0.0, 0.0);     glVertex3f(0.5, -0.5, -0.5);      // P1 is red
	glColor3f(0.0, 1.0, 0.0);     glVertex3f(0.5, 0.5, -0.5);      // P2 is green
	glColor3f(0.0, 0.0, 1.0);     glVertex3f(-0.5, 0.5, -0.5);      // P3 is blue
	glColor3f(1.0, 0.0, 1.0);     glVertex3f(-0.5, -0.5, -0.5);      // P4 is purple

	glEnd();

	// White side - BACK
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	// Purple side - RIGHT
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();

	// Green side - LEFT
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	// Blue side - TOP
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	// Red side - BOTTOM
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();
}

void polygon(int a, int b, int c, int d)
{

	/* draw a polygon via list of vertices */

	glBegin(GL_POLYGON);
	glColor3fv(colors[a]);
	glVertex3fv(vertices[a]);
	glColor3fv(colors[b]);
	glVertex3fv(vertices[b]);
	glColor3fv(colors[c]);
	glVertex3fv(vertices[c]);
	glColor3fv(colors[d]);
	glVertex3fv(vertices[d]);
	glEnd();
}
void colorcube2()
{

	/* map vertices to faces */

	polygon(0, 3, 2, 1);
	polygon(2, 3, 7, 6);
	polygon(0, 4, 7, 3);
	polygon(1, 2, 6, 5);
	polygon(4, 5, 6, 7);
	polygon(0, 1, 5, 4);

}

void colorcube3()
{
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);



	for (int i = 0; i<6; i++)
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &cubeIndices[4 * i]);


	//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);
}

void sphere()
{
	int rings = 10;
	int sectors = 10;
	float const R = 1. / (float)(rings - 1);
	float const S = 1. / (float)(sectors - 1);
	float radius = 0.5;
	float v[100][3];
	int s, r, t = 0;

	for (r = 0; r < rings; r++) {
		for (s = 0; s < sectors; s++) {
			float const z = cos(2 * M_PI * s * S);
			float const x = sin(2 * M_PI * s * S);
			float const y = r/4;

			//float const y = sin(-M_PI / 2 + M_PI * r * R);
			//float const x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
			//float const z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);

			v[t][0] = x * radius;
			v[t][1] = y * radius;
			v[t][2] = z * radius;

			t++;

		}
	}
	

	t = 0;
	int index[400];

	for (r = 0; r < rings - 1; r++) {
		for (s = 0; s < sectors; s++) {
			index[4 * t + 0] = r * sectors + s;
			index[4 * t + 1] = r * sectors + (s + 1);
			index[4 * t + 2] = (r + 1) * sectors + (s + 1);
			index[4 * t + 3] = (r + 1) * sectors + s;
			t++;
		}
	}

	for (int i = 0; i < 89; i++)
	{
		glBegin(GL_LINE_LOOP);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3fv(v[index[4 * i + 0]]);
		glVertex3fv(v[index[4 * i + 1]]);
		glVertex3fv(v[index[4 * i + 2]]);
		glVertex3fv(v[index[4 * i + 3]]);
		glEnd();
	}

	for (int i = 0; i < 9; i++) {
		glBegin(GL_LINE_LOOP);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3fv(v[index[4 * i + 0]]);
		glVertex3fv(v[index[4 * i + 1]]);
		glEnd();
	}

	for (int i = 80; i < 89; i++) {
		glBegin(GL_LINE_LOOP);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
		glVertex3fv(v[index[4 * i + 0]]);
		glVertex3fv(v[index[4 * i + 1]]);
		glEnd();
	}

	/*glBegin(GL_TRIANGLE_STRIP);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, -1.0, 0.0);
	glVertex3fv(v[index[4 * 0 + 0]]);
	glVertex3fv(v[index[4 * 0 + 1]]);
	glVertex3fv(v[index[4 * 0 + 2]]);
	glVertex3fv(v[index[4 * 0 + 3]]);
	glEnd();*/






}
void display() {

	//  Clear screen and Z-buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Other Transformations
	// glTranslatef( 0.1, 0.0, 0.0 );      // Not included
	// glRotatef( 180, 0.0, 1.0, 0.0 );    // Not included

	// Rotate when user changes rotate_x and rotate_y
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);

	// Other Transformations
	// glScalef( 2.0, 2.0, 0.0 );          // Not included

	sphere();

	glFlush();
	glutSwapBuffers();

}
// ----------------------------------------------------------
// specialKeys() Callback Function
// ----------------------------------------------------------
void specialKeys(int key, int x, int y) {

	//  Right arrow - increase rotation by 5 degree
	if (key == GLUT_KEY_RIGHT)
		rotate_y += 5;

	//  Left arrow - decrease rotation by 5 degree
	else if (key == GLUT_KEY_LEFT)
		rotate_y -= 5;

	else if (key == GLUT_KEY_UP)
		rotate_x += 5;

	else if (key == GLUT_KEY_DOWN)
		rotate_x -= 5;

	//  Request display update
	glutPostRedisplay();

}

// ----------------------------------------------------------
// main() function
// ----------------------------------------------------------
int main(int argc, char* argv[]) {

	//  Initialize GLUT and process user parameters
	glutInit(&argc, argv);

	//  Request double buffered true color window with Z-buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Create window
	glutCreateWindow("Color Cube");

	//  Enable Z-buffer depth test
	glEnable(GL_DEPTH_TEST);

	// Callback functions
	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);

	//  Pass control to GLUT for events
	glutMainLoop();

	//  Return to OS
	return 0;

}
