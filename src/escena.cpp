//#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include "TGATextura.h"
#include <cstdlib>
#include <ctime>
#include <stdio.h>

GLfloat LIGHT_POS = 50.0f; //The length of each side of the cube
GLfloat BOX_HEIGHT = 7.0f; //The height of the box off of the ground
GLfloat FLOOR_SIZE = 25.0f; //The length of each side of the floor

GLfloat Zoom = 1;

GLfloat Luz = 0.1;
GLfloat Transparencia = 150; // reflejo del piso

GLint spinX = 0, spinY = 0;

GLint Rot = 0;
GLfloat Rotacion = 0;
GLfloat adrot = 0;

GLfloat angulo=0;
GLfloat x=0;
GLfloat y=-85; // o a la cantidad q tuve q bajar el trompo
GLfloat z=0;

float EjeX,EjeY,EjeZ = 0;
int lados = 35;
int stacks = 2;
GLfloat spin = 0.0;
GLfloat sube = 0;
float inclinacion = 30;
int rotacion = 0;
bool relleno = false;


//Posición de la luz
GLfloat rX = 0;
GLfloat rY = 7.5;
GLfloat rZ = 0;
//luz keypress
GLint isRightKeyPressed = false;
GLint isLeftKeyPressed  = false;
GLint isUpKeyPressed    = false;
GLint isDownKeyPressed  = false;
///

///direccion del balon
GLfloat bx = -10;
GLfloat by = 1;
GLfloat bz = 15;
bool balonEnMovimiento = false;
int direccionBalon = 0;
float rebote = 12;

bool boolx = false;
bool booly = false;
bool boolz = false;

int LIMITZ = 15;
int LIMITX = 15;

float VELOCIDAD_INIT = 0.3;
float velocidad = VELOCIDAD_INIT;
float REDUCCION = 0.0003;

//////////////////////////////////////////////////////////foto
void image(void) {
     glPushMatrix();
        glTranslatef(0, 0, -0.1);
        glScalef(5,5,0);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glScalef(2,2,2);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,texturas[3].ID);
        glColor4ub(255,255,255,0);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f(-1, -1);  // Bottom Left Of The Texture and Quad
        glTexCoord2f(1, 0); glVertex2f( 1, -1);  // Bottom Right Of The Texture and Quad
        glTexCoord2f(1, 1); glVertex2f( 1,  1);  // Top Right Of The Texture and Quad
        glTexCoord2f(0, 1); glVertex2f(-1,  1);  // Top Left Of The Texture and Quad
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}
//////////////////////////////////////////////////////////Helicoptero

void dibujarCola(){
  GLUquadricObj *Cilindro;
  Cilindro = gluNewQuadric();

  glPushMatrix();
      glColor4ub(0, 0, 255, 0);   //Azul
      gluQuadricDrawStyle(Cilindro, GLU_FILL);
      glTranslatef(-25, 0, 0); //x, y, z
      glRotatef(90, 0, -1, 0);
      gluCylinder(Cilindro, 6, 2, 65, 10, 1);
  glPopMatrix();

  gluDeleteQuadric(Cilindro);

}

void dibujarRotorArriba(){

  GLUquadricObj *cilindroAspaArriba;
  cilindroAspaArriba = gluNewQuadric();

  glPushMatrix();
      glColor4ub(0, 0, 255, 0);   //Azul
      gluQuadricDrawStyle(cilindroAspaArriba, GLU_FILL);
      glTranslatef(0, 25, 0); //x, y, z
      glRotatef(90, 1, 0, 0);
      gluCylinder(cilindroAspaArriba, 2, 2, 10, 5, 1);
  glPopMatrix();

  gluDeleteQuadric(cilindroAspaArriba);
}

void dibujarRotorAtras(){

  GLUquadricObj *cilindroAspaAtras;
  cilindroAspaAtras = gluNewQuadric();

  glPushMatrix();
      glColor4ub(255, 0, 0, 0);   //Azul
      gluQuadricDrawStyle(cilindroAspaAtras, GLU_FILL);
      glTranslatef(-85, 0, -7.5); //x, y, z
      //glRotatef(90, 1, 0, 0);
      gluCylinder(cilindroAspaAtras, 2, 2, 10, 5, 1);
  glPopMatrix();

  gluDeleteQuadric(cilindroAspaAtras);
}

