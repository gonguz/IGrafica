#include "escena.h"
#include <GL/freeglut.h>
#include <iostream>
#include "tipos.h" //Puede estar mal
using namespace std;
//-------------------------------------------------------------------------

void Escena::init(){
  // texturas
  // luces
	
	textura->init();
	textura->load("../bmps/Zelda.bmp");

}

//-------------------------------------------------------------------------

Escena::~Escena(){
   // liberar memoria y recursos 
}

//-------------------------------------------------------------------------

void Escena::draw(){
  ejes.draw();
  //tri.draw();
	//triangulo.draw();
  drawDiabolo();
	rectangulo->draw();

}

//-------------------------------------------------------------------------

Ejes::Ejes(GLdouble l) {
  vertices[0].set(0, 0, 0);
  vertices[1].set(l, 0, 0);
  vertices[2].set(0, 0, 0);
  vertices[3].set(0, l, 0);
  vertices[4].set(0, 0, 0);
  vertices[5].set(0, 0, l);

  colores[0].set(1, 0, 0);
  colores[1].set(1, 0, 0);
  colores[2].set(0, 1, 0);
  colores[3].set(0, 1, 0);
  colores[4].set(0, 0, 1);
  colores[5].set(0, 0, 1);
}

//-------------------------------------------------------------------------

void Ejes::draw(){
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_DOUBLE, 0, vertices);
  glEnableClientState(GL_COLOR_ARRAY);
  glColorPointer(3, GL_DOUBLE, 0, colores);

  glLineWidth(2);
  glDrawArrays(GL_LINES, 0, 6); 
  glLineWidth(1);

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);

 /* 
  glLineWidth(2);
  glBegin(GL_LINES);
     glColor3d(1.0, 0.0, 0.0); // red
     glVertex3d(vertices[0].x, vertices[0].y, vertices[0].z);   // origin
     glVertex3d(vertices[1].x, vertices[1].y, vertices[1].z);   // x   

     glColor3d(0.0, 1.0, 0.0); // green
     glVertex3d(vertices[2].x, vertices[2].y, vertices[2].z);   // origin
     glVertex3d(vertices[3].x, vertices[3].y, vertices[3].z);	  // y

     glColor3d(0.0, 0.0, 1.0); // blue
     glVertex3d(vertices[4].x, vertices[4].y, vertices[4].z);   // origin
     glVertex3d(vertices[5].x, vertices[5].y, vertices[5].z);	  // z   
  glEnd();
  glLineWidth(1);
  */
}

Triangulo::Triangulo(GLdouble r){

	GLdouble x = r*cos(6.28 / 3);
	GLdouble y = r *sin(6.28 / 3);

	verticesTri[0].set(r, 0,0);
	verticesTri[1].set(x, y, 0);
	verticesTri[2].set(x, -y, 0);

	normales[0].set(0, 0, 1);
	normales[1].set(0, 0, 1);
	normales[2].set(0, 0, 1);
	coordTextura[0].s = 0; coordTextura[0].t = 1;
	coordTextura[1].s = 0; coordTextura[1].t = 0;
	coordTextura[2].s = 1; coordTextura[2].t = 1;
	coordTextura[3].s = 1; coordTextura[3].t = 0;

	colores[0] = { 0, 0, 0, 1 };
	colores[1] = { 0, 0, 0, 1 };
	colores[2] = { 0, 0, 0, 1 };
}
void Triangulo::set( int numero, double altura){

	verticesTri[numero]= { 0, 0, altura };
}

void Triangulo::draw(){/*
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_DOUBLE, 0, verticesTri);
	//glNormalPointer(GL_DOUBLE, 0, normales);
	glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_DOUBLE, 0, colores);
	

	glLineWidth(2);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glLineWidth(1); 



	glDisableClientState(GL_COLOR_ARRAY);
	//glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	*/
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_TEXTURE_2D);
	glVertexPointer(3, GL_DOUBLE, 0, verticesTri);
	glNormal3d(normales[0].x, normales[0].y, normales[0].z);


	glColor4d(colores[0].red, colores[0].green, colores[0].blue, colores[0].alpha);


	//glLineWidth(2);
	glTexCoordPointer(2, GL_DOUBLE, 0, coordTextura);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
	//	glLineWidth(1);



	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_TEXTURE_2D);

	glDisableClientState(GL_VERTEX_ARRAY);
}

