#include "escena.h"
#include <GL/freeglut.h>
#include <iostream>
#include "tipos.h" //Puede estar mal
using namespace std;
//-------------------------------------------------------------------------
//Estados estado;
void Escena::init(){
  // texturas
  // luces
	//estado = Estados::Recortar;
	
	textura->init();
	textura->load("../bmps/ray.bmp");

}

//-------------------------------------------------------------------------

Escena::~Escena(){
   // liberar memoria y recursos 
}

//-------------------------------------------------------------------------

void Escena::draw(int estado){
	//enum Estados{ Collage = 0, Recortar = 1, Animar = 2, Diabolo = 3};
	ejes.draw();
	switch (estado)
	{
	case 0:
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		break;
	case 1:
		glDisable(GL_DEPTH_TEST);
		rectangulo->draw();
		tri.draw();
		glEnable(GL_DEPTH_TEST);

		break;
	case 2:
		
		//rectangulo->draw();
		tri.draw();
		break;
	case 3:
		drawDiabolo();
		break;
	default:
		break;
	}
  
  //tri.draw();
	//triangulo.draw();
   
 // drawDiabolo();
 

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
	radio = r;
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

void Triangulo::rotar(){
	angulo += _rotar;
}

void Triangulo::posicionar(GLdouble x, GLdouble y){
	centro = { x, y, 0 };
	verticesTri[0] = { radio*cos(angulo) + x, radio * sin(angulo) + y ,0};
	verticesTri[1] = { radio*cos(angulo + 2 * 3.14 / 3) + x, radio * sin(angulo + 2 * 3.14 / 3) + y, 0};
	verticesTri[2] = { radio*cos(angulo + 4 * 3.14 / 3) + x, radio * sin(angulo + 4 * 3.14 / 3) + y, 0 };

}

bool Triangulo::dentro(GLdouble w, GLdouble h){
	/*/SI(Ax - Px) * (By - Py) –(Ay - Py) * (Bx - Px) < 0
		->P está fuera
		SI(Bx - Px) * (Cy - Py) –(By - Py) * (Cx - Px) < 0
		->P está fuera
		SI(Cx - Px) * (Ay - Py) –(Cy - Py) * (Ax - Px) < 0
		->P está fuera
		En otro caso->P está dentro*/
		if (((verticesTri[0].x - w) * (verticesTri[1].y - h)) - ((verticesTri[0].y - h) * (verticesTri[1].x - w)) < 0){
			return false;
		}

		else if (((verticesTri[1].x - w) * (verticesTri[2].y - h)) - ((verticesTri[1].y - h) * (verticesTri[2].x - w)) < 0){
			return false;
		}

		else if (((verticesTri[2].x - w) * (verticesTri[0].y - h)) - ((verticesTri[2].y - h) * (verticesTri[0].x - w)) < 0){
			return false;
		}
		else return true;
}

void Triangulo::draw(){
	/*
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
	*/if (!textura){
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
	}
	else {
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_TEXTURE_2D);
		glVertexPointer(3, GL_DOUBLE, 0, verticesTri);
		glNormal3d(normales[0].x, normales[0].y, normales[0].z);


		glColor4d(colores[0].red, colores[0].green, colores[0].blue, colores[0].alpha);


		//glLineWidth(2);
		glTexCoordPointer(2, GL_DOUBLE, 0, coordTextura);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
		//	glLineWidth(1);



		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_TEXTURE_2D);

		glDisableClientState(GL_VERTEX_ARRAY);
	}
	
}

//-------------------------------------------------------------------------

