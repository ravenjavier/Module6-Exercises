// Exercise Q20 — Capstone: Rotating and Drifting Color Cube [Hard]
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <GL/freeglut.h>
using namespace std;

// three faces - front, right, and top
GLfloat vertices[] = {
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

// one rgb color for each vertex
GLfloat colors[] = {
    // front face
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f,

    // right face
    1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 1.0f,
    1.0f, 0.5f, 0.0f,
    0.0f, 0.5f, 1.0f,

    // top face
    1.0f, 0.3f, 0.3f,
    0.3f, 1.0f, 0.3f,
    0.3f, 0.3f, 1.0f,
    1.0f, 1.0f, 1.0f
};

GLuint VBO = 0;

const int vertexCount = 12;

const float rotationStep = 10.0f;
const float driftX = 0.10f;
const float driftY = 0.10f;

// rotate all vertices around the Z-axis
void rotateZ(float &x, float &y, float &z, float degrees)
{
    float radians = degrees * 3.14159265f / 180.0f;

    float c = cosf(radians);
    float s = sinf(radians);

    float newX = c * x - s * y;
    float newY = s * x + c * y;

    x = newX;
    y = newY;
}

// translate a vertex
void translate(float &x, float &y, float &z,
               float tx, float ty, float tz)
{
    x += tx;
    y += ty;
    z += tz;
}

void initializeVBO()
{
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    GLsizeiptr positionSize = sizeof(vertices);
    GLsizeiptr colorSize = sizeof(colors);
    GLsizeiptr totalSize = positionSize + colorSize;

    glBufferData(GL_ARRAY_BUFFER, totalSize, NULL, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, positionSize, vertices);
    glBufferSubData(GL_ARRAY_BUFFER, positionSize, colorSize, colors);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
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

    glVertexPointer(3, GL_FLOAT, 0, (void*)0);
    glColorPointer(3, GL_FLOAT, 0, (void*)sizeof(vertices));

    glDrawArrays(GL_QUADS, 0, vertexCount);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glutSwapBuffers();
}

void timer(int value)
{
    for (int i = 0; i < vertexCount * 3; i += 3)
    {
        float x = vertices[i];
        float y = vertices[i + 1];
        float z = vertices[i + 2];

        rotateZ(x, y, z, rotationStep);
        translate(x, y, z, driftX, driftY, 0.0f);

        vertices[i]     = x;
        vertices[i + 1] = y;
        vertices[i + 2] = z;
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glutPostRedisplay();

    glutTimerFunc(1000, timer, 0);
}

void monitorKeyboard(unsigned char key, int x, int y)
{
    if (key == 27)
    {
        cout << "ESC pressed. Cleaning up..." << endl;

        if (VBO != 0)
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glDeleteBuffers(1, &VBO);
            VBO = 0;

            cout << "One combined VBO released." << endl;
        }

        cout << "Program closing." << endl;

        exit(0);
    }
}

void initialize()
{
    glClearColor(0.08f, 0.08f, 0.12f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    initializeVBO();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Exercise Q20 - Capstone: Rotating and Drifting Color Cube");
    GLenum status = glewInit();
    if (status != GLEW_OK)
    {
        cout << "GLEW initialization failed!" << endl;
        return 1;
    }

    initialize();

    glutDisplayFunc(display);
    glutKeyboardFunc(monitorKeyboard);

    glutTimerFunc(1000, timer, 0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(
        45.0,
        800.0 / 600.0,
        0.1,
        100.0
    );

    glMatrixMode(GL_MODELVIEW);

    cout << "Rotating and Drifting Color Cube" << endl;
    cout << "Rotation: 10 degrees per second" << endl;
    cout << "Translation: 0.10 units diagonally per second" << endl;
    cout << "Press ESC to release the VBO and exit." << endl;

    glutMainLoop();

    return 0;
}
