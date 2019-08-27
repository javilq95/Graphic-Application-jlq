/*
 * File:   PagRenderer.h
 * Author: Javier L�pez Quesada
 */
#pragma once
#include <cstdlib>
#include "PagRevolutionObject.h"
#include "PagLightAplication.h"
#include "PagShaderProgram.h"
#include "PagCamera.h"
#include "PagPlane.h"
#include "Pag3DGroup.h"
#include <iostream>
#include <GL\glew.h>
#include "PagSpotLight.h"
#include "PagAmbientLight.h"
#include "PagPuntualLight.h"
#include "PagTexture.h"
#include "PagLibraryMaterial.h"
#include "PagLibraryTexture.h"

// - La clase PagRenderer encapsula toda la gesti�n del �rea de dibujo
// OpenGL, eventos, etc.
// Se implementa como un singleton para que pueda ser llamada desde las
// funciones callback del main.cpp
class PagRenderer
{
private:
	int modeShader = 0;
	int modeDebug = 0;
	int modeMov = 0;
	int modeLight = 0;
	PagCamera *camera;
	bool cameraChange = false;
	double cursorX;
	double cursorY;
	Pag3DGroup *escene;
	std::vector<PagLightAplication*> lights;

	//Shader program que se usa para dibujar la geometr�a.
	PagShaderProgram pointShader;
	PagShaderProgram trianglesShader;
	PagShaderProgram wiresShader;
	PagShaderProgram debugShader;
	PagShaderProgram adsShader;
	PagShaderProgram textureShader;

	//Este es el singleton instancia
	static PagRenderer *instance;

	//Constructor privado. Esto impide que se puedan construir nuevos renderers aparte del singleton
	PagRenderer();
public:
	~PagRenderer();
	// - Aqu� se definen los m�todos que gestionar�n el �rea de dibujo
	// OpenGL. Por ejemplo refreshCallback que ser� llamado cada vez
	// que haya que redibujar la escena.
	void refreshCallback();
	void framebuffer_size_callback(int width, int height);
	void key_callback(int key, int scancode, int action, int mods);
	void mouse_button_callback(int button, int action, int mods);
	void scroll_callback(double xoffset, double yoffset);
	void cursorPositionCallback(double xpos, double ypos);

	// - Aqu� se deben definir los m�todos de instancia que faltan para
	// responder a los dem�s eventos
	// - Este m�todo de clase permite acceder al singleton. Cada vez
	// que se necesite llamar al renderer se har� a trav�s de este
	// m�todo.
	static PagRenderer *getInstance();
	void prepareOpenGL();

	double* getCursorX() {
		return &cursorX;
	};
	double* getCursorY() {
		return &cursorY;
	};
};