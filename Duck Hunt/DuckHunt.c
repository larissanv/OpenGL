//g++ DuckHunt.c -o a -lm -lGL -lGLU -lglut

#include <GL/glut.h>    // Header File For The GLUT Library
#include <GL/gl.h>  // Header File For The OpenGL32 Library
#include <GL/glu.h> // Header File For The GLu32 Library
#include <unistd.h>     // needed to sleep
#include <math.h>
#include <stdio.h>
#include "SOIL.h"

#define ESCAPE 27
int texture[2];

int window;

float angulo_mirax = 0;
float angulo_miray = 0;
GLfloat tempo = .0001;
int trigerPato1 = 0;
int trigerPato2 = 0;
int trigerPato3 = 0;
int trigerPato4 = 0;
int trigerPato5 = 0;
int textura_pato = 1;
int textura_fundo = 0;

GLfloat p1x = 0;
GLfloat p1y = 0;
GLfloat posicaoPato1x = -1.5;
GLfloat deltaPato1x = .0001;
GLfloat posicaoPato1y = -0.5;
GLfloat deltaPato1y = .0001;
GLfloat p1 = 0;

GLfloat posicaoPato2x = 1.5;
GLfloat deltaPato2x = .0001;
GLfloat posicaoPato2y = -0.5;
GLfloat deltaPato2y = .0001;

GLfloat posicaoPato3x = -0.5;
GLfloat deltaPato3x = .0001;
GLfloat posicaoPato3y = -0.5;
GLfloat deltaPato3y = .0001;

GLfloat posicaoPato4x = -0.5;
GLfloat deltaPato4x = .0001;
GLfloat posicaoPato4y = -0.5;
GLfloat deltaPato4y = .0001;

GLfloat posicaoPato5x = -1.5;
GLfloat deltaPato5x = .0001;
GLfloat posicaoPato5y = -0.5;
GLfloat deltaPato5y = .0001;

int LoadGLTextures() // Load Bitmaps And Convert To Textures
{
    /* load an image file directly as a new OpenGL texture */
    texture[0] = SOIL_load_OGL_texture
        (
        "img/bg.bmp",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );
 
    if(texture[0] == 0)
        return 0;

    texture[1] = SOIL_load_OGL_texture
        (
        "img/pato.bmp",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );
 
    if(texture[1] == 0)
        return 0;

    texture[2] = SOIL_load_OGL_texture
        (
        "img/pato-morto.bmp",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );
 
    if(texture[2] == 0)
        return 0;

    texture[3] = SOIL_load_OGL_texture
        (
        "img/cachorro.bmp",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );
 
    if(texture[3] == 0)
        return 0;

    texture[4] = SOIL_load_OGL_texture
        (
        "img/gameover.bmp",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );
 
    if(texture[4] == 0)
        return 0;

    texture[5] = SOIL_load_OGL_texture
        (
        "img/win.bmp",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );
 
    if(texture[5] == 0)
        return 0;

    // Typical Texture Generation Using Data From The Bitmap
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glBindTexture(GL_TEXTURE_2D, texture[5]);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
 
    return 1;                                        // Return Success
}

void drawCircle(float cx, float cy, float r, int num_segments) 
{ 
    glBegin(GL_LINE_LOOP); 
    for(int ii = 0; ii < num_segments; ii++) { 
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
        float x = r * cosf(theta);//calculate the x component 
        float y = r * sinf(theta);//calculate the y component 
        glVertex2f(x + cx, y + cy);//output vertex 
    } 
    glEnd(); 
}

void InitGL(int Width, int Height)          // We call this right after our OpenGL window is created.
{
    LoadGLTextures();               // Load The Texture(s) 
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);   // This Will Clear The Background Color To Black
    glClearDepth(1.0);        // Enables Clearing Of The Depth Buffer
    glDepthFunc(GL_LESS);             // The Type Of Depth Test To Do
    glEnable(GL_DEPTH_TEST);            // Enables Depth Testing     
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10,10,-((GLfloat)Width/(GLfloat)Height) * 10,((GLfloat)Width/(GLfloat)Height) * 10, 0, 10);
    //gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.01f,100.0f);
    glMatrixMode(GL_MODELVIEW);
}

