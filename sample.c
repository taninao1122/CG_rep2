/*  p6-LightPosition.c
*  Examination of a light position.
*/
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdlib.h>
#include <GL/glut.h>
#include<stdio.h>
#include <math.h>

unsigned char	mouseFlag = GL_FALSE;		// flag for moving or not
int				xStart, yStart;				// start position when drug begins
double			xAngle = 0.0, yAngle = 0.0;	// angles of the teapot
double	sizeOfTeapot = 1.0;

double	 theta = 0.0;						// angular of tea pot
float mtrl_diffuse[] = { 0.6, 0.6, 0.6, 0.0 };
float mtrl_specular[] = { 1.0, 0.1, 0.3, 0.0 };
float mtrl_shininess[] = { 128.0 };					// range [0,128]

float	light_pos[] = { 5, 0, 0, 1 };

#define	imageWidth 256
#define	imageHeight 256

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

void setUpTexture(char* filename)
{
	readPPMImage(filename);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, texImage);
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




void myDisplay(void)
{
	int i = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	xyzAxes(10.0);

	glPushMatrix();
	
	glTranslated(0.0, 0.0, -3.0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mtrl_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mtrl_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mtrl_shininess);
	glRotated(xAngle, 1.0, 0.0, 0.0);
	setUpTexture("mizutama.ppm");
	glEnable(GL_TEXTURE_2D);
	glRotated(theta, 0.0, 1.0, 0.0);
	glutSolidTeapot(sizeOfTeapot);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	setUpTexture("wood.data");
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	for (i = -35; i< 36; i += 2) {
		glVertex3i(i, -1, -35);
		glVertex3i(i, -1, 35);
		glVertex3i(-50, -1, i);
		glVertex3i(50, -1, i);
	}
	glEnd();
	glPopMatrix();

	glutSwapBuffers();
	glFlush();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
}

void myIdle(void)
{
	theta = fmod(theta + 0.5, 360.0);
	glutPostRedisplay();
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

void myInit(char *progname)
{
	int width = 500, height = 500;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(progname);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (double)width / (double)height, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
}

void myKeyboard(unsigned char key, int x, int y)
{
	if (key == 27) exit(0);
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
