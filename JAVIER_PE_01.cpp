// Exercise Q01 — Immediate-Mode 4-Sided Pyramid [Easy]
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // camera position
    gluLookAt(3.0, 3.0, 5.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glBegin(GL_TRIANGLES);

    // front face - red
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);    
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);

    // right face - blue
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);

    // back face - green
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);

    // left face - yellow
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, 1.0);

    glEnd();

    glutSwapBuffers();
}

void init()
{
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Exercise Q01 - Immediate-Mode 4-Sided Pyramid");

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}