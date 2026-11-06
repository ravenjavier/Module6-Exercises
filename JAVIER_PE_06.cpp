// Exercise Q06 — glBufferSubData for a Colored Line [Easy]
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
#include <GL/freeglut.h>
using namespace std;

// VBO ID
GLuint VBO;

// position data of two endpoints
GLfloat positions[] = {
    -0.5f, 0.0f, 0.0f,
     0.5f, 0.0f, 0.0f
};

// color data - red and green
GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,  // first endpoint - red
    0.0f, 1.0f, 0.0f   // second endpoint - green
};

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, (void*)0);

    glColorPointer(
        3,
        GL_FLOAT,
        0,
        (void*)sizeof(positions)
    );

    // draw line
    glLineWidth(5.0f);
    glDrawArrays(GL_LINES, 0, 2);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glutSwapBuffers();
}

void init()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    // calculate memory sizes
    GLsizeiptr positionSize = sizeof(positions);
    GLsizeiptr colorSize = sizeof(colors);

    // total space for both data blocks
    GLsizeiptr totalSize = positionSize + colorSize;

    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        totalSize,
        NULL,
        GL_STATIC_DRAW
    );

    glBufferSubData(
        GL_ARRAY_BUFFER,
        0,
        positionSize,
        positions
    );

    glBufferSubData(
        GL_ARRAY_BUFFER,
        positionSize,
        colorSize,
        colors
    );

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    cout << "===== GLBUFFERSUBDATA =====" << endl;
    cout << "Position data size: "
         << positionSize << " bytes" << endl;

    cout << "Color data size: "
         << colorSize << " bytes" << endl;

    cout << "Total VBO size: "
         << totalSize << " bytes" << endl;

    cout << "Color offset: "
         << positionSize << " bytes" << endl;

    cout << "VBO data uploaded successfully!" << endl;
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Exercise Q06 - glBufferSubData for a Colored Line");
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        cout << "GLEW initialization failed!" << endl;
        return 1;
    }

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}