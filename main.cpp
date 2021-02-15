#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "BmpLoader.h"

using namespace std;

char title[] = "Sunset Cyberdrive by Muhammad Alfarizi (181511023)";
int refreshMills = 15;
unsigned int ID;
float cameraAngle = 0.0;
float playerPosition = 0.0;
float move = 0.0;
float bulletPosition = 0.0;
float enemyBulletPosition = 0.0;
float enemyPosition = 2.0;
float enemyRoll = -5.2;
int counterFire = 0;
bool bulletFire = false;
bool enemyDirection = false;
bool playerCollision = false;
bool enemyCollision = false;
GLuint  textureGrid, textureSky, textureSunset, textureRoad, textureCar, textureTurretBase, textureTurretBox,
textureTurretBarell, textureBullet, textureWingCover,
textureEnemy, textureCockpit, textureEnemyCockpit, textureEnemyBullet;


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
	glutTimerFunc(refreshMills, Timer, 0);
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
    	glRotatef(cameraAngle, 0.0, 1.0, 0.0);
    	glTranslatef(0,0,10);
    	glTranslatef(0,0,0);
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
    	glRotatef(cameraAngle, 0.0, 1.0, 0.0);
    	glTranslatef(0,0,10);
    	glTranslatef(0,0,move);
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
        glTranslatef(0,5,-10);
        glRotatef(cameraAngle, 0.0, 1.0, 0.0);
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
    glTranslatef(0,5,-10);
    glRotatef(cameraAngle, 0.0, 1.0, 0.0);    
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
	
	//Player's cockpit
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureCockpit);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-10);
    glRotatef(cameraAngle, 0.0, 1.0, 0.0);
	glTranslatef(0,0,10);
	glTranslatef(playerPosition,0,-3); 
        glBegin(GL_QUADS); //upper front
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.3,-0.5,-3.5);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(0.3,-0.5,-3.5);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.5,-0.75,-3.7);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-0.5,-0.75,-3.7);
        glEnd();    
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
	
	//Player's body
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureCar);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-10);
    glRotatef(cameraAngle, 0.0, 1.0, 0.0);
	glTranslatef(0,0,10);
	glTranslatef(playerPosition,0,-3); 
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
    
    //Turret base
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureTurretBase);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-10);
    glRotatef(cameraAngle, 0.0, 1.0, 0.0);
	glTranslatef(0,0,10);
	glTranslatef(playerPosition,0,-3);            
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
    
    //Turret box
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureTurretBox);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-10);
    glRotatef(cameraAngle, 0.0, 1.0, 0.0);
	glTranslatef(0,0,10);
	glTranslatef(playerPosition,0,-3);    
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
    
    //Turret barell
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureTurretBarell);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-10);
    glRotatef(cameraAngle, 0.0, 1.0, 0.0);
	glTranslatef(0,0,10);
	glTranslatef(playerPosition,0,-3);     
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

void drawBullet()
{
	//Player's bulletPosition
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureBullet);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-10);
    glRotatef(cameraAngle, 0.0, 1.0, 0.0);
	glTranslatef(0,0,10);
	glTranslatef(playerPosition,0,-bulletPosition-3);     
        glBegin(GL_QUADS); //top
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.05,-0.25,-3.5);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(0.05,-0.25,-3.5);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.05,-0.25,-3.4);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-0.05,-0.25,-3.4);
        glEnd();
        
        glBegin(GL_QUADS); //bottom
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.05,-0.35,-3.5);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(0.05,-0.35,-3.5);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.05,-0.35,-3.4);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-0.05,-0.35,-3.4);
        glEnd();
        
        glBegin(GL_QUADS); //front
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.05,-0.35,-3.5);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-0.05,-0.25,-3.5);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.05,-0.25,-3.5);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(0.05,-0.35,-3.5);
        glEnd();
        
        glBegin(GL_QUADS); //back
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.05,-0.35,-3.4);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-0.05,-0.25,-3.4);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.05,-0.25,-3.4);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(0.05,-0.35,-3.4);
        glEnd();
        
        glBegin(GL_QUADS); //left
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.05,-0.35,-3.5);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-0.05,-0.25,-3.5);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(-0.05,-0.25,-3.4);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-0.05,-0.35,-3.4);
        glEnd();
        
        glBegin(GL_QUADS); //right
            glTexCoord3f(0.0,1.0,0);  glVertex3f(0.05,-0.35,-3.5);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(0.05,-0.25,-3.5);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.05,-0.25,-3.4);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(0.05,-0.35,-3.4);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

