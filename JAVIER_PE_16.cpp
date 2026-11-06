// Exercise Q16 — Toggleable Face Culling [Hard]
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
#include <GL/freeglut.h>
using namespace std;

// global variable for face culling
bool cullingEnabled = false;

// two triangles
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    if (cullingEnabled)
    {
        glEnable(GL_CULL_FACE);
    }
    else
    {
        glDisable(GL_CULL_FACE);
    }

    glCullFace(GL_BACK);

    // counter-clockwise triangle (left)
    glColor3f(0.0f, 0.8f, 1.0f);

    glBegin(GL_TRIANGLES);

        glVertex2f(-0.8f, 0.5f);
        glVertex2f(-0.8f, -0.5f);
        glVertex2f(-0.2f, 0.0f);

    glEnd();

    // clockwise triangle (right)
    glColor3f(1.0f, 0.4f, 0.1f);

    glBegin(GL_TRIANGLES);

        glVertex2f(0.2f, 0.0f);
        glVertex2f(0.8f, -0.5f);
        glVertex2f(0.8f, 0.5f);

    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);

    glRasterPos2f(-0.95f, 0.85f);

    const char* status = cullingEnabled
        ? "Face Culling: ON (Press F to toggle)"
        : "Face Culling: OFF (Press F to toggle)";

    for (int i = 0; status[i] != '\0'; i++)
    {
        glutBitmapCharacter(
            GLUT_BITMAP_HELVETICA_18,
            status[i]
        );
    }

    glRasterPos2f(-0.95f, -0.85f);

    const char* instruction = "Cyan = Counter-clockwise | Orange = Clockwise";

    for (int i = 0; instruction[i] != '\0'; i++)
    {
        glutBitmapCharacter(
            GLUT_BITMAP_HELVETICA_12,
            instruction[i]
        );
    }

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'f' || key == 'F')
    {
        cullingEnabled = !cullingEnabled;

        if (cullingEnabled)
        {
            cout << "Face Culling: ON" << endl;
        }
        else
        {
            cout << "Face Culling: OFF" << endl;
        }

        glutPostRedisplay();
    }

    if (key == 27)
    {
        glutLeaveMainLoop();
    }
}

void init()
{
    glClearColor(0.08f, 0.08f, 0.12f, 1.0f);
    glFrontFace(GL_CCW);
    glDisable(GL_CULL_FACE);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Exercise Q16 - Toggleable Face Culling");

    GLenum err = glewInit();

    if (err != GLEW_OK)
    {
        cout << "GLEW initialization failed!" << endl;
        return 1;
    }

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    cout << "=================================" << endl;
    cout << "     TOGGLEABLE FACE CULLING     " << endl;
    cout << "=================================" << endl;
    cout << "Press F: Toggle face culling" << endl;
    cout << "Press ESC: Exit program" << endl;
    cout << "=================================" << endl;

    glutMainLoop();

    return 0;
}