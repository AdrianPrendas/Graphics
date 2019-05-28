
/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */
//#include <windows.h>
#include <GL/gl.h>
#include <math.h>
#include "TGATextura.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

GLfloat LIGHT_POS = 50.0f;  //The length of each side of the cube
GLfloat BOX_HEIGHT = 7.0f;  //The height of the box off of the ground
GLfloat FLOOR_SIZE = 25.0f; //The length of each side of the floor

GLfloat Zoom = 1;

GLfloat Luz = 0.4;
GLfloat LuzHeli = 0.9;
GLfloat Transparencia = 150; // reflejo del piso

GLint spinX = 0, spinY = 0;

GLint Rot = 0;
GLfloat Rotacion = 0;

//FROM TROMPO
//GLfloat Rotacion = 0;
GLfloat RotacionDisparo = 20;
GLfloat zoom = 0.05;
GLfloat spin = 1;
GLfloat f = 1;
GLfloat xH = 130;
GLfloat yH = -70;
GLfloat zH = 5;
GLfloat xT = 0;
GLfloat yT = -70;
GLfloat zT = 0;
GLfloat inclinacion = 30;
GLint dLaser = 0;
GLint dBola = 0;
GLint transparenciaObj = 150;
GLint alambrada = true;

// from bola
GLfloat rotate;
GLfloat rotateB = 0;
GLfloat cerca = 0;
GLint mTextura = 2;
GLint Meridianos = 0;
GLfloat xB = 0;
GLfloat yB = 0;
GLfloat zB = 0;

// PARA LUZ
//Posici�n
GLfloat rX = 0;
GLfloat rY = 7.5;
GLfloat rZ = 0;
//Direcci�n
GLint dx = 0;
GLint dy = -1;
GLint dz = 0;

GLint isRightKeyPressed = false;
GLint isLeftKeyPressed = false;
GLint isUpKeyPressed = false;
GLint isDownKeyPressed = false;

void drawBall(void)
{

    glPushMatrix();

    glTranslatef(0 + xB, -6 + yB, -10);

    glRotatef(0, 1, 0, 0);
    glRotatef(rotateB, 0, 0, 1);

    glBindTexture(GL_TEXTURE_2D, texturas[3].ID);

    GLUquadricObj *sphere = NULL;
    sphere = gluNewQuadric();

    gluQuadricDrawStyle(sphere, GLU_FILL);
    gluQuadricTexture(sphere, true);
    gluQuadricNormals(sphere, GLU_SMOOTH);

    glColor4ub(255, 255, 255, 0);

    gluSphere(sphere, 1 + cerca, 24, 24);

    if (Meridianos == 1)
    {
        glColor4ub(25, 112, 112, 255);
        glutWireSphere(1.01 + cerca, 24, 24);
    }

    glColor4ub(255, 255, 255, 0);
    glTranslatef(0 + xB, -3.9 + yB, -11);
    glPopMatrix();

    gluDeleteQuadric(sphere);
}