void dibujarAletaDeCola(){
  //cola abajo
  GLUquadricObj *cilindroColaAbajo;
  cilindroColaAbajo = gluNewQuadric();

  glPushMatrix();
      glColor4ub(0, 255, 0, 0);   //Azul
      gluQuadricDrawStyle(cilindroColaAbajo, GLU_FILL);
      glTranslatef(-86, 0, 0); //x, y, z
      glRotatef(90, 1, 0, 0);
      glScalef(1,1,2);
      glRotatef(-45, 0, 1, 0);
      gluCylinder(cilindroColaAbajo, 4, 1, 10, 5, 1);
  glPopMatrix();

  gluDeleteQuadric(cilindroColaAbajo);
  //cola abajo

  //cola lateral
  GLUquadricObj *cilindroColaLateral;
  cilindroColaLateral = gluNewQuadric();

  glPushMatrix();
      glColor4ub(0, 255, 0, 0);   //Azul
      gluQuadricDrawStyle(cilindroColaLateral, GLU_FILL);
      glTranslatef(-86, 0, 0); //x, y, z
      glRotatef(45, 0, 1, 0);
      glRotatef(-45, 0, 1, 0);
      glScalef(1.5,0.7,1.5);
      gluCylinder(cilindroColaLateral, 4, 1, 10, 5, 1);
  glPopMatrix();

  gluDeleteQuadric(cilindroColaLateral);
  //cola lateral

  //cola arriba
  GLUquadricObj *cilindroColaArriba;
  cilindroColaArriba = gluNewQuadric();

  glPushMatrix();
      glColor4ub(0, 255, 0, 0);   //Azul
      gluQuadricDrawStyle(cilindroColaArriba, GLU_FILL);
      glTranslatef(-101, 15, 0); //x, y, z
      glRotatef(90, 1, 0, 0);
      glRotatef(45, 0, 1, 0);
      glScalef(1,1,2);
      gluCylinder(cilindroColaArriba, 1, 4, 10, 5, 1);
  glPopMatrix();

  gluDeleteQuadric(cilindroColaArriba);
  //cola arriba
}

void dibujarPieDerecho(){

  //pie derecho
  GLUquadricObj *cilindroPieDerecho;
  cilindroPieDerecho = gluNewQuadric();

  glPushMatrix();
      glColor4ub(200, 200, 200, 200);
      gluQuadricDrawStyle(cilindroPieDerecho, GLU_FILL);
      glTranslatef(-25, -28, 15); //x, y, z
      glRotatef(90, 0, 1, 0);
      gluCylinder(cilindroPieDerecho, 2, 2, 50, 5, 1);
  glPopMatrix();

  gluDeleteQuadric(cilindroPieDerecho);


  GLUquadricObj *cilindroPieDerechoA;
  cilindroPieDerechoA = gluNewQuadric();

  glPushMatrix();
      glColor4ub(100, 100, 100, 100);
      gluQuadricDrawStyle(cilindroPieDerechoA, GLU_FILL);
      glTranslatef(-10, -15, 10); //x, y, z
      glRotatef(70, 1, 0, 0);
      gluCylinder(cilindroPieDerechoA, 2, 2, 15, 5, 1);
  glPopMatrix();

  gluDeleteQuadric(cilindroPieDerechoA);


  GLUquadricObj *cilindroPieDerechoB;
  cilindroPieDerechoB = gluNewQuadric();

  glPushMatrix();
      glColor4ub(100, 100, 100, 100);
      gluQuadricDrawStyle(cilindroPieDerechoB, GLU_FILL);
      glTranslatef(10, -15, 10); //x, y, z
      glRotatef(70, 1, 0, 0);
      gluCylinder(cilindroPieDerechoB, 2, 2, 15, 5, 1);
  glPopMatrix();

  gluDeleteQuadric(cilindroPieDerechoB);
  //pie derecho
}

