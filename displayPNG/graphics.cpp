/*
                ***** graphics.cpp *****

OpenGL/GLUT graphics module for image display.

Author: John M. Weiss, Ph.D.
Modified By: Gabriel Hofer, Noah McKenzie
Class:  CSC 315 Data Structures & Algorithms
Date:   Spring 2018
*/

// #include <iostream>
#include <cstdio>
#include <GL/glut.h>
#include <iostream>
#include "image.h"

using namespace std;

typedef unsigned char byte;

// OpenGL callback function prototypes etc.
void display( void );
void reshape( int w, int h );
void keyboard( unsigned char key, int x, int y );
void processMyKeyboardEvents ( int key, int x, int y );
void displayColor( int x, int y, int w, int h, byte** image );
void displayMonochrome( int x, int y, int w, int h, byte** image );
void DrawTextString( char *string, int x, int y, byte r, byte g, byte b );
void display_compression ( );

// symbolic constants
const int ESC = 27;
const int SPACE = 32;

// global vars (unfortunately necessary due to OpenGL callback functions)
static unsigned height, width;
static unsigned int range = 32;
static byte** imageRGB = NULL;
static byte** imageMono = NULL;
static byte** imageQuad = NULL;
static byte** imageWhiteQuad = NULL;
static bool toggle_lines = false;
static int nodes;
static int leaf_nodes;

/************************************************************/

// various commands to initialize OpenGL and GLUT
void initOpenGL( const char *filename, int thresh, unsigned w, unsigned h, byte** imgRGB, 
                 byte** imgGray, byte** imgQuad, byte** imgWhiteQuad )
{
    height = h;
    width = w;
    range = thresh;
    imageRGB = imgRGB;
    imageMono = imgGray;
    imageQuad = imgQuad;
    imageWhiteQuad = imgWhiteQuad;
    
    glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE );	    // 24-bit graphics and single buffering

    glutInitWindowSize( 2 * width, height );	        // initial window size
    glutInitWindowPosition( 0, 0 );			            // initial window position
    glutCreateWindow( filename );			            // window title

    glClearColor( 0.0, 0.0, 0.0, 0.0 );			        // use black for glClear command

    // callback routines
    glutDisplayFunc( display );				// how to redisplay window
    glutReshapeFunc( reshape );				// how to resize window
    glutKeyboardFunc( keyboard );			// how to handle key presses
    glutSpecialFunc( processMyKeyboardEvents );			// how to handle special keys
}

/************************************************************/

// GLUT display callback
void display()
{
    glClear( GL_COLOR_BUFFER_BIT );
    
    // display color and monochrome images, side by side in window
    displayMonochrome( 0, 0, width, height, imageMono );
   
    // statements to toggle between white line quad image and color quad image
    if ( !toggle_lines ) 
    {
        displayMonochrome( width, 0, width, height, imageWhiteQuad );
    }
    else 
    {
        displayMonochrome( width, 0, width, height, imageQuad );        
    }

    // write text labels (in white)
    char str[257];
    sprintf( str, "Original Image" );
    DrawTextString( str, 8, 8, 255, 255, 255 );
    sprintf( str, "Quadtree Image" );
    DrawTextString( str, width + 8, 8, 255, 255, 255 );

    //Quadtree Range Output at top of Window
    char title[255];
    sprintf( title,"Range: %d (spacebar toggles quads)", range);
    glutSetWindowTitle( title );

    glFlush(  );
}

// GLUT reshape callback (handles window resizing)
void reshape( int w, int h )
{
    glViewport( 0, 0, w, h );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity(  );
    gluOrtho2D( 0.0, w, 0.0, h );
}

// GLUT keyboard callback
void keyboard( unsigned char key, int x, int y )
{
    switch ( key )
    {
        case ESC:
            exit( 0 );
            break;
        case SPACE:
            // toggle used to display white lined quad image 
            toggle_lines = !toggle_lines;
            break;
    }
    glutPostRedisplay();
}

// handles updating range by pressing up and down arrow keys 
void processMyKeyboardEvents ( int key, int x, int y )
{
    switch ( key )
    {
        case GLUT_KEY_UP:       //if up key         
            if ( range > 255 )
            {
                range = 0;      //wrap range to 0
            }
            range++;
            
            // reset imageQuad and imageWhiteQuad to allow white lines to be removed and added 
            for ( unsigned int u = 0; u < width; u += 1 ) 
            {
                for (  unsigned int v = 0; v < height; v += 1 ) 
                {
                    imageQuad [ u ][ v ] = imageMono [ u ][ v ];
                    imageWhiteQuad [ u ][ v ] = imageMono [ u ][ v ];
                }
            }
            
            // creates imageQuad and imageWhiteQuad with new udpated range.
            // reset the number of nodes and leaf nodes
            leaf_nodes = 0;
            nodes = 1;
            make_quadtree( imageMono, imageQuad, imageWhiteQuad, 0, 0, width, height, range, leaf_nodes, nodes );           
            cout << "nodes " << nodes << "\nleaf nodes " << leaf_nodes << endl;
            display_compression ();
            break;

        case GLUT_KEY_DOWN:     //if down key
            if ( range < 1 )
            {
                range = 255;    //wrap range around to 255
            }
            range--;
 
            // reset imageQuad and imageWhiteQuad to allow white lines to be removed and added 
            for ( unsigned  int u = 0; u < width; u += 1 ) 
            {
                for (  unsigned int v = 0; v < height; v += 1 ) 
                {
                    imageQuad [ u ][ v ] = imageMono [ u ][ v ];
                    imageWhiteQuad [ u ][ v ] = imageMono [ u ][ v ];
                }
            }
 
            // creates imageQuad and imageWhiteQuad with new udpated range.
            // reset the number of nodes and leaf nodes
            leaf_nodes = 0;
            nodes = 1;
            make_quadtree( imageMono, imageQuad, imageWhiteQuad, 0, 0, width, height, range, leaf_nodes, nodes );
            cout << "nodes " << nodes << "\nleaf nodes " << leaf_nodes << endl;
            display_compression ();
            break;
    }
    glutPostRedisplay();
}


/******************************************************************************/

// display 24-bit color image
void displayColor( int x, int y, int w, int h, byte** image )
{
    glRasterPos2i( x, y );
    glDrawPixels( w, h, GL_RGB, GL_UNSIGNED_BYTE, *image );
}

// display 8-bit monochrome image
void displayMonochrome( int x, int y, int w, int h, byte** image )
{
    glRasterPos2i( x, y );
    glDrawPixels( w, h, GL_LUMINANCE, GL_UNSIGNED_BYTE, *image );
}

// write a text string
void DrawTextString( char *string, int x, int y, byte r, byte g, byte b )
{
    glColor3ub( r, g, b );
    glRasterPos2i( x, y );
    while ( *string )
    {
        glutBitmapCharacter( GLUT_BITMAP_8_BY_13, *string );
        string++;
    }
}



// This function calculates and displays the current compression
// of the image
void display_compression ( ) 
{
    double compression;
    compression = 100 * ((2 * leaf_nodes) / (double)(width * height));
    cout << "compression " << compression << endl;
}



