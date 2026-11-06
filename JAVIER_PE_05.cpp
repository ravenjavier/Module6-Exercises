// Exercise Q05 — Matrix Addition, By Hand [Easy]#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
#include <iomanip>
using namespace std;

// two 2x2 matrices stored as 4-element arrays
float A[4] = {
    1.0f, 2.0f,
    3.0f, 4.0f
};

float B[4] = {
    5.0f, 6.0f,
    7.0f, 8.0f
};

// result matrix
float C[4];

// function to add two matrices
void addMatrices()
{
    for (int i = 0; i < 4; i++)
    {
        C[i] = A[i] + B[i];
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // draw a simple triangle
    glColor3f(0.0f, 0.7f, 1.0f);

    glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f);
    glEnd();

    glutSwapBuffers();
}

void init()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    // perform matrix addition
    addMatrices();
    cout << fixed << setprecision(1);

    cout << "===== MATRIX ADDITION =====" << endl;

    cout << "\nMatrix A:" << endl;
    cout << "[ " << A[0] << "  " << A[1] << " ]" << endl;
    cout << "[ " << A[2] << "  " << A[3] << " ]" << endl;

    cout << "\nMatrix B:" << endl;
    cout << "[ " << B[0] << "  " << B[1] << " ]" << endl;
    cout << "[ " << B[2] << "  " << B[3] << " ]" << endl;

    cout << "\nResult Matrix (A + B):" << endl;
    cout << "[ " << C[0] << "  " << C[1] << " ]" << endl;
    cout << "[ " << C[2] << "  " << C[3] << " ]" << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Exercise Q05 - Matrix Addition, By Hand");

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}