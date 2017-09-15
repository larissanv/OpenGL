//g++ opengl.cpp -o a -lm -lGL -lGLU -lglut

#include <GL/glut.h>
#include <math.h>

void drawCircle(float cx, float cy, float r, int num_segments) { 
	glBegin(GL_LINE_LOOP); 
	for(int ii = 0; ii < num_segments; ii++) 
	{ 
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 

		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 

		glVertex2f(x + cx, y + cy);//output vertex 

	} 
	glEnd(); 
}


void display(void){
  glMatrixMode(GL_MODELVIEW);
  glClear (GL_COLOR_BUFFER_BIT);
  glBegin(GL_LINE_LOOP); //parede
    glColor3f(1.0,1.0,0.0);
    glVertex3f(0.25,0.25,0.0);
    glColor3f(0.0,1.0,1.0);
    glVertex3f(0.75,0.25,0.0);
    glColor3f(1.0,0.0,1.0);
    glVertex3f(0.75,0.75,0.0);
    glColor3f(1.0,1.0,1.0);
    glVertex3f(0.25,0.75,0.0);
  glEnd();
  glBegin(GL_LINE_LOOP);  //janela
    glColor3f(1.0,1.0,0.0);
    glVertex3f(0.55,0.55,0.0);
    glColor3f(0.0,1.0,1.0);
    glVertex3f(0.70,0.55,0.0);
    glColor3f(1.0,0.0,1.0);
    glVertex3f(0.70,0.70,0.0);
    glColor3f(1.0,1.0,1.0);
    glVertex3f(0.55,0.70,0.0);
  glEnd();
  glBegin(GL_LINE_LOOP);  //janela
    glColor3f(1.0,1.0,0.0);
    glVertex3f(0.30,0.55,0.0);
    glColor3f(0.0,1.0,1.0);
    glVertex3f(0.45,0.55,0.0);
    glColor3f(1.0,0.0,1.0);
    glVertex3f(0.45,0.70,0.0);
    glColor3f(1.0,1.0,1.0);
    glVertex3f(0.30,0.70,0.0);
  glEnd();
  glBegin(GL_LINE_LOOP);  //triangulo do telhado
    glColor3f(1.0,0.5,0.0);
    glVertex3f(0.1,0.75,0.0);
    glColor3f(0.0,1.0,1.0);
    glVertex3f(0.175,0.90,0.0);
    glColor3f(1.0,0.0,1.0);
    glVertex3f(0.25,0.75,0.0);
  glEnd();
  glBegin(GL_LINE_LOOP);  //telhado
    glColor3f(1.0,1.0,0.0);
    glVertex3f(0.25,0.75,0.0);
    glColor3f(0.0,1.0,1.0);
    glVertex3f(0.75,0.75,0.0);
    glColor3f(1.0,0.0,1.0);
    glVertex3f(0.75,0.90,0.0);
    glColor3f(1.0,1.0,1.0);
    glVertex3f(0.175,0.90,0.0);
  glEnd();
  glBegin(GL_LINE_LOOP);  //parede do lado
    glColor3f(1.0,1.0,0.0);
    glVertex3f(0.1,0.75,0.0);
    glColor3f(0.0,1.0,1.0);
    glVertex3f(0.1,0.25,0.0);
    glColor3f(1.0,0.0,1.0);
    glVertex3f(0.25,0.25,0.0);
    glColor3f(1.0,1.0,1.0);
    glVertex3f(0.25,0.75,0.0);
  glEnd();
  glBegin(GL_LINE_LOOP);  //porta
    glColor3f(1.0,1.0,0.0);
    glVertex3f(0.12,0.68,0.0);
    glColor3f(0.0,1.0,1.0);
    glVertex3f(0.12,0.25,0.0);
    glColor3f(1.0,0.0,1.0);
    glVertex3f(0.23,0.25,0.0);
    glColor3f(1.0,1.0,1.0);
    glVertex3f(0.23,0.68,0.0);
  glEnd();
  glBegin(GL_LINE_LOOP);  //chamine
    glColor3f(1.0,1.0,0.0);
    glVertex3f(0.60,0.90,0.0);
    glColor3f(0.0,1.0,1.0);
    glVertex3f(0.65,0.90,0.0);
    glColor3f(1.0,0.0,1.0);
    glVertex3f(0.65,0.94,0.0);
    glColor3f(1.0,1.0,1.0);
    glVertex3f(0.60,0.94,0.0);
  glEnd();
  glBegin(GL_LINE_LOOP);  //chamine
    glColor3f(1.0,1.0,0.0);
    glVertex3f(0.58,0.94,0.0);
    glColor3f(0.0,1.0,1.0);
    glVertex3f(0.67,0.94,0.0);
    glColor3f(1.0,0.0,1.0);
    glVertex3f(0.67,0.99,0.0);
    glColor3f(1.0,1.0,1.0);
    glVertex3f(0.58,0.99,0.0);
  glEnd();

	glColor3f (1.0, 1.0, 1.0);
	drawCircle(0.175, 0.8, 0.038, 5);	//janela circular

  glFlush();
}

void init(void){
  glClearColor(0.0,0.0,0.0,0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);
}

void keyboardCB( unsigned char key, int x, int y ){
  switch (key){
    case 27: // ESC
      exit (0);
      break;
  }
  glutPostRedisplay();
}

int main(int argc, char** argv){
	  glutInit(&argc, argv);
	  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	  glutInitWindowSize(500,500);
	  glutInitWindowPosition(300,300);
	  glutCreateWindow("Casa");
	  init();
		glutDisplayFunc(display);
glutKeyboardFunc(keyboardCB);
	  glutMainLoop();

	  return 0;
}
