// Exercise Q07 — glArrayElement Basics [Easy]
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

// triangle vertex positions (X, Y, Z)
GLfloat vertices[] = {
     0.0f,  0.5f, 0.0f,  // vertex 0 - top
    -0.5f, -0.5f, 0.0f,  // vertex 1 - left
     0.5f, -0.5f, 0.0f   // vertex 2 - right
};

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, (void*)0);
    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_TRIANGLES);

        glArrayElement(0);
        glArrayElement(1);
        glArrayElement(2);

    glEnd();

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

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    cout << "===== GLARRAYELEMENT BASICS =====" << endl;
    cout << "VBO created successfully!" << endl;
    cout << "Number of vertices: 3" << endl;
    cout << "Triangle ready to display!" << endl;
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Exercise Q07 - glArrayElement Basics");
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