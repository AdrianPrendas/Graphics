#include <GL/glut.h>
#include<stdio.h>
#include<windows.h>

GLint spinX, spinY; //Para rotar la escena

GLfloat zoom = 1;

void drawTeaPot(){
    glColor4ub(0, 255, 0, 0);
    glPushMatrix();
        glTranslatef(15,6,15);
        glutSolidTeapot(5);
    glPopMatrix();
}

void glass(){
    glColor4ub(255, 255, 255, 100);
    glPushMatrix();
      glTranslatef(0,2,0);
      glBegin(GL_QUADS); //tamaño del cubo
        glVertex3f(27,0,23);
        glVertex3f(-27,0,23);
        glVertex3f(-27,0,-23);
        glVertex3f(27,0,-23);
      glEnd();
    glPopMatrix();
}

void foot(int x, int z){
    glColor4ub(0, 0, 255, 200);
    glPushMatrix();
      glTranslatef(x,-12,z);
      glScalef(3,25,3);
      glutSolidCube (1); //tamaño del cubo
    glPopMatrix();
}

void marcoA(int x){
    glColor4ub(255, 255, 0, 0);
    glPushMatrix();
      glTranslatef(x,0,0);
      glScalef(3,3,45);
      glutSolidCube (1); //tamaño del cubo
    glPopMatrix();
}

void marcoB(int x){
    glColor4ub(255, 0, 255, 0);
    glPushMatrix();
        glRotatef(90,0,1,0);
      glTranslatef(x,0,0);
      glScalef(3,3,60);
      glutSolidCube (1); //tamaño del cubo
    glPopMatrix();
}

void drawTable(){
    glPushMatrix();
        glass();
        foot(26,22);
        foot(-26,-22);
        foot(-26,22);
        foot(26,-22);
        marcoA(28);
        marcoA(-28);
        marcoB(22);
        marcoB(-22);
        drawTeaPot();
    glPopMatrix();
}




void handleKeypress(unsigned char key, int x, int y) {
  switch (key) {
    case 27: //Escape key
      exit(0);
    break;

  }
}

void display(void){

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  //Rota la escena
  glRotatef(spinX, 1, 0, 0);
  glRotatef(spinY, 0, 1, 0);

  glScalef(zoom,zoom,zoom);

  glPushMatrix();

    drawTable();


  glPopMatrix();

  glutSwapBuffers();
}

void spinDisplay(void){//nos permitira hacer animaciones

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

  glutInit(&argc, argv);   //Inicializa la librer
                            //con el sistema de ventanas
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //Activa el modo inicial de despliegue
                            //GLUT_DOUBLE doble buffer  GLUT_RGB = GLUT_RGBA
  glutInitWindowSize (600, 600); //Tamaño de la ventana 500 x 500
  glutInitWindowPosition (100, 100); //Posición de la ventana en la pantalla
  glutCreateWindow ("Trompo"); //Crea la ventana y le pone la etiqueta

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
