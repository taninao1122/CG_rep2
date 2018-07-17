/* p5-RotateTeaPot.c
* Rotate the teapot by using glutMousFunc() and glutMotionFunc().
*/
#include <stdlib.h>
#include <GL/glut.h>

unsigned char	mouseFlag = GL_FALSE;		// flag for moving or not
int				xStart, yStart;				// start position when drug begins
double			xAngle = 0.0, yAngle = 0.0;	// angles of the teapot

void myKeyboard(unsigned char key, int x, int y)
{
	if (key == 27) exit(0);
}

void myInit(char *progname)
{
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(progname);
	glClearColor(0.0, 0.0, 0.0, 1.0);
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
	//	sizeOfTeapot = 0.5;
		break;
	case 2:
	//	sizeOfTeapot = 1.0;
		break;
	case 3:
	//	sizeOfTeapot = 2.0;
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

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glColor3d(1.0, 0.0, 0.0);
	glRotated(xAngle, 1.0, 0.0, 0.0);
	glRotated(yAngle, 0.0, 1.0, 0.0);
	glutWireTeapot(1.0);
	glPopMatrix();
	glutSwapBuffers();
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
	glutKeyboardFunc(myKeyboard);
	mySetMenu();
	glutMouseFunc(myMouseFunc);
	glutMotionFunc(myMouseMotion);

	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}
