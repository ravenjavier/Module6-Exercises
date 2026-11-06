// Exercise Q13 — Rotation and Homogeneous Coordinates [Medium]
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
#include <iomanip>
#include <GL/freeglut.h>
using namespace std;

// rotate a vector around the z-axis
void rotateZ(float degrees, float vector[4], float result[4])
{
    float radians = degrees * 3.14159265f / 180.0f;

    float c = cosf(radians);
    float s = sinf(radians);

    // z-axis rotation matrix
    float Rz[16] = {
         c, -s, 0, 0,
         s,  c, 0, 0,
         0,  0, 1, 0,
         0,  0, 0, 1
    };

    // matrix multiplication
    for (int row = 0; row < 4; row++)
    {
        result[row] = 0.0f;

        for (int col = 0; col < 4; col++)
        {
            result[row] += Rz[row * 4 + col] * vector[col];
        }
    }

}

// print vector results
void printVector(const char* label, float v[4])
{
    cout << label << endl;

    cout << "X = " << v[0] << endl;
    cout << "Y = " << v[1] << endl;
    cout << "Z = " << v[2] << endl;
    cout << "W = " << v[3] << endl;

    cout << "------------------------" << endl;
}

void drawText(float x, float y, const char* text)
{
    glRasterPos2f(x, y);

    for (int i = 0; text[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
    }
}

void drawArrow(float x, float y, float r, float g, float b)
{
    glColor3f(r, g, b);
    glLineWidth(3.0f);

    // main arrow line
    glBegin(GL_LINES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(x, y);
    glEnd();

    // arrow head
    glBegin(GL_LINES);

        if (x > 0.5f)
        {
            glVertex2f(x, y);
            glVertex2f(x - 0.15f, y + 0.10f);

            glVertex2f(x, y);
            glVertex2f(x - 0.15f, y - 0.10f);
        }
        else if (y > 0.5f)
        {
            glVertex2f(x, y);
            glVertex2f(x - 0.10f, y - 0.15f);

            glVertex2f(x, y);
            glVertex2f(x + 0.10f, y - 0.15f);
        }

    glEnd();

    glLineWidth(1.0f);
}

// coordinate axes
void drawAxes()
{
    glLineWidth(1.0f);
    glColor3f(0.6f, 0.6f, 0.6f);

    glBegin(GL_LINES);

        // X-axis
        glVertex2f(-1.3f, 0.0f);
        glVertex2f(1.3f, 0.0f);

        // Y-axis
        glVertex2f(0.0f, -1.3f);
        glVertex2f(0.0f, 1.3f);

    glEnd();

    glColor3f(1, 1, 1);
    drawText(1.15f, -0.12f, "X");
    drawText(0.08f, 1.15f, "Y");
    drawText(0.08f, -0.12f, "O");
}

// comparison panel
void drawPanel(const char* title, const char* wLabel)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.5, 1.5, -1.5, 1.5);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawAxes();

    // original vector - red arrow pointing right
    drawArrow(1.0f, 0.0f, 1.0f, 0.2f, 0.2f);

    // rotated vector - blue arrow pointing upward
    drawArrow(0.0f, 1.0f, 0.2f, 0.7f, 1.0f);

    // panel labels
    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(-1.35f, 1.35f, title);
    drawText(-1.35f, 1.20f, wLabel);

    // arrow labels
    glColor3f(1.0f, 0.3f, 0.3f);
    drawText(0.65f, -0.25f, "Original");

    glColor3f(0.2f, 0.7f, 1.0f);
    drawText(0.12f, 0.85f, "Rotated");
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);

    // left panel - position vector
    glViewport(0, 0, width / 2, height);
    drawPanel("POSITION VECTOR", "W = 1");

    // right panel - direction vector
    glViewport(width / 2, 0, width / 2, height);
    drawPanel("DIRECTION VECTOR", "W = 0");

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    // original position vector (w = 1)
    float position[4] = {
        1.0f, 0.0f, 0.0f, 1.0f
    };

    // original direction vector (w = 0)
    float direction[4] = {
        1.0f, 0.0f, 0.0f, 0.0f
    };

    float rotatedPosition[4];
    float rotatedDirection[4];

    // Apply the same 90-degree rotation
    rotateZ(90.0f, position, rotatedPosition);
    rotateZ(90.0f, direction, rotatedDirection);

    // Display console results
    cout << fixed << setprecision(2);

    cout << "=====================================" << endl;
    cout << "ROTATION AND HOMOGENEOUS COORDINATES" << endl;
    cout << "=====================================" << endl;

    cout << "Rotation: 90 degrees around Z-axis" << endl;
    cout << "---------------------------------" << endl;

    printVector("ROTATED POSITION (W = 1):", rotatedPosition);
    printVector("ROTATED DIRECTION (W = 0):", rotatedDirection);

    cout << "CONCLUSION:" << endl;
    cout << "Both vectors rotate around the z-axis." << endl;
    cout << "Position keeps W = 1." << endl;
    cout << "Direction keeps W = 0." << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(900, 500);
    glutCreateWindow("Exercise Q13 - Rotation and Homogeneous Coordinates");

    glClearColor(0.08f, 0.08f, 0.12f, 1.0f);

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}