void dibujarPieIzquierdo(){
  //pie izquierdo
  GLUquadricObj *cilindroPieIzquierdo;
  cilindroPieIzquierdo = gluNewQuadric();

  glPushMatrix();
      glColor4ub(200, 200, 200, 200);
      gluQuadricDrawStyle(cilindroPieIzquierdo, GLU_FILL);
      glTranslatef(-25, -28, -17); //x, y, z
      glRotatef(90, 0, 1, 0);
      gluCylinder(cilindroPieIzquierdo, 2, 2, 50, 5, 1);
  glPopMatrix();

  gluDeleteQuadric(cilindroPieIzquierdo);

  GLUquadricObj *cilindroPieDerechoA;
  cilindroPieDerechoA = gluNewQuadric();

  glPushMatrix();
      glColor4ub(100, 100, 100, 100);
      gluQuadricDrawStyle(cilindroPieDerechoA, GLU_FILL);
      glTranslatef(-10, -15, -10); //x, y, z
      glRotatef(120, 1, 0, 0);
      gluCylinder(cilindroPieDerechoA, 2, 2, 15, 5, 1);
  glPopMatrix();

  gluDeleteQuadric(cilindroPieDerechoA);


  GLUquadricObj *cilindroPieDerechoB;
  cilindroPieDerechoB = gluNewQuadric();

  glPushMatrix();
      glColor4ub(100, 100, 100, 100);
      gluQuadricDrawStyle(cilindroPieDerechoB, GLU_FILL);
      glTranslatef(10, -15, -10); //x, y, z
      glRotatef(120, 1, 0, 0);
      gluCylinder(cilindroPieDerechoB, 2, 2, 15, 5, 1);
  glPopMatrix();

  gluDeleteQuadric(cilindroPieDerechoB);
  //pie izquierdo
}

void dibujarEsferasDelTrenDeAtterizaje(){

  glColor4ub(255, 0, 0, 255);   //Rojo
  glPushMatrix();
    glTranslatef(25, -28, 15); //x, y, z
    //glScalef(0.7,0.5,0.5);
    glRotatef(90, 0, 1, 0); //rotando la esfera en el eje (x) y z
    glutSolidSphere(3, 20, 5); //tamaño de la esfera, meridianos, paralelos
  glPopMatrix();


  glPushMatrix();
    glTranslatef(-25, -28, 15); //x, y, z
    //glScalef(0.7,0.5,0.5);
    glRotatef(90, 0, 1, 0); //rotando la esfera en el eje (x) y z
    glutSolidSphere(3, 20, 5); //tamaño de la esfera, meridianos, paralelos
  glPopMatrix();


  glPushMatrix();
    glTranslatef(-25, -28, -17); //x, y, z
    //glScalef(0.7,0.5,0.5);
    glRotatef(90, 0, 1, 0); //rotando la esfera en el eje (x) y z
    glutSolidSphere(3, 20, 5); //tamaño de la esfera, meridianos, paralelos
  glPopMatrix();



  glPushMatrix();
    glTranslatef(25, -28, -17); //x, y, z
    //glScalef(0.7,0.5,0.5);
    glRotatef(90, 0, 1, 0); //rotando la esfera en el eje (x) y z
    glutSolidSphere(3, 20, 5); //tamaño de la esfera, meridianos, paralelos
  glPopMatrix();

}


void dibujarCabina(){
  //dibujando la cabina // con una esfera

  glPushMatrix(); //este scope asila ala esfera para que rote individualmente del cubo
    glColor4ub(255, 0, 0, 0);   //Rojo
    //glRotatef(Rotacion, 0, -1, 0); //Para rotar la esfera
    glScalef(0.7,0.5,0.5);
    glRotatef(90, 0, 1, 0); //rotando la esfera en el eje (x) y z
    glutSolidSphere(40, 30, 10); //tamaño de la esfera, meridianos, paralelos
  glPopMatrix();

  glPushMatrix(); //este scope asila ala esfera para que rote individualmente del cubo
    glColor4ub(0, 0, 255, 0);   //Rojo
    //glRotatef(Rotacion, 0, -1, 0); //Para rotar la esfera
    glTranslatef(10,-20,10);
    glScalef(0.02,0.02,0.02);
    glutSolidSphere(20, 30, 10); //tamaño de la esfera, meridianos, paralelos
  glPopMatrix();
}

