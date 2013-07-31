// teapot.cpp: Displays a teapot using GLEW
//
// Copyright (c) 2013 Ashwin Nanjappa
//
// Released under the MIT License.
// Please see the LICENSE file for details.

#include <cstdio>
#include <GL/glew.h>
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

char* readShaderFile(const char* fname)
{
    FILE* f = fopen(fname, "r");
    fseek(f, 0, SEEK_END);
    const long charNum = ftell(f);

    fseek(f, 0, SEEK_SET);
    char * fileBuf = (char *) malloc(charNum + 1);
    fread(fileBuf, charNum, 1, f);
    fileBuf[charNum] = '\0';
    fclose(f);

    return fileBuf;
}

GLhandleARB v;
GLhandleARB f;
GLhandleARB p;

void setShaders()
{
    v = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
    f = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);

    char* vs = readShaderFile("teapot.vert");
    char* fs = readShaderFile("teapot.frag");

    const char* vv = vs;
    const char* ff = fs;

    glShaderSourceARB(v, 1, &vv, NULL);
    glShaderSourceARB(f, 1, &ff, NULL);

    free(vs);
    free(fs);

    glCompileShaderARB(v);
    glCompileShaderARB(f);

    p = glCreateProgramObjectARB();
    glAttachObjectARB(p,f);
    glAttachObjectARB(p,v);

    glLinkProgramARB(p);
    glUseProgramObjectARB(p);
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

    if (GLEW_OK != glewInit())
    {
        printf("GLEW init error!\n");
        exit(1);
    }

    if (!GLEW_ARB_vertex_shader || !GLEW_ARB_fragment_shader)
    {
        printf("No GLSL support\n");
        exit(1);
    }

    setShaders();
    glutMainLoop();

    return 0;
}