void copa(void)
{
    //CREAMOS EL CILINDRO
    GLUquadricObj *Cilindro;
    Cilindro = gluNewQuadric();
    //capa 0
    glPushMatrix();
    if (alambrada == 1)
    {
        gluQuadricDrawStyle(Cilindro, GLU_FILL);
    }
    else
    {
        gluQuadricDrawStyle(Cilindro, GLU_LINE);
    }
    glEnable(GL_BLEND);                                //Enable blending.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set blending function.
    glColor4ub(125, 232, 213, transparenciaObj);       //gris
    //capa 1
    glPushMatrix();
    glColor4ub(232, 44, 12, transparenciaObj);
    //gluQuadricDrawStyle(Cilindro, GLU_LINE);
    //glTranslatef(0,0,0); //x, y, z
    glRotatef(90, -1, 0, 0); //angulo, x,y,z
    gluCylinder(Cilindro, 22, 20, 10, 50, 10);
    glPopMatrix();
    //capa 2
    glPushMatrix();
    glColor4ub(232, 44, 12, transparenciaObj);
    //gluQuadricDrawStyle(Cilindro, GLU_FILL);
    glRotatef(90, -1, 0, 0); //angulo, x,y,z
    glTranslatef(0, 0, -10); //x, y, z
    gluCylinder(Cilindro, 24, 22, 10, 50, 10);
    glPopMatrix();
    //capa 3
    glPushMatrix();
    glColor4ub(232, 44, 12, transparenciaObj);
    //gluQuadricDrawStyle(Cilindro, GLU_LINE);
    glRotatef(90, -1, 0, 0); //angulo, x,y,z
    glTranslatef(0, 0, -20); //x, y, z
    gluCylinder(Cilindro, 24, 24, 10, 50, 10);
    glPopMatrix();
    //capa 4
    glPushMatrix();
    glColor4ub(232, 44, 12, transparenciaObj);
    //gluQuadricDrawStyle(Cilindro, GLU_FILL);
    glRotatef(90, -1, 0, 0); //angulo, x,y,z
    glTranslatef(0, 0, -35); //x, y, z
    gluCylinder(Cilindro, 20, 24, 15, 50, 10);
    glPopMatrix();
    //capa 5
    glPushMatrix();
    glColor4ub(232, 44, 12, transparenciaObj);
    //gluQuadricDrawStyle(Cilindro, GLU_LINE);
    glRotatef(90, -1, 0, 0); //angulo, x,y,z
    glTranslatef(0, 0, -40); //x, y, z
    gluCylinder(Cilindro, 17, 20, 5, 50, 10);
    glPopMatrix();
    //capa 6
    glPushMatrix();
    glColor4ub(232, 44, 12, transparenciaObj);
    //gluQuadricDrawStyle(Cilindro, GLU_FILL);
    glRotatef(90, -1, 0, 0); //angulo, x,y,z
    glTranslatef(0, 0, -45); //x, y, z
    gluCylinder(Cilindro, 14, 17, 5, 50, 10);
    glPopMatrix();
    //capa 7
    glPushMatrix();
    glColor4ub(232, 44, 12, transparenciaObj);
    //gluQuadricDrawStyle(Cilindro, GLU_LINE);
    glRotatef(90, -1, 0, 0); //angulo, x,y,z
    glTranslatef(0, 0, -50); //x, y, z
    gluCylinder(Cilindro, 10, 14, 5, 50, 10);
    glPopMatrix();
    //capa 8
    glPushMatrix();
    glColor4ub(232, 44, 12, transparenciaObj);
    //gluQuadricDrawStyle(Cilindro, GLU_FILL);
    glRotatef(90, -1, 0, 0); //angulo, x,y,z
    glTranslatef(0, 0, -55); //x, y, z
    gluCylinder(Cilindro, 6, 10, 5, 50, 10);
    glPopMatrix();
    //capa 9
    glPushMatrix();
    glColor4ub(232, 44, 12, transparenciaObj);
    //gluQuadricDrawStyle(Cilindro, GLU_LINE);
    glRotatef(90, -1, 0, 0); //angulo, x,y,z
    glTranslatef(0, 0, -60); //x, y, z
    gluCylinder(Cilindro, 3, 6, 5, 50, 10);
    glPopMatrix();
    //capa 10
    glPushMatrix();
    glColor4ub(232, 44, 12, transparenciaObj);
    //gluQuadricDrawStyle(Cilindro, GLU_FILL);
    glRotatef(90, -1, 0, 0); //angulo, x,y,z
    glTranslatef(0, 0, -90); //x, y, z
    gluCylinder(Cilindro, 3, 3, 30, 50, 10);
    glPopMatrix();
    //capa 11
    glPushMatrix();
    glColor4ub(232, 44, 12, transparenciaObj);
    //gluQuadricDrawStyle(Cilindro, GLU_LINE);
    glRotatef(90, -1, 0, 0); //angulo, x,y,z
    glTranslatef(0, 0, -95); //x, y, z
    gluCylinder(Cilindro, 6, 3, 5, 50, 10);
    glPopMatrix();
    //capa 12
    glPushMatrix();
    glColor4ub(232, 44, 12, transparenciaObj);
    //gluQuadricDrawStyle(Cilindro, GLU_FILL);
    glRotatef(90, -1, 0, 0); //angulo, x,y,z
    glTranslatef(0, 0, -98); //x, y, z
    gluCylinder(Cilindro, 10, 6, 3, 50, 10);
    glPopMatrix();
    //capa 13
    glPushMatrix();
    glColor4ub(232, 44, 12, transparenciaObj);
    //gluQuadricDrawStyle(Cilindro, GLU_LINE);
    glRotatef(90, -1, 0, 0);  //angulo, x,y,z
    glTranslatef(0, 0, -101); //x, y, z
    gluCylinder(Cilindro, 15, 10, 3, 50, 10);
    glPopMatrix();
    //capa 14
    glPushMatrix();
    glColor4ub(232, 144, 12, transparenciaObj);
    //gluQuadricDrawStyle(Cilindro, GLU_FILL);
    glRotatef(90, -1, 0, 0);  //angulo, x,y,z
    glTranslatef(0, 0, -102); //x, y, z
    gluCylinder(Cilindro, 0, 15, 1, 50, 10);
    glPopMatrix();
    glDisable(GL_BLEND);
    glPopMatrix();
}

