/*
 * File:   PagCamera.cpp
 * Author: Javier L�pez Quesada
 */
#include "PagCamera.h"

/**
 * @brief Calcula el vector v, mediante una serie de operaciones (Tema 5 Pg 9)
 */
void PagCamera::calculateV() {
	n = position - lookAt;
	n = glm::normalize(n);
	u = glm::cross(up, n);
	u = glm::normalize(u);
	v = cross(n, u);
}

/**
 * @brief M�todo privado para el c�lculo de la matriz de visi�n
 */
void PagCamera::calculateViewMatrix() {
	calculateV();
	viewMatrix = glm::lookAt(position, lookAt, up);
}

/**
  * @brief M�todo privado para el c�lculo de la matriz de proyecci�n
  */
void PagCamera::calculateProjMatrix() {
	projMatrix = glm::perspective(glm::radians(fovY), width / height, zNear, zFar);
}

/**
 * @brief Constructor parametrizado de PagCamera
 * @param _position posici�n de la c�mara
 * @param _lookAt punto al que mira la c�mara
 * @param _up vector arriba (normalmente (0, 1, 0))
 * @param _fovY �ngulo de visi�n en y
 * @param _znear marca el l�mite de recorte de la escena m�s cercano
 * @param _zfar marca el l�mite de recorte de la escena m�s lejano
 * @param _width ancho de la ventana
 * @param _height alto de la ventana
 */
PagCamera::PagCamera(glm::vec3 _position, glm::vec3 _lookAt, glm::vec3 _up, float _fovY, float _zNear, float _zFar, float _width, float _height) :
	position(_position), lookAt(_lookAt), up(_up), fovY(_fovY), zNear(_zNear), zFar(_zFar), width(_width), height(_height)
{
	calculateV();
	calculateViewMatrix();
	calculateProjMatrix();
}

/**
 * @brief Destructor de PagCamera
 */
PagCamera::~PagCamera()
{
}

/**
 * @brief Devuelve la matriz de visi�n
 * @return matriz visi�n
 */
glm::mat4 PagCamera::getView() {
	calculateViewMatrix();
	return viewMatrix;
}

/**
 * @brief Devuelve la matriz de proyecci�n
 * @return matriz proyecci�n
 */
glm::mat4 PagCamera::getProj() {
	calculateProjMatrix();
	return projMatrix;
}

/**
 * @brief Devuelve la matriz de visi�n proyecci�n, que se obtiene con el producto de estas
 */
glm::mat4 PagCamera::getViewProj() {
	return getProj() * getView();
}

/**
 * @brief Modifica la anchura de la ventana
 * @param _width ancho de la ventana
 */
void PagCamera::setWidth(float _width) {
	width = _width;
	calculateViewMatrix();
	calculateProjMatrix();
}

/**
 * @brief Modifica la altura de la ventana
 * @param _width alto de la ventana
 */
void PagCamera::setHeight(float _height) {
	height = _height;
	calculateViewMatrix();
	calculateProjMatrix();
}

/**
 * @brief Cambia los par�metros de la c�mara para cambiarla de posici�n, referencia, �ngulo...
 * @param _position posici�n de la c�mara
 * @param _lookAt punto al que mira la c�mara
 * @param _up vector arriba
 * @param _fovy �ngulo de visi�n en y
 * @param _width ancho de la ventana
 * @param _height alto de la ventana
 * @param _znear marca el l�mite de recorte de la escena m�s cercano
 * @param _zfar marca el l�mite de recorte de la escena m�s lejano
 */
void PagCamera::setCamera(glm::vec3 _position, glm::vec3 _lookAt, glm::vec3 _up, float _fovY,
	float _zNear, float _zFar, float _width, float _height) {
	position = _position;
	lookAt = _lookAt;
	up = _up;
	fovY = _fovY;
	width = _width;
	height = _height;
	zNear = _zNear,
	zFar = _zFar;
	calculateV();
	calculateViewMatrix();
	calculateProjMatrix();
}

