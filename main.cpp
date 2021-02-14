#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "BmpLoader.h"

using namespace std;

char title[] = "Sunset Cyberdrive by Muhammad Alfarizi (181511023)";
int refreshMills = 15;
unsigned int ID;
float angle = 0.0;
float strafe = 0.0;
float move = 0.0;
GLuint textureWall, textureDoor, textureGrid, textureRoof, textureSky, textureWindow1, textureWindow2, textureFence, textureArch,
textureSunset, textureRoad, textureCar, textureTurretBase, textureTurretBox, textureTurretBarell;


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

/*
Draws the map which includes:
- Skybox
- Floor
- Road
*/
void drawMap()
{
    // Floor
    glPushMatrix();
    	glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureGrid);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0,0,-10);
    	glRotatef(angle, 0.0, 1.0, 0.0);
    	glTranslatef(0,0,10);
    	glTranslatef(strafe,0,0);
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
    	glTranslatef(0,0,-10);
    	glRotatef(angle, 0.0, 1.0, 0.0);
    	glTranslatef(0,0,10);
    	glTranslatef(strafe,0,move);
    	glBegin(GL_QUADS);
    		glTexCoord3f(0.0,20.0,0);  glVertex3f(-2.5,-1.4,200);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-2.5,-1.4,-200);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(2.5,-1.4,-200);
            glTexCoord3f(1.0,20.0,0);  glVertex3f(2.5,-1.4,200);
        glEnd();
        glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
    // Skybox
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
        glBegin(GL_QUADS); //Front
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-50,50,50);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-50,-50,50);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(50,-50,50);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(50,50,50);
        glEnd();
        glBegin(GL_QUADS); //Right
            glTexCoord3f(1.0,1.0,0);  glVertex3f(50,50,-50);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(50,-50,-50);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(50,-50,50);
            glTexCoord3f(0.0,1.0,0);  glVertex3f(50,50,50);
        glEnd();
        glBegin(GL_QUADS); //Left
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-50,50,-50);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-50,-50,-50);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(-50,-50,50);
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-50,50,50);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

	
}

