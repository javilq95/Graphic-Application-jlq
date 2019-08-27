/*
 * File:   PagLightSource.cpp
 * Author: Javier López Quesada
 */
#include "PagLightSource.h"

/**
 * @brief Constructor por defecto
 */
PagLightSource::PagLightSource() : Ia(0), Id(0), Is(0), direction(glm::vec3(0, 0, 1)), position(glm::vec3(0, 0, 1)), 
exponent(0), angle(45), at1(0.5), at2(0.5), at3(0.5)
{
}

/**
 * @brief Destructor de PagLightSource
 */
PagLightSource::~PagLightSource()
{
}

/**
 * @brief Modifica el tipo de luz
 * @param a tipo de luz
 */
void PagLightSource::setType(PagLightAplication *a) {
	this->applicator = a;
	this->type = a->getType();
}

/**
 * @brief Devuelve el color ambiental
 * @return Ia
 */
glm::vec3 PagLightSource::getIa() {
	return Ia;
};

/**
 * @brief Modifica el color ambiental
 * @param _Ia color ambiental
 */
void PagLightSource::setIa(glm::vec3 _Ia) {
	Ia = _Ia;
}

/**
 * @brief Devuelve el color difuso
 * @return Id
 */
glm::vec3 PagLightSource::getId()
{
	return Id;
}

/**
 * @brief Modifica el color difuso
 * @param _Id color difuso
 */
void PagLightSource::setId(glm::vec3 _Id)
{
	Id = _Id;
}

/**
 * @brief Devuelve el color especular
 * @return Is
 */
glm::vec3 PagLightSource::getIs()
{
	return Is;
}

/**
 * @brief Modifica el color especular
 * @param _Is color especular
 */
void PagLightSource::setIs(glm::vec3 _Is)
{
	Is = _Is;
}

/**
 * @brief Devuelve la posición
 * @return position
 */
glm::vec3 PagLightSource::getPosition()
{
	return position;
}

/**
 * @brief Modifica la posición
 * @param _position posición
 */
void PagLightSource::setPosition(glm::vec3 _position)
{
	position = _position;
}

/**
 * @brief Devuelve la dirección
 * @return direction
 */
glm::vec3 PagLightSource::getDirection()
{
	return direction;
}

/**
 * @brief Modifica el vector de dirección
 * @param _direction dirección
 */
void PagLightSource::setDirection(glm::vec3 _direction)
{
	direction = _direction;
};

/**
 * @brief Devuelve el coeficiente de atenuación 1
 * @return at1
 */
float PagLightSource::getAt1() {
	return at1;
};

/**
 * @brief Modifica el coeficiente de atenuación 1
 * @param _at1 coeficiente de atenuación 1
 */
void PagLightSource::setAt1(float _at1)
{
	at1 = _at1;
}

/**
 * @brief Devuelve el coeficiente de atenuación 2
 * @return at2
 */
float PagLightSource::getAt2() {
	return at2;
};

/**
 * @brief Modifica el coeficiente de atenuación 2
 * @param _at2 coeficiente de atenuación 2
 */
void PagLightSource::setAt2(float _at2)
{
	at2 = _at2;
}

/**
 * @brief Devuelve el coeficiente de atenuación 3
 * @return at3
 */
float PagLightSource::getAt3() {
	return at3;
};

/**
 * @brief Modifica el coeficiente de atenuación 3
 * @param _at3 coeficiente de atenuación 3
 */
void PagLightSource::setAt3(float _at3)
{
	at3 = _at3;
}

/**
 * @brief Devuelve el ángulo
 * @return angle
 */
float PagLightSource::getAngle()
{
	return angle;
}

/**
 * @brief Modifica el ángulo
 * @param _angle angulo
 */
void PagLightSource::setAngle(float _angle)
{
	angle = _angle;
}

/**
 * @brief Devuelve el exponente
 * @return exponente
 */
float PagLightSource::getExponent()
{
	return exponent;
}

/**
 * @brief Modifica el exponente
 * @param _exponent exponente
 */
void PagLightSource::setExponent(float _exponent)
{
	exponent = _exponent;
}