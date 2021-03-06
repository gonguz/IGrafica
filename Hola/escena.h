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
	void PosyRota();
	CTEx2 * getCordenadas(){
		return coordTextura;


	}
	void texturatrue(){ textura = true; }
	void cambiaCoord(int i, GLdouble cambios, GLdouble cambiot){
		coordTextura[i].s = cambios;
		coordTextura[i].t = cambiot;

	}
	
	
protected:
	CTEx2 coordTextura[4];
	bool textura = false;
	PVec3 verticesTri[3]; 
	PVec3 normales[2];
	Color4 colores[3];
	
	GLdouble angulo = 0;
	GLdouble _rotar = 5;
	PVec3 centro = { 0, 0, 0 };
	GLdouble radio;
	

};
//piramide variable auxiliar triangulo parametro radio y altura, tiene tres caras el vertice donde confluyen es el 0,0,altura, nos valemos de los vertices(noramles) que hemos
//usado en el triangulo

class piramideTri {
	
	GLdouble altura;
public: 
	piramideTri(GLdouble r, GLdouble h);
	~piramideTri(){
		delete triangulos[0];
		triangulos[0] = nullptr;

		delete triangulos[1];
		triangulos[1] = nullptr;

		delete triangulos[2];
		triangulos[2] = nullptr;
	}
	void texturizar(CTEx2 *coordTextur);
	
	void const draw();
protected:
	vector <Triangulo*> triangulos;
	
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
	Escena() : ejes(200), tri(30.0, 40.0, 50.0), triangulo(50), piramide(50.0, _alt){};
  ~Escena(){
	  delete rectangulo;
	  rectangulo = nullptr;
	  delete rectangulo2;
	  rectangulo2 = nullptr;
	  delete textura;
	  textura = nullptr;
	  delete textura2;
	  textura2 = nullptr;
	  delete textura3;
	  textura3 = nullptr;
	  delete textura4;
	  textura4 = nullptr;
  }
  void init();
  void draw(int x);
  void drawDiabolo();

  int _alt = 100; 
  triAnimado getTri(){
	  return tri;
  }
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
