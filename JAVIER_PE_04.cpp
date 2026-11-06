// Exercise Q04 — A Simple translateX() Helper [Easy]
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

// triangle vertex data (X, Y, Z)
GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,  // Vertex 1
     0.5f, -0.5f, 0.0f,  // Vertex 2
     0.0f,  0.5f, 0.0f   // Vertex 3
};

// translateX function
void translateX(float x, int startindex)
{
    GLfloat* mapV = (GLfloat*)glMapBuffer(
        GL_ARRAY_BUFFER,
        GL_READ_WRITE
    );

    if (mapV == NULL)
    {
        cout << "Error: Unable to map VBO!" << endl;
        return;
    }

    mapV[startindex] += x;

    if (glUnmapBuffer(GL_ARRAY_BUFFER) == GL_FALSE)
    {
        cout << "Error: VBO data became invalid!" << endl;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableClientState(GL_VERTEX_ARRAY);

    // set vertex pointer
    glVertexPointer(3, GL_FLOAT, 0, (void*)0);

    // draw the translated triangle
    glColor3f(0.0f, 0.7f, 1.0f);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glutSwapBuffers();
}

void init()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
    glMatrixMode(GL_MODELVIEW);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    translateX(0.5f, 0);  // Vertex 1
    translateX(0.5f, 3);  // Vertex 2
    translateX(0.5f, 6);  // Vertex 3
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    cout << "===== TRANSLATE X =====" << endl;
    cout << "Translation amount: 0.5" << endl;
    cout << "Triangle translated to the right!" << endl;
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Exercise Q04 - A Simple translateX() Helper");
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