/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
void ReSizeGLScene(int Width, int Height)
{
    if (Height==0)        // Prevent A Divide By Zero If The Window Is Too Small
       Height=1;

    glViewport(0, 0, Width, Height);    // Reset The Current Viewport And Perspective Transformation
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
    glOrtho(-10,10,-((GLfloat)Width/(GLfloat)Height) * 10,((GLfloat)Width/(GLfloat)Height) * 10, 0, 10);
    glMatrixMode(GL_MODELVIEW);
}
void drawMira()
{
    glColor3f(1.0f,0.0f,0.0f);    //red
    //glutWireSphere(.2f, 20.0f, 2.0f);
    glTranslatef(((angulo_mirax/250) * 10 -10.5),((angulo_miray/250) * -10 +11),0);
    drawCircle(0.4, 0.8, 0.3, 40);  
    drawCircle(0.4, 0.8, 0.2, 20); 
    drawCircle(0.4, 0.8, 0.1, 10); 
    drawCircle(0.4, 0.8, 0.01, 10);   
    glColor3f(1.0f,1.0f,1.0f);    //branco
}


void drawfinal()
{
   glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, texture[textura_fundo]);   // choose the texture to use.
    glTranslatef(0.0f,0.0f,-10.0f);              // move 5 units into the screen.

    glBegin(GL_QUADS);

    // Front Face (note that the texture's corners have to match the quad's corners)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -10.0f,  1.0f); // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 10.0f, -10.0f,  1.0f); // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 10.0f,  10.0f,  1.0f); // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f,  10.0f,  1.0f); // Top Left Of The Texture and Quad
    
    // Back Face
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, -10.0f, -1.0f);    // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f,  10.0f, -1.0f);    // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 10.0f,  10.0f, -1.0f);    // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 10.0f, -10.0f, -1.0f);    // Bottom Left Of The Texture and Quad
    
    // Top Face
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f,  10.0f, -1.0f);    // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f,  10.0f,  1.0f);    // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 10.0f,  10.0f,  1.0f);    // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 10.0f,  10.0f, -1.0f);    // Top Right Of The Texture and Quad
    
    // Bottom Face       
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f, -10.0f, -1.0f);    // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 10.0f, -10.0f, -1.0f);    // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 10.0f, -10.0f,  1.0f);    // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, -10.0f,  1.0f);    // Bottom Right Of The Texture and Quad
    
    // Right face
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 10.0f, -10.0f, -1.0f);    // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 10.0f,  10.0f, -1.0f);    // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 10.0f,  10.0f,  1.0f);    // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 10.0f, -10.0f,  1.0f);    // Bottom Left Of The Texture and Quad
    
    // Left Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -10.0f, -1.0f); // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, -10.0f,  1.0f); // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f,  10.0f,  1.0f); // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f,  10.0f, -1.0f); // Top Left Of The Texture and Quad

    glEnd();
    glDisable(GL_TEXTURE_2D);
}



void drawDog()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[3]);   // choose the texture to use.
    glPushMatrix();
    glTranslatef(0.0f,-2.5f,-6.0f);              // move 5 units into the screen.

    // glTranslatef(posicaoPato1x * 3,posicaoPato1y*3,0);
    glBegin(GL_QUADS);

    // Front Face (note that the texture's corners have to match the quad's corners)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, -2.0f,  2.0f); // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.0f, -2.0f,  2.0f); // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.0f,  0.0f,  2.0f); // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f,  0.0f,  2.0f); // Top Left Of The Texture and Quad
    
    // Back Face
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.0f, -2.0f, -2.0f);    // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.0f,  0.0f, -2.0f);    // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f,  0.0f, -2.0f);    // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0f, -2.0f, -2.0f);    // Bottom Left Of The Texture and Quad
    
    // Top Face
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f,  0.0f, -2.0f);    // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f,  0.0f,  2.0f);    // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.0f,  0.0f,  2.0f);    // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.0f,  0.0f, -2.0f);    // Top Right Of The Texture and Quad
    
    // Bottom Face       
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.0f, -2.0f, -2.0f);    // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f, -2.0f, -2.0f);    // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0f, -2.0f,  2.0f);    // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.0f, -2.0f,  2.0f);    // Bottom Right Of The Texture and Quad
    
    // Right face
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.0f, -2.0f, -2.0f);    // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.0f,  0.0f, -2.0f);    // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f,  0.0f,  2.0f);    // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0f, -2.0f,  2.0f);    // Bottom Left Of The Texture and Quad
    
    // Left Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, -2.0f, -2.0f); // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.0f, -2.0f,  2.0f); // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.0f,  0.0f,  2.0f); // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f,  0.0f, -2.0f); // Top Left Of The Texture and Quad

    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
   
}

