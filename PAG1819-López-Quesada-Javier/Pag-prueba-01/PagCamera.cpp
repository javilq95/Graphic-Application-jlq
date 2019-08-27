/*
 * File:   PagCamera.cpp
 * Author: Javier López Quesada
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
 * @brief Método privado para el cálculo de la matriz de visión
 */
void PagCamera::calculateViewMatrix() {
	calculateV();
	viewMatrix = glm::lookAt(position, lookAt, up);
}

/**
  * @brief Método privado para el cálculo de la matriz de proyección
  */
void PagCamera::calculateProjMatrix() {
	projMatrix = glm::perspective(glm::radians(fovY), width / height, zNear, zFar);
}

/**
 * @brief Constructor parametrizado de PagCamera
 * @param _position posición de la cámara
 * @param _lookAt punto al que mira la cámara
 * @param _up vector arriba (normalmente (0, 1, 0))
 * @param _fovY ángulo de visión en y
 * @param _znear marca el límite de recorte de la escena más cercano
 * @param _zfar marca el límite de recorte de la escena más lejano
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
 * @brief Devuelve la matriz de visión
 * @return matriz visión
 */
glm::mat4 PagCamera::getView() {
	calculateViewMatrix();
	return viewMatrix;
}

/**
 * @brief Devuelve la matriz de proyección
 * @return matriz proyección
 */
glm::mat4 PagCamera::getProj() {
	calculateProjMatrix();
	return projMatrix;
}

/**
 * @brief Devuelve la matriz de visión proyección, que se obtiene con el producto de estas
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
 * @brief Cambia los parámetros de la cámara para cambiarla de posición, referencia, ángulo...
 * @param _position posición de la cámara
 * @param _lookAt punto al que mira la cámara
 * @param _up vector arriba
 * @param _fovy ángulo de visión en y
 * @param _width ancho de la ventana
 * @param _height alto de la ventana
 * @param _znear marca el límite de recorte de la escena más cercano
 * @param _zfar marca el límite de recorte de la escena más lejano
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
 * @brief Movimiento Orbit: Mover la cámara fisicamente alrededor de un objetivo
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
 * @brief Movimiento Pan: Se rota la cámara en el eje x
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
 * @brief Movimiento Truck: Se mueve la cámara fisicamente en z, y la distancia focal permanece igual
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
 * @brief Movimiento Crane: Se mueve la cámara fisicamente en y, y la distancia focal permanece igual
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
 * @brief Movimiento Dolly: Se mueve la cámara fisicamente en x, y la distancia focal permanece igual
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
 * @brief Movimiento Zoom: No se mueve la cámara fisicamente sino que cambia la distancia focal
 * @param zoom angulo de visión
 */
void PagCamera::movZoom(float zoom) {
	//Para evitar que se invierta la escena al acercar mucho el zoom
	if ((fovY + zoom) > 0 && (fovY + zoom) < 180)
		fovY += zoom;
}