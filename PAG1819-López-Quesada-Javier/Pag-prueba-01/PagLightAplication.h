/*
 * File:   PagLightAplication.h
 * Author: Javier López Quesada
 */
#pragma once
#include"PagShaderProgram.h"
#include "PagLightSource.h"

class PagLightSource;

/**
 * @class PagLightAplication
 * @brief Clase padre encargada de definir el aplicador de las distintas luces
 */
class PagLightAplication
{
public:
	virtual void shaderApplicator(PagShaderProgram *shader, glm::mat4 visionMatrix) = 0;
	virtual int getType() = 0;
};

