/*
                    ***** callbacks.cpp *****

OpenGL graphics program, illustrating use of GLUT and callback functions.

Author: John M. Weiss, Ph.D.
Class:  CSC 315 Data Structures & Algorithms
Date:   Spring 2018

Modifications:
*/

// include files
#include <cstdlib>
#include <iostream>
using namespace std;

// the GLUT header automatically includes gl.h and glu.h
#include <GL/freeglut.h>
#include "globals.h"
#include "callbacks.h"
#include "graphics.h"

/******************************************************************************/
/*                          OpenGL callback functions                         */
/******************************************************************************/

// callback function that tells OpenGL how to redraw window
void display( void )
{
    // clear the display
    glClear( GL_COLOR_BUFFER_BIT );

    // draw a line, rectangle, a filled rectangle, and a circle
    // note that objects are NOT resized with window (except line)
    DrawLine( 10, 20, ScreenWidth - 10, ScreenHeight - 20, Yellow );
    DrawRectangle( 500, 400, 700, 500, Cyan );
    DrawFilledRectangle( 200, 100, 300, 300, Red );
    DrawEllipse( 100, 50, 600, 200, Green );
    DrawFilledEllipse( 100, 50, 250, 450, Magenta );

    // label display with text
    DrawTextString( "OpenGL Demo", 32, ScreenHeight - 32, White );

    // flush graphical output
    glFlush();
}

/******************************************************************************/

// callback function that tells OpenGL how to resize window
// note that this is called when the window is first created
void reshape( int w, int h )
{
    // store new window dimensions globally
    ScreenWidth = w;
    ScreenHeight = h;

    // how to project 3-D scene onto 2-D
    glMatrixMode( GL_PROJECTION );		// use an orthographic projection
    glLoadIdentity();				// initialize transformation matrix
    gluOrtho2D( 0.0, w, 0.0, h );		// make OpenGL coordinates
    glViewport( 0, 0, w, h );			// the same as the screen coordinates
}

/******************************************************************************/

// callback function that tells OpenGL how to handle keystrokes
void keyboard( unsigned char key, int x, int y )
{
    // correct for upside-down screen coordinates
    y = ScreenHeight - y;
    cerr << "keypress: " << key << " (" << int( key ) << ") at (" << x << "," << y << ")\n";

    switch ( key )
    {
        // Escape quits program
	case 'q':
	case EscapeKey:
	    exit( 0 );
	    break;

        // anything else redraws window
	default:
	    glutPostRedisplay();
	    break;
    }
}

/******************************************************************************/

// callback function for mouse button click events
void mouseclick( int button, int state, int x, int y )
{
    // correct for upside-down screen coordinates
    y = ScreenHeight - y;

    // handle mouse click events
    switch ( button )
    {
	case GLUT_LEFT_BUTTON:				// left button: should create objects
	    if ( state == GLUT_DOWN )			// press
		cerr << "mouse click: left press at    (" << x << "," << y << ")\n";
	    else if ( state == GLUT_UP )		// release
		cerr << "mouse click: left release at  (" << x << "," << y << ")\n";
	    break;

	case GLUT_RIGHT_BUTTON:				// right button: should move objects
	    if ( state == GLUT_DOWN )			// press
		cerr << "mouse click: right press at   (" << x << "," << y << ")\n";
	    else if ( state == GLUT_UP )		// release
		cerr << "mouse click: right release at (" << x << "," << y << ")\n";
	    break;
    }
}