GLfloat Rotacion2 = 0;
int spped =5;
void dibujarAspas () {
  // aspas de arriba
  glColor4ub(255, 255, 0, 0);   //Verde
  glPushMatrix();
      glRotatef(Rotacion2, 0, 1, 0); //Para rotar la esfera
      glTranslatef(0,23,0);
      glScalef(5,1,150);
      glutSolidCube (1); //tamaño del cubo
  glPopMatrix();

  glPushMatrix();
      glRotatef(Rotacion2, 0, 1, 0); //Para rotar la esfera
      glTranslatef(0,23,0);
      glScalef(150,1,5);
      glutSolidCube (1); //tamaño del cubo
  glPopMatrix();
  // aspas de arriba

  // aspas de atras
  glPushMatrix();
      glTranslatef(-85,0,-5);
      glRotatef(90, 0, 1, 0); //Para rotar la esfera
      glRotatef(Rotacion2, 1, 0, 0); //Para rotar la esfera
      glScalef(1,3,30);
      glutSolidCube (1); //tamaño del cubo
  glPopMatrix();

  glPushMatrix();
      glTranslatef(-85,0,-5);
      glRotatef(90, 0, 1, 0); //Para rotar la esfera
      glRotatef(Rotacion2, 1, 0, 0); //Para rotar la esfera
      glScalef(1,30,3);
      glutSolidCube (1); //tamaño del cubo
  glPopMatrix();
  // aspas de atras
}

void dibujarHelicoptero () {

  /*
  printf("\n");
  printf("x: %.2f\n", rX );
  printf("y: %.2f\n", rY );
  printf("z: %.2f\n", rZ );
  printf("\n");
  */

  glPushMatrix();
    glScalef(0.6,0.6,0.6);

    dibujarCola();

    dibujarAletaDeCola();

    dibujarRotorArriba();

    dibujarRotorAtras();

    dibujarPieDerecho();

    dibujarPieIzquierdo();

    dibujarAspas ();

    dibujarEsferasDelTrenDeAtterizaje();

    dibujarCabina();


  glPopMatrix();
}

////////////////////////////////////////////////////////mesa
void drawTeaPot(){
    glColor4ub(0, 255, 0, 0);
    glutSolidTeapot(5);
}

void glass(){
    glEnable(GL_BLEND);
    glColor4ub(255, 255, 255, 100);
    glPushMatrix();
      glTranslatef(0,2,0);
      glBegin(GL_QUADS); //tamaño del cubo
        glVertex3f(29,0,23);
        glVertex3f(-29,0,23);
        glVertex3f(-29,0,-23);
        glVertex3f(29,0,-23);
      glEnd();
    glPopMatrix();
    glDisable(GL_BLEND);
}

void foot(int x, int z){
    glColor4ub(255, 255, 0, 0);
    glPushMatrix();
      glTranslatef(x,-12,z);
      glScalef(3,25,3);
      glutSolidCube (1); //tamaño del cubo
    glPopMatrix();
}

void marcoA(GLfloat x){
    glColor4ub(255, 255, 0, 0);
    glPushMatrix();
      glTranslatef(x,0,0);
      glScalef(3,3,45);
      glutSolidCube (1); //tamaño del cubo
    glPopMatrix();
}

void marcoB(GLfloat x){
    glColor4ub(255, 255, 0, 0);
    glPushMatrix();
        glRotatef(90,0,1,0);
      glTranslatef(x,0,0);
      glScalef(3,3,60);
      glutSolidCube (1); //tamaño del cubo
    glPopMatrix();
}
///////////////////////////////////////////////////////////////////copa

