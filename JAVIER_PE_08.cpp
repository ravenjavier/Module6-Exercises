// Exercise Q08 — scale() Applied to Every Vertex of a Shape [Medium]
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
#include <GL/freeglut.h>
using namespace std;

// quad vertices: x, y, z
GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};

GLuint VBO;

// scaling matrix function
void scaleAll(float sx, float sy, float sz)
{
    // apply scaling to every vertex
    for (int i = 0; i < 12; i += 3)
    {
        float x = vertices[i];
        float y = vertices[i + 1];
        float z = vertices[i + 2];
        float w = 1.0f;

        // scaling matrix multiplication
        vertices[i]     = sx * x;
        vertices[i + 1] = sy * y;
        vertices[i + 2] = sz * z;

        // w remains 1.0f
        w = 1.0f;
    }
}

void init()
{
    scaleAll(2.0f, 2.0f, 2.0f);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
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
    glColor3f(0.0f, 0.7f, 1.0f);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Exercise Q08 - scale() Applied to Every Vertex of a Shape");
    glewInit();

    init();

    glutDisplayFunc(display);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glutMainLoop();

    return 0;
}