void Triangulo::recortar(GLdouble ancho, GLdouble alto){
	//coordTextura = ver 
	coordTextura[0].s = (ancho / 2 + verticesTri[0].x) / ancho;
	coordTextura[0].t = (alto / 2 + verticesTri[0].y) / alto;
	coordTextura[1].s = (ancho / 2 + verticesTri[1].x) / ancho;
	coordTextura[1].t = (alto / 2 + verticesTri[1].y) / alto;
	coordTextura[2].s = (ancho / 2 + verticesTri[2].x) / ancho;
	coordTextura[2].t = (alto / 2 + verticesTri[2].y) / alto;


	
}



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

	verticesRect[0].set(-w/2, h/2, 0);
	verticesRect[1].set(-w/2, -h/2, 0);
	verticesRect[2].set(w/2, h/2, 0);
	
	verticesRect[3].set(w/2, -h/2, 0);
	
	
	

	coordTextura[0].s = 0; coordTextura[0].t = 1;
	coordTextura[1].s = 0; coordTextura[1].t = 0;
	coordTextura[2].s = 1; coordTextura[2].t = 1;
	coordTextura[3].s = 1; coordTextura[3].t = 0;


	normal = { 0, 0, 1 };

}

void Rectangulo::draw(){
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_TEXTURE_2D);
	glVertexPointer(3, GL_DOUBLE, 0, verticesRect);
	glNormal3d(normal.x, normal.y, normal.z);

	
	

	glTexCoordPointer(2, GL_DOUBLE, 0, coordTextura);
	//glLineWidth(2);
	
	glColor4d(color.red, color.green, color.blue, color.alpha);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//	glLineWidth(1);



	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_TEXTURE_2D);

	glDisableClientState(GL_VERTEX_ARRAY);
}

void Rectangulo::set(GLdouble ancho, GLdouble alto){
	verticesRect[0].set(-ancho/2,alto/2, 0);
	verticesRect[1].set(-ancho/2, -alto/2, 0);
	verticesRect[2].set(ancho/2, alto/2, 0);
	verticesRect[3].set(-ancho/2, -alto/2, 0);
}
void Escena::drawDiabolo(){
	/*glRotated(90.0, 1.0, 0.0, 0.0);// de las tres ultimas cifras la que tenga un 1 es la que gira el angulo de los  grados que le pongas
	glTranslated(0.0, 0.0,-altura());
	piramide.draw();

	glRotated(-180, 1.0, 0.0, 0.0);
	//glTranslated(0.0, 0.0, -2*altura());
	piramide.draw();

	glRotated(60.0f, 0.0, 0.0, 1.0);
	piramide.draw();

	//glTranslated(0.0, 0.0, 2*altura());
	glRotated(180, 1.0, 0.0, 0.0);
	
	piramide.draw();
	//Para que vuelva a la posicion original

	glRotated(-180, 1.0, 0.0, 0.0);
	glRotated(-60.0f, 0.0, 0.0, 1.0);
	glRotated(180, 1.0, 0.0, 0.0);
	
	glRotated(-90.0, 1.0, 0.0, 0.0);
	*/
	glTranslated(0.0,altura(),0.0);
	glRotated(90.0, 1.0, 0.0, 0.0);
	piramide.draw();
	glRotated(60.0f, 0.0, 0.0, 1.0);
	piramide.draw();
	glRotated(-180, 1.0, 0.0, 0.0);
	glTranslated(0.0, 0.0, - 2*altura());
	piramide.draw();
	glRotated(-60, 0.0, 0.0, 1.0);
	piramide.draw();
	
	glRotated(60, 0.0, 0.0, 1.0);
	glTranslated(0.0, 0.0, 2 * altura());
	glRotated(180, 1.0, 0.0, 0.0);
	glRotated(-60.0f, 0.0, 0.0, 1.0);
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glTranslated(0.0, -altura(), 0.0);
	
}

triAnimado::triAnimado(GLdouble rotacion, GLdouble giroz, GLdouble radio):Triangulo(radio){
	_rotaux = rotacion;
	_giroaux= giroz;
}

void triAnimado::update(){
	_rot += _rotaux;
	_giro += _giroaux;
}

void  triAnimado::draw(){
	if (!textura)Triangulo::draw();
	else{
		GLdouble x = radio * cos(_giro / 6.28);
		GLdouble y = radio * sin(_giro / 6.28);
		glTranslated(x, y, 0);
		glRotated(triAnimado::_rot, 0.0, 0.0, 1.0);
		Triangulo::draw();
		glRotated(-triAnimado::_rot, 0.0, 0.0, 1.0);
		glTranslated(-x, -y, 0);
	}
}