void drawPato(GLfloat px,GLfloat py)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[textura_pato]);   // choose the texture to use.
    glPushMatrix();
    glTranslatef(px * 3,py*3,0);
    glBegin(GL_QUADS);

    // Front Face (note that the texture's corners have to match the quad's corners)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f); // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f); // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f); // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f); // Top Left Of The Texture and Quad
    
    // Back Face
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);    // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);    // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);    // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);    // Bottom Left Of The Texture and Quad
    
    // Top Face
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);    // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);    // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);    // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);    // Top Right Of The Texture and Quad
    
    // Bottom Face       
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);    // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);    // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);    // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);    // Bottom Right Of The Texture and Quad
    
    // Right face
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);    // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);    // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);    // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);    // Bottom Left Of The Texture and Quad
    
    // Left Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f); // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f); // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f); // Top Left Of The Texture and Quad

    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


void drawFundo()
{
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, texture[textura_fundo]);   // choose the texture to use.
    glTranslatef(0.0f,0.0f,-10.0f);              // move 5 units into the screen.

    glBegin(GL_QUADS);

    // Front Face (note that the texture's corners have to match the quad's corners)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -10.0f,  1.0f); // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 10.0f, -10.0f,  1.0f); // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 10.0f,  10.0f,  1.0f); // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f,  10.0f,  1.0f); // Top Left Of The Texture and Quad
    
    // Back Face
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, -10.0f, -1.0f);    // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f,  10.0f, -1.0f);    // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 10.0f,  10.0f, -1.0f);    // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 10.0f, -10.0f, -1.0f);    // Bottom Left Of The Texture and Quad
    
    // Top Face
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f,  10.0f, -1.0f);    // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f,  10.0f,  1.0f);    // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 10.0f,  10.0f,  1.0f);    // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 10.0f,  10.0f, -1.0f);    // Top Right Of The Texture and Quad
    
    // Bottom Face       
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f, -10.0f, -1.0f);    // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 10.0f, -10.0f, -1.0f);    // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 10.0f, -10.0f,  1.0f);    // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, -10.0f,  1.0f);    // Bottom Right Of The Texture and Quad
    
    // Right face
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 10.0f, -10.0f, -1.0f);    // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 10.0f,  10.0f, -1.0f);    // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 10.0f,  10.0f,  1.0f);    // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 10.0f, -10.0f,  1.0f);    // Bottom Left Of The Texture and Quad
    
    // Left Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -10.0f, -1.0f); // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, -10.0f,  1.0f); // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f,  10.0f,  1.0f); // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f,  10.0f, -1.0f); // Top Left Of The Texture and Quad

    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void animacao_patos()
{     
    //define o tempo do jogo
    tempo += deltaPato1y;

    p1y +=  deltaPato1y;
    p1x +=  deltaPato1x;

    //TRATAR colisoes

    if (tempo > 0 && tempo < 4){

        glPushMatrix();
        glTranslatef(posicaoPato1x,posicaoPato1y,0);
        drawPato(posicaoPato1x,posicaoPato1y);
        glPopMatrix();

        if (trigerPato1 == 1){
            textura_pato = 2;
            posicaoPato1y -= 5 * deltaPato1y;
        }else{
            // printf("%f\n",posicaoPato1y);
            textura_pato = 1;
            posicaoPato1y += 2 * deltaPato1y;
            //inverte voo
            if(posicaoPato1y > 1){
                posicaoPato1x -= 2*deltaPato1x;
            }else{
                posicaoPato1x += 2* deltaPato1x;
            }
        }

    }else if(tempo > 4 && tempo < 7){

        if (trigerPato2 == 1){
            textura_pato = 2;
        }else{
            textura_pato = 1;
            glPushMatrix();
            glTranslatef(posicaoPato2x * 4,posicaoPato2y*4,0);
            drawPato(posicaoPato2x,posicaoPato2y);
            glPopMatrix();
            
            posicaoPato2y += deltaPato2y;
            //inverte voo
            if(posicaoPato2y > 0.5f){
                posicaoPato2x += deltaPato2x;
            }else{
                posicaoPato2x -= deltaPato2x;
            }
        }
    }
    else if(tempo > 7 && tempo < 9){
        if (trigerPato3 == 1){
            textura_pato = 2;
        }else{
            textura_pato = 1;
            glPushMatrix();
            glTranslatef(posicaoPato3x * 4,posicaoPato3y*4,0);
            drawPato(posicaoPato3x,posicaoPato3y);
            glPopMatrix();
            
            posicaoPato3y += deltaPato3y;
            if(posicaoPato3y > 1.2f){
                posicaoPato3x -= deltaPato3x;
            }else{
               posicaoPato3x += deltaPato3x;
            }
        }
    }
    else if(tempo > 9 && tempo < 11){
        if (trigerPato4 == 1){
            textura_pato = 2;
        }else{
            textura_pato = 1;
            glPushMatrix();
            glTranslatef(posicaoPato4x * 4,posicaoPato4y*5,0);
            // drawPato();
            glPopMatrix();
            
            posicaoPato4y += deltaPato4y;
            if(posicaoPato4y > 0.8f){
                posicaoPato4x -= deltaPato4x;
            }else{
                posicaoPato4x += deltaPato4x;
            }
        }
    } else if(tempo > 11 && tempo < 14){
        if (trigerPato5 == 1){
            textura_pato = 2;
        }else{
            textura_pato = 1;
            glPushMatrix();
            glTranslatef(posicaoPato5x * 4,posicaoPato5y*4,0);
            drawPato(posicaoPato5x,posicaoPato5y);
            glPopMatrix();
            
            posicaoPato5y += deltaPato5y;
            if(posicaoPato5y > 1.5f){
                posicaoPato5x -= deltaPato5x;
            }else{
                posicaoPato5x += deltaPato5x;
            }
        }
    }else if(tempo > 14){
        //FIM
       
        //if matou pato1, pato2, pato3 ....  mostra win

        //VERFICAR SE MATOU TODOS
        //SE MATOU TODOS ENTÃO

        //SE NÃO MATOU TODOS 
        // textura_fundo = 4; //perdeu
        //fazer if para verificar as morte 
        textura_fundo = 5; //ganhou
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); // Clear The Screen And The Depth Buffer
        // drawfinal();
        drawFundo();
    }
        
    // glFlush();
    // glutPostRedisplay();   
}


