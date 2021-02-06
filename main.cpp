#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "BmpLoader.h"

using namespace std;

char title[] = "Muhammad Alfarizi & 181511023";
int refreshMills = 15;
unsigned int ID;
float angle = 0.0;
float strafe = 0.0;
float move = 0.0;
GLuint textureWall, textureDoor, textureGrass, textureRoof, textureSky, textureWindow1, textureWindow2, textureFence, textureArch,
textureSunset, textureRoad;


void Init();
void KeyboardHandler(unsigned char key, int x, int y);
void Reshape(GLsizei width, GLsizei height);
void Display();
void Timer(int value);
GLuint loadTexture(const char* filename);

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow(title);
	glEnable(GL_DEPTH_TEST);
	
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyboardHandler);
	Init();
	glutMainLoop();
	return 0;
}

void drawMap()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Grass
    glPushMatrix();
    	glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureGrass );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(strafe,0,-10);
        glRotatef(angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0,70.0,0);  glVertex3f(-50,-1.5,50);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-50,-1.5,-50);
            glTexCoord3f(70.0,0.0,0);  glVertex3f(50,-1.5,-50);
            glTexCoord3f(70.0,70.0,0);  glVertex3f(50,-1.5,50);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    //Road
    glPushMatrix();
    	glEnable(GL_TEXTURE_2D);
    	glBindTexture(GL_TEXTURE_2D, textureRoad);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    	glTranslatef(strafe,0,move-10);
    	glRotatef(angle, 0.0, 1.0, 0.0);
    	glBegin(GL_QUADS);
    		glTexCoord3f(0.0,20.0,0);  glVertex3f(-3,-1.4,100);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-3,-1.4,-100);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(3,-1.4,-100);
            glTexCoord3f(1.0,20.0,0);  glVertex3f(3,-1.4,100);
        glEnd();
        glDisable(GL_TEXTURE_2D);
	glPopMatrix();
    // Sky
    glPushMatrix();
    	glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureSunset);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(strafe,5,-10);
        glRotatef(angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS); //Belakang
            glTexCoord3f(0,1,0);  glVertex3f(-50,50,-50);
            glTexCoord3f(0,0,0);  glVertex3f(-50,-50,-50);
            glTexCoord3f(1,0,0);  glVertex3f(50,-50,-50);
            glTexCoord3f(1,1,0);  glVertex3f(50,50,-50);
        glEnd();
    glPopMatrix();
	
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureSky);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(strafe,5,-10);
    glRotatef(angle, 0.0, 1.0, 0.0);    
        glBegin(GL_QUADS); //Depan
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-50,50,50);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-50,-50,50);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(50,-50,50);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(50,50,50);
        glEnd();
        glBegin(GL_QUADS); //Kanan
            glTexCoord3f(1.0,1.0,0);  glVertex3f(50,50,-50);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(50,-50,-50);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(50,-50,50);
            glTexCoord3f(0.0,1.0,0);  glVertex3f(50,50,50);
        glEnd();
        glBegin(GL_QUADS); //Kiri
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-50,50,-50);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-50,-50,-50);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(-50,-50,50);
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-50,50,50);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

	glutSwapBuffers();
}

void Display()
{
	drawMap();
	
}

void Timer(int value) {
   glutPostRedisplay();
   glutTimerFunc(refreshMills, Timer, 0);
}

void Init(){
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	
	textureGrass = loadTexture("./assets/grid.bmp");
	textureSky = loadTexture("./assets/sky2.bmp");
	textureWall = loadTexture("./assets/wall.bmp");
	textureRoof = loadTexture("./assets/roof.bmp");
	textureDoor = loadTexture("./assets/door.bmp");
	textureWindow1 = loadTexture("./assets/window1.bmp");
	textureWindow2 = loadTexture("./assets/window2.bmp");
	textureFence = loadTexture("./assets/fence.bmp");
	textureArch = loadTexture("./assets/arch.bmp");
	textureSunset = loadTexture("./assets/sunset.bmp");
	textureRoad = loadTexture("./assets/road.bmp");
}

void Reshape(GLsizei width, GLsizei height) {
	const float ar = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void KeyboardHandler(unsigned char key, int x, int y)
{
	
	// d dan f
	switch (key) {
	case 'a':  
		strafe += 0.5;
		if (strafe > 2.5) strafe = 2.5;
		break;
	case 'd':
        strafe -= 0.5;
        if (strafe < -2.5) strafe = -2.5;
	    break;
	case 's':
		move -= 0.5;
        if (move < -39) move = -39.0;
		break;
	case 'w':
		move += 0.5;
        if (move > 48) move = 48.0;
		break;
	case 'q':
		exit(0);
		break;
	default: 
		break;
	}
	glutPostRedisplay();
}

GLuint loadTexture(const char* filename) {
	BmpLoader bl(filename);	
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D,
				 0,
				 GL_RGB,
				 bl.iWidth, bl.iHeight,
				 0,
				 GL_RGB,
				 GL_UNSIGNED_BYTE,
				 bl.textureData);
	return textureId;
}

