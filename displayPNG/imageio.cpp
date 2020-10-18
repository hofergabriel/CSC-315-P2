/*
                ***** imageio.cpp *****

readPNG:    read in a PNG image with LodePNG, return 24-bit RGB color image.
grayscale:  convert 24-bit RGB color image to 8-bit grayscale.

Author: John M. Weiss, Ph.D.
Modified By:  Gabriel Hofer, Noah McKenzie
Class:  CSC 315 Data Structures & Algorithms
Date:   Spring 2018
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "lodepng.h"
#include "image.h"

using namespace std;

// read PNG image using LodePNG, and return as 2-D array of RGB pixels
byte** readPNG( char* filename, unsigned& width, unsigned& height )
{
    // read input PNG file
    byte* pixels;
    unsigned error = lodepng_decode_file( &pixels, &width, &height, filename, LCT_RGB, 8 );
    if ( error )
    {
        printf( "decoder error while reading file %s\n", filename );
        printf( "error code %u: %s\n", error, lodepng_error_text( error ) );
        return NULL;
    }
    // printf( "%s: %d x %d\n", filename, width, height );
    unsigned nbytes = width * 3;

    // make width a multiple of 4, else grayscale image does not display properly in OpenGL
    unsigned pad = 0;
    if ( width % 4 != 0 ) pad = 4 - width % 4;
    width += pad;

    // flip image as we copy it into 2-D array
    byte** image = alloc2D( height, width * 3 );
    byte* img = pixels;
    for ( int row = height - 1; row >= 0; --row, pixels += nbytes )
        memcpy( image[row], pixels, nbytes );

    // finish up
    free( img );
    return image;
}

// generate 8-bit grayscale intensity image from 24-bit RGB color image
byte** grayscale( unsigned width, unsigned height, byte** imgRGB )
{
    byte** image = alloc2D( height, width );
    byte* img = *imgRGB;
    for ( unsigned row = 0; row < height; ++row )
    {
        for ( unsigned col = 0; col < width; ++col )
        {
            int r = *img++;
            int g = *img++;
            int b = *img++;
            image[row][col] = 0.3 * r + 0.6 * g + 0.1 * b + 0.5;
        }
    }
    return image;
}

// This functions draws white lines over the
// original Mono-gray image. This function is void.
void ColorWhiteQuad ( byte** imgMono, byte** imgWhiteQuad, int x, int y, int w, int h ) 
{
    int i, j;

    // color the upper horizontal border of the image containint white lines
    for ( i = x; i < x + w; i += 1 ) 
    {
        // we assign the maximum intensity value (white)
        // to this pixel
        imgWhiteQuad [ i ][ y ] = 255;
    }
    // color the left vertical border of the image containing white lines
    for ( j = y; j < y + h; j += 1 ) 
    {
        // we assign the maximum intensity value (white)
        // to this pixel
        imgWhiteQuad [ x ][ j ] = 255;
    }
    
    return;
}

// This function colors one quad in the image. Moreover, this
// function iterates to each pixel in the quad and assigns
// each pixel the same intensity value. Specifically, every 
// pixel in the quad is assigned the intensity value of the 
// upper-leftmost pixel-intensity value. This is a void function.
void ColorQuad ( byte** imgMono, byte** imgQuad, int x, int y, int w, int h ) 
{
    int i, j;

    // iterate to each pixel in the current Quad
    for ( i = x; i < x + w; i += 1 ) 
    {
        for ( j = y; j < y + h; j += 1 ) 
        {
            // assign an intensity value of the upper-leftmost pixel
            imgQuad [ i ][ j ] = imgMono [ x ][ y ];
        }
    }
    return;
}

// This function tests whether every pixel in the current quad is within
// the range. If not every pixel in the current quad is within the range,
// then we return false. Otherwise, This is a valid quad and we return true.
bool quad_test ( byte** imgMono, byte** imgQuad, int x, int y, int w, int h, int range ) 
{
    int i, j;
    for ( i = x; i < x + w; i += 1 ) 
    {
        for ( j = y; j < y + h; j += 1 ) 
        {
            if ( abs ( imgMono [ i ][ j ] - imgMono [ x ][ y ] ) > range ) 
            {
                return false;
            }
        }
    }
    return true;
}

// This function constructs two images recursively. There is a base case
// and there is a recursive case in this function. For the base case, we
// call quad_test, and if quad_test returns true, then we know that every
// pixel in the current quad is within the range. 
// Otherwise, we execute the recursive case: 
// we make four recursive calls dividing the current quad into
// four smaller quads. 
void make_quadtree ( byte** imgMono, byte** imgQuad, byte **imgWhiteQuad, 
                        int x, int y, int w, int h, int range, 
                        int & leaf_nodes, int & nodes ) 
{
    if ( quad_test ( imgMono, imgQuad, x, y, w, h, range ) ) 
    {
        leaf_nodes += 1;    
        ColorQuad ( imgMono, imgQuad, x, y, w, h );
        ColorWhiteQuad ( imgMono, imgWhiteQuad, x, y, w, h );
        return;
    }
    else 
    {
        nodes += 4;
        make_quadtree ( imgMono, imgQuad, imgWhiteQuad, x, y, w/2, h/2, range, leaf_nodes, nodes );
        make_quadtree ( imgMono, imgQuad, imgWhiteQuad, x + (w/2), y, w/2, h/2, range, leaf_nodes, nodes);
        make_quadtree ( imgMono, imgQuad, imgWhiteQuad, x, y + (h/2), w/2, h/2, range, leaf_nodes, nodes );
        make_quadtree ( imgMono, imgQuad, imgWhiteQuad, x + (w/2), y + (h/2), w/2, h/2, range, leaf_nodes, nodes );
        return;
    }
}


























