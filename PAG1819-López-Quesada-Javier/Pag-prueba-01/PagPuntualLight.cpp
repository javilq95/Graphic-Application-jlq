/*
 * File:   PagPuntualLight.cpp
 * Author: Javier López Quesada
 */
#include "PagPuntualLight.h"

/**
 * @brief Constructor parametrizado de PagPuntualLight
 * @param _id color difuso
 * @param _is color especular
 * @param _position posición de la luz
 * @param _at1 coeficiente de atenuación 1
 * @param _at2 coeficiente de atenuación 2
 * @param _at3 coeficiente de atenuación 3
 */
PagPuntualLight::PagPuntualLight(glm::vec3 _id, glm::vec3 _is, glm::vec3 _position, float _at1, float _at2, float _at3)
{
	light = new PagLightSource();
	light->setId(_id);
	light->setIs(_is);
	light->setPosition(_position);
	light->setAt1(_at1);
	light->setAt2(_at2);
	light->setAt3(_at3);
	light->setType(this);
}

/**
 * @brief Destructor de PagPuntualLight
 */
PagPuntualLight::~PagPuntualLight()
{
	delete light;
}

/**
 * @brief Aplica el shader a una luz tipo puntual
 * @param shader shader aplicado
 * @param visionMatrix matriz de visión
 */
void PagPuntualLight::shaderApplicator(PagShaderProgram *shader, glm::mat4 visionMatrix)
{
	//Se calcula la posición en base a la matriz de visión actual
	glm::vec3 position = glm::vec3(visionMatrix * glm::vec4(light->getPosition(), 1.0));

	//Uniforms útiles para una luz puntual
	shader->setUniform("positionL", position);
	shader->setUniform("Id", light->getId());
	shader->setUniform("Is", light->getIs());
	shader->setUniform("at1", light->getAt1());
	shader->setUniform("at2", light->getAt2());
	shader->setUniform("at3", light->getAt3());
	shader->setUniform("modeLight", this->getType());

	//Uniforms no utilizados (inicializados por defecto)
	shader->setUniform("Ia", glm::vec3());
	shader->setUniform("direction", glm::vec3());
	shader->setUniform("exponent", 0.0f);
	shader->setUniform("cosAngle", 0.0f);
}