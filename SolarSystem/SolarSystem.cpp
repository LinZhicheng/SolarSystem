// SolarSystem.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdlib.h"
#include "GL/glut.h"
#include "GL/glaux.h"
#include "windows.h"

int w = 1024, h = 576;
int year = 0, month = 0, day = 0;

void init(GLvoid)     // Create Some Everyday Functions
{

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glEnable(GL_COLOR_MATERIAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void display(void)   // Create The Display Function
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	glTranslatef(0.0f, 0.0f, -6.0f);					// Move Left 1.5 Units And Into The Screen 6.0
	gluLookAt(0, -1, 0, 0, 0, 0, 0, 0, -1);
	glColor3f(0.8f, 0.0f, 0.0f);
	glutSolidSphere(1, 32, 32);
	
	year = year % 360;
	month = month % 360;
	day = day % 360;
	
	glRotatef((GLfloat)year, 0, 1, 0);
	glTranslatef(3.0f, 0, 0);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidSphere(0.2, 32, 32);
	
	glRotatef((GLfloat)month, 0, 1, 0);
	glTranslatef(0.5f, 0, 0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidSphere(0.05, 32, 32);
	
	glTranslatef(-0.5f, 0, 0);
	glTranslatef(-3.0f, 0, 0);
	
	year += 1;
	month += 12;
	glutPostRedisplay();
	
	Sleep(25);

	glutSwapBuffers();
	// Swap The Buffers To Not Be Left With A Clear Screen
}

void reshape(int w, int h)   // Create The Reshape Function (the viewport)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);  // Select The Projection Matrix
	glLoadIdentity();                // Reset The Projection Matrix
	gluPerspective(60, (GLdouble)w/(GLdouble)h, 1.0, 5000.0);
	glMatrixMode(GL_MODELVIEW);  // Select The Model View Matrix
	glLoadIdentity();    // Reset The Model View Matrix
}

void keyboard(unsigned char key, int x, int y)  // Create Keyboard Function
{
	switch (key) {
	case 27:        // When Escape Is Pressed...
		exit(0);   // Exit The Program
		break;        // Ready For Next Case
	default:        // Now Wrap It Up
		break;
	}
}

void arrow_keys(int a_keys, int x, int y)  // Create Special Function (required for arrow keys)
{
	switch (a_keys) {
	case GLUT_KEY_UP:     // When Up Arrow Is Pressed...
		glutFullScreen(); // Go Into Full Screen Mode
		break;
	case GLUT_KEY_DOWN:               // When Down Arrow Is Pressed...
		glutReshapeWindow(640, 480); // Go Into A 500 By 500 Window
		break;
	default:
		break;
	}
}

void main(int argc, char** argv)   // Create Main Function For Bringing It All Together
{
	glutInit(&argc, argv); // Erm Just Write It =)
	init();
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // Display Mode
	glutInitWindowSize(w, h); // If glutFullScreen wasn't called this is the window size
	glutCreateWindow("Solar System"); // Window Title (argv[0] for current directory as title)
	glutDisplayFunc(display);  // Matching Earlier Functions To Their Counterparts
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrow_keys);
	glutMainLoop();          // Initialize The Main Loop
}

