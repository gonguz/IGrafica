#include "Textura.h"


bool Textura::load(const std::string & BMP_Name) {
	// la textura debe estar inicializada -> escena::init()
	PixMap24RGB pixMap;
	pixMap.load_bmpBGR(BMP_Name); // cargar
	if (!pixMap.is_null()){
		w = pixMap.width();
		h = pixMap.height();
		glBindTexture(GL_TEXTURE_2D, id); // transferir a openGL
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB,
			GL_UNSIGNED_BYTE, pixMap.map());
		return true;
	}
	else return false;
}
bool Textura::load(const std::string & BMP_Name, GLubyte alpha){
	// la textura debe estar inicializada -> escena::init()
	PixMap24RGB pixMap;
	pixMap.load_bmpBGR(BMP_Name); // cargar
	if (!pixMap.is_null()){
		w = pixMap.width();
		h = pixMap.height();
		GLubyte*p = pixMap.create_RGBA(alpha);
		glBindTexture(GL_TEXTURE_2D, id); // transferir a openGL
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, p);
		return true;
	}
	else return false;

}
//, 200);
bool Textura::load(const std::string & BMP_Name, PixMap24RGB::rgb_color colorKey, GLubyte alpha){
	// la textura debe estar inicializada -> escena::init()
	PixMap24RGB pixMap;
	pixMap.load_bmpBGR(BMP_Name); // cargar
	if (!pixMap.is_null()){
		w = pixMap.width();
		GLubyte*p = pixMap.create_RGBA(colorKey,alpha);
		h = pixMap.height();
		glBindTexture(GL_TEXTURE_2D, id); // transferir a openGL
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA,
			GL_UNSIGNED_BYTE,p);
		return true;
	}
	else return false;

}
void Textura::save(const std::string & BMP_Name) {
	pA.create_pixmap(800, 600);
	glReadBuffer(GL_FRONT);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, 800, 600, 0); 
	glReadBuffer(GL_BACK);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, pA.data());
	pA.save_bmpBGR(BMP_Name);
}

												