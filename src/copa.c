#include <GL/glut.h>
#include<stdio.h>

GLint spinX, spinY; //Para rotar la escena
GLfloat Rotacion = 0;

GLfloat zoom = 1;


int fill = 0;
GLfloat material = GLU_LINE;


void cilindro(GLfloat y, GLfloat a, GLfloat b){
  GLUquadricObj *Cilindro;
  Cilindro = gluNewQuadric();

  glPushMatrix();
      glColor4ub(255, 255, 255, 255);   //Azul
      gluQuadricDrawStyle(Cilindro, material);
      glTranslatef(0, y, 0); //x, y, z
      glRotatef(90, 1, 0, 0);
      gluCylinder(Cilindro, a, b, 10, 20,1);
  glPopMatrix();

  gluDeleteQuadric(Cilindro);
}

void dibujarCopa(){
  int y=90, a=50, b=50;

  for(int i=0;i<=6;i++){
    printf("n:%d y:%d, a:%d, b:%d \n",i, y, a, b);
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
    printf("n:%d y:%d, a:%d, b:%d \n",i, y, a, b);
    cilindro(y,a,b);
    y -= 10;
  }

  for(int i=0;i<=3;i++){
    b+=i*i*i;
    printf("n:%d y:%d, a:%d, b:%d \n",i, y, a, b);
    cilindro(y,a,b);
    a =b;
    y -= 10;
  }
}


void handleKeypress(unsigned char key, int x, int y) {
  switch (key) {
    case 27: //Escape key
      exit(0);
    break;
    case 'f':
    if(fill == 0){
      fill = 1;
      material = GLU_FILL;
    }else{
      material = GLU_LINE;
      fill = 0;
    }
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

  dibujarCopa();

  glutSwapBuffers();
}

void spinDisplay(void){//nos permitira hacer animaciones

  Rotacion += 1.2;

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
  glutCreateWindow ("Copa"); //Crea la ventana y le pone la etiqueta

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
