// Exercise Q19 — Continuous Y-Axis Rotation With Cleanup [Hard] 
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

// quad vertices - x, y, z
GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};

// one color for each vertex - r, g, b
GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,  // red
    0.0f, 1.0f, 0.0f,  // green
    0.0f, 0.0f, 1.0f,  // blue
    1.0f, 1.0f, 0.0f   // yellow
};

GLuint VBO;
float angleY = 0.0f;

// rotate the quad around the Y-axis
void rotateY(float degrees)
{
    float radians = degrees * 3.14159265f / 180.0f;

    float c = cosf(radians);
    float s = sinf(radians);

    // y-axis rotation matrix (row-major and column-vector convention)
    float R[16] = {
         c, 0.0f,  s, 0.0f,
         0.0f, 1.0f, 0.0f, 0.0f,
        -s, 0.0f,  c, 0.0f,
         0.0f, 0.0f, 0.0f, 1.0f
    };

    for (int i = 0; i < 12; i += 3)
    {
        float x = vertices[i];
        float y = vertices[i + 1];
        float z = vertices[i + 2];

        vertices[i]     = R[0] * x + R[1] * y + R[2] * z;
        vertices[i + 1] = R[4] * x + R[5] * y + R[6] * z;
        vertices[i + 2] = R[8] * x + R[9] * y + R[10] * z;
    }
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

// draws the rotating quad
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(
        2.5, 2.0, 3.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0
    );

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, (void*)0);
    glColorPointer(3, GL_FLOAT, 0, (void*)sizeof(vertices));

    glDrawArrays(GL_QUADS, 0, 4);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glutSwapBuffers();
}

// rotate once every second
void timer(int value)
{
    rotateY(15.0f);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glutPostRedisplay();
    glutTimerFunc(1000, timer, 0);
}

void monitorKeyboard(unsigned char key, int x, int y)
{
    if (key == 27) // esc key
    {
        cout << "ESC pressed. Releasing VBO..." << endl;

        if (VBO != 0)
        {
            glDeleteBuffers(1, &VBO);
            VBO = 0;
        }

        cout << "VBO released. Closing program." << endl;

        exit(0);
    }
}

void initialize()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    initializeVBO();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 500);
    glutCreateWindow("Exercise Q19 - Continuous Y-Axis Rotation With Cleanup");
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
    gluPerspective(45.0, 700.0 / 500.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);

    cout << "Continuous Y-Axis Rotation" << endl;
    cout << "Press ESC to release the VBO and exit." << endl;

    glutMainLoop();

    return 0;
}