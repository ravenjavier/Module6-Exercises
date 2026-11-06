// Exercise Q15 — Scaled-Then-Animated Color Cube [Hard]
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
#include <GL/freeglut.h>
using namespace std;

// three faces of the cube - front, right, and top
GLfloat positions[] = {
    // front face
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,

    // right face
     1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,

    // top face
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f
};

// four colors per face and one for each vertex
GLfloat colors[] = {
    // front face - red, green, blue, yellow
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f,

    // right face - cyan, magenta, orange, white
    0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f,
    1.0f, 0.5f, 0.0f,
    1.0f, 1.0f, 1.0f,

    // top face - pink, light green, purple, orange
    1.0f, 0.3f, 0.5f,
    0.3f, 1.0f, 0.3f,
    0.5f, 0.3f, 1.0f,
    1.0f, 0.6f, 0.2f
};

GLuint VBO;

bool ready = false;

void scaleAll(float sx, float sy, float sz)
{
    for (int i = 0; i < 36; i += 3)
    {
        positions[i]     *= sx;
        positions[i + 1] *= sy;
        positions[i + 2] *= sz;
    }
}

void translate(float tx, float ty, float tz)
{
    for (int i = 0; i < 36; i += 3)
    {
        positions[i]     += tx;
        positions[i + 1] += ty;
        positions[i + 2] += tz;
    }
}

void updateVBO()
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    GLsizeiptr positionSize = sizeof(positions);
    GLsizeiptr colorSize = sizeof(colors);
    GLsizeiptr totalSize = positionSize + colorSize;

    if (!ready)
    {
        scaleAll(0.5f, 0.5f, 0.5f);

        glBufferData(
            GL_ARRAY_BUFFER,
            totalSize,
            NULL,
            GL_DYNAMIC_DRAW
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

        ready = true;

        cout << "Initial VBO upload completed!" << endl;
        cout << "Cube scaled down by half." << endl;
    }
    else
    {
        glBufferSubData(
            GL_ARRAY_BUFFER,
            0,
            positionSize,
            positions
        );
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void timer(int value)
{
    translate(0.15f, 0.15f, 0.0f);
    updateVBO();
    glutPostRedisplay();
    glutTimerFunc(1000, timer, 0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        4.0, 3.0, 5.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0
    );

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer( 3, GL_FLOAT, 0, (void*)0);
    glColorPointer(3, GL_FLOAT, 0, (void*)sizeof(positions));
    glDrawArrays(GL_QUADS, 0, 12);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glutSwapBuffers();
}

void reshape(int width, int height)
{
    if (height == 0)
        height = 1;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(
        45.0,
        (double)width / height,
        1.0,
        100.0
    );

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Exercise Q15 - Scaled-Then-Animated Color Cube");
    
    GLenum err = glewInit();

    if (err != GLEW_OK)
    {
        cout << "GLEW initialization failed!" << endl;
        return 1;
    }

    glEnable(GL_DEPTH_TEST);

    glClearColor(
        0.08f, 0.08f, 0.12f, 1.0f
    );

    glGenBuffers(1, &VBO);
    updateVBO();

    cout << "=========================" << endl;
    cout << "SCALED-THEN-ANIMATED CUBE" << endl;
    cout << "=========================" << endl;
    cout << "Number of faces: 3" << endl;
    cout << "Scaling: 0.5 (once at startup)" << endl;
    cout << "Translation: 0.15 X and 0.15 Y" << endl;
    cout << "Animation interval: 1 second" << endl;
    cout << "=================================" << endl;

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutTimerFunc(1000, timer, 0);

    glutMainLoop();

    return 0;
}