//
//  main.h
//  LightsGL
//
//  Created by Laura del Pino Díaz on 5/4/16.
//  Copyright © 2016 Laura del Pino Díaz. All rights reserved.
//

#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>

#define WINDOW_ANCHO 500
#define WINDOW_ALTO 500

// Espacio para las variables globales de la ventana
float gl_fovy = 60.0f;
float gl_fovy_min = 10.0f, gl_fovy_max = 90.0f, gl_fovy_paso = 1.0f;
float gl_cerca=1.0f, gl_lejos=100.0f;
float gl_center = 7.0f; // centro donde pondremos los objetos


// Espacio para otras variables globales
double theta = M_PI_2, phi=0.0;
double radio = 7.0;
float r_carbono = 1.0f;
float r_hidrogeno = 0.5;
float r_enlace = 0.2f;
float l_enlace = 3.0f;



// Espacio para la declaración de funciones
void InitGL();
void Display();
void ReshapeSize(int ancho, int alto);
void PosicionRaton(int x, int y);
void RuedaRaton(int key, int x, int y);
void setLight0();
void setMaterial();
void carbono(float x, float y, float z);
void hidrogeno(float x, float y, float z);
void enlace(float x1, float y1, float z1, float x2, float y2, float z2);