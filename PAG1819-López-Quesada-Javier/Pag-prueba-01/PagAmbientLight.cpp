/*
 * File:   PagAmbientLight.cpp
 * Author: Javier López Quesada
 */
#include "PagAmbientLight.h"

/**
 * @brief Constructor parametrizado de PagAmbientLight
 * @param _ia color ambiental
 */
PagAmbientLight::PagAmbientLight(glm::vec3 _ia)
{
	light = new PagLightSource();
	light->setIa(_ia);
	light->setType(this);
}

/**
 * @brief Destructor de PagAmbientLight
 */
PagAmbientLight::~PagAmbientLight()
{
	delete light;
}

/**
 * @brief Aplica el shader a una luz tipo ambiental
 * @param shader shader aplicado
 * @param visionMatrix matriz de visión
 */
void PagAmbientLight::shaderApplicator(PagShaderProgram *shader, glm::mat4 visionMatrix)
{
	//Uniforms útiles para una luz ambiental
	shader->setUniform("Ia", light->getIa());
	shader->setUniform("modeLight", getType());

	//Uniforms no utilizados (inicializados por defecto)
	shader->setUniform("Id", glm::vec3());
	shader->setUniform("Is", glm::vec3());
	shader->setUniform("positionL", glm::vec3());
	shader->setUniform("direction", glm::vec3());
	shader->setUniform("exponent", 0.0f);
	shader->setUniform("cosAngle", 0.0f);
	shader->setUniform("at1", 0.0f);
	shader->setUniform("at2", 0.0f);
	shader->setUniform("at3", 0.0f);
}