//-------------------------------------------------------------------------



piramideTri::piramideTri(GLdouble r, GLdouble h){
	//Aqui rellenas el vector de tangulos en los cuales vas cambiando las coordenadas de una esquinaç
	// La altura se debe meter tambien para ver donde colocamos la piramide

	triangulos.push_back(new Triangulo(r));
	triangulos[0]->set(0, h);
	triangulos.push_back( new Triangulo(r));
	triangulos[1]->set(1, h);
	triangulos.push_back(new Triangulo(r));
	triangulos[2]->set(2, h);
}

void const piramideTri::draw() {
	for (int i = 2; i >= 0; i--) {
		triangulos[i]->draw();
	}
}

Rectangulo::Rectangulo(GLdouble h, GLdouble w){

	verticesRect[0].set(0, h, 0);
	verticesRect[1].set(0, 0, 0);
	verticesRect[2].set(w, h, 0);
	
	verticesRect[3].set(w, 0, 0);
	
	
	

	coordTextura[0].s = 0; coordTextura[0].t = 1;
	coordTextura[1].s = 0; coordTextura[1].t = 0;
	coordTextura[2].s = 1; coordTextura[2].t = 1;
	coordTextura[3].s = 1; coordTextura[3].t = 0;


	normal.set(0, 0, 1);

}

void Rectangulo::draw(){
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_TEXTURE_2D);
	glVertexPointer(3, GL_DOUBLE, 0, verticesRect);
	glNormal3d(normal.x, normal.y, normal.z);

	
	glColor4d(color.red, color.green, color.blue, color.alpha);


	//glLineWidth(2);
	glTexCoordPointer(2, GL_DOUBLE, 0, coordTextura);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//	glLineWidth(1);



	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_TEXTURE_2D);

	glDisableClientState(GL_VERTEX_ARRAY);
}

void Rectangulo::set(GLdouble ancho, GLdouble alto){
	verticesRect[0].set(0,alto, 0);
	verticesRect[1].set(0, 0, 0);
	verticesRect[2].set(ancho, alto, 0);
	verticesRect[3].set(0, 0, 0);
}
void Escena::drawDiabolo(){
	glRotated(90.0, 1.0, 0.0, 0.0);// de las tres ultimas cifras la que tenga un 1 es la que gira el angulo de los  grados que le pongas
	glTranslated(0.0, 0.0,-altura());
	piramide.draw();

	glRotated(-180, 1.0, 0.0, 0.0);
	glTranslated(0.0, 0.0, -2*altura());
	piramide.draw();

	glRotated(60.0f, 0.0, 0.0, 1.0);
	piramide.draw();

	glTranslated(0.0, 0.0, 2*altura());
	glRotated(180, 1.0, 0.0, 0.0);
	
	piramide.draw();
	//Para que vuelva a la posicion original

	glRotated(-180, 1.0, 0.0, 0.0);
	glRotated(-60.0f, 0.0, 0.0, 1.0);
	glRotated(180, 1.0, 0.0, 0.0);
	
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glTranslated(0.0, 0.0, altura());
}

triAnimado::triAnimado(GLdouble rotacion, GLdouble giroz, GLdouble radio){
	_rotaux = rotacion;
	_giroaux= giroz;
	_rad = radio;
}

void triAnimado::update(){
	_rot += _rotaux;
	_giro += _giroaux;
}

void const triAnimado::draw(){
	GLdouble radio = getRadio();
	GLdouble x = radio * cos(_giro / 6.28);
	GLdouble y = radio * sin(_giro / 6.28);
	glTranslated(x, y, 0);
	glRotated(triAnimado::_rot, 0.0, 0.0, 1.0);
	tri->draw();
	glRotated(-triAnimado::_rot, 0.0, 0.0, 1.0);
	glTranslated(-x, -y, 0);
}