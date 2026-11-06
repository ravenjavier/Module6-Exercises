// Exercise Q03 — Scalar Product Matrix, By Hand [Easy]
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
#include <iomanip>
using namespace std;

// input point
float x = 2.0f;
float y = 1.0f;

// scalar value
float s = 2.0f;

// output point
float newX, newY;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    // draw original point - red
    glPointSize(12.0f);
    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_POINTS);
        glVertex2f(x, y);
    glEnd();

    // draw transformed point - green
    glColor3f(0.0f, 1.0f, 0.0f);

    glBegin(GL_POINTS);
        glVertex2f(newX, newY);
    glEnd();

    // draw a line connecting both points
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(newX, newY);
    glEnd();

    glutSwapBuffers();
}

void init()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    // set to 2D coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-5.0, 5.0, -5.0, 5.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    newX = (s * x);
    newY = (s * y);
    cout << fixed << setprecision(1);

    cout << "===== SCALAR PRODUCT MATRIX =====" << endl;

    cout << "\nScalar Matrix:" << endl;
    cout << "[ 2.0  0.0 ]" << endl;
    cout << "[ 0.0  2.0 ]" << endl;

    cout << "\nBefore Transformation:" << endl;
    cout << "X = " << x << endl;
    cout << "Y = " << y << endl;

    cout << "\nAfter Transformation:" << endl;
    cout << "X = " << newX << endl;
    cout << "Y = " << newY << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Exercise Q03 - Scalar Product Matrix, By Hand");

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}