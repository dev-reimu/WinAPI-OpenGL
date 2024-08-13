#include <windows.h>
#include <GL/gl.h>



void opengl_update(HDC dc) {

    glClearColor(0.1f, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
 
    glBegin(GL_TRIANGLES);

    glColor3f(1, 0, 0);
    glVertex2f(0, 0.5f);
    glColor3f(0, 1, 0);
    glVertex2f(-0.25f, -0.5f);
    glColor3f(0, 0, 1);
    glVertex2f(0.25f, -0.5f);

    glEnd();
    SwapBuffers(dc);

}