void cilindro(GLfloat y, GLfloat a, GLfloat b){
  GLUquadricObj *Cilindro;
  Cilindro = gluNewQuadric();

  glPushMatrix();
      gluQuadricDrawStyle(Cilindro, GLU_FILL);
      glTranslatef(0, y, 0); //x, y, z
      glRotatef(90, 1, 0, 0);
      gluCylinder(Cilindro, a, b, 10, 20,1);
  glPopMatrix();

  gluDeleteQuadric(Cilindro);
}

void dibujarCopa(){
    glEnable(GL_BLEND);
    glColor4ub(250, 250, 250, 200);

  int y=90, a=50, b=50;

  for(int i=0;i<=6;i++){
    //printf("n:%d y:%d, a:%d, b:%d \n",i, y, a, b);
    cilindro(y,a,b);
    y -= 10;
    a = b;
    b -= i*i;
    if(a<0)
      a *=-1;
    if(b<0)
      b *=-1;
    if(b>a){
      b = a;
      break;
    }
  }

  for(int i=0;i<=4;i++){
    //printf("n:%d y:%d, a:%d, b:%d \n",i, y, a, b);
    cilindro(y,a,b);
    y -= 10;
  }

  for(int i=0;i<=3;i++){
    b+=i*i*i;
    //printf("n:%d y:%d, a:%d, b:%d \n",i, y, a, b);
    cilindro(y,a,b);
    a =b;
    y -= 10;
  }
  glDisable(GL_BLEND);
}
////////////////////////////////////////////////////////////////////////////PELOTA
GLfloat rotate;
GLfloat cerca = 0;
GLint mTextura = 2;
GLint Meridianos = 0;
void drawBall(void) {

  glPushMatrix();
    glTranslatef(0, 0, -16);
    if(balonEnMovimiento){
      glRotated(spin,boolx,0,0);
      glRotated(spin,0,booly,0);
      glRotated(spin,0,0,boolz);
    }
    glEnable(GL_TEXTURE_2D);
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
    glDisable(GL_TEXTURE_2D);

    gluDeleteQuadric(sphere);
}
////////////////////////////////////////////////////////////////////////////PELOTA

/////////////////////////////////////////////////////////////////////copa

void drawTable(){
    glPushMatrix();
        foot(26,22);
        foot(-26,-22);
        foot(-26,22);
        foot(26,-22);
        marcoA(28.5);
        marcoA(-28.5);
        marcoB(22);
        marcoB(-22);
        glass();

        glPushMatrix();
            glTranslatef(-15,7,15);
            glScalef(0.07,0.07,0.07);
            dibujarCopa();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(15,6,15);
            drawTeaPot();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,7,0);
            glScalef(2,2,2);
            image();
        glPopMatrix();

    glPopMatrix();
}

////////////////////////////////////////////////////////mesa