void drawTeapot(void)
{
    glColor4ub(0, 112, 0, 255);
    glPushMatrix();
    glTranslatef(-8, -2.5, 5); //x, y(altura), z
    glutSolidTeapot(1);
    glPopMatrix();
}

void drawOctahedron(void)
{
    glColor4ub(0, 112, 0, 255);
    glPushMatrix();
    glutSolidOctahedron();
    glPopMatrix();
}

void drawVidrioMesa(void)
{
    glPushMatrix();
    glEnable(GL_BLEND);                                //Enable blending.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set blending function.
    glColor4ub(125, 232, 213, 100);                    //gris
    glBegin(GL_QUADS);
    glVertex3f(-5, -2.9, 3);
    glVertex3f(-5, -2.9, 13);
    glVertex3f(-11, -2.9, 13);
    glVertex3f(-11, -2.9, 3);
    glEnd();
    glDisable(GL_BLEND);
    glPopMatrix();
}

void mesa(void)
{
    GLfloat altura = -3.5;

    glPushMatrix();
    glColor4ub(232, 72, 32, 0);
    glTranslatef(-8, altura, 3); //x, y(altura), z
    glScaled(5, 1, 1);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glColor4ub(232, 72, 32, 0);
    glTranslatef(-8, altura, 13); //x, y(altura), z
    glScaled(5, 1, 1);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glColor4ub(232, 72, 32, 0);
    glTranslatef(-11, altura, 8); //x, y(altura), z
    glScaled(1, 1, 11);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glColor4ub(232, 72, 32, 0);
    glTranslatef(-5, altura, 8); //x, y(altura), z
    glScaled(1, 1, 11);
    glutSolidCube(1);
    glPopMatrix();
    //patas
    glPushMatrix();
    glColor4ub(232, 72, 32, 0);
    glTranslatef(-5, -5, 3); //x, y(altura), z
    glScaled(1, 4, 1);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glColor4ub(232, 72, 32, 0);
    glTranslatef(-11, -5, 3); //x, y(altura), z
    glScaled(1, 4, 1);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glColor4ub(232, 72, 32, 0);
    glTranslatef(-5, -5, 13); //x, y(altura), z
    glScaled(1, 4, 1);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glColor4ub(232, 72, 32, 0);
    glTranslatef(-11, -5, 13); //x, y(altura), z
    glScaled(1, 4, 1);
    glutSolidCube(1);
    glPopMatrix();

    drawTeapot();
    glPushMatrix();
    glTranslatef(-8, -1.0, 8); //x, y, z
    glScaled(0.02, 0.02, 0.02);
    copa();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-8, -4.8, 8);
    drawOctahedron();
    glPopMatrix();
}

void aletas(GLUquadricObj *Cabina)
{
    glColor4ub(255, 255, 255, 0); //Azul
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glRotatef(-20, 0, 1, 0);
    glTranslatef(-48, 2, 2);
    glScalef(1, 0.3, 1);
    gluCylinder(Cabina, 2, 3, 15, 10, 1);
    glPopMatrix();
    //-------------------------
    glPushMatrix();
    glRotatef(-20, 0, 1, 0);
    //glRotatef(90,-1,-1,-1);
    glTranslatef(-48, 2, 2);
    glScalef(1, 0.3, 1);
    gluCylinder(Cabina, 2, 3, 15, 10, 1);
    glPopMatrix();
}

void DibujaEsfera(void)
{

    GLUquadricObj *Cilindro;
    Cilindro = gluNewQuadric();

    glPushMatrix();
    glColor4ub(0, 0, 255, 0); //Azul
    gluQuadricDrawStyle(Cilindro, GLU_FILL);
    glTranslatef(-25, 0, 0); //x, y, z
    glRotatef(90, 0, -1, 0);
    gluCylinder(Cilindro, 6, 3, 40, 10, 1);
    glPopMatrix();

    gluDeleteQuadric(Cilindro);

    glColor4ub(255, 0, 0, 0); //Rojo
    glPushMatrix();
    //glRotatef(Rotacion, 0, -10, 0); //Para rotar la esfera
    glRotatef(90, 0, 1, 0); //rota el polo en el primer parametro
    //glutWireSphere(30, 50, 10);
    glTranslated(0, 0, 0); //mover la esfera
    glScaled(0.7, 0.7, 1);
    glutWireSphere(30, 50, 10);
    glPopMatrix();

    aletas(Cilindro);
}

