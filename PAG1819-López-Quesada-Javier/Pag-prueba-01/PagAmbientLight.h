/*
 * File:   PagAmbientLight.h
 * Author: Javier López Quesada
 */
#pragma once
#include "PagLightAplication.h"

/**
 * @class PagAmbientLight
 * @brief Clase de una fuente luminosa ambiental
 */
class PagAmbientLight : public PagLightAplication
{
private:
	PagLightSource *light;
public:
	PagAmbientLight(glm::vec3 _ia);
	~PagAmbientLight();
	virtual void shaderApplicator(PagShaderProgram *shader, glm::mat4 visionMatrix);
	virtual int getType() {
		//Tipo luz ambiental = 0
		return 0;
	}
};

