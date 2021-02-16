#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "utils.h"
#include "BmpLoader.h"


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

/*
	Menggambar map yang digunakan dalam game.
	Yang digambarkan termasuk:
	- lantai
	- Jalan
	- Skybox
*/
void drawMap()
{
    // Map's floor
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
	
    // Map's skybox
    glPushMatrix();
    	glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureSunset);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0,5,-10);
        glRotatef(cameraAngle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS); //back
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


/*
	Menggambarkan model 3D yang akan dikendalikan oleh pemain
*/
void drawPlayerModel()
{
	
	//Player model's cockpit
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
	
	//Player model's  body
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
    
    //Player model's  base
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


/*
	Menggambarkan peluru yang ditembakkan oleh model pemain
*/
void drawBullet()
{
	//Player's bullet
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


/*
	Menggambarkan model 3D kendaraan musuh
*/
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


/*
	Menggambarkan peluru yang ditembakkan oleh model musuh
*/
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


/*
	Memanggil fungsi-fungsi penggambar agar model 3D dapat digambarkan
*/
void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	drawMap();
	
	
	//collision detection untuk musuh
	//kondisi if dibuat demikian agar ketika peluru pemain mengenai model musuh, model musuh berhenti digambarkan
	if(bulletPosition >= 7 && bulletPosition <= 8 && playerPosition >= enemyPosition-0.3 && playerPosition<= enemyPosition+0.3){
		enemyCollision = true;	
	}
	if(!enemyCollision){
		drawEnemy();
		drawEnemyBullet();
	}
	
	
	//collision detection untuk pemain
	//kondisi if dibuat demikian agar ketika peluru musuh mengenai model pemain, model pemain berhenti digambarkan
	if(enemyBulletPosition >= 5 && enemyBulletPosition <= 6 && enemyPosition >= playerPosition-0.3 && enemyPosition<= playerPosition+0.3){
		playerCollision = true;	
	}
	if(!playerCollision){
		drawPlayerModel();
		drawBullet();
	}

	glutSwapBuffers();
	
}


/*
	Fungsi Timer() digunakan agar dapat dilakukan looping
*/
void Timer(int value) {
	
	//kondisi if dibuat demikian agar posisi peluru pemain bergerak maju ketika variabel bulletFire bernilai true
	if(bulletFire){
		bulletPosition = bulletPosition + 0.5;
	}
	if(bulletPosition >=55){
		bulletFire = false;
	}
	
	//kondisi if dibuat demikian agar posisi model musuh dapat bergerak ke kiri dan kekanan
	if(enemyPosition >= 2.0 ){
		enemyDirection = true;
	}
	if(enemyPosition <= -2.0){
		enemyDirection = false;
	}
	
	//kondisi if dibuat demikian agar model musuh berotasi sedikit ke kiri dan kanan seiring bergerak
	if(enemyDirection){
		enemyPosition -= 0.07;
		enemyRoll += 0.2;
	}
	else{
		enemyPosition += 0.07;
		enemyRoll -= 0.2;
	}
	
	
	//kondisi if dibuat demikian dibuat agar posisi peluru musuh berubah dan ketika musuh sudah tidak digambarkan, 
	//nilai enemyBulletPosition tidak berubah sehingga model pemain tidak mati ketika musuh sudah tidak ada di layar
	if(!enemyCollision){
		enemyBulletPosition += 0.05;
		if(counterFire == 160){
			enemyBulletPosition = 0;
			counterFire = 0;
		}
		counterFire++;
	}
	if(enemyCollision){
		enemyBulletPosition = 0;
	}
	
	//kondisi if dibuat demikian agar ketika jalan sudah dilakukan looping sampai akhir, posisi jalan akan di-reset
	//sehingga jalan terlihat tidak habis-habis
	move += 0.5;
	if (move > 150) move = -150.0;
	
   glutPostRedisplay();
   glutTimerFunc(refreshMills, Timer, 0);
}


/*
	Inisialisasi dan load tekstur ke dalam variabel masing-masing
*/
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


/*
	Mengatur input keyboard
	'a' = menggerakkan model pemain ke kiri
	'd' = menggerakkan model pemain ke kanan
	'q' = memutar kamera ke kiri
	'e' = memutar kamera ke kanan
	space/spasi = menembak
	'l' = keluar dari game
	'r' = memunculkan kembali model pemain
	'f' = memunculkan kembali model musuh
*/
void KeyboardHandler(unsigned char key, int x, int y)
{
	
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


/*
	melakukan load tekstur dari file ke dalam game
*/
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

