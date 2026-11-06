// Exercise Q10 — Combining Translate and Scale [Medium] 
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
#include <GL/freeglut.h>
using namespace std;

// triangle vertices- x, y, z
GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

GLuint VBO;

// general purpose 4x4 matrix multiplication
void multiply4x4(float A[16], float B[16], float result[16])
{
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            result[row * 4 + col] = 0.0f;

            for (int k = 0; k < 4; k++)
            {
                result[row * 4 + col] +=
                    A[row * 4 + k] * B[k * 4 + col];
            }
        }
    }
}

// apply a 4x4 matrix to every vertex
void applyMatrix(float matrix[16])
{
    for (int i = 0; i < 9; i += 3)
    {
        float x = vertices[i];
        float y = vertices[i + 1];
        float z = vertices[i + 2];
        float w = 1.0f;

        float newX = matrix[0] * x + matrix[1] * y +
                     matrix[2] * z + matrix[3] * w;

        float newY = matrix[4] * x + matrix[5] * y +
                     matrix[6] * z + matrix[7] * w;

        float newZ = matrix[8] * x + matrix[9] * y +
                     matrix[10] * z + matrix[11] * w;

        float newW = matrix[12] * x + matrix[13] * y +
                     matrix[14] * z + matrix[15] * w;

        vertices[i]     = newX;
        vertices[i + 1] = newY;
        vertices[i + 2] = newZ;
    }
}

// initialize matrices and VBO
void init()
{
    // translation matrix
    float translate[16] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0.5f, 0.0f, 0.0f, 1
    };

    // scaling matrix
    float scale[16] = {
        2.0f, 0, 0, 0,
        0, 2.0f, 0, 0,
        0, 0, 2.0f, 0,
        0, 0, 0, 1
    };

    float combined[16];
    multiply4x4(translate, scale, combined);
    applyMatrix(combined);

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

    glColor3f(1.5f, 0.0f, 1.5f);

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
    glutCreateWindow("Exercise Q10 - Combining Translate and Scale");
    glewInit();

    init();

    glutDisplayFunc(display);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glutMainLoop();

    return 0;
}