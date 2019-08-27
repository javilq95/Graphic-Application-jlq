/*
 * File:   PagSporLight.h
 * Author: Javier López Quesada
 */
#pragma once
#include "PagLightAplication.h"

/**
 * @class PagSpotLight
 * @brief Clase de una fuente luminosa tipo foco
 */
class PagSpotLight : public PagLightAplication
{
private:
	PagLightSource *light;
public:
	PagSpotLight(glm::vec3 _id, glm::vec3 _is, glm::vec3 _direction, glm::vec3 _position, float _exp,
		float _angle, float _c1, float _c2, float _c3);
	~PagSpotLight();
	virtual void shaderApplicator(PagShaderProgram *shader, glm::mat4 visionMatrix);
	virtual int getType() {
		//Tipo luz spot = 2
		return 2;
	}
};

