// Exercise Q12 — Timer-Driven translate() Animation [Medium]
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
#include <GL/freeglut.h>
using namespace std;

// triangle vertices - x, y, z
GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

GLuint VBO;

// translation matrix function
void translate(float tx, float ty, float tz)
{
    // translation matrix
    float T[16] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        tx, ty, tz, 1
    };

    // apply translation to every vertex
    for (int i = 0; i < 9; i += 3)
    {
        float x = vertices[i];
        float y = vertices[i + 1];
        float z = vertices[i + 2];
        float w = 1.0f;

        float newX = T[0] * x + T[1] * y +
                     T[2] * z + T[3] * w;

        float newY = T[4] * x + T[5] * y +
                     T[6] * z + T[7] * w;

        float newZ = T[8] * x + T[9] * y +
                     T[10] * z + T[11] * w;

        float newW = T[12] * x + T[13] * y +
                     T[14] * z + T[15] * w;

        vertices[i]     = newX;
        vertices[i + 1] = newY;
        vertices[i + 2] = newZ;
    }
}

// timer callback
void timer(int value)
{
    translate(0.0f, 0.2f, 0.0f);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferSubData(
        GL_ARRAY_BUFFER,
        0,
        sizeof(vertices),
        vertices
    );

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glutPostRedisplay();
    // reschedule timer (LAST line)
    glutTimerFunc(1000, timer, 0);
}

void init()
{
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_DYNAMIC_DRAW
    );

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnable(GL_DEPTH_TEST);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        0.0, 0.0, 5.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0
    );

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, (void*)0);

    glColor3f(0.0f, 0.8f, 0.4f);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Exercise Q12 - Timer-Driven translate() Animation");
    glewInit();

    init();

    glutDisplayFunc(display);

    // start timer after one second
    glutTimerFunc(1000, timer, 0);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glutMainLoop();

    return 0;
}