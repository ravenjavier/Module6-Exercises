// Exercise Q18 — Two Shapes, One Combined Buffer [Hard]
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
#include <GL/freeglut.h>
using namespace std;

// pyramid face - 3 vertices
GLfloat pyramidPositions[] = {
    -1.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -1.0f,  0.8f, 0.0f
};

// cube face - 4 vertices
GLfloat cubePositions[] = {
     0.5f, -0.5f, 0.0f,
     1.5f, -0.5f, 0.0f,
     1.5f,  0.5f, 0.0f,
     0.5f,  0.5f, 0.0f
};

// pyramid vertex colors
GLfloat pyramidColors[] = {
    1.0f, 0.0f, 0.0f,  // red
    0.0f, 1.0f, 0.0f,  // green
    0.0f, 0.0f, 1.0f   // blue
};

// cube vertex colors
GLfloat cubeColors[] = {
    1.0f, 1.0f, 0.0f,  // yellow
    0.0f, 1.0f, 1.0f,  // cyan
    1.0f, 0.0f, 1.0f,  // magenta
    1.0f, 0.5f, 0.0f   // orange
};

GLuint VBO;

GLsizeiptr pyramidPositionSize;
GLsizeiptr cubePositionSize;
GLsizeiptr pyramidColorSize;
GLsizeiptr cubeColorSize;

GLintptr pyramidPositionOffset = 0;
GLintptr cubePositionOffset;
GLintptr pyramidColorOffset;
GLintptr cubeColorOffset;

GLsizeiptr totalSize;

void init()
{
    // calculate sizes
    pyramidPositionSize = sizeof(pyramidPositions);
    cubePositionSize = sizeof(cubePositions);
    pyramidColorSize = sizeof(pyramidColors);
    cubeColorSize = sizeof(cubeColors);

    // calculate offsets
    cubePositionOffset = pyramidPositionSize;

    pyramidColorOffset =
        pyramidPositionSize + cubePositionSize;

    cubeColorOffset =
        pyramidPositionSize + cubePositionSize
        + pyramidColorSize;

    totalSize =
        pyramidPositionSize + cubePositionSize
        + pyramidColorSize + cubeColorSize;

    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        totalSize,
        NULL,
        GL_STATIC_DRAW
    );

    // pyramid positions
    glBufferSubData(
        GL_ARRAY_BUFFER,
        pyramidPositionOffset,
        pyramidPositionSize,
        pyramidPositions
    );

    // cube positions
    glBufferSubData(
        GL_ARRAY_BUFFER,
        cubePositionOffset,
        cubePositionSize,
        cubePositions
    );

    // pyramid colors
    glBufferSubData(
        GL_ARRAY_BUFFER,
        pyramidColorOffset,
        pyramidColorSize,
        pyramidColors
    );

    // cube colors
    glBufferSubData(
        GL_ARRAY_BUFFER,
        cubeColorOffset,
        cubeColorSize,
        cubeColors
    );

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    cout << "=================================" << endl;
    cout << "   TWO SHAPES, ONE COMBINED VBO  " << endl;
    cout << "=================================" << endl;

    cout << "Pyramid position offset: "
         << pyramidPositionOffset << " bytes" << endl;

    cout << "Cube position offset: "
         << cubePositionOffset << " bytes" << endl;

    cout << "Pyramid color offset: "
         << pyramidColorOffset << " bytes" << endl;

    cout << "Cube color offset: "
         << cubeColorOffset << " bytes" << endl;

    cout << "Total VBO size: "
         << totalSize << " bytes" << endl;

    cout << "=================================" << endl;
    cout << "Four data blocks uploaded successfully!" << endl;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    // pyramid face
    glVertexPointer(3, GL_FLOAT, 0, (void*)pyramidPositionOffset);
    glColorPointer(3, GL_FLOAT, 0, (void*)pyramidColorOffset);

    glDrawArrays(GL_TRIANGLES, 0, 3);


    // cube face
    glVertexPointer(3, GL_FLOAT, 0, (void*)cubePositionOffset);
    glColorPointer( 3, GL_FLOAT, 0, (void*)cubeColorOffset);
    glDrawArrays(GL_QUADS, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glutSwapBuffers();
}

void setup()
{
    glClearColor(0.08f, 0.08f, 0.12f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -1.5, 1.5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Exercise Q18 - Two Shapes, One Combined Buffer");

    GLenum err = glewInit();

    if (err != GLEW_OK)
    {
        cout << "GLEW initialization failed!" << endl;
        return 1;
    }

    setup();
    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}