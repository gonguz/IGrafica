//#pragma once
#ifndef _H_escena_H_
#define _H_escena_H_
#include "tipos.h"

//-------------------------------------------------------------------------
class Ejes {
public:
  Ejes(GLdouble l);
  ~Ejes(){};
  void draw();
public:
  PVec3 vertices[6];
  PVec3 colores[6];
};

//-------------------------------------------------------------------------
class Triangulo {
public:
	Triangulo(GLdouble r);
	void draw();
	PVec3 verticesTri[3];
	PVec3 normales[2];
	PVec3 colores[3];
};
//piramide variable auxiliar triangulo parametro radio y altura, tiene tres caras el vertice donde confluyen es el 0,0,altura, nos valemos de los vertices(noramles) que hemos
//usado en el triangulo

class piramideTri {
public: 
	piramideTri(GLdouble r, GLdouble h);
	void draw();
};

class Escena {
public:
  Escena(): ejes(200), triangulo(100) {};
  ~Escena();
  void init();
  void draw();
public:
  Ejes ejes;
  Triangulo triangulo;
};


//-------------------------------------------------------------------------

#endif  // _H_escena_H_
