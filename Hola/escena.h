//#pragma once
#ifndef _H_escena_H_
#define _H_escena_H_
#include "tipos.h" 
#include "Textura.h"
#include <vector>

using namespace std;
class CTex2;
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
	bool dentro(GLdouble w, GLdouble h);
	void posicionar(GLdouble x, GLdouble y);
	void rotar();
	void recortar(GLdouble x, GLdouble y);
	PVec3 verticesTri[3]; 
	PVec3 normales[2];
	Color4 colores[3];
	CTEx2 coordTextura[4];
	GLdouble angulo = 0;
	GLdouble _rotar = 10;
	PVec3 centro = { 0, 0, 0 };
	GLdouble radio;
	bool textura = false;

};
//piramide variable auxiliar triangulo parametro radio y altura, tiene tres caras el vertice donde confluyen es el 0,0,altura, nos valemos de los vertices(noramles) que hemos
//usado en el triangulo

class piramideTri {
	vector<Triangulo*> triangulos;
public: 
	piramideTri(GLdouble r, GLdouble h);
	void const draw();
	
};

class triAnimado : public Triangulo{
public:
	triAnimado(GLdouble rotacion, GLdouble giroz, GLdouble radio);
	 void update();
	 void  draw();
	 GLdouble const getRadio(){ return radio; }
private:

	GLdouble _rotaux;
	GLdouble _giroaux;
	GLdouble _rot = 0;
	GLdouble _giro = 0;

};

class Rectangulo{
public:
	Rectangulo(GLdouble h, GLdouble w);
	void draw();
	void set(GLdouble ancho, GLdouble alto);

private:
	PVec3 verticesRect[4];
	CTEx2 coordTextura[4];
	Color4 color = { 1, 0, 0, 1 };
	PVec3 normal;
};

class Escena {
public:
  Escena(): ejes(200) ,tri(0.0,0.0,50.0),triangulo(50),piramide(50.0,_alt){};
  ~Escena();
  void init();
  void draw(int x);
  void drawDiabolo();

  int _alt = 100;
  int altura(){ return _alt; };
  
public:
	
  Ejes ejes;
  Triangulo triangulo;
  triAnimado tri;// = new triAnimado(10, 10, 100);
  piramideTri piramide;
  Rectangulo *rectangulo = new Rectangulo(600, 800);
  Rectangulo* rectangulo2 = new Rectangulo(100, 200);
  Textura* textura = new Textura();
  Textura* textura2 = new Textura();
  Textura* textura3 = new Textura();
  Textura* textura4 = new Textura();
};


//-------------------------------------------------------------------------

#endif  // _H_escena_H_