void patas(void)
{

    GLUquadricObj *Cilindro;
    Cilindro = gluNewQuadric();
    //*********************************************
    glPushMatrix();
    glColor4ub(232, 44, 12, 1);
    gluQuadricDrawStyle(Cilindro, GLU_FILL);
    glTranslatef(22, -30, 20); //x, y, z
    glRotatef(90, 0, -1, 0);
    gluCylinder(Cilindro, 2, 2, 50, 10, 10);
    glPopMatrix();
    glPushMatrix();
    glColor4ub(232, 44, 12, 1);
    gluQuadricDrawStyle(Cilindro, GLU_FILL);
    glTranslatef(10, -15, 5); //x, y, z
    glRotatef(-45, -1, 0, 0);
    gluCylinder(Cilindro, 2, 2, 20, 10, 1);
    glPopMatrix();
    glPushMatrix();
    glColor4ub(232, 44, 12, 1);
    gluQuadricDrawStyle(Cilindro, GLU_FILL);
    glTranslatef(-15, -15, 5); //x, y, z
    glRotatef(-45, -1, 0, 0);
    gluCylinder(Cilindro, 2, 2, 20, 10, 50);
    glPopMatrix();
    //******************************************************
    //SEGUNDA PATA
    glPushMatrix();
    glColor4ub(232, 44, 12, 1);
    gluQuadricDrawStyle(Cilindro, GLU_FILL);
    glTranslatef(22, -30, -20); //x, y, z
    glRotatef(90, 0, -1, 0);
    gluCylinder(Cilindro, 2, 2, 50, 10, 10);
    glPopMatrix();
    glPushMatrix();
    glColor4ub(100, 44, 12, 1);
    gluQuadricDrawStyle(Cilindro, GLU_FILL);
    glTranslatef(10, -15, -10); //x, y, z
    glRotatef(238, -1, 0, 0);
    gluCylinder(Cilindro, 2, 2, 20, 10, 1);
    glPopMatrix();
    glPushMatrix();
    glColor4ub(100, 44, 12, 1);
    gluQuadricDrawStyle(Cilindro, GLU_FILL);
    glTranslatef(-15, -15, -10); //x, y, z
    glRotatef(238, -1, 0, 0);
    gluCylinder(Cilindro, 2, 2, 20, 10, 1);
    glPopMatrix();

    gluDeleteQuadric(Cilindro);
}

void DibujaCubo(void)
{
    glColor4ub(0, 255, 105, 0); //Verde
    glPushMatrix();
    glTranslatef(-65, 0, 3);       //mover la cruz
    glRotatef(Rotacion, 0, 0, -1); //Para rotar la cruz
    glRotatef(90, 0, 1, 90);
    glScaled(25, 5, 1);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-65, 0, 3);       //mover la cruz
    glRotatef(Rotacion, 0, 0, -1); //Para rotar la cruz
    glRotatef(90, 0, 1, 90);
    glScaled(5, 25, 1);
    glutSolidCube(1);
    glPopMatrix();
    ///*************
    glPushMatrix();
    glRotatef(Rotacion, 0, -10, 0); //Para rotar la cruz
    glRotatef(0, 0, 0, 0);
    glTranslatef(0, 22, 0); //mover la cruz
    glScaled(65, 1, 5);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glRotatef(Rotacion, 0, -20, 0); //Para rotar la cruz
    glRotatef(0, 0, 0, 0);
    glTranslatef(0, 22, 0); //mover la cruz
    glScaled(5, 1, 65);
    glutSolidCube(1);
    glPopMatrix();
    patas();
}

void hacerLuz()
{
    // ================ LUZ
    glPushMatrix();
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat diffuseMaterial[] = {1.0, 1.0, 1.0, 0.0};
    GLfloat lmodel_ambient[] = {Luz, Luz, Luz, Luz};

    GLfloat lightColor[] = {1.0f, 1.0f, 0.0f, 0.0f}; //Amarillo

    GLfloat lightPos[] = {rX, rY, rZ, 1};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 65.0f);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

    GLfloat spot_direction[] = {dx, dy, dz};
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0); //Grados
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0);
    //printf("dx=%d dy=%d dz=%d \n", dx, dy, dz);
    // ============= LUZ
    glPushMatrix();
    glColor4ub(255, 255, 0, 1);
    glTranslatef(rX, rY, rZ);
    glutSolidSphere(1, 50, 50);
    glPopMatrix();
    glPopMatrix();
}

