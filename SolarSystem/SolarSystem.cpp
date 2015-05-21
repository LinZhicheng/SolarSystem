// SolarSystem.cpp : 定义控制台应用程序的入口点。
//

#include "windows.h"
#include "GL/glut.h"
#include "GL/GLAux.h"

int w = 1024, h = 576;
int year = 0, month = 0, day = 0;
GLuint texture[3];
GLUquadricObj *g_quadratic;

// Load A BMP
AUX_RGBImageRec *LoadBMP(LPCWSTR Filename)				// Loads A Bitmap Image
{
	if (!Filename)										// Make Sure A Filename Was Given
	{
		return NULL;									// If Not Return NULL
	}

	return auxDIBImageLoad(Filename);				// Load The Bitmap And Return A Pointer

}

int LoadGLTextures()									// Load Bitmaps And Convert To Textures
{
	int Status = 0;									// Status Indicator

	AUX_RGBImageRec *TextureImage[1];					// Create Storage Space For The Texture

	memset(TextureImage, 0, sizeof(void *) * 1);           	// Set The Pointer To NULL

	// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
	if (TextureImage[0] = LoadBMP(L"资源文件/sun256128.bmp"))
	{
		Status += 1;

		glGenTextures(1, &texture[0]);					// Create The Texture

		glBindTexture(GL_TEXTURE_2D, texture[0]);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
	}

	if (TextureImage[0])									// If Texture Exists
	{
		if (TextureImage[0]->data)							// If Texture Image Exists
		{
			free(TextureImage[0]->data);					// Free The Texture Image Memory
		}

		free(TextureImage[0]);								// Free The Image Structure
	}

	memset(TextureImage, 0, sizeof(void *) * 1);           	// Set The Pointer To NULL

	if (TextureImage[0] = LoadBMP(L"资源文件/earth_clouds256128.bmp"))
	{
		Status +=1;									

		glGenTextures(1, &texture[1]);					// Create The Texture

		glBindTexture(GL_TEXTURE_2D, texture[1]);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
	}

	if (TextureImage[0])									// If Texture Exists
	{
		if (TextureImage[0]->data)							// If Texture Image Exists
		{
			free(TextureImage[0]->data);					// Free The Texture Image Memory
		}

		free(TextureImage[0]);								// Free The Image Structure
	}

	memset(TextureImage, 0, sizeof(void *) * 1);           	// Set The Pointer To NULL

	if (TextureImage[0] = LoadBMP(L"资源文件/moon256128.bmp"))
	{
		Status += 1;

		glGenTextures(1, &texture[2]);					// Create The Texture

		glBindTexture(GL_TEXTURE_2D, texture[2]);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
	}

	if (TextureImage[0])									// If Texture Exists
	{
		if (TextureImage[0]->data)							// If Texture Image Exists
		{
			free(TextureImage[0]->data);					// Free The Texture Image Memory
		}

		free(TextureImage[0]);								// Free The Image Structure
	}

	return Status;
}

void init(GLvoid)     // Create Some Everyday Functions
{
	int num = LoadGLTextures();
	if (num != 3)
		return;
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glEnable(GL_COLOR_MATERIAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


	g_quadratic = gluNewQuadric();
	if (g_quadratic == 0) return;
	gluQuadricNormals(g_quadratic, GLU_SMOOTH);        // Create Smooth Normals (NEW)
	gluQuadricTexture(g_quadratic, GL_TRUE);           // Create Texture Coords (NEW)
}

void display(void)   // Create The Display Function
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	glTranslatef(0.0f, 0.0f, -6.0f);					// Move Left 1.5 Units And Into The Screen 6.0
	//gluLookAt(0, -1, 0, 0, 0, 0, 0, 0, -1);
	glColor3f(0.8f, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	gluSphere(g_quadratic, 1, 32, 32);

	year = year % 360;
	month = month % 360;
	day = day % 360;

	glRotatef((GLfloat)year, 0, 1, 0);
	glTranslatef(3.0f, 0, 0);
	glColor3f(0.0f, 0.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	gluSphere(g_quadratic, 0.2, 32, 32);

	glRotatef((GLfloat)month, 0, 1, 0);
	glTranslatef(0.5f, 0, 0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	gluSphere(g_quadratic, 0.05, 32, 32);

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
	gluPerspective(60, (GLdouble)w / (GLdouble)h, 1.0, 5000.0);
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
		glutReshapeWindow(w, h); // Go Into A 500 By 500 Window
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

