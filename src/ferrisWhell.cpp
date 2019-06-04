#include <GL/gl.h>
#include <math.h>
#include "TGATextura.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
GLint spinX, spinY;
GLfloat ortho = 0.0;
GLfloat VelocidadGiro = 0.08;
GLint Transparencia = 200;

GLfloat orbitDegrees = 0; //Gira la escena

GLint Rot = 0;
GLfloat Rotacion = 0;
GLfloat Pausa = 0;

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


void dibujarBanca(int n){
GLUquadricObj *Cubo;
Cubo = gluNewQuadric();
glPushMatrix();
glTranslatef(-70,-63,-160);
glScalef(3,3,10);
glRotatef(90,0,1,0);

glColor4ub(179, 128, 80, 1.0);
glPushMatrix();
glPushMatrix();
glTranslatef(-9,-5.5,-5);
glScalef(0.3,3,0.2);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glTranslatef(-5,-5.5,-5);
glScalef(0.3,3,0.2);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glTranslatef(-9,-4.5,-8);
glScalef(0.3,5,0.2);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glTranslatef(-5,-4.5,-8);
glScalef(0.3,5,0.2);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glTranslatef(-5,-4.1,-6.5);
glScalef(0.3,0.2,3);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glTranslatef(-9,-4.1,-6.5);
glScalef(0.3,0.2,3);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glTranslatef(-7,-4.1,-5);
glScalef(4,0.2,0.3);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glTranslatef(-7,-4.1,-8);
glScalef(4,0.2,0.3);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glTranslatef(-7,-2,-8);
glScalef(4.2,0.2,0.3);
glutSolidCube(1);
glPopMatrix();


glPushMatrix();
glColor4ub(66, 37, 0,200);
glTranslatef(-7,-4,-6.5);
glScalef(4.2,0.1,3.2);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glTranslatef(-7,-3,-8);
glScalef(3.7,2,0.1);
glutSolidCube(1);
glPopMatrix();

glPopMatrix();
glPopMatrix();
gluDeleteQuadric(Cubo);

glPushMatrix();
  glScalef(5,5,5);
  glTranslatef(0,-8,-20);
  DrawLamp();
glPopMatrix();

}

void drawArmazon(){

  GLUquadricObj *Tubo;
  Tubo = gluNewQuadric();
  gluQuadricNormals(Tubo, GLU_SMOOTH);

  GLfloat largo = 12;
  GLint angulo = 35;


  glPushMatrix();
    glTranslatef(0, 70, 0);
    glRotatef(angulo, 0,1,0);
    glRotatef(-angulo, 1,0,0);
    gluCylinder(Tubo, 0.5 , 0.5, largo, 10, 6);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0, 70, 0);
    glRotatef(-angulo, 0,1,0);
    glRotatef(-angulo, 1,0,0);
    gluCylinder(Tubo, 0.5 , 0.5, largo, 10, 6);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0, 70, 0);
    glRotatef(-angulo-110, 0,1,0);
    glRotatef(-angulo, 1,0,0);
    gluCylinder(Tubo, 0.5 , 0.5, largo, 10, 6);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0, 70, 0);
    glRotatef(angulo+110, 0,1,0);
    glRotatef(-angulo, 1,0,0);
    gluCylinder(Tubo, 0.5 , 0.5, largo, 10, 6);
  glPopMatrix();

}

void DrawCabina(){

  glPushMatrix();
    glTranslatef(0, 0, 0);
    glRotatef(90, 0,1,0);
    glPushMatrix();
      glTranslatef(0,-13,8);
      drawArmazon();
      glPushMatrix();
        glTranslatef(0,153,0);
        glRotatef(180, 1,0,0);
        drawArmazon();
      glPopMatrix();
    glPopMatrix();

  

    glPushMatrix();
      glRotatef(90,0,1,0);
      //glTranslatef(-8,65,0);
      glTranslatef(-8,78,0);
      glColor4ub(120, 120,120, 250);   //Rojo
      glRotatef(90, 0, 1, 0);
      glScalef(0.3, 0.3, 0.3);
      glutWireSphere(25, 10, 5);
    glPopMatrix();
  glPopMatrix();
}




