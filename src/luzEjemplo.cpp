//#include <windows.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>

#include <math.h>
#include "TGATextura.h"

GLfloat LIGHT_POS = 20.0f; //The length of each side of the cube
GLfloat BOX_HEIGHT = 7.0f; //The height of the box off of the ground

GLint Lados = 30;

GLint isRightKeyPressed = false;
GLint isLeftKeyPressed  = false;
GLint isUpKeyPressed    = false;
GLint isDownKeyPressed  = false;

GLint ArrowColor;

GLfloat Zoom = 1;

GLfloat Luz = 0.5;
GLfloat Transparencia = 200;

GLfloat aZh = 0;

GLfloat _angle = 0;

GLfloat spinX=0.0, spinY=0.0;

//Dirección
GLint dx = 0; GLint dy = -1; GLint dz = 0;

//Posición de la luz
GLfloat rX = 0;
GLfloat rY = 7.5;
GLfloat rZ = 0;

void drawFloor(){
    GLfloat Lado = 12;
    GLfloat Brick = Lado/8;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texturas[0].ID);

    glPushMatrix();
    glTranslatef(-Brick, 0, -Brick);

    glBegin(GL_QUADS);
    for(int i=0;i<18;i++){
       for(int j=0;j<18;j++){
            if((i+j)%2==0){
                glColor4ub(25, 25, 112,Transparencia);
            }else{
                glColor4ub(112, 112, 112,Transparencia);
            }
                glTexCoord2f(0, 0); glVertex3f(-Lado+(i*Brick), 0, -Lado+(j*Brick));
                glTexCoord2f(1, 0); glVertex3f(-(Lado-Brick)+(i*Brick), 0, -Lado+(j*Brick));
                glTexCoord2f(1, 1); glVertex3f(-(Lado-Brick)+(i*Brick), 0, -(Lado-Brick)+(j*Brick));
                glTexCoord2f(0, 1); glVertex3f(-Lado+(i*Brick), 0, -(Lado-Brick)+(j*Brick));
        }
    }
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}


void DrawLamp (void) {
   GLUquadricObj *qobj; //Define el objeto
   qobj = gluNewQuadric();

   gluQuadricDrawStyle(qobj, GLU_FILL);

   glPushMatrix();
     glColor4ub(112, 112, 112, 0); //Rojo

     glPushMatrix();
       glTranslatef(0, 1.3, 0);
       glRotatef(90, 1, 0, 0);
       gluCylinder(qobj, 0.2, 1, 1.5, 8, 1);
     glPopMatrix();

     gluQuadricDrawStyle(qobj, GLU_LINE);
     glPushMatrix();
       glTranslatef(0, -0.2, 0);
       glRotatef(90, 1, 0, 0);
       gluCylinder(qobj, 1, 0.2, 0.5, 8, 1);
     glPopMatrix();

     gluQuadricDrawStyle(qobj, GLU_FILL);

     glPushMatrix();
       glTranslatef(0, -0.5, 0);
       glRotatef(90, 1, 0, 0);
       gluCylinder(qobj, 0.2, 0.2, 5.5, 30, 1);
     glPopMatrix();

     glPushMatrix();
       glTranslatef(0, -5.5, 0);
       glRotatef(90, 1, 0, 0);
       gluCylinder(qobj, 0.2, 0.8, 1.5, 8, 1);
     glPopMatrix();

   glPopMatrix();

   gluDeleteQuadric(qobj);
//glutWireCube (4);
}

void drawScene() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  // ================ LUZ
  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat diffuseMaterial[] = { 1.0, 1.0, 1.0, 0.0 };
  GLfloat lmodel_ambient[] = { Luz, Luz, Luz, Luz };

  GLfloat lightColor[] = {1.0f, 1.0f, 0.0f, 0.0f}; //Amarillo

  GLfloat lightPos[] = {rX, rY, rZ, 1};

  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
  //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialf(GL_FRONT, GL_SHININESS, 65.0f);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

   GLfloat spot_direction[] = { dx, dy, dz };
   glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0); //Grados
   glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
   glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0);
   //printf("dx=%d dy=%d dz=%d \n", dx, dy, dz);
   // ============= LUZ

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glTranslatef(0, 0, -40);
  glRotatef(30, 1, 0, 0);

  glScalef(Zoom, Zoom, Zoom);

  glRotatef(spinX, 1, 0, 0);
  glRotatef(spinY, 0, 1, 0);

  glPushMatrix();
    glColor4ub(255, 255, 0, 1);
    glTranslatef(rX, rY, rZ);
    glutSolidSphere(0.3, 50, 50);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0, BOX_HEIGHT, 0);
    //Aquí debe llamar a los objetos
    DrawLamp ();

  glPopMatrix();

  glEnable(GL_STENCIL_TEST); //Enable using the stencil buffer
  glColorMask(0, 0, 0, 0); //Disable drawing colors to the screen
  glDisable(GL_DEPTH_TEST); //Disable depth testing
  glStencilFunc(GL_ALWAYS, 1, 1); //Make the stencil test always pass

  //Make pixels in the stencil buffer be set to 1 when the stencil test passes
  glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

  //Aquí se dibuja el piso
  drawFloor();

  glColorMask(1, 1, 1, 1); //Enable drawing colors to the screen
  glEnable(GL_DEPTH_TEST); //Enable depth testing

  //Make the stencil test pass only when the pixel is 1 in the stencil buffer
  glStencilFunc(GL_EQUAL, 1, 1);
  glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //Make the stencil buffer not change

  //Draw the cube, reflected vertically, at all pixels where the stencil
  //buffer is 1
  glPushMatrix();
    glScalef(1, -1, 1);
    glTranslatef(0, BOX_HEIGHT, 0);
    //Aquí se dibujan los objetos que se van a reflejar
    DrawLamp();

  glPushMatrix();
    glColor4ub(255, 255, 0, 1);
    glTranslatef(rX, rY-7.5, rZ);
    glutSolidSphere(0.3, 50, 50);
  glPopMatrix();

  glPopMatrix();

  glDisable(GL_STENCIL_TEST); //Disable using the stencil buffer
  //Blend the floor onto the screen
  glEnable(GL_BLEND);

