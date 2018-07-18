/* p5-RotateTeaPot.c
* Rotate the teapot by using glutMousFunc() and glutMotionFunc().
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>

unsigned char	mouseFlag = GL_FALSE;		// flag for moving or not
int				xStart, yStart;				// start position when drug begins
double			xAngle = 0.0, yAngle = 0.0;	// angles of the teapot
int anime = 0;
double dist = 0.0;
double	sizeOfTeapot = 1.0;

#define	imageWidth 256
#define	imageHeight 256

float mtrl_diffuse[] = { 0.6, 0.6, 0.6, 0.0 };
float mtrl_specular[] = { 1.0, 0.1, 0.3, 0.0 };
float mtrl_shininess[] = { 128.0 };

float	light_pos[] = { 5, 0, 0, 1 };

double	theta = 0.0;
unsigned char texImage[imageHeight][imageWidth][3];


void readPPMImage(char* filename)
{
	FILE *fp;
	int  ch;

	if ((fp = fopen(filename, "r")) == NULL) {
		fprintf(stderr, "Cannot open ppm file %s\n", filename);
		exit(1);
	}
	fread(texImage, 1, imageWidth*imageHeight * 3, fp);	// read RGB data
	fclose(fp);
}

void setUpTexture(void)
{
	readPPMImage("wood.ppm");
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight,0, GL_RGB, GL_UNSIGNED_BYTE, texImage);
}


void myKeyboard(unsigned char key, int x, int y)
{
	if (key == 27)
	{
		exit(0);
	}
	else if (key == 'a')
	{
			anime = 1;	
	}
	else if (key == 's') 
	{
		anime = 0;
	}
}

void myInit(char *progname)
{	
	int width = 640, height = 480;

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(progname);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (double)width / (double)height, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
}

void myReshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)width / (double)height, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0.0, 0.0, -5.0);		// move teapot
}

void getValueFromMenu(int value)
{
	switch (value) {
	case 1:
		sizeOfTeapot = 0.5;
		break;
	case 2:
		sizeOfTeapot = 1.0;
		break;
	case 3:
		sizeOfTeapot = 2.0;
		break;
	default:
		break;
	}
}


void mySetMenu()
{
	glutCreateMenu(getValueFromMenu);
	glutAddMenuEntry("x 0.5", 1);
	glutAddMenuEntry("x 1.0", 2);
	glutAddMenuEntry("x 2.0", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void xyzAxes(double length)
{
	glBegin(GL_LINES);
	glColor3d(1.0, 1.0, 0.0);	// yellow
	glVertex3d(0.0, 0.0, 0.0); glVertex3d(length, 0.0, 0.0);	//x-axis
	glColor3d(1.0, 0.0, 0.0);	// red
	glVertex3d(0.0, 0.0, 0.0); glVertex3d(0.0, length, 0.0);	//y-axis
	glColor3d(0.0, 0.0, 1.0);	// blue
	glVertex3d(0.0, 0.0, 0.0); glVertex3d(0.0, 0.0, length);	//z-axis
	glEnd();
}

void myIdle(void)
{
	glutPostRedisplay();
}

void myDisplay()
{
	int i = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	xyzAxes(10.0);

	glPushMatrix();

//	gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glTranslated(0.0, 0.0, -3.0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mtrl_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mtrl_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mtrl_shininess);
	glRotated(xAngle, 1.0, 0.0, 0.0);
	glRotated(yAngle, 0.0, 1.0, 0.0);
	glutSolidTeapot(sizeOfTeapot);
	

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	for (i = -35; i< 36; i += 2) {

		glVertex3i(i, -1, -35);
//		glVertex3i(-35, -1, -35);
//		glVertex3i(35, -1, -35);

		glVertex3i(i, -1, 35);
	//	glVertex3i(-35, -1, 35);
	//	glVertex3i(35, -1, 35);


		glVertex3i(-50, -1, i);
	//	glVertex3i(-50, -1, -36);
	//	glVertex3i(-50, -1, 35);

		glVertex3i(50, -1, i);
	//	glVertex3i(50, -1, -35);
	//	glVertex3i(50, -1, 35);
	
	}
	glEnd();
	glPopMatrix();
	glutSwapBuffers();

	glFlush();
	glDisable(GL_TEXTURE_2D);
}

void myMouseMotion(int x, int y)
{
	int		xdis, ydis;
	double	a = 0.5;

	if (mouseFlag == GL_FALSE) return;
	xdis = x - xStart;
	ydis = y - yStart;
	/* To match mouse's movement and its rotation axis */
	xAngle += (double)ydis *a;
	yAngle += (double)xdis *a;

	xStart = x;
	yStart = y;
	glutPostRedisplay();
}

void myMouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		xStart = x;
		yStart = y;
		mouseFlag = GL_TRUE;
	}
	else {
		mouseFlag = GL_FALSE;
	}
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	myInit(argv[0]);
	setUpTexture();
	glEnable(GL_LIGHT0);
	glutKeyboardFunc(myKeyboard);
	mySetMenu();
	glutMouseFunc(myMouseFunc);
	glutMotionFunc(myMouseMotion);
	glutIdleFunc(myIdle);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}
