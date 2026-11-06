// Exercise Q11 — Color Cube Face via glBufferSubData [Medium]
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
#include <GL/freeglut.h>
using namespace std;

GLuint VBO;

// four vertices of the front cube face
GLfloat positions[] = {
    -1.0f, -1.0f, 0.0f,  // Bottom-left
     1.0f, -1.0f, 0.0f,  // Bottom-right
     1.0f,  1.0f, 0.0f,  // Top-right
    -1.0f,  1.0f, 0.0f   // Top-left
};

// different colors for each vertex
GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,  // Red
    0.0f, 1.0f, 0.0f,  // Green
    0.0f, 0.0f, 1.0f,  // Blue
    1.0f, 1.0f, 0.0f   // Yellow
};

void init()
{
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Calculate memory sizes
    GLsizeiptr positionSize = sizeof(positions);
    GLsizeiptr colorSize = sizeof(colors);
    GLsizeiptr totalSize = positionSize + colorSize;

    // reserve the full combined memory
    glBufferData(
        GL_ARRAY_BUFFER,
        totalSize,
        NULL,
        GL_STATIC_DRAW
    );

    // upload position data at offset 0
    glBufferSubData(
        GL_ARRAY_BUFFER,
        0,
        positionSize,
        positions
    );

    // upload color data after position data
    glBufferSubData(
        GL_ARRAY_BUFFER,
        positionSize,
        colorSize,
        colors
    );

    cout << "=== Q11: Color Cube Face VBO ===" << endl;
    cout << "Position data size: " << positionSize << " bytes" << endl;
    cout << "Color data size: " << colorSize << " bytes" << endl;
    cout << "Color data offset: " << positionSize << " bytes" << endl;
    cout << "Total VBO size: " << totalSize << " bytes" << endl;

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
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(
        3,
        GL_FLOAT,
        0,
        (void*)0
    );

    glColorPointer(
        3,
        GL_FLOAT,
        0,
        (void*)sizeof(positions)
    );

    // draw the colored cube face
    glDrawArrays(GL_QUADS, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Exercise Q11 - Color Cube Face via glBufferSubData");

    glewInit();

    init();

    glutDisplayFunc(display);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glutMainLoop();

    return 0;
}