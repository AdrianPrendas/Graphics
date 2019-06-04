/*
Con "t" cambia la textura
    "H" acerca la esfera
    "h" aleja  la esfera
    "m" agrega o quita los paralelos y los meridianos
*/
//#include <windows.h>
#include <GL/glut.h>
#include "TGATextura.h"
#include <string.h>

GLfloat rotate;
GLfloat cerca = 0;
GLint mTextura = 0;
GLint Meridianos = 0;

void drawBall(void) {

  glPushMatrix();

  glTranslatef(0, 0, -16);

  glRotatef(90, 1, 0, 0);
  glRotatef(rotate, 0, 0, 1);

  glBindTexture(GL_TEXTURE_2D,texturas[mTextura].ID);

  GLUquadricObj *sphere=NULL;
  sphere = gluNewQuadric();

  gluQuadricDrawStyle(sphere, GLU_FILL);
  gluQuadricTexture(sphere, true);
  gluQuadricNormals(sphere, GLU_SMOOTH);

  glColor4ub(255, 255, 255, 0);

  gluSphere(sphere, 3+cerca, 24, 24);

  if (Meridianos == 1) {
      glColor4ub(25, 112, 112, 255);
      glutWireSphere(3.01+cerca, 24, 24);
  }

  glColor4ub(255, 255, 255, 0);

  glPopMatrix();

  gluDeleteQuadric(sphere);
}

//El cielo tiene una textura con estrellas colocada sobre un cuadro en el fondo
void drawSky() {
  glBindTexture(GL_TEXTURE_2D,texturas[2].ID); //Fondo estrellado

   glPushMatrix();
     glTranslatef(0, 0, -20);
     glScalef(9, 9, 0);
     glBegin(GL_QUADS);
      glTexCoord2f(0, 0); glVertex2f(-1, -1);  // Bottom Left Of The Texture and Quad
      glTexCoord2f(1, 0); glVertex2f( 1, -1);  // Bottom Right Of The Texture and Quad
      glTexCoord2f(1, 1); glVertex2f( 1,  1);  // Top Right Of The Texture and Quad
      glTexCoord2f(0, 1); glVertex2f(-1,  1);  // Top Left Of The Texture and Quad
     glEnd();
   glPopMatrix();
}

void drawScene() {

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);

  glLoadIdentity();

  glEnable(GL_TEXTURE_2D);  //Activa la textura

  drawSky();
  drawBall();

  glDisable(GL_TEXTURE_2D); //Desactiva la textura

  glutSwapBuffers();
}

void handleKeypress(unsigned char key, int x, int y) {
  switch (key) {

    case 27: //Escape key
      exit(0);

    case 'H':
         cerca += 0.05;
    break;

    case 'h':
         cerca -= 0.05;
    break;

    case 'm':
         if (Meridianos == 0)
             Meridianos = 1;
         else
             Meridianos = 0;;
    break;

    case 't':
         if (mTextura == 0)
             mTextura = 1;
         else
             mTextura = 0;;
    break;

  }
}

void initRendering() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  if(!cargarTGA("./data/Earth4.tga", &texturas[0]) ||
     !cargarTGA("./data/Bola.tga", &texturas[1]) ||
     !cargarTGA("./data/Estrellas2.tga", &texturas[2]) ) {
     printf("Error cargando textura\n");
     exit(0); // Cargamos la textura y chequeamos por errores
    }
}

void handleResize(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

void update(int value)
{
    rotate+=0.5f;

    if(rotate>360.f)
    {
        rotate-=360;
    }

    glutPostRedisplay();
    glutTimerFunc(25,update,0);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(600, 600);
  glutCreateWindow("Tierra - Textura");
  initRendering();
  glutTimerFunc(25,update,0);
  glutDisplayFunc(drawScene);
  glutKeyboardFunc(handleKeypress);
  glutReshapeFunc(handleResize);
  glutMainLoop();
  return 0;
}