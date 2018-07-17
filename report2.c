/*  p4-RotateTeaPot.c
*  Rotating tea pot
*/
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

double	 theta = 0.0;
						// angular of tea pot
/*
void mySetLight()
{
	
	float light0_position[] = {  1.0,  1.0, 1.0, 1.0 };	// point light source
	float light1_position[] = { -1.0, -1.0, 1.0, 1.0 };	// point light source
	float light1_ambient[]  = { 0.0, 0.0, 0.5, 1.0 };
//	float light1_diffuse[]  = { 0.0, 0.0, 1.0, 1.0 };
//	float light1_specular[] = { 0.0, 0.0, 1.0, 1.0 };
	

/* Set up LIGHT0 which uses the default parameters except position */
//	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
/* Set up LIGHT1 */
//	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
//	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
//	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
//	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);

//	glEnable(GL_LIGHT0);		// enable the 0th light
//	glEnable(GL_LIGHT1);		// enable the 1st light
//}

void myKeyboard(unsigned char key, int x, int y)
{
	if (key == 27) exit(0);
}
/*
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
*/
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	glRotated(theta, 0.0, 1.0, 0.0);
	glColor3d(1.0, 1.0, 1.0);
	glutWireTeapot(1.0);
	glPopMatrix();

	glutSwapBuffers();

void myIdle(void)
{
//	theta = fmod(theta + 0.5, 360.0);
	glutPostRedisplay();
}

void myInit(char *progname)
{
	int width = 500, height = 500;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(progname);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (double)width / (double)height, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 1.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	myInit(argv[0]);
	glutKeyboardFunc(myKeyboard);
	glutIdleFunc(myIdle);
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}