void drawFloor(){
    GLfloat Lado = 12;
    GLfloat Brick = Lado/8;
    GLint Cuadros = 18;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texturas[0].ID);
    glPushMatrix();
    glTranslatef(-Brick, 0, 0);
    glBegin(GL_QUADS);
    for(int i=0;i<Cuadros;i++){
       for(int j=0;j<Cuadros;j++){
            if((i+j)%2==0){
                glColor4ub(0, 0, 0,Transparencia);
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

void drawUmbrella (void) {

   GLint Lados = 30;

   GLUquadricObj *qobj, *qobj2, *qobj3; //Define el objeto
   qobj = gluNewQuadric();
   qobj2 = gluNewQuadric();
   qobj3 = gluNewQuadric();
   gluQuadricDrawStyle(qobj, GLU_FILL); //Se dibuja un trompo
   gluQuadricDrawStyle(qobj2, GLU_LINE); //Se dibuja un trompo
   gluQuadricDrawStyle(qobj3, GLU_LINE); //Se dibuja un trompo

    GLfloat ambient[]   = { 0.20, 0.05, 0.05, 1.0 };
    GLfloat diffuse[]   = { 0.89, 0.64, 0.14, 1.0 };
    GLfloat specular[]  = { 0.00, 0.00, 0.00, 1.0 };
    GLfloat emission[]  = { 0.00, 0.00, 0.00, 1.0 };
    GLfloat shininess[] = { 128.0 };

    glMaterialfv( GL_FRONT, GL_AMBIENT,   ambient );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,   diffuse );
    glMaterialfv( GL_FRONT, GL_SPECULAR,  specular );
    glMaterialfv( GL_FRONT, GL_EMISSION,  emission );
    glMaterialfv( GL_FRONT, GL_SHININESS, shininess );

   glPushMatrix();
     glTranslatef(0, -3.7 ,0);
     glRotatef(45, 1, 0, 0);
     glColor4ub(255, 0, 0, 0); //Capa roja
     gluCylinder(qobj, 0, 3.9, 1, 11, 1);
     glColor4ub(255,255,255,0);
     glTranslated(0,0,0.02);
     gluCylinder(qobj2, 0, 3.9, 1, 11, 1);
     glColor4ub(0,0,0,0);
     glPushMatrix();
        glTranslated(0,-0.1,0.6);
        gluCylinder(qobj3,2,0,1,11,1);
     glPopMatrix();
     glColor4ub(100, 100, 100, 0); //Palo gris
     gluCylinder(qobj, 0.05, 0.05, 4.7, 10, 1);
   glPopMatrix();

   gluDeleteQuadric(qobj);

}

void cilindro(GLfloat y, GLfloat a, GLfloat b, GLfloat ancho, int red, int green, int blue, int alpha){
  GLUquadricObj *Cilindro;
  Cilindro = gluNewQuadric();

  glPushMatrix();
      glColor4ub(red, green, blue, alpha);   //Azul
      if(b == 0 && ancho == 0){
        gluQuadricTexture(Cilindro, true);
      }
      gluQuadricDrawStyle(Cilindro, GLU_FILL);
      glTranslatef(0, y, 0); //x, y, z
      glRotatef(90, 1, 0, 0);
      gluCylinder(Cilindro, a, b, ancho, 20,1);
  glPopMatrix();

  gluDeleteQuadric(Cilindro);

}

void dibujarTrompo(){

  
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,texturas[1].ID);
  
  cilindro(115, 22, 0, 0, 255,255,255,0);
  
  
  glDisable(GL_TEXTURE_2D);

  cilindro(115, 22, 22, 10, 255,0,0,0);
  cilindro(105, 22, 37, 5, 200,0,0,0);
  cilindro(100, 37, 47, 10, 255,0,0,0);
  
  int y=90, a=48, b=50, ancho=10;

  for(int i=0;i<=8;i++){
    //printf("n:%d y:%d, a:%d, b:%d \n",i, y, a, b);
    if(i%2==0){
      cilindro(y,a,b,ancho, 255,0,0,0);  
    }else{
      cilindro(y,a,b,ancho, 200,0,0,0);  
    }
    
    y -= 10;
    a = b;

    if(b-i*2>0){
      b -= i*2;  
    }else{
      //printf("----n:%d y:%d, a:%d, b:%d \n",i, y, a, b);
      b -= 5;
      cilindro(y,a,b, ancho-6, 100,100,100,100);
      //printf("saliendo \n");
      y -=4;
      break;
    }
  }

  //printf("afuera \n");
  //printf("y:%d, a:%d, b:%d \n", y, a, b);

  cilindro(y,3,5, ancho-5, 100,100,100,100);
  cilindro(y-5,5,1, ancho-5, 100,100,100,100);
}


void drawScene() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat diffuseMaterial[] = { 1.0, 1.0, 1.0, 0.0 };
  GLfloat lmodel_ambient[] = { Luz, Luz, Luz, Luz};

  GLfloat lightColor[] = {2.0f, 2.0f, 2.0f, 2.0f};

  GLfloat lightPos[] = {rX, rY, rZ, 1};

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glTranslatef(0, 0, -40);
  glRotatef(30, 1, 0, 0);

  glScalef(Zoom, Zoom, Zoom);

  glRotatef(spinX, 1, 0, 0);
  glRotatef(spinY, 0, 1, 0);

  

  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialf(GL_FRONT, GL_SHININESS, 64.0f);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

  glPushMatrix();
    glColor4ub(255, 255, 0, 1);
    glTranslatef(rX, rY-1, rZ);
    glutSolidSphere(0.3, 50, 50);
  glPopMatrix();

  /*glPushMatrix();
    glColor4ub(255, 255, 0, 0);
    glTranslatef(x, LIGHT_POS, 0);
    glutSolidSphere(0.3, 50, 50);
  glPopMatrix();*/
  //cuatro esquinas //**
  glPushMatrix();
    glColor4ub(255, 0, 0, 1);
    glTranslatef(15, 0, 15);
    glutSolidSphere(0.3, 50, 50);
  glPopMatrix();
  glPushMatrix();
    glColor4ub(255, 0, 0, 1);
    glTranslatef(-15, 0, -12);
    glutSolidSphere(0.3, 50, 50);
  glPopMatrix();
  glPushMatrix();
    glColor4ub(255, 0, 0, 1);
    glTranslatef(-15, 0, 15);
    glutSolidSphere(0.3, 50, 50);
  glPopMatrix();
  glPushMatrix();
    glColor4ub(255, 0, 0, 1);
    glTranslatef(15, 0, -12);
    glutSolidSphere(0.3, 50, 50);
  glPopMatrix();
  //cuatro esquinas //**
  

  glPushMatrix();
    glTranslatef(-9,3.9,-8);
    glScalef(0.15,0.15,0.15);
    drawTable();
  glPopMatrix();

    glPushMatrix();
        glTranslatef(8,7,-8);
        drawUmbrella();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(x, 0, z);
        glRotated(spin,0,1,0);
        glRotated(inclinacion,1,0,0);
        glScalef(0.03,0.03,0.03);

        dibujarTrompo();
    glPopMatrix();

  glPushMatrix();
    glTranslatef(bx,by,bz);
    printf("balon x:%.2f, y:%.2f, z:%.2f, rebote:%.2f velocidad:%.2f \n", bx, by, bz, rebote, velocidad);
    glScalef(0.4,0.4,0.4);
    drawBall();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(rX,rY,rZ);
    glRotated(135,0,1,0);
    glRotated(Rot,0,1,0);
    glScalef(0.1,0.1,0.1);
    dibujarHelicoptero();
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
    glTranslatef(0, 0, 0);

    glPushMatrix();
    glTranslatef(-9,3.9,-8);
    glScalef(0.15,0.15,0.15);
    drawTable();
  glPopMatrix();

    glPushMatrix();
        glTranslatef(8,7,-8);
        drawUmbrella();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(x, 0, z);
        glRotated(spin,0,1,0);
        glRotated(inclinacion,1,0,0);
        glScalef(0.03,0.03,0.03);

        dibujarTrompo();
    glPopMatrix();

  glPushMatrix();
    //glRotated(180,boolx,booly,boolz);
    glTranslatef(bx,by,bz);
    glScalef(0.4,0.4,0.4);
    drawBall();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(rX,rY,rZ);
    glRotated(135,0,1,0);
    glRotated(Rot,0,1,0);
    glScalef(0.1,0.1,0.1);
    dibujarHelicoptero();
  glPopMatrix();


    
  glPopMatrix();

  glDisable(GL_STENCIL_TEST); //Disable using the stencil buffer
  //Blend the floor onto the screen
  glEnable(GL_BLEND);

  //Aquí se dibuja el piso que refleja
  drawFloor();
  glDisable(GL_BLEND);

  glutSwapBuffers();
}