void DrawLamp(void)
{
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
    hacerLuz();
    //glutWireCube (4);
}

void Helicoptero(void)
{

    glPushMatrix();
    glScaled(0.1, 0.1, 0.1);
    glScalef(0.6, 0.6, 0.6);
    glTranslatef(xH, yH, zH); //x, y, z
    DibujaEsfera();
    DibujaCubo();
    // Poner luz
    hacerLuz();
    if (dLaser == 1)
    {
        glLineWidth(10);
        glBegin(GL_LINES);
        glColor4ub(255, 161, 0, 0); //amarillo
        glTranslatef(5, 5, 5);
        glVertex3f(200, -30, -20);
        glVertex3f(0, -30, -15); //L�nea Norte a Sur
        glVertex3f(200, -30, 15);
        glVertex3f(0, -30, 15); //L�nea Norte a Sur
        glEnd();
    }
    glLineWidth(1);

    if (dBola == 1)
    {
        glPushMatrix();
        glTranslatef(20, -30, -20);
        glutWireSphere(5, 50, 10);
        glPopMatrix();
    }

    glPopMatrix();
}

void tropo(void)
{
    //CREAMOS EL CILINDRO
    GLUquadricObj *Cilindro;
    Cilindro = gluNewQuadric();

    glPushMatrix();
    glScalef(zoom, zoom, zoom);

    glTranslatef(xT, yT, zT); //x, y, z
    gluQuadricDrawStyle(Cilindro, GLU_FILL);
    glRotatef(Rotacion, 0, -10, 0); //Para rotar la esfera

    glRotatef(inclinacion, -1, 0, 0); //angulo, x,y,z

    //capa -4 tapa 1
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturas[1].ID);
    gluQuadricTexture(Cilindro, GL_TRUE);

    glPushMatrix();
    glColor4ub(20, 220, 120, 1);
    glRotatef(90, -1, 0, 0); //angulo, x,y,z
    glTranslatef(0, 0, 35);  //x, y, z
    //gluCylinder(Cilindro, 5, 0, 7, 50, 10);
    gluDisk(Cilindro, 0, 6, 5, 1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //capa -3
    glPushMatrix();
    glColor4ub(232, 44, 12, 1);
    glRotatef(90, -1, 0, 0); //angulo, x,y,z
    glTranslatef(0, 0, 25);  //x, y, z
    gluCylinder(Cilindro, 5, 5, 10, 50, 10);
    glPopMatrix();
    //capa -2 amarillo
    glPushMatrix();
    glColor4ub(0, 1, 250, 1);
    glRotatef(90, -1, 0, 0);  //angulo, x,y,z
    glTranslatef(0, 0, 24.5); //x, y, z
    gluCylinder(Cilindro, 12, 0, 2, 5, 10);
    glPopMatrix();
    //capa -2 amarillo
    glPushMatrix();
    glColor4ub(232, 244, 12, 1);
    glRotatef(90, -1, 0, 0); //angulo, x,y,z
    glTranslatef(0, 0, 24);  //x, y, z
    gluCylinder(Cilindro, 12, 0, 2, 50, 10);
    glPopMatrix();
    //capa -1
    glPushMatrix();
    glColor4ub(232, 44, 12, 1);
    glRotatef(90, -1, 0, 0); //angulo, x,y,z
    glTranslatef(0, 0, 20);  //x, y, z
    gluCylinder(Cilindro, 15, 12, 4, 50, 10);
    glPopMatrix();
    //capa 0
    glPushMatrix();
    glColor4ub(232, 44, 12, 1);
    glRotatef(90, -1, 0, 0); //angulo, x,y,z
    glTranslatef(0, 0, 10);  //x, y, z
    gluCylinder(Cilindro, 20, 15, 10, 50, 10);
    glPopMatrix();
    //capa 1
    glPushMatrix();
    glColor4ub(232, 44, 12, 1);
    glRotatef(90, -1, 0, 0); //angulo, x,y,z
    gluCylinder(Cilindro, 22, 20, 10, 50, 10);
    glPopMatrix();
    //capa 2
    glPushMatrix();
    glColor4ub(232, 44, 12, 1);
    glRotatef(90, -1, 0, 0); //angulo, x,y,z
    glTranslatef(0, 0, -10); //x, y, z
    gluCylinder(Cilindro, 24, 22, 10, 50, 10);
    glPopMatrix();
    //capa 3
    glPushMatrix();
    glColor4ub(232, 44, 12, 1);
    glRotatef(90, -1, 0, 0); //angulo, x,y,z
    glTranslatef(0, 0, -20); //x, y, z
    gluCylinder(Cilindro, 24, 24, 10, 50, 10);
    glPopMatrix();
    //capa 4
    glPushMatrix();
    glColor4ub(232, 44, 12, 1);
    glRotatef(90, -1, 0, 0); //angulo, x,y,z
    glTranslatef(0, 0, -35); //x, y, z
    gluCylinder(Cilindro, 20, 24, 15, 50, 10);
    glPopMatrix();
    //capa 5
    glPushMatrix();
    glColor4ub(232, 44, 12, 1);
    glRotatef(90, -1, 0, 0); //angulo, x,y,z
    glTranslatef(0, 0, -40); //x, y, z
    gluCylinder(Cilindro, 17, 20, 5, 50, 10);
    glPopMatrix();
    //capa 6
    glPushMatrix();
    glColor4ub(232, 44, 12, 1);
    glRotatef(90, -1, 0, 0); //angulo, x,y,z
    glTranslatef(0, 0, -45); //x, y, z
    gluCylinder(Cilindro, 14, 17, 5, 50, 10);
    glPopMatrix();
    //capa 7
    glPushMatrix();
    glColor4ub(232, 44, 12, 1);
    glRotatef(90, -1, 0, 0); //angulo, x,y,z
    glTranslatef(0, 0, -50); //x, y, z
    gluCylinder(Cilindro, 10, 14, 5, 50, 10);
    glPopMatrix();
    //capa 8
    glPushMatrix();
    glColor4ub(232, 44, 12, 1);
    glRotatef(90, -1, 0, 0); //angulo, x,y,z
    glTranslatef(0, 0, -55); //x, y, z
    gluCylinder(Cilindro, 6, 10, 5, 50, 10);
    glPopMatrix();
    //capa 9
    glPushMatrix();
    glColor4ub(232, 44, 12, 1);
    glRotatef(90, -1, 0, 0); //angulo, x,y,z
    glTranslatef(0, 0, -60); //x, y, z
    gluCylinder(Cilindro, 3, 6, 5, 50, 10);
    glPopMatrix();
    //capa 10
    glPushMatrix();
    glColor4ub(232, 44, 12, 1);
    glRotatef(90, -1, 0, 0); //angulo, x,y,z
    glTranslatef(0, 0, -72); //x, y, z
    gluCylinder(Cilindro, 3, 3, 12, 50, 10);
    glPopMatrix();
    glPushMatrix();
    glColor4ub(44, 111, 120, 1);
    glTranslatef(0, -70, 0); //x, y, z
    glutSolidSphere(4, 50, 10);
    glPopMatrix();
    glPopMatrix();
}

