
#include <GL/glut.h>

GLint spinX, spinY; //Para rotar la escena
GLfloat Rotacion = 0;

GLfloat zoom = 1;

GLfloat xI = 0;
GLfloat yI = 0;
GLfloat zI = 0;

GLfloat xR = 0;
GLfloat yR = 0;
GLfloat zR = 0;

GLfloat rotacionInput = 0;

int speed = 0;
int laser = 0;

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
  
  glColor4ub(255, 0, 0, 0);   //Rojo
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
    glutWireSphere(40, 30, 10); //tamaño de la esfera, meridianos, paralelos
  glPopMatrix();
}


void dibujarAspas () {
  // aspas de arriba 
  glColor4ub(255, 255, 0, 0);   //Verde
  glPushMatrix();
      glRotatef(Rotacion, 0, 1, 0); //Para rotar la esfera
      glTranslatef(0,23,0);
      glScalef(5,1,150);
      glutSolidCube (1); //tamaño del cubo
  glPopMatrix();

  glPushMatrix();
      glRotatef(Rotacion, 0, 1, 0); //Para rotar la esfera
      glTranslatef(0,23,0);
      glScalef(150,1,5);
      glutSolidCube (1); //tamaño del cubo
  glPopMatrix();
  // aspas de arriba 

  // aspas de atras
  glPushMatrix();
      glTranslatef(-85,0,-5);
      glRotatef(90, 0, 1, 0); //Para rotar la esfera
      glRotatef(Rotacion, 1, 0, 0); //Para rotar la esfera
      glScalef(1,3,30);
      glutSolidCube (1); //tamaño del cubo
  glPopMatrix();

  glPushMatrix();
      glTranslatef(-85,0,-5);
      glRotatef(90, 0, 1, 0); //Para rotar la esfera
      glRotatef(Rotacion, 1, 0, 0); //Para rotar la esfera
      glScalef(1,30,3);
      glutSolidCube (1); //tamaño del cubo
  glPopMatrix();
  // aspas de atras
}

void dispararLaser(){
  if (laser == 1) {
    glLineWidth(5);

    glBegin(GL_LINES);
        glColor4ub(255, 0, 0, 0); //Rojo
        glVertex3f( 500, -30, -15 ); 
        glVertex3f( 0, -30, -15 ); //Línea Norte a Sur
        glVertex3f( 500, -30,  15 ); 
        glVertex3f( 0, -30,  15 ); //Línea Norte a Sur
    glEnd ();
  }
}

void dibujarHelicoptero () {

  glPushMatrix();

    glTranslatef(xI,yI,zI);
    glRotatef(rotacionInput,xR,yR,zR);

    dibujarCola();

    dibujarAletaDeCola();

    dibujarRotorArriba();

    dibujarRotorAtras();

    dibujarPieDerecho();

    dibujarPieIzquierdo();

    dibujarAspas ();

    dibujarEsferasDelTrenDeAtterizaje();

    dibujarCabina();

    dispararLaser();

  glPopMatrix();
}

void display(void){
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  //Rota la escena
  glRotatef(spinX, 1, 0, 0);
  glRotatef(spinY, 0, 1, 0);

  glScalef(zoom,zoom,zoom);

  dibujarHelicoptero();

  glutSwapBuffers();
}

void spinDisplay(void){//nos permitira hacer animaciones

  Rotacion += speed;

  glutPostRedisplay(); //Vuelve a dibujar
}

void init(void) {
  glClearColor (0.0, 0.0, 0.0, 0.0); //Colores para iniciar la ventana (Fondo)
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);
}

void reshape(int w, int h) {
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0); //Izq, Der, Abajo, Arriba, Cerca, lejos
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluPerspective(45.0, (float)w / (float)h, 100.0, 100.0);
}

void handleKeypress(unsigned char key, int x, int y) {
  switch (key) {
    case 27: //Escape key
      exit(0);
    break;
    
    case 'z':
      zoom -=0.1;
    break;

    case 'Z':
      zoom +=0.1;
    break;

    case 'w':
      xI +=5;
    break;

    case 's':
      xI -=5;
    break;

    case 'q':
      yI -=5;
    break;

    case 'e':
      yI +=5;
    break;

    case 'a':
      rotacionInput +=5;
      yR = 1;
    break;
    case 'd':
      rotacionInput -=5;
      yR = 1;
    break;

    case 'm':
      speed +=2;
    break;

    case 'n':
      speed -=2;
    break;
    
    case 32:
      if(laser == 0)
        laser = 1;
      else 
        laser = 0;
    break;

  }
}

void mouseMotion(int x, int y){
  spinX = y;
  spinY = x;
}

void mouse(int button, int state, int x, int y){
  switch (button) {
    case GLUT_LEFT_BUTTON:
      if (state == GLUT_DOWN)
        glutIdleFunc(spinDisplay);
    break;

    case GLUT_RIGHT_BUTTON:
      if (state == GLUT_DOWN)
        glutIdleFunc(NULL);
    break;

    default:
    break;
  }
}

int main(int argc, char** argv){
   
  glutInit(&argc, argv);   //Inicializa la librería GLUT y negocia una sesión
                            //con el sistema de ventanas
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //Activa el modo inicial de despliegue
                            //GLUT_DOUBLE doble buffer  GLUT_RGB = GLUT_RGBA
  glutInitWindowSize (600, 600); //Tamaño de la ventana 500 x 500
  glutInitWindowPosition (100, 100); //Posición de la ventana en la pantalla
  glutCreateWindow ("Esfera - Cubo"); //Crea la ventana y le pone la etiqueta

  init ();  //Ejecuta el método "init"

  glutDisplayFunc(display);  //Ejecuta el método "display"
  glutKeyboardFunc(handleKeypress);
  glutReshapeFunc(reshape); //Ejecuta el método "reshape"
  glutMouseFunc(mouse); //Activa los controles del mouse
  glutMotionFunc(mouseMotion);
  glutMainLoop(); //Repite el main indefinidamente (¡Animación!)
  return 0;   /* ANSI C requires main to return int. */
}
//gcc helicoptero.c -o se2  -lGL -lGLU -lglut
//tipos demovimientos rotar, escalar, trasladar