int getRandom(int n){
  
  return std::rand() % n + 1;
}

void handleKeypress(unsigned char key, int x, int y) {
  switch (key) {
    case 27: //Escape key
         exit(0);
    break;

    case 'r': //giro del helicoptero

      Rot +=2;
      if(Rot>360){
        Rot = 0;
      }
        
    break;

    case 'R': // giro del helicoptero en centido contrario

    Rot -=2;
      if(Rot<0){
        Rot = 360;
      }

    break;

    case 'l': //Luz
         Luz -= 0.005;
         if (Luz < 0)
             Luz = 1;
    break;

    case 'z':
        if (Zoom > 0)
            Zoom -= 0.01;
    break;

    case 'Z':
        if (Zoom < 10)
            Zoom += 0.01;
    break;

    case 't': //Sube
         if (++Transparencia > 255)
             Transparencia = 0;
    break;

    case 'e':
        ++rY;
    break;

    case 'q':
      
      if (rY > 2.50)
        --rY;

    break;

    case 'b':
      balonEnMovimiento = true;
      direccionBalon = getRandom(5);
      rebote = 12;
      velocidad=VELOCIDAD_INIT;
    break;
  }
}

void handleSpecialKeypress(int key, int x, int y) {

 switch (key) {
    case GLUT_KEY_LEFT:
         isLeftKeyPressed = true;
         if (!isRightKeyPressed) {
             if(rX >= -10){
                --rX;
                
             }

         }
    break;

    case GLUT_KEY_RIGHT:
         isRightKeyPressed = true;
         if (!isLeftKeyPressed) {
             if (rX <= 10){
                ++rX;
             }
         }
    break;

    case GLUT_KEY_UP:
         isUpKeyPressed = true;
         if (!isDownKeyPressed) {
             if (rZ >= -10)
                --rZ;
         }
             
    break;

    case GLUT_KEY_DOWN:
         isDownKeyPressed = true;
         if (!isUpKeyPressed) {
          if (rZ <= 10)
                ++rZ;
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

  if(!cargarTGA("./data/Piso5.tga", &texturas[0]) ||
     !cargarTGA("./data/Star.tga", &texturas[1]) ||
     !cargarTGA("./data/Bola.tga", &texturas[2]) ||
     !cargarTGA("./data/yoG.tga", &texturas[3])){
        printf("Error cargando textura");
        exit(0);
     }
}

void handleResize(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (float)w/ (float)h, 1.0, 200.0);
}


void moveball(){
  if(balonEnMovimiento){
    velocidad-=REDUCCION;
    switch(direccionBalon){
      case 1:
        if(boolx)
          bx+= velocidad;
        else
          bx-= velocidad;
      break;

      case 2:
        if(boolz)
          bz+= velocidad;
        else
          bz-= velocidad;
      break;

      case 3:
        if(boolx)
          bx+= velocidad;
        else
          bx-= velocidad;
        if(boolz)
          bz+= velocidad;
        else
          bz-= velocidad;
      break;
      case 4:
      if(boolx)
          bx+= velocidad;
        else
          bx-= velocidad;
        if(boolz)
          bz+= velocidad;
        else
          bz-= velocidad;
       break;
       case 5:break;
    }

    if(bx > LIMITX)
      boolx = false;

    if(bz > 20)
      boolz = false;

    if(bx < -LIMITX)
      boolx = true;
    
    if(bz < -5)
      boolz = true;


    if(rebote > 1){

      if(booly)
        by+=velocidad;
      else
        by-=velocidad;

      if(by > rebote)
        booly=false;
        
      if(by < 2){
        rebote--;
        booly=true;
      }

    }else{
      by=1;
      balonEnMovimiento = false;
      rebote = 12;
      velocidad=VELOCIDAD_INIT;
    }
  }
}

void spinDisplay(void) {
 Rotacion2 += 5;
 adrot += 1.05;
 rotate += 2.5;

    GLfloat r;
     if(angulo<25){
        angulo+=0.02;
     }

     r =10- pow(2.7182,0.1*angulo);
     if(0<r){
        x = r* cos(angulo);
        z = r * sin(angulo);
     }

    if (inclinacion > 0)
       inclinacion -= 0.01;


   spin += 5;
   if (spin >360)
       spin = 0;


  if (sube < 78)
    sube += 0.01;

  moveball();

glutPostRedisplay(); //Vuelve a dibujar
}

void mouse(int button, int state, int x, int y) {
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN) {
            glutIdleFunc(spinDisplay);
         }
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

// g++ src/escena.cpp -o escena -lGL -lGLU -lglut
int main(int argc, char** argv) {
  std::srand(std::time(0));

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
  glutInitWindowSize(600, 600);

  glutCreateWindow("escena con multiples objetos en movimiento");
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
