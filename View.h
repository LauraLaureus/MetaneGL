//
//  View.h
//  3DPrototype
//
//  Created by Laura del Pino Díaz on 15/3/16.
//  Copyright © 2016 Laura del Pino Díaz. All rights reserved.
//

#ifndef View_h
#define View_h

#include <stdio.h>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <math.h>

#endif /* View_h */


#ifndef GLOBAL_VARS_VIEW

#define WINDOW_ANCHO 500
#define WINDOW_ALTO 500

extern float gl_ancho , gl_alto, gl_cerca, gl_lejos;
extern int w_ancho, w_alto;
extern float gl_fovy;
extern float gl_fovy_min, gl_fovy_max, gl_fovy_paso;
extern float gl_cerca, gl_lejos;
extern float gl_center;
extern double theta,phi,radio;

#endif

#ifndef VIEW_PROTO
void InitGL();
void ReshapeSize(int ancho, int alto);
void Display();
void PosicionRaton(int x, int y);
void RuedaRaton(int button,int x, int y);
#endif