drawEnemy()
{
	
	//Enemy's cockpit
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureEnemyCockpit);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-7);
    glRotatef(cameraAngle, 0.0, 1.0, 0.0);
	glTranslatef(0,0,7);
	glTranslatef(enemyPosition,0,0); 
	glRotatef(enemyRoll, 0, 0, 1);
        glBegin(GL_QUADS); //top
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.3,-0.1,-9);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-0.1,-0.5,-10);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.1,-0.5,-10);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(0.3,-0.1,-9);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
	
	//Enemy's body
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureEnemy);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-7);
    glRotatef(cameraAngle, 0.0, 1.0, 0.0);
	glTranslatef(0,0,7);
	glTranslatef(enemyPosition,0,0);
	glRotatef(enemyRoll, 0, 0, 1);
        glBegin(GL_QUADS); //front
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.1,-0.5,-10);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(0.1,-0.5,-10);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.1,-0.8,-10);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-0.1,-0.8,-10);
        glEnd();
        
        glBegin(GL_QUADS); //Back
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.3,-0.1,-9);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(0.3,-0.1,-9);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.3,-0.9,-9);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-0.3,-0.9,-9);
        glEnd();
        
        glBegin(GL_QUADS); //top
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.3,-0.1,-9);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-0.1,-0.5,-10);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.1,-0.5,-10);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(0.3,-0.1,-9);
        glEnd();
        
        glBegin(GL_QUADS); //bottom
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.3,-0.9,-9);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-0.1,-0.8,-10);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.1,-0.8,-10);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(0.3,-0.9,-9);
        glEnd();
        
        glBegin(GL_QUADS); //left
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.3,-0.1,-9);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-0.1,-0.5,-10);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(-0.1,-0.8,-10);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-0.3,-0.9,-9);
        glEnd();
        
        glBegin(GL_QUADS); //right
            glTexCoord3f(0.0,1.0,0);  glVertex3f(0.3,-0.1,-9);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(0.1,-0.5,-10);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.1,-0.8,-10);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(0.3,-0.9,-9);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    //Enemy's wings
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureEnemy);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-7);
    glRotatef(cameraAngle, 0.0, 1.0, 0.0);
	glTranslatef(0,0,7);
	glTranslatef(enemyPosition,0,0);
	glRotatef(enemyRoll, 0, 0, 1);
        glBegin(GL_QUADS); //left wing
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.1,-0.36,-9.2);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-0.5,-0.65,-9.2);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(-0.5,-0.65,-9.6);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-0.1,-0.37,-9.6);
        glEnd();
        
        glBegin(GL_QUADS); //right wing
            glTexCoord3f(0.0,1.0,0);  glVertex3f(0.1,-0.36,-9.2);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(0.5,-0.65,-9.2);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.5,-0.65,-9.6);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(0.1,-0.37,-9.6);
        glEnd();
        
        glBegin(GL_QUADS); //bottom of wings
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.5,-0.65,-9.2);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-0.5,-0.65,-9.6);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.5,-0.65,-9.6);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(0.5,-0.65,-9.2);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    //Enemy's wing covers
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureWingCover);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-7);
    glRotatef(cameraAngle, 0.0, 1.0, 0.0);
	glTranslatef(0,0,7);
	glTranslatef(enemyPosition,0,0);
	glRotatef(enemyRoll, 0, 0, 1);
        glBegin(GL_TRIANGLES); // back left wing cover
        	glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.1,-0.36,-9.2);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-0.5,-0.65,-9.2);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(-0.1,-0.65,-9.2);
        glEnd();
        
        glBegin(GL_TRIANGLES); // front left wing cover
        	glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.1,-0.36,-9.6);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-0.5,-0.65,-9.6);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(-0.1,-0.65,-9.6);
        glEnd();
        
        glBegin(GL_TRIANGLES); // back right wing cover
        	glTexCoord3f(0.0,1.0,0);  glVertex3f(0.1,-0.36,-9.2);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(0.5,-0.65,-9.2);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.1,-0.65,-9.2);
        glEnd();
        
        glBegin(GL_TRIANGLES); // front right wing cover
        	glTexCoord3f(0.0,1.0,0);  glVertex3f(0.1,-0.36,-9.6);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(0.5,-0.65,-9.6);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.1,-0.65,-9.6);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    //Enemy's gun
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureTurretBarell);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-7.1);
    glRotatef(cameraAngle, 0.0, 1.0, 0.0);
	glTranslatef(0,0,7.1);
	glTranslatef(enemyPosition,0,0);
	glRotatef(enemyRoll, 0, 0, 1);
        glBegin(GL_QUADS); //top
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.05,-0.25,-9);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(0.05,-0.25,-9);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.05,-0.25,-9.1);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-0.05,-0.25,-9.1);
        glEnd();
        
        glBegin(GL_QUADS); //bottom
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.05,-0.35,-9);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(0.05,-0.35,-9);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.05,-0.35,-9.1);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-0.05,-0.35,-9.1);
        glEnd();
        
        glBegin(GL_QUADS); //front
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.05,-0.35,-9);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-0.05,-0.25,-9);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.05,-0.25,-9);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(0.05,-0.35,-9);
        glEnd();
        
        glBegin(GL_QUADS); //left
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.05,-0.35,-9);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-0.05,-0.25,-9);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(-0.05,-0.25,-9.1);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-0.05,-0.35,-9.1);
        glEnd();
        
        glBegin(GL_QUADS); //right
            glTexCoord3f(0.0,1.0,0);  glVertex3f(0.05,-0.35,-9);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(0.05,-0.25,-9);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.05,-0.25,-9.1);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(0.05,-0.35,-9.1);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void drawEnemyBullet()
{
	//Enemy's bullet
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureEnemyBullet);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-7.1);
    glRotatef(cameraAngle, 0.0, 1.0, 0.0);
	glTranslatef(0,0,7.1);
	glTranslatef(enemyPosition,0,enemyBulletPosition);     
        glBegin(GL_QUADS); //top
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.05,-0.25,-9);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(0.05,-0.25,-9);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.05,-0.25,-9.1);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-0.05,-0.25,-9.1);
        glEnd();
        
        glBegin(GL_QUADS); //bottom
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.05,-0.35,-9);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(0.05,-0.35,-9);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.05,-0.35,-9.1);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-0.05,-0.35,-9.1);
        glEnd();
        
        glBegin(GL_QUADS); //front
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.05,-0.35,-9);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-0.05,-0.25,-9);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.05,-0.25,-9);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(0.05,-0.35,-9);
        glEnd();
        
        glBegin(GL_QUADS); //back
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.05,-0.35,-9.1);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-0.05,-0.25,-9.1);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.05,-0.25,-9.1);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(0.05,-0.35,-9.1);
        glEnd();
        
        glBegin(GL_QUADS); //left
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.05,-0.35,-9);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-0.05,-0.25,-9);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(-0.05,-0.25,-9.1);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-0.05,-0.35,-9.1);
        glEnd();
        
        glBegin(GL_QUADS); //right
            glTexCoord3f(0.0,1.0,0);  glVertex3f(0.05,-0.35,-9);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(0.05,-0.25,-9);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(0.05,-0.25,-9.1);
            glTexCoord3f(1.0,1.0,0);  glVertex3f(0.05,-0.35,-9.1);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	drawMap();
	
	
	//collision detection
	if(bulletPosition >= 9 && bulletPosition <= 10 && playerPosition >= enemyPosition-0.3 && playerPosition<= enemyPosition+0.3){
		enemyCollision = true;	
	}
	
	if(!enemyCollision){
		drawEnemy();
		drawEnemyBullet();
	}
	
	if(enemyBulletPosition >= 0 && enemyBulletPosition <= 0.5 && enemyPosition >= playerPosition-0.3 && enemyPosition<= playerPosition+0.3){
		playerCollision = true;	
	}
	
	if(!playerCollision){
		drawPlayer();
		drawBullet();
	}

	glutSwapBuffers();
	
}