void DrawBase(){


  glPushMatrix();
    glColor4ub(255, 255, 0, 0);
      glTranslatef(0,-90,60);
      glScalef(5,1,60);
      glutSolidCube (1); //tamaño del cubo
  glPopMatrix();

  glPushMatrix();
    glColor4ub(255, 255, 0, 0);
      glTranslatef(0,-89,30);
      glScalef(5,1,5);
      glutSolidCube (1); //tamaño del cubo
  glPopMatrix();

  glPushMatrix();
    glColor4ub(255, 255, 0, 0);
      glTranslatef(0,-88,25);
      glScalef(5,1,5);
      glutSolidCube (1); //tamaño del cubo
  glPopMatrix();

  glPushMatrix();
    glColor4ub(255, 255, 0, 0);
      glTranslatef(0,-87,20);
      glScalef(5,1,5);
      glutSolidCube (1); //tamaño del cubo
  glPopMatrix();

  glPushMatrix();
    glColor4ub(255, 255, 0, 0);
      glTranslatef(0,-86,15);
      glScalef(5,1,5);
      glutSolidCube (1); //tamaño del cubo
  glPopMatrix();

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   //Patas
   GLUquadricObj *pata;
   pata = gluNewQuadric();
   gluQuadricNormals(pata, GLU_SMOOTH);
   GLint Lados = 20; //de los tubos
   GLint largo = 105;
   //1
   glPushMatrix();
    glTranslatef(0, 0, 25);
    glRotatef(75, 1, 0, 0);  //angulo, x,y,z
    glRotatef(20, 0, -1, 0); //angulo, x,y,z
    glColor4ub(0, 0,200, 0);   //Rojo
    gluCylinder(pata, 2, 10, largo, Lados, 2); //base,top,height,slices,stacks
   glPopMatrix();
   //2
   glPushMatrix();
    glTranslatef(0, 0, 25);
    glRotatef(75, 1, 0, 0);   //angulo, x,y,z
    glRotatef(-20, 0, -1, 0); //angulo, x,y,z
    glColor4ub(0, 0,200, 0);   //Rojo
    gluCylinder(pata, 2, 10, largo, Lados, 2); //base,top,height,slices,stacks
   glPopMatrix();

   for(int i = 0, j=-5; i< 10;i++, j-=2){

      glPushMatrix();
        glTranslatef(j, -10-(i*5), 26+i+2);
        glColor4ub(0, 0,200, 0);   //Rojo
        glRotatef(90, 0, 1,0);
        gluCylinder(pata, 2, 2, 10+3*i+i, Lados, 2); //base,top,height,slices,stacks
      glPopMatrix();
   }

   

}

void DrawFerrisWhell(void)
{
   GLUquadricObj *Tubo;
   Tubo = gluNewQuadric();
   gluQuadricNormals(Tubo, GLU_SMOOTH);

   GLint Lados = 20; //de los tubos
   GLint LadosRueda = 24;

   GLfloat Grosor = 0.7;
   glColor4ub(255, 0, 0, 0); //Color del objeto

   glPushMatrix();
  glRotatef(Rotacion, 0, 0, 1); //Rotaci�n de la rueda
  glPushMatrix();
    

    //Rueda de lado
    glPushMatrix();
      glColor4ub(0, 250, 0, 0); //verde
      glutSolidTorus(Grosor + 0.2, 64, 6, LadosRueda);
      glTranslatef(0, 0, -1.2);
      glutSolidTorus(Grosor + 0.2, 4, 6, LadosRueda);
    glPopMatrix();

    //Rueda de lado
    glPushMatrix();
      glColor4ub(0, 250, 0, 0); //verde
      glTranslatef(0, 0, 16);
      glutSolidTorus(Grosor + 0.2, 64, 6, LadosRueda);
      glTranslatef(0, 0, 1.2);
      glutSolidTorus(Grosor + 0.2, 4, 6, LadosRueda);
    glPopMatrix();

    glPushMatrix(); //Rueda �nica
      glColor4ub(233, 189, 21, 0); //amarillo
      glTranslatef(0, 0, 8);
      glutSolidTorus(Grosor + 0.2, 58, 6, LadosRueda);
    glPopMatrix();

    glPushMatrix(); //Eje central
      glTranslatef(0, 0, -8);
      gluCylinder(Tubo, 3 * Grosor, 3 * Grosor, 32, Lados, 6);
    glPopMatrix();

   // CABINAS
   //1
    glPushMatrix();
      glTranslatef(0, 0, 0);
      //glRotatef(75, 1, 0, 0);  //angulo, x,y,z
      glColor4ub(79, 130, 255, 1);
      gluCylinder(Tubo, 0.8, 0.8, 20, Lados, 2); //base,top,height,slices,stacks
    glPopMatrix();


  
  glPopMatrix();
   //#####################################################
   // Dibujar las cosas que no se mueven

   //Bola derecha
    glPushMatrix();
      glColor4ub(255, 0, 0, 1);
      glTranslatef(0, 0, 25);
      glutSolidSphere(3, 20, 20);
    glPopMatrix();
    //Bola izquierda
    glPushMatrix();
      glColor4ub(255, 255, 0, 1);
      glTranslatef(0, 0, -11);
      glutSolidSphere(3, 20, 20);
    glPopMatrix();


   for(int i=0;i<360;i+=15){
    glPushMatrix(); //Rayos
    glColor4ub(200, 0, 0, 1);
    glRotatef(90, 0, 1, 0);
    glPushMatrix(); //Rayos
        glTranslatef(2, 0, 0);
        glRotatef(i, 1, 0, 0);
        glRotatef(16, 0, -1, 0);
        gluCylinder(Tubo, Grosor-0.2, Grosor-0.2, 67, 6, Lados); //Eje central
     glPopMatrix();
     glPopMatrix();
    }

    for(int i=0;i<360;i+=15){
    glPushMatrix(); //Rayos
      glRotatef(90, 0, 1, 0);
      glPushMatrix(); //Rayos
        glColor4ub(200, 0, 0, 1);
        glTranslatef(-18, 0, 0);
        glRotatef(i, 1, 0, 0);
        glRotatef(16, 0, 1, 0);
        gluCylinder(Tubo, Grosor-0.2, Grosor-0.2, 67, 6, Lados); //Eje central
      glPopMatrix();

      glPushMatrix();
      glColor4ub(100, 100, 100, 1);
        glTranslatef(-15.5, 0, 0);
        glRotatef(i, 1, 0, 0);
        DrawCabina();
      glPopMatrix();

     glPopMatrix();
     }



   //#####################################################
   gluDeleteQuadric(Tubo);
   


   

   glPopMatrix();
}

