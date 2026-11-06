// Exercise Q14 — glArrayElement in a Loop, Five Colors [Medium]
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
#include <GL/freeglut.h>
using namespace std;

// five pentagon vertices
GLfloat positions[] = {
     0.0f,  0.8f, 0.0f,   // top
    -0.76f, 0.25f, 0.0f,  // upper left
    -0.47f,-0.65f, 0.0f,  // lower left
     0.47f,-0.65f, 0.0f,  // lower right
     0.76f, 0.25f, 0.0f   // upper right
};

// five different vertex colors
GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,  // red
    0.0f, 1.0f, 0.0f,  // green
    0.0f, 0.0f, 1.0f,  // blue
    1.0f, 1.0f, 0.0f,  // yellow
    1.0f, 0.0f, 1.0f   // magenta
};

GLuint VBO;

void init()
{
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Calculate memory sizes
    GLsizeiptr positionSize = sizeof(positions);
    GLsizeiptr colorSize = sizeof(colors);
    GLsizeiptr totalSize = positionSize + colorSize;

    // reserve space for both arrays
    glBufferData(
        GL_ARRAY_BUFFER,
        totalSize,
        NULL,
        GL_STATIC_DRAW
    );

    // upload position data
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

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    cout << "========================" << endl;
    cout << "GLARRAYELEMENT PENTAGON" << endl;
    cout << "========================" << endl;

    cout << "Number of vertices: 5" << endl;
    cout << "Position data size: " << positionSize << " bytes" << endl;
    cout << "Color data size: " << colorSize << " bytes" << endl;
    cout << "Color data offset: " << positionSize << " bytes" << endl;
    cout << "Total VBO size: " << totalSize << " bytes" << endl;

    cout << "=================================" << endl;
    cout << "Pentagon successfully initialized!" << endl;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
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

    glBegin(GL_POLYGON);

    for (int i = 0; i < 5; i++)
    {
        glArrayElement(i);
    }

    glEnd();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Exercise Q14 - glArrayElement in a Loop, Five Colors");
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        cout << "GLEW initialization failed!" << endl;
        return 1;
    }

    init();

    glClearColor(0.08f, 0.08f, 0.12f, 1.0f);

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}