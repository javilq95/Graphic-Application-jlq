/*
 * File:   PagPuntualLight.h
 * Author: Javier López Quesada
 */
#pragma once
#include "PagLightAplication.h"

/**
 * @class PagPuntualLight
 * @brief Clase de una fuente luminosa puntual
 */
class PagPuntualLight : public PagLightAplication
{
private:
	PagLightSource *light;
public:
	PagPuntualLight(glm::vec3 _id, glm::vec3 _is, glm::vec3 _position, float _at1, float _at2, float _at3);
	~PagPuntualLight();
	virtual void shaderApplicator(PagShaderProgram *shader, glm::mat4 visionMatrix);
	virtual int getType() {
		//Tipo luz puntual = 1
		return 1;
	}
};