void drawFloor()
{
    GLfloat Lado = 12;
    GLfloat Brick = Lado / 8;
    GLint Cuadros = 18;

    //activar la textura
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturas[6].ID);

    glPushMatrix();
    glTranslatef(-Brick, 0, 0);
    glBegin(GL_QUADS);
    for (int i = 0; i < Cuadros; i++)
    {
        for (int j = 0; j < Cuadros; j++)
        {
            if ((i + j) % 2 == 0)
            {
                glColor4ub(25, 25, 112, Transparencia);
            }
            else
            {
                glColor4ub(112, 112, 112, Transparencia);
            }
            glTexCoord2f(0, 0);
            glVertex3f(-Lado + (i * Brick), 0, -Lado + (j * Brick));
            glTexCoord2f(1, 0);
            glVertex3f(-(Lado - Brick) + (i * Brick), 0, -Lado + (j * Brick));
            glTexCoord2f(1, 1);
            glVertex3f(-(Lado - Brick) + (i * Brick), 0, -(Lado - Brick) + (j * Brick));
            glTexCoord2f(0, 1);
            glVertex3f(-Lado + (i * Brick), 0, -(Lado - Brick) + (j * Brick));
        }
    }
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void drawUmbrella(void)
{

    GLint Lados = 30;

    GLUquadricObj *qobj; //Define el objeto
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_FILL); //Se dibuja un trompo

    GLfloat ambient[] = {0.20, 0.05, 0.05, 1.0};
    GLfloat diffuse[] = {0.89, 0.64, 0.14, 1.0};
    GLfloat specular[] = {0.00, 0.00, 0.00, 1.0};
    GLfloat emission[] = {0.00, 0.00, 0.00, 1.0};
    GLfloat shininess[] = {128.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    glPushMatrix();
    glTranslatef(9, -3.7, 9);
    glRotatef(45, 1, 0, 0);
    glColor4ub(255, 0, 0, 0); //Capa roja
    gluCylinder(qobj, 0, 3.9, 1, 11, 1);
    glColor4ub(100, 100, 100, 0); //Palo gris
    gluCylinder(qobj, 0.05, 0.05, 4.7, 10, 1);
    glPopMatrix();

    gluDeleteQuadric(qobj);
}

