#include <GL/glut.h>
#include<stdio.h>

GLint spinX, spinY; //Para rotar la escena
GLfloat Rotacion = 0;

GLfloat zoom = 1;


int fill = 0;
GLfloat material = GLU_LINE;

GLfloat _x=0, _y=0, _z=0, r=0, tambaleo= 0;

void cilindro(GLfloat y, GLfloat a, GLfloat b, GLfloat ancho, int red, int green, int blue, int alpha){
  GLUquadricObj *Cilindro;
  Cilindro = gluNewQuadric();

  glPushMatrix();
      glColor4ub(red, green, blue, alpha);   //Azul
      gluQuadricDrawStyle(Cilindro, material);
      glTranslatef(0, y, 0); //x, y, z
      glRotatef(90, 1, 0, 0);
      gluCylinder(Cilindro, a, b, ancho, 20,1);
  glPopMatrix();

  gluDeleteQuadric(Cilindro);

}

void dibujarTrompo(){

  cilindro(115, 22, 0, 0, 255,0,0,0);
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

void trompo(){

  glPushMatrix();

    glScalef(0.6,0.6,0.6);    
    glRotatef(Rotacion, 0, 1, 0); 
    glTranslatef(_x, 0, _z);
    
    dibujarTrompo();
  glPopMatrix();

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
    case 'w':
      _z+=2;
    break;
    case 's':
      _z-=1;
    break;
    case 'a':
      _x-=2;
    break;
    case 'd':
      _x+=2;
    break;

    case 32:
      _x=0;
      _y=0;
    break;
    case 'r':
      if(r==0){
        r=1;
      }else{
        r=0;
      }
    break;
    case 'm':
      tambaleo += 2;
    break;
    case 'n':
      tambaleo -= 2;
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
    glRotatef(Rotacion, 0, r, 0); 
    glRotatef(tambaleo, r, 0, 0); 

    trompo();
  glPopMatrix();

  glutSwapBuffers();
}

void spinDisplay(void){//nos permitira hacer animaciones

  Rotacion += 2;

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
