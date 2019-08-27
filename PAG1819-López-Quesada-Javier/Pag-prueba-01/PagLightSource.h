/*
 * File:   PagLightSource.h
 * Author: Javier López Quesada
 */
#pragma once
#include "PagLightAplication.h"

class PagLightAplication;

/**
 * @class PagLightSource
 * @brief Clase que almacena los atributos de las distintas luces
 */
class PagLightSource
{
private:
	glm::vec3 Ia;
	glm::vec3 Id;
	glm::vec3 Is;
	glm::vec3 position;
	glm::vec3 direction;
	float angle;
	float exponent;
	float at1;
	float at2;
	float at3;
	PagLightAplication *applicator;
	int type;
public:
	PagLightSource();
	~PagLightSource();
	glm::vec3 getIa();
	void setIa(glm::vec3 _Ia);
	glm::vec3 getId();
	void setId(glm::vec3 _Id);
	glm::vec3 getIs();
	void setIs(glm::vec3 _Is);
	glm::vec3 getPosition();
	void setPosition(glm::vec3 _position);
	glm::vec3 getDirection();
	void setDirection(glm::vec3 _direction);
	float getAt1();
	void setAt1(float _at1);
	float getAt2();
	void setAt2(float _at2);
	float getAt3();
	void setAt3(float _at3);
	float getAngle();
	void setAngle(float _angle);
	float getExponent();
	void setExponent(float _exponent);
	void setType(PagLightAplication *a);
};

