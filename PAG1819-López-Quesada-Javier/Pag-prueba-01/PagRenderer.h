/*
 * File:   PagRenderer.h
 * Author: Javier López Quesada
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

// - La clase PagRenderer encapsula toda la gestión del área de dibujo
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

	//Shader program que se usa para dibujar la geometría.
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
	// - Aquí se definen los métodos que gestionarán el área de dibujo
	// OpenGL. Por ejemplo refreshCallback que será llamado cada vez
	// que haya que redibujar la escena.
	void refreshCallback();
	void framebuffer_size_callback(int width, int height);
	void key_callback(int key, int scancode, int action, int mods);
	void mouse_button_callback(int button, int action, int mods);
	void scroll_callback(double xoffset, double yoffset);
	void cursorPositionCallback(double xpos, double ypos);

	// - Aquí se deben definir los métodos de instancia que faltan para
	// responder a los demás eventos
	// - Este método de clase permite acceder al singleton. Cada vez
	// que se necesite llamar al renderer se hará a través de este
	// método.
	static PagRenderer *getInstance();
	void prepareOpenGL();

	double* getCursorX() {
		return &cursorX;
	};
	double* getCursorY() {
		return &cursorY;
	};
};