void drawLake(void)
{
   GLUquadricObj *Disco;
   Disco = gluNewQuadric();
   gluQuadricDrawStyle(Disco, GLU_FILL);
   gluQuadricNormals(Disco, GLU_SMOOTH);

   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texturas[0].ID);
   gluQuadricTexture(Disco, GL_TRUE);

   glColor4ub(80, 85, 200, Transparencia); //Color del lago

   glPushMatrix();
   glTranslatef(0, -82, 8);
   glRotatef(-90, 1, 0, 0);
   gluDisk(Disco, 0, 80, 50, 5);
   glPopMatrix();

   glDisable(GL_TEXTURE_2D);

   gluDeleteQuadric(Disco);
}

//Draws the floor
void drawFloor()
{
   GLint Lado = 200;
   glColor4ub(0, 112, 0, 0); //line color green

   glBegin(GL_QUADS);
   glVertex3f(-Lado, -83, -Lado); //Punto 1
   glVertex3f(Lado, -83, -Lado);  //Punto 2
   glVertex3f(Lado, -83, Lado);   //Punto 3
   glVertex3f(-Lado, -83, Lado);  //Punto 4
   glEnd();
}

void dibujar2bancas(int grados, int n){
  glPushMatrix();
    glRotatef(grados,0, 1, 0);
    glPushMatrix();
          glTranslatef(0,-65,120);
          glRotatef(90,0,1,0);
          glScalef(0.2,0.2,0.2);
          dibujarBanca( n);
      glPopMatrix();

         glPushMatrix();
          glTranslatef(30,-65,120);
          glRotatef(90,0,1,0);
          glScalef(0.2,0.2,0.2);
          dibujarBanca( n);
      glPopMatrix();
    glPopMatrix();
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   glOrtho(-100.0 + ortho, 100.0 - ortho, -100.0 + ortho, 100.0 - ortho, -500 + ortho, 500.0 - ortho); //Izq, Der, Abajo, Arriba, Cerca, lejos

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   glRotatef(spinX, 1, 0, 0);
   glRotatef(spinY, 0, 1, 0);
   //printf("x = %d Y = %d\n", spinX, spinY);

   /*
   gluLookAt(Camera[0], Camera[1], Camera[2], //look from camera XYZ
          0, 0, 30, // look at the origin
          0, 1, 0); // positive Y up vector
*/

   glRotatef(orbitDegrees, 0, 1, 0); // orbit the Y axis

   glPushMatrix();
    glTranslatef(0,10,0);
    DrawFerrisWhell();
    DrawBase();
    glPushMatrix();
      glTranslatef(0,0,15);
      glRotatef(180,0,1,0);
      DrawBase();
    glPopMatrix();
   glPopMatrix();


   dibujar2bancas(0, 0);
   dibujar2bancas(45, 1);
   dibujar2bancas(90, 2);
   dibujar2bancas(135, 3);
   dibujar2bancas(180, 4);
   dibujar2bancas(225, 5);
   dibujar2bancas(270, 6);
   dibujar2bancas(315, 7);
   dibujar2bancas(360, 8);
   


   


   glEnable(GL_STENCIL_TEST);      //Enable using the stencil buffer
   glColorMask(0, 0, 0, 0);        //Disable drawing colors to the screen
   glDisable(GL_DEPTH_TEST);       //Disable depth testing
   glStencilFunc(GL_ALWAYS, 1, 1); //Make the stencil test always pass

   //Make pixels in the stencil buffer be set to 1 when the stencil test passes
   glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

   //Aqu� se dibuja el laguito
   drawLake();

   glColorMask(1, 1, 1, 1); //Enable drawing colors to the screen
   glEnable(GL_DEPTH_TEST); //Enable depth testing

   //Make the stencil test pass only when the pixel is 1 in the stencil buffer
   glStencilFunc(GL_EQUAL, 1, 1);
   glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //Make the stencil buffer not change

   //Draw the cube, reflected vertically, at all pixels where the stencil
   //buffer is 1
   glPushMatrix();
   glScalef(1, -1, 1);
   glTranslatef(0, 164, 0);
   //Aqu� se dibujan los objetos que se van a reflejar

    glPushMatrix();
    glTranslatef(0,10,0);
    DrawFerrisWhell();
    DrawBase();
    glPushMatrix();
      glTranslatef(0,0,15);
      glRotatef(180,0,1,0);
      DrawBase();
    glPopMatrix();
   glPopMatrix();

   glPopMatrix();

   glDisable(GL_STENCIL_TEST); //Disable using the stencil buffer
   //Blend the floor onto the screen
   glEnable(GL_BLEND);

   //Aqu� se dibuja el laguito que refleja
   drawLake();
   glDisable(GL_BLEND);

   drawFloor(); //Aqu� se dibuja el piso para que no afecte el reflejo del laguito

   glutSwapBuffers();
}