void DrawGLScene()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); // Clear The Screen And The Depth Buffer

    glPushMatrix(); //  Salva a matriz corrente
    drawFundo();
    glPopMatrix();  //  Desempilha a matriz corrente
    

    glPushMatrix();
    drawDog();
    glPopMatrix();

	glPushMatrix(); //  Salva a matriz corrente
    drawMira();
    glPopMatrix();  //  Desempilha a matriz corrente

    glPushMatrix();
    animacao_patos();
    glPopMatrix();


    glutSwapBuffers();
}

/* The function called whenever a key is pressed. */
void keyboardCB( unsigned char key, int x, int y )
{
    switch (key){
        case 27: // ESC
            exit (0);
            break;
  }
  // glutPostRedisplay();
}


void MouseClique(int button, int state, int xcoord, int ycoord)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        trigerPato1 = 1;
        printf("atirou\n");

        // if((p1y < (angulo_miray/250)) && ((p1y +0.5) >(angulo_miray/250 ) )&& ((p1x) >(angulo_mirax/250)) && ((p1x +0.5) >(angulo_mirax/250))){
        // 	trigerPato1 = 1;
        // 	printf("posx %f\n",p1y );
        // 	printf("posx %f\n",((angulo_miray/250)) );
        // }
    }
    // glutPostRedisplay();
}

void MouseMove(int xcoord, int ycoord)
{
  angulo_mirax = GLfloat(xcoord);
  angulo_miray = GLfloat(ycoord);

  // glutPostRedisplay();
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0, 0);
    window = glutCreateWindow("DUCK HUNT");
    // glutFullScreen();
    
    glutSetCursor(GLUT_CURSOR_NONE);


    glutDisplayFunc(&DrawGLScene);
    glutIdleFunc(&DrawGLScene);
    glutReshapeFunc(&ReSizeGLScene);
    glutPassiveMotionFunc(MouseMove);
    glutKeyboardFunc(keyboardCB);
    glutMouseFunc(MouseClique);
    InitGL(500, 500);
    glutMainLoop();

    return 1;
}
