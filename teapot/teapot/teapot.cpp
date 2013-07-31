// teapot.cpp: Displays a teapot
//
// Copyright (c) 2013 Ashwin Nanjappa
//
// Released under the MIT License.
// Please see the LICENSE file for details.

#include <GL/glut.h>

void initGraphics()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    const float lightPos[4] = {1, .5, 1, 0};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void onResize(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(40, (float) w / h, 1, 100);
    glMatrixMode(GL_MODELVIEW);
}

void onDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0,
              0.0, 0.0, 1.0,
              0.0, 1.0, 0.0);
    glutSolidTeapot(1);
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Teapot");

    initGraphics();
    glutDisplayFunc(onDisplay);
    glutReshapeFunc(onResize);

    glutMainLoop();
    return 0;
}