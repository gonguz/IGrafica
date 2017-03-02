//#pragma once
#ifndef _H_escena_H_
#define _H_escena_H_
#include "tipos.h" 
#include <vector>
using namespace std;

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
	void set(int numero,double altura);

	PVec3 verticesTri[3];
	PVec3 normales[2];
	PVec3 colores[3];
};
//piramide variable auxiliar triangulo parametro radio y altura, tiene tres caras el vertice donde confluyen es el 0,0,altura, nos valemos de los vertices(noramles) que hemos
//usado en el triangulo

class piramideTri {
	vector<Triangulo*> triangulos;
public: 
	piramideTri(GLdouble r, GLdouble h);
	void const draw();
	
};

class triAnimado{
public:
	triAnimado(GLdouble rotacion, GLdouble giroz, GLdouble radio);
	 void update();
	 void const draw();
private:
	Triangulo*tri = new Triangulo(50);
	GLdouble _rotaux;
	GLdouble _giroaux;
	GLdouble _rot = 0;
	GLdouble _giro = 0;
	GLdouble _rad;

};
class Escena {
public:
  Escena(): ejes(200) ,tri(10.0,10.0,200.0),triangulo(50),piramide(50.0,50.0){};
  ~Escena();
  void init();
  void draw();
  void drawDiabolo();
  int _alt = 100;
  int altura(){ return _alt; };
  
public:
  Ejes ejes;
  Triangulo triangulo;
  triAnimado tri;// = new triAnimado(10, 10, 100);
  piramideTri piramide;
};


//-------------------------------------------------------------------------

#endif  // _H_escena_H_
