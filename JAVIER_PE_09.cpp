// Exercise Q09 — rotateZ() Applied Once [Medium]
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
#include <GL/freeglut.h>
using namespace std;

// quad vertices - x, y, z
GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};

GLuint VBO;

// rotate every vertex around the z-axis
void rotateZ(float degrees)
{
    // convert degrees to radians
    float radians = degrees * 3.14159265f / 180.0f;

    float c = cosf(radians);
    float s = sinf(radians);

    // rotation matrix Rz
    float Rz[16] = {
         c,  s, 0.0f, 0.0f,
        -s,  c, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    // apply rotation to every vertex
    for (int i = 0; i < 12; i += 3)
    {
        float x = vertices[i];
        float y = vertices[i + 1];
        float z = vertices[i + 2];
        float w = 1.0f;

        float newX = Rz[0] * x + Rz[4] * y +
                     Rz[8] * z + Rz[12] * w;

        float newY = Rz[1] * x + Rz[5] * y +
                     Rz[9] * z + Rz[13] * w;

        float newZ = Rz[2] * x + Rz[6] * y +
                     Rz[10] * z + Rz[14] * w;

        float newW = Rz[3] * x + Rz[7] * y +
                     Rz[11] * z + Rz[15] * w;

        vertices[i]     = newX;
        vertices[i + 1] = newY;
        vertices[i + 2] = newZ;

        // Homogeneous coordinate remains 1
        w = newW;
    }
}

void init()
{
    rotateZ(45.0f);

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

    glColor3f(0.0f, 0.0f, 1.0f);

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
    glutCreateWindow("Exercise Q09 - rotateZ() Applied Once");
    glewInit();

    init();

    glutDisplayFunc(display);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glutMainLoop();

    return 0;
}