//  glColor4ub(0, 0, 255, 100);
  //Aquí se dibuja el piso que refleja
  drawFloor();
  glDisable(GL_BLEND);

  glutSwapBuffers();
}

void spinDisplay(void) {

   _angle += 0.002;
   if (_angle > 360) {
       _angle -= 360;
   }

   glutPostRedisplay(); //Vuelve a dibujar
}

void handleKeypress(unsigned char key, int x, int y) {

  switch (key) {
    case 27: //Escape key
         exit(0);
    break;

    case 'F': //Posición de la luz
        ++LIGHT_POS;
    break;

    case 'f': //Posición de la luz
        --LIGHT_POS;
    break;

    case 'l': //Luz
         Luz -= 0.01;
         if (Luz < 0)
             Luz = 1;
    break;

    case 'A':
        dx += 1;
    break;
    case 'a':
        dx -= 1;
    break;
    case 'B':
        dy += 1;
    break;
    case 'b':
        dy -= 1;
    break;
    case 'C':
        dz += 1;
    break;
    case 'c':
        dz -= 1;
    break;

    case 'h':
        if (Zoom > 0)
            Zoom -= 0.01;
    break;

    case 'H':
        if (Zoom < 10)
            Zoom += 0.01;
    break;

    case 't': //Sube
         if (++Transparencia > 255)
             Transparencia = 0;
    break;
  }
}

void handleSpecialKeypress(int key, int x, int y) {

 switch (key) {
    case GLUT_KEY_LEFT:
         isLeftKeyPressed = true;
         if (!isRightKeyPressed) {
             if(rX > -25)
                --rX;
         }
    break;

    case GLUT_KEY_RIGHT:
         isRightKeyPressed = true;
         if (!isLeftKeyPressed) {
             if (rX < 25)
                ++rX;
         }
    break;

    case GLUT_KEY_UP:
         isUpKeyPressed = true;
         if (!isDownKeyPressed) {
             if (rY < 25)
                ++rY;
         }
    break;

    case GLUT_KEY_DOWN:
         isDownKeyPressed = true;
         if (!isUpKeyPressed) {
             if (rY > 0)
                --rY;
         }
    break;
 }
}

void handleSpecialKeyReleased(int key, int x, int y) {
 switch (key) {
 case GLUT_KEY_LEFT:
      isLeftKeyPressed = false;
 break;

 case GLUT_KEY_RIGHT:
      isRightKeyPressed = false;
 break;

 case GLUT_KEY_UP:
      isUpKeyPressed = false;
 break;

 case GLUT_KEY_DOWN:
      isDownKeyPressed = false;
 break;

 }
}

void init() {
  glClearColor(0, 0, 0, 0); //Fondo negro en toda la escena
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  //Carga los archivos con las texturas
  if(!cargarTGA("data/Piso.tga", &texturas[0]) ||
     !cargarTGA("data/Star.tga", &texturas[1])) {
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

void mouse(int button, int state, int x, int y) {
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
            glutIdleFunc(spinDisplay);
         break;

      case GLUT_RIGHT_BUTTON:
      case GLUT_MIDDLE_BUTTON:
         if (state == GLUT_DOWN)
            glutIdleFunc(NULL);
         break;

      default:
         break;
   }
}

void mouseMotion(int x, int y) {
     spinX = y;
     spinY = x;
     //printf("X %5.2f Y %5.2f\n", spinX, spinY);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
  glutInitWindowSize(600, 600);

  glutCreateWindow("Luz spot");
  init();

  glutDisplayFunc(drawScene);
  glutKeyboardFunc(handleKeypress);
  glutReshapeFunc(handleResize);
  glutMouseFunc(mouse); //Activa los controles del mouse
  glutMotionFunc(mouseMotion);

  glutSpecialFunc(handleSpecialKeypress);
  glutSpecialUpFunc(handleSpecialKeyReleased);

  glutMainLoop();

  return 0;
}