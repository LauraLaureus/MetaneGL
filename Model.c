//
//  Model.c
//  BodyGL
//
//  Created by Laura del Pino Díaz on 29/3/16.
//  Copyright © 2016 Laura del Pino Díaz. All rights reserved.
//

#include "Model.h"
#include "View.h"


void caja(float x, float y, float z){
    glPushMatrix();
    glScalef(x, y, z);
    glutWireCube(1.0f);
    glPopMatrix();
}

void body(){
    float cuerpo_ancho = 1.5f, cuerpo_alto = 2.0f, cuerpo_grueso = 0.5f;
    float cabeza = 1.0f; // head
    float pierna = 2.5f;
    float brazo = 2.0f;
    glPushMatrix();
    // cabeza
    glPushMatrix();
    glTranslatef(0.0f, cuerpo_alto / 2.0 + cabeza / 2.0, 0.0f);
    glRotatef(80.0f, 1.0f, 0.0f, 0.0f);
    glutWireSphere(cabeza / 2.0, 10, 10);
    glPopMatrix();
    // cuerpo
    caja(cuerpo_ancho, cuerpo_alto, cuerpo_grueso);
    // pierna
    glPushMatrix();
    glTranslatef(0.8f*cuerpo_ancho / 2, -cuerpo_alto / 2, 0.0f);
    glRotatef(15.0f, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, -pierna / 2.0f, 0.0f);
    caja(0.2f, pierna, 0.2f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.8f*cuerpo_ancho / 2, -cuerpo_alto / 2, 0.0f);
    glRotatef(-15.0f, 0.0f, 0.01, 1.0f);
    glTranslatef(0.0f, -pierna / 2.0f, 0.0f);
    caja(0.2f, pierna, 0.2f);
    glPopMatrix(); // brazo
    
    glPushMatrix();
    glTranslatef(cuerpo_ancho / 2, cuerpo_alto / 2, 0.0f);
    glRotatef(135.0f, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, -brazo / 2.0f, 0.0f);
    caja(0.2f, brazo, 0.2f);
    glPopMatrix(); // brazo
    
    glPushMatrix();
    glTranslatef(-cuerpo_ancho / 2, cuerpo_alto / 2, 0.0f);
    glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, -brazo / 2.0f, 0.0f);
    caja(0.2f, brazo, 0.2f);
    glPopMatrix();
    glPopMatrix();
}


