/*
NeHe (nehe.gamedev.net) OpenGL tutorial series
GLUT port.in 2001 by milix (milix_gr@hotmail.com)
Most comments are from the original tutorials found in NeHe.
For VC++ users, create a Win32 Console project and link
the program with glut32.lib, glu32.lib, opengl32.lib
*/

#include <windows.h>   // Standard Header For MSWindows Applications
#include <gl/glut.h>   // The GL Utility Toolkit (GLUT) Header
#include <GL/GLAux.h>

// The Following Directive Fixes The Problem With Extra Console Window
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

// Global Variables
bool g_gamemode;       // GLUT GameMode ON/OFF
bool g_fullscreen;     // Fullscreen Mode ON/OFF (When g_gamemode Is OFF)

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
	if (TextureImage[0] = LoadBMP(L"sun256128.bmp"))
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

	if (TextureImage[0] = LoadBMP(L"earth_clouds256128.bmp"))
	{
		Status += 1;

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

	if (TextureImage[0] = LoadBMP(L"moon256128.bmp"))
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

// Our GL Specific Initializations
bool init(void)
{
	int num = LoadGLTextures();
	if (num != 3)
		return false;
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glEnable(GL_COLOR_MATERIAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


	g_quadratic = gluNewQuadric();
	if (g_quadratic == 0) return false;
	gluQuadricNormals(g_quadratic, GLU_SMOOTH);        // Create Smooth Normals (NEW)
	gluQuadricTexture(g_quadratic, GL_TRUE);           // Create Texture Coords (NEW)
	return true;
}

// Our Rendering Is Done Here
void render(void)
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

	// Swap The Buffers To Become Our Rendering Visible
	glutSwapBuffers();
}

// Our Reshaping Handler (Required Even In Fullscreen-Only Modes)
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);     // Select The Projection Matrix
	glLoadIdentity();                // Reset The Projection Matrix
									 // Calculate The Aspect Ratio And Set The Clipping Volume
	if (h == 0) h = 1;
	gluPerspective(80, (float)w / (float)h, 1.0, 5000.0);
	glMatrixMode(GL_MODELVIEW);      // Select The Modelview Matrix
	glLoadIdentity();                // Reset The Modelview Matrix
}

// Our Keyboard Handler (Normal Keys)
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:        // When Escape Is Pressed...
		exit(0);    // Exit The Program
		break;          // Ready For Next Case
	default:        // Now Wrap It Up
		break;
	}
}

// Our Keyboard Handler For Special Keys (Like Arrow Keys And Function Keys)
void special_keys(int a_keys, int x, int y)
{
	switch (a_keys) {
	case GLUT_KEY_F1:
		// We Can Switch Between Windowed Mode And Fullscreen Mode Only
		if (!g_gamemode) {
			g_fullscreen = !g_fullscreen;       // Toggle g_fullscreen Flag
			if (g_fullscreen) glutFullScreen(); // We Went In Fullscreen Mode
			else glutReshapeWindow(w, h);   // We Went In Windowed Mode
		}
		break;
	default:
		break;
	}
}

// Ask The User If He Wish To Enter GameMode Or Not
void ask_gamemode()
{
	int answer;
	// Use Windows MessageBox To Ask The User For Game Or Windowed Mode
	answer = MessageBox(NULL, L"Do you want to enter game mode?", L"Question",
		MB_ICONQUESTION | MB_YESNO);
	g_gamemode = (answer == IDYES);
	// If Not Game Mode Selected, Use Windowed Mode (User Can Change That With F1)
	g_fullscreen = false;
}

// Main Function For Bringing It All Together.
int main(int argc, char** argv)
{
	ask_gamemode();                                  // Ask For Fullscreen Mode
	glutInit(&argc, argv);                           // GLUT Initializtion
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);     // Display Mode (Rgb And Double Buffered)
	if (g_gamemode) {
		glutGameModeString("640x480:16");            // Select The 640x480 In 16bpp Mode
		if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE))
			glutEnterGameMode();                     // Enter Full Screen
		else g_gamemode = false;                     // Cannot Enter Game Mode, Switch To Windowed
	}
	if (!g_gamemode) {
		glutInitWindowSize(w, h);                // Window Size If We Start In Windowed Mode
		glutCreateWindow("SolarSystem"); // Window Title 
	}
	init();                                          // Our Initialization
	glutDisplayFunc(render);                         // Register The Display Function
	glutReshapeFunc(reshape);                        // Register The Reshape Handler
	glutKeyboardFunc(keyboard);                      // Register The Keyboard Handler
	glutSpecialFunc(special_keys);                   // Register Special Keys Handler
	glutMainLoop();                                  // Go To GLUT Main Loop
	return 0;
}
