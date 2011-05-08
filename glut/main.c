#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int g_phase = 0;
float pixels[100*100*3];

void setPixel(int x, int y, float r, float g, float b) {
  x = 99 - x;
  float *out = pixels + 3*(x*100+y);
  *out++ = r;
  *out++ = g;
  *out = b;
}

void init (void) {
  glClearColor(1.0, 1.0, 1.0, 1.0);

  setPixel(10, 10, 1.0f, 0.0f, 0.0f); //red
  setPixel(10, 20, 0.0f, 1.0f, 0.0f); //blue
  setPixel(10, 30, 0.0f, 0.0f, 1.0f); //green
}

void display ( void ) {
  int i,j;
  glClear(GL_COLOR_BUFFER_BIT);

  for (i=20;i<100;i++) {
    for (j=0;j<100;j++) {
      setPixel(i, j, pow(sin((i+g_phase)/8.0f),2.0f), j/100.0f, 0.5f);
    }
  }

  glDrawPixels(100, 100, GL_RGB, GL_FLOAT, pixels);
  glutSwapBuffers();  // double buffering woo hoo!
}

// Delete two functions below for non-animated version
void idle(void) {
  g_phase++;
  glutPostRedisplay();
}

void visible(int vis) {
  if (vis == GLUT_VISIBLE) {
    glutIdleFunc(idle);
  } else {
    glutIdleFunc(NULL);
  }
}

int main (int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowSize(100, 100);
  glutCreateWindow(argv[0]);
  init();
  glutDisplayFunc(display);
  glutVisibilityFunc(visible);
  glutMainLoop();
  return 0;
}