void drawFoto()
{
    glPushMatrix();
    glTranslatef(0, -4.5, 0);
    glPushMatrix();
    glRotatef(20, -1, 0, 0);
    glTranslatef(0, 0, 1.5);
    glPushMatrix();
    glRotatef(180, 1, 0, 0);
    glTranslatef(-8, 1, -10); //x, y(altura), z
    glBindTexture(GL_TEXTURE_2D, texturas[5].ID);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(-1, -1); // Bottom Left Of The Texture and Quad
    glTexCoord2f(1, 0);
    glVertex2f(1, -1); // Bottom Right Of The Texture and Quad
    glTexCoord2f(1, 1);
    glVertex2f(1, 1); // Top Right Of The Texture and Quad
    glTexCoord2f(0, 1);
    glVertex2f(-1, 1); // Top Left Of The Texture and Quad
    glEnd();
    glPopMatrix();
    //marco
    glPushMatrix();
    glColor4ub(215, 232, 142, 0);
    glTranslatef(-8, -1, 9.85); //x, y(altura), z
    glScaled(2.5, 3, 0.2);
    glutSolidCube(1);
    glPopMatrix();
    //Soporte
    glPushMatrix();
    glColor4ub(235, 122, 255, 0);
    glTranslatef(-8, -1, 9); //x, y(altura), z
    glRotatef(-45, -1, 0, 0);
    glScaled(1, 2, 0.2);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}

void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat diffuseMaterial[] = {1.0, 1.0, 1.0, 0.0};
    GLfloat lmodel_ambient[] = {Luz, Luz, Luz, Luz};

    GLfloat lightColor[] = {1.0f, 1.0f, 1.0f, 1.0f};

    GLfloat lightPos[] = {LIGHT_POS / 2, LIGHT_POS, LIGHT_POS / 2, 0};

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0, 0, -40);
    glRotatef(30, 1, 0, 0);

    glScalef(Zoom, Zoom, Zoom);

    glRotatef(spinX, 1, 0, 0);
    glRotatef(spinY, 0, 1, 0);

    if (Rot == 1)
        glRotatef(Rotacion, 0, 1, 0);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 64.0f);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

    glPushMatrix();
    glColor4ub(255, 255, 0, 0);
    glTranslatef(0, LIGHT_POS, 0);
    glutSolidSphere(0.3, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, BOX_HEIGHT, 0);
    //Aqu� debe llamar a los objetos
    drawUmbrella();
    tropo();
    Helicoptero();
    glEnable(GL_TEXTURE_2D); //Activa la textura
    drawBall();
    drawFoto();
    glDisable(GL_TEXTURE_2D); //Desactiva la textura
    mesa();
    //drawVidrioMesa();
    glPopMatrix();

    glEnable(GL_STENCIL_TEST);      //Enable using the stencil buffer
    glColorMask(0, 0, 0, 0);        //Disable drawing colors to the screen
    glDisable(GL_DEPTH_TEST);       //Disable depth testing
    glStencilFunc(GL_ALWAYS, 1, 1); //Make the stencil test always pass

    //Make pixels in the stencil buffer be set to 1 when the stencil test passes
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    //Aqu� se dibuja el piso
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
    //Aqu� se dibujan los objetos que se van a reflejar
    drawUmbrella();
    tropo();
    Helicoptero();
    glEnable(GL_TEXTURE_2D); //Activa la textura
    drawBall();
    drawFoto();
    glDisable(GL_TEXTURE_2D); //Desactiva la textura
    mesa();
    glPopMatrix();

    glDisable(GL_STENCIL_TEST); //Disable using the stencil buffer
    //Blend the floor onto the screen
    glEnable(GL_BLEND);

    //Aqu� se dibuja el piso que refleja
    drawFloor();
    glDisable(GL_BLEND);
    glPushMatrix();
    glTranslatef(0, 7, 0);
    drawVidrioMesa();
    glPopMatrix();
    glutSwapBuffers();
}

