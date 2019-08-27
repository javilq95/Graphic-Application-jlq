/*
 * File:   PagCamera.h
 * Author: Javier López Quesada
 */
#pragma once
#include <cstdlib>
#include <GL\glew.h>
#include "PagStructures.h"
#include <gtc/matrix_transform.hpp>

/**
 * @class PagCamera
 * @brief Clase encargada de la cámara
 */
class PagCamera
{
private:
	glm::vec3 position;
	glm::vec3 lookAt;
	glm::vec3 up;
	float fovY;
	float zNear;
	float zFar;
	float width;
	float height;
	glm::vec3 v;
	glm::vec3 u;
	glm::vec3 n;
	glm::mat4 viewMatrix;
	glm::mat4 projMatrix;
	void calculateV();
	void calculateViewMatrix();
	void calculateProjMatrix();
public:
	PagCamera(glm::vec3 _position, glm::vec3 _lookAt, glm::vec3 _up, float _fovY, float _zNear, float _zFar, float _width, float _height);
	~PagCamera();
	glm::mat4 getView();
	glm::mat4 getProj();
	glm::mat4 getViewProj();
	void setWidth(float _width);
	void setHeight(float _height);
	void setCamera(glm::vec3 _position, glm::vec3 _lookAt, glm::vec3 _up, float _fovY,
		float _zNear, float _zFar, float _width, float _height);
	void movOrbit(double xpos, double cursorX, double ypos, double cursorY);
	void movPan(double xpos, double cursorX, double ypos, double cursorY);
	void movTruck(double xpos, double cursorX, double ypos, double cursorY);
	void movCrane(double xpos, double cursorX, double ypos, double cursorY);
	void movDolly(double xpos, double cursorX, double ypos, double cursorY);
	void movZoom(float zoom);
};