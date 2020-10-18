/*
                ***** image.h *****

Header file for various image processing applications.

Author: John M. Weiss, Ph.D.
Modified By: Gabriel Hofer, Noah McKenzie
Class:  CSC 315 Data Structures & Algorithms
Date:   Spring 2018
*/

#ifndef IMAGE_H
#define IMAGE_H

// convenience data type
typedef unsigned char byte;

// function prototypes
byte** alloc2D( int nrows, int ncols );
void free2D( byte** image );
byte** readPNG( char* filename, unsigned& width, unsigned& height );
byte** grayscale( unsigned width, unsigned height, byte** imgRGB );
byte** quadtree( unsigned width, unsigned height, byte** imgRGB );
void initOpenGL( const char *filename, int thresh, unsigned w, unsigned h, byte** imgRGB, 
                 byte** imgGray, byte** imgQuad, byte** imgWhiteQuad );

void ColorQuad ( byte ** imgMono, byte ** imgQuad, int x, int y, int w, int h );
void ColorWhiteQuad ( byte ** imgMono, byte ** imgWhiteQuad, int x, int y, int w, int h );
bool quad_test ( byte ** imgMono, byte ** imgQuad, int x, int y, int w, int h, int range );
void make_quadtree ( byte ** imgMono, byte ** imgQuad, byte ** imgWhiteQuad, 
                       int x, int y, int w, int h, int range, int & leaf_nodes, int & nodes );
#endif
