/*
        ***** quadtree.cpp *****

Read in a PNG image with LodePNG, convert to grayscale,
and display color/mono images side by side using OpenGL.

Description: Program reads an image file into an array, and converts the image 
             to a quadtree encoding, and then decodes the quadtree back to an 
             image array. Using OpenGL, the original image is displayed on the 
             left side of the application window, and the decoded image on the 
             right. The user can toggle the quadtree structure by pressing the 
             space bar. The quadtree structure is shown by superimposed lines on
             the decoded image, which illustrates the process of subdividing the
             image into “quads”. 

Quadtree Encoding Program for CSC315 PA#2
Usage:  quadtree image.png range

Author: John M. Weiss, Ph.D.
Modified By: Gabriel Hofer, Noah McKenzie
Class:  CSC 315 Data Structures & Algorithms
Date:   Spring 2018
*/

#include <cstdio>
#include <ctime>
#include <GL/freeglut.h>
#include "image.h"

// main function
int main( int argc, char *argv[] )
{
    // process command-line arguments
    char* filename;         // input filename
    int thresh = 128;
    switch ( argc )
    {
        // reads in the user input thresh(range)
        case 3:
            thresh = atoi( argv[2] );
            if ( thresh < 1 || thresh > 255 ) thresh = 128;
        // reads in the user selected image filename
        case 2:
            filename = argv[1];
            break;
        default:
            printf( "Usage: %s image.png\n", argv[0] );
            return -1;
    }
    
    // read input PNG file into 1-D array of 24-bit RGB color pixels
    printf( "reading %s: ", filename );
    unsigned width = 0, height = 0;
    byte** imageRGB = readPNG( filename, width, height );
    printf( "%d x %d\n", width, height );

    // generate 8-bit grayscale intensity image from 24-bit color image
    byte** imageGray = grayscale( width, height, imageRGB );
    // generate quadtree image coloring quads
    byte** imageQuad = grayscale( width, height, imageRGB );
    // generate white line separated quad image 
    byte** imageWhiteQuad = grayscale ( width, height, imageRGB );    
    
    // perform various OpenGL initializations
    glutInit( &argc, argv );
    initOpenGL( filename, thresh, width, height, imageRGB, imageGray, imageQuad, imageWhiteQuad );

    // go into OpenGL/GLUT main loop, never to return
    glutMainLoop();

    // yeah I know, but it keeps compilers from bitching
    return 0;
}