/**
 * @brief Movimiento Orbit: Mover la c�mara fisicamente alrededor de un objetivo
 * @param xpos posicion actual x
 * @param cursorX posicion anterior x
 * @param ypos posicion actual y
 * @param cursorY posicion anterior y
 */
void PagCamera::movOrbit(double xpos, double cursorX, double ypos, double cursorY) {
	glm::mat4 moveOrigin = glm::translate(glm::mat4(1.0f), -lookAt);
	glm::mat4 move = glm::translate(glm::mat4(1.0f), lookAt);
	glm::mat4 rotate;

	if (xpos < cursorX) {
		rotate = glm::rotate(glm::mat4(1.0f), 0.05f, v);
	}
	else {
		rotate = glm::rotate(glm::mat4(1.0f), -0.05f, v);
	}

	position = glm::vec3((move * rotate * moveOrigin) * glm::vec4(position, 1.0));
}

/**
 * @brief Movimiento Pan: Se rota la c�mara en el eje x
 * @param xpos posicion actual x
 * @param cursorX posicion anterior x
 * @param ypos posicion actual y
 * @param cursorY posicion anterior y
 */
void PagCamera::movPan(double xpos, double cursorX, double ypos, double cursorY) {
	glm::mat4 moveOrigin = glm::translate(glm::mat4(1.0f), -position);
	glm::mat4 move = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotate;

	if (xpos < cursorX) {
		rotate = glm::rotate(glm::mat4(1.0f), 0.05f, v);
	}
	else {
		rotate = glm::rotate(glm::mat4(1.0f), -0.05f, v);
	}

	lookAt = glm::vec3((move * rotate * moveOrigin) * glm::vec4(lookAt, 1.0));
	position = glm::vec3((move * rotate * moveOrigin) * glm::vec4(position, 1.0));
}

/**
 * @brief Movimiento Truck: Se mueve la c�mara fisicamente en z, y la distancia focal permanece igual
 * @param xpos posicion actual x
 * @param cursorX posicion anterior x
 * @param ypos posicion actual y
 * @param cursorY posicion anterior y
 */
void PagCamera::movTruck(double xpos, double cursorX, double ypos, double cursorY) {
	if (ypos > cursorY) {
		position = position + 0.05f*n;
		lookAt = lookAt + 0.05f*n;
	}
	else {
		position = position - 0.05f*n;
		lookAt = lookAt - 0.05f*n;
	}
}

/**
 * @brief Movimiento Crane: Se mueve la c�mara fisicamente en y, y la distancia focal permanece igual
 * @param xpos posicion actual x
 * @param cursorX posicion anterior x
 * @param ypos posicion actual y
 * @param cursorY posicion anterior y
 */
void PagCamera::movCrane(double xpos, double cursorX, double ypos, double cursorY) {
	if (ypos < cursorY) {
		position = position + 0.05f*v;
		lookAt = lookAt + 0.05f*v;
	}
	else {
		position = position - 0.05f*v;
		lookAt = lookAt - 0.05f*v;
	}
}

/**
 * @brief Movimiento Dolly: Se mueve la c�mara fisicamente en x, y la distancia focal permanece igual
 * @param xpos posicion actual x
 * @param cursorX posicion anterior x
 * @param ypos posicion actual y
 * @param cursorY posicion anterior y
 */
void PagCamera::movDolly(double xpos, double cursorX, double ypos, double cursorY) {
	if (xpos < cursorX) {
		position = position + 0.05f*u;
		lookAt = lookAt + 0.05f*u;
	}
	else {
		position = position - 0.05f*u;
		lookAt = lookAt - 0.05f*u;
	}
}

/**
 * @brief Movimiento Zoom: No se mueve la c�mara fisicamente sino que cambia la distancia focal
 * @param zoom angulo de visi�n
 */
void PagCamera::movZoom(float zoom) {
	//Para evitar que se invierta la escena al acercar mucho el zoom
	if ((fovY + zoom) > 0 && (fovY + zoom) < 180)
		fovY += zoom;
}