/*
                    ***** globals.h *****

OpenGL graphics program, illustrating use of GLUT and callback functions.

Author: John M. Weiss, Ph.D.
Class:  CSC 315 Data Structures & Algorithms
Date:   Spring 2018

Modifications:
*/

// guard against multiple inclusions
#ifndef _Globals_H_
#define _Globals_H_

// symbolic constants

// keypresses
const int EscapeKey = 27;

// colors
const float Black[]	= { 0.0, 0.0, 0.0 };
const float Red[]	= { 1.0, 0.0, 0.0 };
const float Green[]	= { 0.0, 1.0, 0.0 };
const float Blue[]	= { 0.0, 0.0, 1.0 };
const float Magenta[]	= { 1.0, 0.0, 1.0 };
const float Cyan[]	= { 0.0, 1.0, 1.0 };
const float Yellow[]	= { 1.0, 1.0, 0.0 };
const float White[]	= { 1.0, 1.0, 1.0 };

// global vars
extern int ScreenWidth;
extern int ScreenHeight;

#endif
