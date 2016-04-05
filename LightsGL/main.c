#include "main.h"

//main
int main(int argc, char *argv[]){
    
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WINDOW_ANCHO, WINDOW_ALTO);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    
    glutCreateWindow("OpenGL Practica ");
    InitGL();
    glutDisplayFunc(Display); // registra la funcion de rendering
    glutReshapeFunc(ReshapeSize);
    glutMotionFunc(PosicionRaton);
    glutSpecialFunc(RuedaRaton);
    
    glutMainLoop(); // bucle principal
    
    return 0;
}
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
    
    //Setting for lights
    glEnable(GL_LIGHTING);
    //glShadeModel(GL_FLAT);
    glShadeModel(GL_SMOOTH);
    setLight0();
}

// cambio de dimensiones de la ventana, manteniendo la dimension de los objetos
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

void RuedaRaton(int key, int x, int y){
    float sentido;
    if(key == GLUT_KEY_UP) sentido = 1;
    if(key == GLUT_KEY_DOWN) sentido = -1;
    if(key == GLUT_KEY_UP || key == GLUT_KEY_DOWN ){
        gl_fovy -= gl_fovy_paso*(float)sentido;
        if (gl_fovy < gl_fovy_min) gl_fovy = gl_fovy_min;
        if (gl_fovy > gl_fovy_max) gl_fovy = gl_fovy_max;
        setProjection();
    }
    glutPostRedisplay();
}


void setLight0(){
    float ambient[4] = {0.2f, 0.2f,0.2f,1.0f};
     float diffuse[4] = {1.0f, 1.0f,1.0f,1.0f};
     float specular[4] = {1.0f, 1.0f,1.0f,1.0f};
    
     float position[4] = {1.0f, 1.0f,1.0f,1.0f};
     float direction[4] = {-1.0f,-1.0f,-1.0f,1.0f};
    float cutoff = 90.0f;
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
    glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, &cutoff);
    glEnable(GL_LIGHT0);
}


void setMaterial(){
    const float ambient[4] = {0.2f, 0.2f,0.2f,1.0f};
    const float diffuse[4] = {0.4f, 0.4f,0.4f,0.4f};
    const float specular[4] = {0.9f, 0.9f,0.9f,0.9f};
    const float shininess = 3.0f;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);
    
}


void carbono(float x, float y, float z){
    glPushMatrix();
    glTranslatef(x, y, z);
    setMaterial(200.0f / 255.0f, 200.0f / 255.0f, 200.0f / 255.0f);
    glutSolidSphere(r_carbono, 20, 20);
    glPopMatrix();
}

void hidrogeno(float x, float y, float z){
    glPushMatrix();
    glTranslatef(x, y, z);
    setMaterial(200.0f / 255.0f, 200.0f / 255.0f, 200.0f / 255.0f);
    glutSolidSphere(r_carbono, 20, 20);
    glPopMatrix();
}


void enlace(float x1, float yy1, float z1, float x2, float y2, float z2){
    glPushMatrix();
    x2 -= x1;
    y2 -= yy1;
    z2 -= z1;
    glTranslatef((x1+x2)/2, (yy1+y2)/2, (z1+z2)/2);
    float d = (float)sqrt(x2*x2 + y2*y2 + z2*z2);
    float angle = (float)acos(z2 / d)*180.0 / M_PI;
    glScalef(0.5f, 0.5f, 0.5f);
    glRotatef(-angle, y2, -x2, 0.0f);
    setMaterial(200.0f / 255.0f, 200.0f / 255.0f, 200.0f / 255.0f);
    glutSolidCube(1.0f);
    
    
    glPopMatrix();
}


// función de gestion de ventana
void Display(){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra todo lo existente en el framebuffer
    setModelView();
    
    // poicionamos el centro de coordenadas
    glTranslatef(0.0f, 0.0f, -gl_center);
    
    // el eje cenital es el Y
    float x = (float)(radio*sin(theta)*sin(phi));
    float y = (float)(radio*cos(theta));
    float z = (float)(radio*sin(theta)*cos(phi));
    gluLookAt(x,y,z,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f); // mira al (0,0,0)
    
    // TO DO
    double angle = 109.5;
    double pangle = angle*M_PI / 180.0;
    float cos_enlace = l_enlace*cos(pangle);
    float sin_enlace = l_enlace*sin(pangle);
    
    float x1 = 0.0f;
    float yy1 = 1.0f*l_enlace;
    float z1 = 0.0f;
    
    float x2 = 0.0f;
    float y2 = cos_enlace;
    float z2 = sin_enlace;
    
    float x3 = sin_enlace*(float)sin(2 * M_PI / 3);
    float y3 = cos_enlace;
    float z3 = sin_enlace*(float)cos(2 * M_PI / 3);
    
    float x4 = -sin_enlace*(float)sin(2 * M_PI / 3);
    float y4 = cos_enlace;
    float z4 = sin_enlace*(float)cos(2 * M_PI / 3);
    
    // carbon en el centro
    carbono(0.0f, 0.0f, 0.0f);
    hidrogeno(x1, yy1, z1);
    hidrogeno(x2, y2, z2);
    hidrogeno(x3, y3, z3);
    hidrogeno(x4, y4, z4);

    enlace(0.0f, 0.0f, 0.0f, x1, yy1, z1);
    enlace(0.0f, 0.0f, 0.0f, x2, y2, z2);
    enlace(0.0f, 0.0f, 0.0f, x3, y3, z3);
    enlace(0.0f, 0.0f, 0.0f, x4, y4, z4);

    
    
    glFlush(); // actualiza el framebuffer
    glutSwapBuffers(); // en caso de animacion
}

