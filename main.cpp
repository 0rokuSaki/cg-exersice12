/*****************************************************************//**
 * \file   main.cpp
 * \brief  My solution for exersice ('Maman') 12 in Computer Graphics (20562) course
 * 
 * This program marks the intersection point of two lines in OpenGL.
 * You can change the value of the points in 'main' function.
 * 
 * Repo link: https://github.com/0rokuSaki/cg-exersice12
 * 
 * *** BUILD INSTRUCTIONS (VS2019/VS2022 Windows 11) ***
 * 1. Setup OpenGL: https://www.geeksforgeeks.org/how-to-setup-opengl-with-visual-studio-2019-on-windows-10/.
 * 2. Select x86 Debug configuration.
 * 3. Build the solution (ctrl + shift + B).
 * 
 * \author aaron
 * \date   March 2023
 *********************************************************************/

#include <Windows.h>
#include <GL/glut.h>
#include <cfloat>
#include <cmath>

#include "Point.h"


/* Window constants */
#define WINDOW_X_OFFSET   100u         // Initial window left-offset
#define WINDOW_Y_OFFSET   100u         // Initial window top-offset
#define WINDOW_HEIGHT     500u         // Initial window height
#define WINDOW_WIDTH      500u         // Initial window width
#define X_COORD_MAX       100.0        // X coord max value
#define Y_COORD_MAX       100.0        // Y coord max value
#define WINDOW_TITLE    "CG Maman 12"  // Window title

/* Line constants */
#define LINE_WIDTH         5.0f              // Width of lines
#define LINE_COLOR_1       1.0f, 0.0f, 0.0f  // First line color
#define LINE_COLOR_2       0.0f, 1.0f, 0.0f  // Second line color
#define INTERSECTION_COLOR 0.0f, 0.0f, 1.0f  // Intersection point color

/* Other constants */
#define EPSILON 0.0001


/* Points */
Point P, Q, R, S;


/* Creates and initializes GLUT display-window. */
void createWindow(int argc, char** argv)
{
    /* Create the window */
    glutInit(&argc, argv);                        // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // Set display mode
    glutInitWindowPosition(WINDOW_X_OFFSET, WINDOW_Y_OFFSET);  // Set top-left window position
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);           // Set window width and height
    glutCreateWindow(WINDOW_TITLE);  // Create window

    /* Initialize the window */
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);  // Set window color to white
}


/**
 * Checks if two lines AB and CD intersect. Based on cramer's rule for solving a
 * system of linear equations.
 * 
 * \param A point A of line AB.
 * \param B point B of line AB.
 * \param C point C of line CD.
 * \param D point D of line CD.
 * \return Intersecion point if lines intersect. If they don't, then (DBL_MAX, DBL_MAX).
 */
Point twoLineIntersection(const Point& A, const Point& B, const Point& C, const Point& D)
{
    // Line RS is represented as a1*x + b1*y = c1
    const double a1 = A.y - B.y;
    const double b1 = B.x - A.x;
    const double c1 = a1 * A.x + b1 * A.y;

    // Line PQ is represented as a2*x + b2*y = c2
    const double a2 = C.y - D.y;
    const double b2 = D.x - C.x;
    const double c2 = a2 * C.x + b2 * C.y;

    const double determinant = a1 * b2 - a2 * b1;

    if (abs(determinant) <= EPSILON)
    {
        // The lines are parallel. This is simplified
        // by returning the pair (DBL_MAX, DBL_MAX)
        return Point(DBL_MAX, DBL_MAX);
    }
    else
    {
        const double xIntersect = (b2 * c1 - b1 * c2) / determinant;
        const double yIntersect = (a1 * c2 - a2 * c1) / determinant;
        return Point(xIntersect, yIntersect);
    }
}


/* Checks if a point P is inside the rectangle defined by A and B. */
bool isBetweenTwoPoints(const Point& P, const Point& A, const Point& B)
{
    double xMax = max(A.x, B.x), xMin = min(A.x, B.x);
    double yMax = max(A.y, B.y), yMin = min(A.y, B.y);
    return (xMin <= P.x && P.x <= xMax) && (yMin <= P.y && P.y <= yMax);
}


void displayLines(void)
{
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, X_COORD_MAX, 0.0, Y_COORD_MAX);

    /* Draw the lines in different colors */
    glLineWidth(LINE_WIDTH);

    glColor3f(LINE_COLOR_1);
    glBegin(GL_LINES);
        glVertex2d(P.x, P.y);
        glVertex2d(Q.x, Q.y);
    glEnd();

    glColor3f(LINE_COLOR_2);
    glBegin(GL_LINES);
        glVertex2d(R.x, R.y);
        glVertex2d(S.x, S.y);
    glEnd();

    /* Check if lines intersect */
    Point intersection = twoLineIntersection(P, Q, R, S);
    if (intersection.x != DBL_MAX && intersection.y != DBL_MAX &&
        isBetweenTwoPoints(intersection, P, Q))
    {
        /* Draw intersection point */
        glColor3f(INTERSECTION_COLOR);
        glPointSize(LINE_WIDTH);
        glBegin(GL_POINTS);
            glVertex2d(intersection.x, intersection.y);
        glEnd();
    }
}


/* Callback for 'glutDisplayFunc' */
void displayCallback(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    displayLines();

    glFlush();
}


/* Assigns callback functions for events */
void registerCallbacks(void)
{
    glutDisplayFunc(displayCallback);
}


/* Main function */
int main(int argc, char** argv)
{
    /* Initialize points */
    P = Point(1,78), Q = Point(66, 42);
    R = Point(71, 16), S = Point(15, 82);

    createWindow(argc, argv);  // Create the display-window
    registerCallbacks();       // Assign callback functions for events
    glutMainLoop();            // Display everything and wait
}