void handleKeypress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: //Escape key
        exit(0);
        break;

    case 'F': //Posici�n de la luz
        ++LIGHT_POS;
        break;

    case 'f': //Posici�n de la luz
        --LIGHT_POS;
        break;

    case 'r': //La esfera gira
        if (Rot == 1)
            Rot = 0;
        else
            Rot = 1;
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

    case 'B':
        xB += 0.22;
        rotateB -= 4;

        break;

    case 'b':
        xB -= 0.22;
        rotateB += 4;
        break;

    case '8':
        yB += 0.22;
        rotateB -= 4;
        break;

    case '5':
        yB -= 0.22;
        rotateB += 4;
        break;

    case 'H':
        yH += 2;
        rotateB -= 4;
        break;

    case 'h':
        yH -= 2;
        rotateB += 4;
        break;

    case 'm':
        if (Meridianos == 0)
            Meridianos = 1;
        else
            Meridianos = 0;
        ;
        break;

    case 'k':
        if (mTextura == 0)
            mTextura = 1;
        else
            mTextura = 0;
        ;
        break;
    }
}
void handleSpecialKeypress(int key, int x, int y)
{
    switch (key)
    {

    case GLUT_KEY_LEFT:
        isLeftKeyPressed = true;
        if (!isRightKeyPressed)
        {
            if (xH > -50)
                --xH;
        }
        break;

    case GLUT_KEY_RIGHT:
        isRightKeyPressed = true;
        if (!isLeftKeyPressed)
        {
            if (xH < 50)
                ++xH;
        }
        break;

    case GLUT_KEY_UP:
        isUpKeyPressed = true;
        if (!isDownKeyPressed)
        {
            if (yH < 50)
                ++yH;
        }
        break;

    case GLUT_KEY_DOWN:
        isDownKeyPressed = true;
        if (!isUpKeyPressed)
        {
            if (yH > 0)
                --yH;
        }
        break;
    }
}

void handleSpecialKeyReleased(int key, int x, int y)
{
    switch (key)
    {
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

void init()
{
    glClearColor(0, 0, 0, 0); //Fondo negro en toda la escena
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //carga los archivos con las texturas
    if (
        !cargarTGA("data/Piso.tga", &texturas[0]) ||
        !cargarTGA("data/Star.tga", &texturas[1]) ||
        !cargarTGA("data/Earth4.tga", &texturas[2]) ||
        !cargarTGA("data/Bola.tga", &texturas[3]) ||
        !cargarTGA("data/Estrellas2.tga", &texturas[4]) ||
        !cargarTGA("data/andres4.tga", &texturas[5]) ||
        !cargarTGA("data/grass.TGA", &texturas[6])

    )
    {
        printf("Error con la carga de las texturas\n");
        exit(0);
    }
}

void handleResize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

void spinDisplay(void)
{

    /*Rotacion += 0.01;
       if (Rotacion >= 360) {
           Rotacion = 0;
    }
    glutPostRedisplay(); //Vuelve a dibujar
    */
    // PARA EL TROMPO
    Rotacion += 0.9;
    if (inclinacion > 0)
    {
        inclinacion -= 0.005;
    }
    glutPostRedisplay(); //Vuelve a dibujar
}

void mouse(int button, int state, int x, int y)
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
        {
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

void mouseMotion(int x, int y)
{
    spinX = y;
    spinY = x;
    //printf("X %5.2f Y %5.2f\n", spinX, spinY);
}

void update(int value)
{

    rotate += 0.5f;

    if (rotate > 360.f)
    {
        rotate -= 360;
    }

    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(500, 200); //Posici�n de la ventana en la pantalla

    glutCreateWindow("Sombrilla con reflejo y Bola");
    init();

    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);
    glutTimerFunc(25, update, 0);
    glutMouseFunc(mouse); //Activa los controles del mouse
    glutMotionFunc(mouseMotion);

    glutSpecialFunc(handleSpecialKeypress);
    glutSpecialUpFunc(handleSpecialKeyReleased);

    glutMainLoop();

    return 0;
}
