/*
 * File:   PagPlane.h
 * Author: Javier López Quesada
 */
#pragma once
#include "Pag3DElement.h"
#include "PagVAO.h"

/**
 * @class PagPlane
 * @brief Clase encargada de crear planos
 */
class PagPlane : public Pag3DElement
{
private:
	PagVAO *plane;
	float width;
	float height;
	int verticalSquares;
	int horizontalSquares;
public:
	PagPlane(float _width, float _height, int _verticalSquares, int _horizontalSquares);
	~PagPlane();
	virtual void drawAsPoints(PagShaderProgram *shader, glm::mat4 viewProject);
	virtual void drawAsTriangles(PagShaderProgram *shader, glm::mat4 viewProject, glm::mat4 view);
	virtual void drawAsLines(PagShaderProgram *shader, glm::mat4 viewProject);
};

