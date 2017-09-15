///Como compilar:
//g++ BracoRobotico.c -o a -lm -lGL -lGLU -lglut

#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

float angulo = 0;
float angulo2 = 0;
float angulo3 = 0;
float angulo4 = 0;
float angulo5 = 10;
float angulo6 = -10;


void display(void)
{
/*  clear all pixels  */
    glClear (GL_COLOR_BUFFER_BIT);

/*	ir para matriz Modelview para podermos fazer as transformações	*/
	glMatrixMode(GL_MODELVIEW);
/*	carregar a identidade para que qualquer transformação em quadros anteriores sejam descartadas	*/
    glLoadIdentity();
    glTranslatef(0,-30.0f,0);

    glPushMatrix();               //Braco
    glScalef(40.0f,10.0f,10.0f);
    glutWireCube(1.0f);
    glPopMatrix();

    glTranslatef(0.0f,10.0f,0);

    glPushMatrix();				//Bolinha
    glScalef(5.0f,5.0f,5.0f);
    glutWireSphere(1.0f,10,10);
    glPopMatrix();

    glRotatef(angulo,0,0,1);	//Rodar o ombro

    glTranslatef(0,15.0f,0);	//antibraco
    glPushMatrix();
    glScalef(10.0f,20.0f,10.0f);
    glutWireCube(1.0f);
    glPopMatrix();


    glTranslatef(0.0f,15.0f,0);	//Bolinha
    glPushMatrix();
    glScalef(5.0f,5.0f,5.0f);
    glutWireSphere(1.0f,10,10);
    glPopMatrix();

    glRotatef(angulo2,0,0,1);	//Rodar o cotovelo

    glTranslatef(0.0f,15.0f,0);	//Braco
    glPushMatrix();
    glScalef(10.0f,20.0f,10.0f);
    glutWireCube(1.0f);
    glPopMatrix();

    glTranslatef(0.0f,15.0f,0);

    glPushMatrix();				//Bolinha
    glScalef(5.0f,5.0f,5.0f);
    glutWireSphere(1.0f,10,10);
    glPopMatrix();

    glRotatef(angulo3,0,0,1);	//Rodar a mao em z
    glRotatef(angulo4,0,1,0);	//Rodar a mao em y

    glTranslatef(0.0f,10.0f,0);	//mao
    glPushMatrix();
    glScalef(30.0f,10.0f,10.0f);
    glutWireCube(1.0f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(angulo5,10.0f,0);	//dedo
    glScalef(10.0f,10.0f,10.0f);
    glutWireCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(angulo6,10.0f,0);	//dedo
    glScalef(10.0f,10.0f,10.0f);
    glutWireCube(1.0f);
    glPopMatrix();

/*  don't wait!
 *  start processing buffered OpenGL routines
 */
    glFlush ();
}

void keyboardCB(int key, int x, int y ){
  switch (key){
    /*case 27: // ESC
      exit (0);
      break;*/
    case GLUT_KEY_LEFT: // ombro
    	if(angulo < 90)
      		angulo = angulo + 5.0;
     	break;
    case GLUT_KEY_RIGHT: // ombro
    	if(angulo > -90)
      		angulo = angulo - 5.0;
      	break;
    case GLUT_KEY_UP: // cotovelo
   		if(angulo2 < 0)
      		angulo2 = angulo2 + 5.0;
      	break;
    case GLUT_KEY_DOWN: // cotovelo
        if(angulo2 > -120)
      		angulo2 = angulo2 - 5.0;
      	break;
    case  GLUT_KEY_F1: // mao z
     	if(angulo3 < 45)
      		angulo3 = angulo3 + 5.0;
      	break;
    case  GLUT_KEY_F2: // mao z
    	if(angulo3 > -45)
      		angulo3 = angulo3 - 5.0;
      	break;
    case  GLUT_KEY_F3: // mao y 
    	if(angulo4 < 90)
      		angulo4 = angulo4 + 5.0;
      	break;
    case  GLUT_KEY_F4: // mao y
    	if(angulo4 > -90)
      		angulo4 = angulo4 - 5.0;
      	break;
    case  GLUT_KEY_F5: // abrir dedos
    	if(angulo5 > 5 && angulo6 < -5){
      		angulo6 = angulo6 + 1.0;
      		angulo5 = angulo5 - 1.0;
      	}
      	break;
    case  GLUT_KEY_F6: // fechar dedos
      	if(angulo5 < 10 && angulo6 > -10){
    		angulo6 = angulo6 - 1.0;
      		angulo5 = angulo5 + 1.0;
      	}
      	break;
  }
  glutPostRedisplay();
}

void init (void)
{
/*  select clearing (background) color       */
    glClearColor (0.0, 0.0, 0.0, 0.0);

/*  initialize viewing values  */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
/*	janela definida de -5 a 5 em X e Y e de -1 a 1 em Z, centralizada nos pontos médios	*/
    glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0f, 100.0f);
}

/*
 *  Declare initial window size, position, and display mode
 *  (single buffer and RGBA).  Open window with "hello"
 *  in its title bar.  Call initialization routines.
 *  Register callback function to display graphics.
 *  Enter main loop and process events.
 */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (800, 800);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Braço robotico");
    init ();
    glutDisplayFunc(display);
    //glutKeyboardFunc(keyboardCB);
    glutSpecialFunc(keyboardCB);
    glutMainLoop();
    return 0;   /* ISO C requires main to return int. */
}
