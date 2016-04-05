//
//  View.c
//  3DPrototype
//
//  Created by Laura del Pino Díaz on 15/3/16.
//  Copyright © 2016 Laura del Pino Díaz. All rights reserved.
//

#include "View.h"
#include "Model.h"

void setViewport(){
    int ancho = glutGet(GLUT_WINDOW_WIDTH);
    int alto = glutGet(GLUT_WINDOW_HEIGHT);
    glViewport(0, 0, ancho, alto); // utiliza la totalidad de la ventana
}

void setProjection(){
    int ancho = glutGet(GLUT_WINDOW_WIDTH);
    int alto = glutGet(GLUT_WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(gl_fovy, (float)ancho / (float)alto, gl_cerca, gl_lejos);
}

void setModelView(){
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void InitGL(){
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    // para cambiar el criterio de lo que se ve.
    // LESS es el de defecto: se ve lo que tiene menor profundidad
    glDepthFunc(GL_LESS);
    // TO DO
    
    setViewport();
    setProjection();
}


void ReshapeSize(int ancho, int alto){
    setViewport();
    setProjection();
    glutPostRedisplay();
}

void PosicionRaton(int x, int y){
    
    int ancho = glutGet(GLUT_WINDOW_WIDTH);
    int alto = glutGet(GLUT_WINDOW_HEIGHT);
    
    theta = M_PI*(double)y / (double)alto;
    phi = - M_PI + 2*M_PI * (double)x / (double)ancho;
    glutPostRedisplay();
}

void RuedaRaton( int button, int x, int y){
    
    if ((button == GLUT_KEY_UP) || (button == GLUT_KEY_DOWN))
    {
            float sentido;
            if(button == GLUT_KEY_UP) sentido = 1.0 ; else sentido = -1.0;
            gl_fovy -= gl_fovy_paso*sentido;
            if (gl_fovy < gl_fovy_min) gl_fovy = gl_fovy_min;
            if (gl_fovy > gl_fovy_max) gl_fovy = gl_fovy_max;
            setProjection();
    }else
    {printf("Tengo hambre\n");}
   
    glutPostRedisplay();
}


// función de gestion de ventana
void Display(){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra todo lo existente en el framebuffer
    glLoadIdentity(); // a partie de aqui empieza poner modelos y transformarlos.
      // TO DO
    body();
    
    glFlush(); // actualiza el framebuffer
    glutSwapBuffers(); // en caso de animacion
}
