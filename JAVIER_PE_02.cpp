// Exercise Q02 — VBO Conversion of One Cube Face [Easy]
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

// VBO ID
GLuint VBO;

GLfloat vertices[] = {
    -1.0f,  1.0f, -1.0f,  // top-left
     1.0f,  1.0f, -1.0f,  // top-right
     1.0f,  1.0f,  1.0f,  // bottom-right
    -1.0f,  1.0f,  1.0f   // bottom-left
};

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // camera position
    gluLookAt(3.0, 3.0, 5.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glColor3f(0.0f, 0.6f, 1.0f);
    glEnableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexPointer(3, GL_FLOAT, 0, (void*)0);
    glDrawArrays(GL_QUADS, 0, 4);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glutSwapBuffers();
}

void init()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    // unbind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Exercise Q02 - VBO Conversion of One Cube Face");
    // initialize GLEW after creating the OpenGL context
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