/*
 * File:   PagSpotLight.cpp
 * Author: Javier López Quesada
 */
#include "PagSpotLight.h"
#include "gtc/constants.hpp"

/**
 * @brief Constructor parametrizado de PagSpotLight
 * @param _id color difuso
 * @param _is color especular
 * @param _direction dirección(es un vector no una posición)
 * @param _position posición de la luz
 * @param _exp exponente de Warn
 * @param _angle ángulo del foco
 * @param _at1 coeficiente de atenuación 1
 * @param _at2 coeficiente de atenuación 2
 * @param _at3 coeficiente de atenuación 3
 */
PagSpotLight::PagSpotLight(glm::vec3 _id, glm::vec3 _is, glm::vec3 _direction, glm::vec3 _position, float _exp,
	float _angle, float _at1, float _at2, float _at3)
{
	light = new PagLightSource();
	light->setId(_id);
	light->setIs(_is);
	light->setDirection(_direction);
	light->setPosition(_position);
	light->setExponent(_exp);
	light->setAngle(_angle);
	light->setAt1(_at1);
	light->setAt2(_at2);
	light->setAt3(_at3);
	light->setType(this);
}

/**
 * @brief Destructor de PagSpotLight
 */
PagSpotLight::~PagSpotLight()
{
	delete light;
}

/**
 * @brief Aplica el shader a una luz tipo foco
 * @param shader shader aplicado
 * @param visionMatrix matriz de visión
 */
void PagSpotLight::shaderApplicator(PagShaderProgram *shader, glm::mat4 visionMatrix)
{
	//Se calcula la posición y la dirección (normalizada) en base a la matriz de visión actual
	glm::vec3 position = glm::vec3(visionMatrix * glm::vec4(light->getPosition(), 1.0));
	glm::vec3 direction = glm::normalize(glm::vec3(visionMatrix * glm::vec4(light->getDirection(), 0.0)));

	//Se calcula el coseno del ángulo aquí para ahorrar una operación en el adsShader
	float cosAngle = cos(glm::radians(light->getAngle()));

	//Uniforms útiles para una luz tipo spot
	shader->setUniform("Id", light->getId());
	shader->setUniform("Is", light->getIs());
	shader->setUniform("positionL", position);
	shader->setUniform("direction", direction);
	shader->setUniform("exponent", light->getExponent());
	shader->setUniform("cosAngle", cosAngle);
	shader->setUniform("at1", light->getAt1());
	shader->setUniform("at2", light->getAt2());
	shader->setUniform("at3", light->getAt3());
	shader->setUniform("modeLight", this->getType());

	//Uniforms no utilizados (inicializados por defecto)
	shader->setUniform("Ia", glm::vec3());
}
