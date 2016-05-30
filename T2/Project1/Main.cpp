#include <stdio.h>
#define _USE_MATH_DEFINES
#include <cmath>

#include <GL\glew.h>
#include <GL\freeglut.h>

#define WINDOW_ANCHO 500
#define WINDOW_ALTO 500

// Espacio para las variables globales de la ventana
float gl_fovy = 60.0f;
float gl_fovy_min = 10.0f, gl_fovy_max = 90.0f, gl_fovy_paso = 1.0f;
float gl_cerca = 1.0f, gl_lejos = 100.0f;
float gl_center = 7.0f; // centro donde pondremos los objetos


// Espacio para otras variables globales
double theta = M_PI_2, phi = 0.0;
double radio = 7.0;
float r_carbono = 1.0f;
float r_hidrogeno = 0.5;
float r_enlace = 0.2f;
float l_enlace = 3.0f;

// Espacio para la declaración de funciones
void InitGlew();
void InitGL();
void Display();
void ReshapeSize(int ancho, int alto);
void PosicionRaton(int x, int y);
void RuedaRaton(int rueda, int sentido, int x, int y);

//main
int main(int argc, char *argv[]){

	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_ANCHO, WINDOW_ALTO);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("OpenGL Practica 8 Laura del pino");
	InitGlew(); // despues de crear la primera ventana
	InitGL();
	glutDisplayFunc(Display); // registra la funcion de rendering
	glutReshapeFunc(ReshapeSize);
	glutMotionFunc(PosicionRaton);
	glutMouseWheelFunc(RuedaRaton);

	glutMainLoop(); // bucle principal

	return 0;
}

void setMaterial(float r, float g, float b){
	const GLfloat ambient[4] = { 0.3f, 0.3f, 0.3f, 1.0f };
	const GLfloat diffuse[4] = { r, g, b, 1.0f };
	const GLfloat specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat shininess = 100.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
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
	setMaterial(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f);
	glutSolidSphere(r_hidrogeno, 20, 20);
	glPopMatrix();
}

void enlace(float x1, float y1, float z1, float x2, float y2, float z2){
	glPushMatrix();

	glTranslatef(x1, y1, z1);
	x2 -= x1;
	y2 -= y1;
	z2 -= z1;
	float d = (float)sqrt(x2*x2 + y2*y2 + z2*z2);
	float angle = (float)acos(z2 / d)*180.0 / M_PI;
	glRotatef(-angle, y2, -x2, 0.0f);
	setMaterial(200.0f / 255.0f, 200.0f / 255.0f, 200.0f / 255.0f);
	glutSolidCylinder(r_enlace, d, 20, 20);

	glPopMatrix();
}

void InitGlew(){

	// para poder utilizar trasnparentemente todas las extensiones de OpenGL

	GLenum glew_init = glewInit();
	if (glew_init != GLEW_OK)
	{
		// Problem: glewInit failed, something is seriously wrong.
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_init));
	}
	else
		fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
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

void setLight0(){
	float ambient[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
	float diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	float position[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float direction[4] { -1.0f, -1.0f, -1.0f, 1.0f };
	float cut_off = 90.0f;

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, cut_off);
	glEnable(GL_LIGHT0);
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

	glEnable(GL_LIGHTING);
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
	phi = -M_PI + 2 * M_PI * (double)x / (double)ancho;
	glutPostRedisplay();
}

void RuedaRaton(int rueda, int sentido, int x, int y){

	gl_fovy -= gl_fovy_paso*(float)sentido;
	if (gl_fovy < gl_fovy_min) gl_fovy = gl_fovy_min;
	if (gl_fovy > gl_fovy_max) gl_fovy = gl_fovy_max;
	setProjection();
	glutPostRedisplay();
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
	gluLookAt(x, y, z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); // mira al (0,0,0)

	// TO DO
	//coordendas de los atoms de hidrogeno.
	double angle = 109.5;
	double pangle = angle*M_PI / 180.0;
	float cos_enlace = l_enlace*cos(pangle);
	float sin_enlace = l_enlace*sin(pangle);

	float x1 = 0.0f;
	float y1 = 1.0f*l_enlace;
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
	hidrogeno(x1, y1, z1);
	hidrogeno(x2, y2, z2);
	hidrogeno(x3, y3, z3);
	hidrogeno(x4, y4, z4);

	enlace(0.0f, 0.0f, 0.0f, x1, y1, z1);
	enlace(0.0f, 0.0f, 0.0f, x2, y2, z2);
	enlace(0.0f, 0.0f, 0.0f, x3, y3, z3);
	enlace(0.0f, 0.0f, 0.0f, x4, y4, z4);


	glFlush(); // actualiza el framebuffer
	glutSwapBuffers(); // en caso de animacion
}