void Timer(int value) {
	
	if(bulletFire){
		bulletPosition = bulletPosition + 0.5;
	}
	
	if(enemyPosition >= 2.0 ){
		enemyDirection = true;
	}
	if(enemyPosition <= -2.0){
		enemyDirection = false;
	}
	
	if(enemyDirection){
		enemyPosition -= 0.07;
		enemyRoll += 0.2;
	}
	else{
		enemyPosition += 0.07;
		enemyRoll -= 0.2;
	}
	
	if(!enemyCollision){
		enemyBulletPosition += 0.03;
		if(counterFire == 160){
			enemyBulletPosition = 0;
			counterFire = 0;
		}
		counterFire++;
	}
	
	move += 0.5;
	if (move > 150) move = -150.0;
	
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
	textureSunset = loadTexture("./assets/sunset.bmp");
	textureRoad = loadTexture("./assets/road.bmp");
	textureCar = loadTexture("./assets/car.bmp");
	textureTurretBase = loadTexture("./assets/turret_base.bmp");
	textureTurretBox = loadTexture("./assets/turret_box.bmp");
	textureTurretBarell = loadTexture("./assets/turret_barell.bmp");
	textureBullet = loadTexture("./assets/bullet.bmp");
	textureWingCover = loadTexture("./assets/wing_cover.bmp");
	textureEnemy = loadTexture("./assets/enemy.bmp");
	textureCockpit = loadTexture("./assets/cockpit.bmp");
	textureEnemyCockpit = loadTexture("./assets/enemy_cockpit.bmp");
	textureEnemyBullet = loadTexture("./assets/enemy_bullet.bmp");
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
	case 'd':  
		playerPosition += 0.5;
		if (playerPosition > 2.0) playerPosition = 2.0;
		break;
	case 'a':
        playerPosition -= 0.5;
        if (playerPosition < -2.0) playerPosition = -2.0;
	    break;
	case 'q':
		cameraAngle += 1.5;
		if (cameraAngle > 360) cameraAngle = 0.0;
		break;
	case 'e':
		cameraAngle -= 1.5;
        if (cameraAngle > 360) cameraAngle = 0.0;
		break;
	case ' ':
		bulletFire = true;
		bulletPosition = 0;
		break;
	case 'l':
		exit(0);
		break;
	case 'r':
		playerCollision = false;
		break;
	case 'f':
		enemyCollision = false;
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

