// Exercise Q17 — Triggering the Error Callback [Hard] 
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
#include <GL/freeglut.h>
using namespace std;

// opengL debug callback function
void APIENTRY debugCallback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    cout << "\n=================================" << endl;
    cout << " OPENGL DEBUG CALLBACK TRIGGERED" << endl;
    cout << "=================================" << endl;

    cout << "Message ID: " << id << endl;
    cout << "Source: " << source << endl;
    cout << "Type: " << type << endl;
    cout << "Severity: " << severity << endl;

    cout << "Diagnostic message: ";

    if (length > 0)
        cout.write(message, length);
    else
        cout << message;

    cout << endl;
    cout << "=================================" << endl;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

void init()
{
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debugCallback, NULL);

    cout << "OpenGL debug callback registered!" << endl;

    while (glGetError() != GL_NO_ERROR)
    {
        // clear existing errors
    }

    cout << "\nTriggering an intentional OpenGL error..." << endl;

    glEnable((GLenum)0xFFFFFFFF);

    glFinish();

    GLenum error = glGetError();

    if (error == GL_INVALID_ENUM)
    {
        cout << "\nOpenGL error confirmed: GL_INVALID_ENUM" << endl;
    }
    else
    {
        cout << "\nUnexpected error code: " << error << endl;
    }

    cout << "\nProgram continues running." << endl;
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutInitContextFlags(GLUT_DEBUG);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Exercise Q17 - Triggering the Error Callback");

    GLenum err = glewInit();

    if (err != GLEW_OK)
    {
        cout << "GLEW initialization failed: "
             << glewGetErrorString(err) << endl;
        return 1;
    }

    if (!GLEW_VERSION_4_3 && !GLEW_KHR_debug)
    {
        cout << "OpenGL debug output is not supported!" << endl;
        return 1;
    }

    cout << "==============================" << endl;
    cout << "TRIGGERING THE ERROR CALLBACK" << endl;
    cout << "==============================" << endl;

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}