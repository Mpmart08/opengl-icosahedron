// Draw an Icosahedron
// ECE4122/8893 Project 5

#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

#define NFACE 20
#define NVERTEX 12

#define X .525731112119133606 
#define Z .850650808352039932
#define WIN 500

// These are the 12 vertices for the icosahedron
static GLfloat vdata[NVERTEX][3] = {    
     {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},    
     {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},    
     {Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0} 
};

// These are the 20 faces.  Each of the three entries for each 
// vertex gives the 3 vertices that make the face.
static GLint tindices[NFACE][3] = { 
     {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},    
     {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},    
     {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6}, 
     {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11} };

int testNumber; // Global variable indicating which test number is desired
int depth;
static int updateRate = 10;
 
void drawTriangle(GLfloat* v1, GLfloat* v2, GLfloat* v3, GLfloat r, GLfloat g, GLfloat b)
{
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 1.0, 1.0); // White triangles
    glColor3f(r, g, b); // Random colored triangles
    glNormal3fv(v1); glVertex3fv(v1);
    glNormal3fv(v2); glVertex3fv(v2);
    glNormal3fv(v3); glVertex3fv(v3);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0, 1.0, 1.0); // White lines
    glNormal3fv(v1); glVertex3fv(v1);
    glNormal3fv(v2); glVertex3fv(v2);
    glNormal3fv(v3); glVertex3fv(v3);
    glEnd();
}

void normalize(GLfloat V[3])
{
    GLfloat d = sqrt((V[0] * V[0]) + (V[1] * V[1]) + (V[2] * V[2]));
    if (d == 0.0) return;
    V[0] /= d;
    V[1] /= d;
    V[2] /= d;
}

void subDivide(GLfloat* v1, GLfloat* v2, GLfloat* v3, int depth)
{
    if (depth == 0){
        GLfloat r = ((GLfloat)rand()) / RAND_MAX;
        GLfloat g = ((GLfloat)rand()) / RAND_MAX;
        GLfloat b = ((GLfloat)rand()) / RAND_MAX;
        drawTriangle(v1, v2, v3, r, g, b);
        return;
    }

    // Find midpoints
    GLfloat v12[3];
    GLfloat v23[3];
    GLfloat v31[3];
    for (int i = 0; i < 3; i++){
        v12[i] = v1[i] + v2[i];
        v23[i] = v2[i] + v3[i];
        v31[i] = v3[i] + v1[i];
    }
    normalize(v12);
    normalize(v23);
    normalize(v31);

    // Draw smaller triangles
    subDivide(v1, v12, v31, depth-1);
    subDivide(v2, v23, v12, depth-1);
    subDivide(v3, v31, v23, depth-1);
    subDivide(v12, v23, v31, depth-1);
}

void draw()
{
    srand(0);
    for (int i = 0; i < NFACE; i++){
        GLfloat r = ((GLfloat)rand()) / RAND_MAX;
        GLfloat g = ((GLfloat)rand()) / RAND_MAX;
        GLfloat b = ((GLfloat)rand()) / RAND_MAX;
        drawTriangle(vdata[tindices[i][0]], vdata[tindices[i][1]], vdata[tindices[i][2]], r, g, b);
    }
}

void draw(int depth)
{
    srand(0);
    for (int i = 0; i < NFACE; i++){
        subDivide(vdata[tindices[i][0]], vdata[tindices[i][1]], vdata[tindices[i][2]], depth);
    }
}

// Test cases.  Fill in your code for each test case
void Test1()
{
    draw();
}

void Test2()
{
    draw();
}

void Test3()
{
    draw(1);
}

void Test4()
{
    draw(1);
}

void Test5(int depth)
{
    draw(depth);
}

void Test6(int depth)
{
    draw(depth);
}

void display(void)
{
    glLineWidth(2); // make the lines pretty
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);
    // clear all
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // draw white Icosahedron
    glColor3f(1.0, 1.0, 1.0);
    // Clear the matrix
    glLoadIdentity();
    // Set the viewing transformation
    gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(WIN/2, WIN/2, 0);
    glScalef(WIN/2, WIN/2, WIN/2);

    // Rotate
    if (testNumber % 2 == 0){
        static GLfloat rotX = 0.0;
        static GLfloat rotY = 0.0;
        glRotatef(rotX, 1.0, 0.0, 0.0);
        glRotatef(rotY, 0.0, 1.0, 0.0);
        rotX += 1.0;
        rotY += 1.0;
    }

    // Draw
    switch(testNumber){
        case 1: Test1(); break;
        case 2: Test2(); break;
        case 3: Test3(); break;
        case 4: Test4(); break;
        case 5: Test5(depth); break;
        case 6: Test6(depth); break;
    }

    glPopMatrix();
    // Flush buffer
    glutSwapBuffers(); // If double buffering
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void reshape(int w, int h)
{
    glViewport(0,0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, (GLdouble)w, (GLdouble)0.0, h, (GLdouble)-w, (GLdouble)w);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000.0 / updateRate, timer, 0);
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cout << "Usage: icosahedron testnumber" << endl;
        exit(1);
    }
    testNumber = atol(argv[1]);
    if (argc > 2) {
        depth = atol(argv[2]);
    }

    // Initialize glut and create your window here
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIN, WIN);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Icosahedron");

    // Set your glut callbacks here
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(1000.0 / updateRate, timer, 0);

    // Enter the glut main loop here
    glutMainLoop();

    return 0;
}