void spinDisplay(void)
{
   if (Rot == 1)
      if (Rotacion < 360)
      {
         Rotacion += VelocidadGiro;
      }
      else
      {
         if (++Pausa > 100)
         {
            Rotacion = 0;
            Pausa = 0;
         }
      }

   //orbitDegrees += 0.05; //Para girar la escena

   glutPostRedisplay(); //Vuelve a dibujar
}

void init(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0); //Colores para iniciar la ventana (Fondo)
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   
   glEnable(GL_NORMALIZE);
   glEnable(GL_COLOR_MATERIAL);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   //Carga los archivos con las texturas
   if (!cargarTGA("data/sky.tga", &texturas[0]))
   {
      printf("Error cargando textura\n");
      exit(0); // Cargamos la textura y chequeamos por errores
   }
}

void reshape(int w, int h)
{
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   glOrtho(-100.0, 100.0, -100.0, 100.0, -500.0, 500.0); //Izq, Der, Abajo, Arriba, Cerca, lejos
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

void reshape1(int w, int h)
{
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

void handleKeypress(unsigned char key, int x, int y)
{
   switch (key)
   {
   case 27: //Escape key
      exit(0);
      break;

   case 'r': //La esfera gira
      if (Rot == 1)
         Rot = 0;
      else
         Rot = 1;
    break;

   case 'M':
      VelocidadGiro += 0.01;
      break;

   case 'm':
      VelocidadGiro -= 0.01;
      break;

   case 'H':
      ortho += 0.5;
      break;

   case 'h':
      ortho -= 0.5;
      break;

   case 't':
      if (++Transparencia == 256)
         Transparencia = 0;
      break;

   case 'v':
      spinX = 0;
      spinY = 0;
      break;

   case 'V':
      spinX = 90;
      spinY = 90;
      break;

   case 'p':
      spinX = 200;
      spinY = 270;
      break;
   }
}

void mouseMotion(int x, int y)
{
   spinX = y;
   spinY = x;
}

void mouse(int button, int state, int x, int y)
{
   switch (button)
   {
   case GLUT_LEFT_BUTTON:
      if (state == GLUT_DOWN)
         glutIdleFunc(spinDisplay);
      break;

   case GLUT_RIGHT_BUTTON:
      //      case GLUT_MIDDLE_BUTTON:
      if (state == GLUT_DOWN)
         glutIdleFunc(NULL);
      break;

   default:
      break;
   }
}

/*
 *  Request double buffer display mode.
 *  Register mouse input callback functions
 */
int main(int argc, char **argv)
{
   glutInit(&argc, argv); //Inicializa la librer�a GLUT y negocia una sesi�n
                          //con el sistema de ventanas
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
   //GLUT_DOUBLE doble buffer  GLUT_RGB = GLUT_RGBA

   glutInitWindowSize(800, 800); //Tama�o de la ventana 600 x 600

   glutInitWindowPosition(100, 100); //Posici�n de la ventana en la pantalla

   glutCreateWindow("Ferris Wheel 4.0"); //Crea la ventana y le pone la etiqueta

   init(); //Ejecuta el m�todo "init"

   glutDisplayFunc(display); //Ejecuta el m�todo "display"
   glutKeyboardFunc(handleKeypress);
   glutReshapeFunc(reshape); //Ejecuta el m�todo "reshape"
   glutMouseFunc(mouse);     //Activa los controles del mouse
   glutMotionFunc(mouseMotion);
   glutMainLoop(); //Repite el main indefinidamente (�Animaci�n!)
   return 0;       /* ANSI C requires main to return int. */
}