void drawPlayer()
{
	
	//Car's body
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureCar);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-10);
    glRotatef(angle, 0.0, 1.0, 0.0);
	glTranslatef(0,0,10);
	glTranslatef(0,0,-3); 
        glBegin(GL_QUADS); //upper back
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.2,-0.5,-2.3);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(0.2,-0.5,-2.3);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.5,-0.75,-2.0);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-0.5,-0.75,-2.0);
        glEnd();
        
        glBegin(GL_QUADS); //lower back
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-0.5,-0.75,-2.0);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.5,-0.75,-2.0);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(0.3,-1.,-2.3);
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.3,-1,-2.3);
        glEnd();
        
        glBegin(GL_QUADS); //upper front
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.3,-0.5,-3.5);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(0.3,-0.5,-3.5);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.5,-0.75,-3.7);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-0.5,-0.75,-3.7);
        glEnd();
        
        glBegin(GL_QUADS); //lower front
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.5,-0.75,-3.7);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(0.5,-0.75,-3.7);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.3,-1,-3.5);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-0.3,-1,-3.5);
        glEnd();
        
        glBegin(GL_QUADS); //upper left
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.2,-0.5,-2.3);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-0.3,-0.5,-3.5);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(-0.5,-0.75,-3.7);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-0.5,-0.75,-2.0);
        glEnd();
        
        glBegin(GL_QUADS); //upper right
            glTexCoord3f(0.0,1.0,0);  glVertex3f(0.2,-0.5,-2.3);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(0.3,-0.5,-3.5);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.5,-0.75,-3.7);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(0.5,-0.75,-2.0);
        glEnd();
        
        glBegin(GL_QUADS); //lower left
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.3,-1,-2.3);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-0.3,-1,-3.5);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(-0.5,-0.75,-3.7);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-0.5,-0.75,-2.0);
        glEnd();
        
        glBegin(GL_QUADS); //lower right
            glTexCoord3f(0.0,1.0,0);  glVertex3f(0.3,-1,-2.3);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(0.3,-1,-3.5);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.5,-0.75,-3.7);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(0.5,-0.75,-2.0);
        glEnd();
        
        glBegin(GL_QUADS); //top
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.2,-0.5,-2.3);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-0.3,-0.5,-3.5);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.3,-0.5,-3.5);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(0.2,-0.5,-2.3);
        glEnd();
        
        glBegin(GL_QUADS); //bottom
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.2,-1,-2.3);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-0.3,-1,-3.5);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.3,-1,-3.5);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(0.2,-1,-2.3);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    //Car's turret base
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureTurretBase);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-10);
    glRotatef(angle, 0.0, 1.0, 0.0);
	glTranslatef(0,0,10);
	glTranslatef(0,0,-3);            
        glBegin(GL_QUADS); //back
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-0.05,-0.5,-2.6);
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.05,-0.4,-2.6);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(0.05,-0.4,-2.6);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.05,-0.5,-2.6);
        glEnd();
        
        glBegin(GL_QUADS); //front
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-0.05,-0.5,-2.7);
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.05,-0.4,-2.7);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(0.05,-0.4,-2.7);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.05,-0.5,-2.7);
        glEnd();
        
        glBegin(GL_QUADS); //left
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-0.05,-0.5,-2.7);
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.05,-0.4,-2.7);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-0.05,-0.4,-2.6);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(-0.05,-0.5,-2.6);
        glEnd();
        glBegin(GL_QUADS); //right
            glTexCoord3f(0.0,0.0,0);  glVertex3f(0.05,-0.5,-2.7);
            glTexCoord3f(0.0,1.0,0);  glVertex3f(0.05,-0.4,-2.7);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(0.05,-0.4,-2.6);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.05,-0.5,-2.6);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    //Car's turret box
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureTurretBox);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-10);
    glRotatef(angle, 0.0, 1.0, 0.0);
	glTranslatef(0,0,10);
	glTranslatef(0,0,-3);    
        glBegin(GL_QUADS); //top
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.15,-0.2,-3.0);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(0.15,-0.2,-3.0);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.15,-0.2,-2.5);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-0.15,-0.2,-2.5);
        glEnd();
        
        glBegin(GL_QUADS); //bottom
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.15,-0.4,-3.0);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(0.15,-0.4,-3.0);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.15,-0.4,-2.5);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-0.15,-0.4,-2.5);
        glEnd();
        
        glBegin(GL_QUADS); //back
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.15,-0.4,-2.5);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-0.15,-0.2,-2.5);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.15,-0.2,-2.5);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(0.15,-0.4,-2.5);
        glEnd();
        
        glBegin(GL_QUADS); //front
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.15,-0.4,-3.0);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-0.15,-0.2,-3.0);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.15,-0.2,-3.0);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(0.15,-0.4,-3.0);
        glEnd();
        
        glBegin(GL_QUADS); //left
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.15,-0.4,-2.5);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-0.15,-0.2,-2.5);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(-0.15,-0.2,-3.0);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-0.15,-0.4,-3.0);
        glEnd();
        
        glBegin(GL_QUADS); //right
            glTexCoord3f(0.0,1.0,0);  glVertex3f(0.15,-0.4,-2.5);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(0.15,-0.2,-2.5);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.15,-0.2,-3.0);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(0.15,-0.4,-3.0);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    //Car's turret barell
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureTurretBarell);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-10);
    glRotatef(angle, 0.0, 1.0, 0.0);
	glTranslatef(0,0,10);
	glTranslatef(0,0,-3);     
        glBegin(GL_QUADS); //top
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.05,-0.25,-3.5);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(0.05,-0.25,-3.5);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.05,-0.25,-3.0);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-0.05,-0.25,-3.0);
        glEnd();
        
        glBegin(GL_QUADS); //bottom
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.05,-0.35,-3.5);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(0.05,-0.35,-3.5);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.05,-0.35,-3.0);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-0.05,-0.35,-3.0);
        glEnd();
        
        glBegin(GL_QUADS); //front
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.05,-0.35,-3.5);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-0.05,-0.25,-3.5);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.05,-0.25,-3.5);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(0.05,-0.35,-3.5);
        glEnd();
        
        glBegin(GL_QUADS); //left
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.05,-0.35,-3.5);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-0.05,-0.25,-3.5);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(-0.05,-0.25,-3.0);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-0.05,-0.35,-3.0);
        glEnd();
        
        glBegin(GL_QUADS); //right
            glTexCoord3f(0.0,1.0,0);  glVertex3f(0.05,-0.35,-3.5);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(0.05,-0.25,-3.5);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.05,-0.25,-3.0);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(0.05,-0.35,-3.0);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    

}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	drawMap();
	drawPlayer();
	
	glutSwapBuffers();
	
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
	
	textureGrid = loadTexture("./assets/grid.bmp");
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
	textureCar = loadTexture("./assets/car.bmp");
	textureTurretBase = loadTexture("./assets/turret_base.bmp");
	textureTurretBox = loadTexture("./assets/turret_box.bmp");
	textureTurretBarell = loadTexture("./assets/turret_barell.bmp");
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
		if (strafe > 2.0) strafe = 2.0;
		break;
	case 'd':
        strafe -= 0.5;
        if (strafe < -2.0) strafe = -2.0;
	    break;
	case 's':
		move -= 0.5;
        if (move < -150) move = -150.0;
		break;
	case 'w':
		move += 0.5;
        if (move > 150) move = -150.0;
		break;
	case 'v':
		angle += 1;
		if (angle > 360) angle = 0.0;
		break;
	case 'b':
		angle -= 1;
        if (angle > 360) angle = 0.0;
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

