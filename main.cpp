#include <windows.h>
#include <GL/glut.h>
#include "utils.h"

char title[] = "Sunset Cyberdrive by Muhammad Alfarizi (181511023)";

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow(title);
	glEnable(GL_DEPTH_TEST);
	
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutTimerFunc(15, Timer, 0);
	glutKeyboardFunc(KeyboardHandler);
	Init();
	glutMainLoop();
	return 0;
}
