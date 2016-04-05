//
//  main.c
//  3DPrototype
//
//  Created by Laura del Pino Díaz on 15/3/16.
//  Copyright © 2016 Laura del Pino Díaz. All rights reserved.
//
#include "View.h"

float gl_fovy = 60.0f;
float gl_fovy_min = 10.0f, gl_fovy_max = 90.0f, gl_fovy_paso = 1.0f;
float gl_cerca=1.0f, gl_lejos=100.0f;
float gl_center = 7.0f;
double theta = M_PI_2,phi = 0.0,radio = 7.0;
int w_ancho=500, w_alto=500;



int main(int argc, char *argv[]){
    
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WINDOW_ANCHO, WINDOW_ALTO);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    
    glutCreateWindow("OpenGL Practica Laura del Pino Díaz");
    InitGL();
    glutDisplayFunc(Display); // registra la funcion de rendering
    glutReshapeFunc(ReshapeSize);
    glutMotionFunc(PosicionRaton);
    //glutMouseWheelFunc(RuedaRaton);
    glutSpecialFunc(RuedaRaton);
    glutMainLoop(); // bucle principal
    
    return 0;
}


