/*
 * File:   PagSubdivisionProfile.cpp
 * Author: Javier López Quesada
 */
#pragma once
#include "PagSubdivisionProfile.h"

const float EPSILON = glm::epsilon<double>();
const float PI = glm::pi<double>();

/**
 * @brief Constructor por defecto de PagSubdivisionProfile
 */
PagSubdivisionProfile::PagSubdivisionProfile()
{
}

/**
 * @brief Constructor parametrizado de PagSubdivisionProfile, deberá procesar el perfil que se pasa en el array, descartar los puntos erróneos y comprobar si
		  el perfil tiene o no tapas.
 * @param points
 */
PagSubdivisionProfile::PagSubdivisionProfile(std::vector<glm::vec2> points)
{

	//Evitamos los casos sin puntos y con un sólo punto
	if (points.size() < 2) {
		isValidProfile = false;
	}

	//Evitamos los casos con dos puntos y que ambos estén en el eje
	if (points.size() == 2) {
		if (abs(points[0].x - 0) < EPSILON && abs(points[1].x - 0) < EPSILON) {
			isValidProfile = false;
		}
	}

	//Evitamos los casos con dos puntos y que ambos estén en el eje
	if (points.size() == 3) {
		if (abs(points[0].x - 0) < EPSILON && abs(points[2].x - 0) < EPSILON) {
			isValidProfile = false;
		}
	}

	if (isValidProfile) {

		//Comprobación de tapa inferior
		if (abs(points[0].x - 0) < EPSILON) {
			hasBottomFan = true;
			vPoints.push_back(points[0]);
		}
		else {
			if (points[0].x > EPSILON)
				vPoints.push_back(points[0]);
		}

		//Se recorren todos los puntos (excepto el primero y el último) descartando los puntos con x<=0
		for (int i = 1; i < points.size() - 1; i++) {
			if (points[i].x > EPSILON) {
				vPoints.push_back(points[i]);
			}
		}

		//Comprobación de tapa superior
		if (abs(points[points.size() - 1].x - 0) < EPSILON) {
			hasTopFan = true;
			vPoints.push_back(points[points.size() - 1]);
		}
		else {
			if (points[points.size() - 1].x > EPSILON)
				vPoints.push_back(points[points.size() - 1]);
		}

		//Repetimos el proceso anterior por si al descartar puntos se dan algunos de estos casos en el vector final
		if (vPoints.size() < 2) {
			isValidProfile = false;
		}

		if (vPoints.size() == 2) {
			if (abs(vPoints[0].x - 0) < EPSILON && abs(vPoints[1].x - 0) < EPSILON) {
				isValidProfile = false;
			}
		}

		if (vPoints.size() == 3) {
			if (abs(vPoints[0].x - 0) < EPSILON && abs(vPoints[2].x - 0) < EPSILON) {
				isValidProfile = false;
			}
		}
	}
}

/**
 * @brief Destructor de PagSubdivisionProfile
 */
PagSubdivisionProfile::~PagSubdivisionProfile()
{
}

/**
 * @brief Genera un nuevo perfil de subdivisión (el perfil original debe permanecer sin cambios)
 * @param times número de veces que se aplica la subdivision
 * @return perfil de subdivisión
 */
PagSubdivisionProfile PagSubdivisionProfile::subdivide(unsigned int times)
{

	if (isValidProfile) {
		for (int j = 0; j < times; j++) {
			vPoints = subdivision(vPoints);
		}
		return *this;
	}
}

std::vector<glm::vec2> PagSubdivisionProfile::subdivision(std::vector<glm::vec2> v) {
	std::vector<glm::vec2> vPrima;

	//Añadir p0 a P’
	vPrima.push_back(vPoints[0]);

	for (int i = 1; i <= vPoints.size() - 2; i++) {

		//Añadir (pi-1+pi)/2 a P’
		glm::vec2 h1((vPoints[i - 1].x + vPoints[i].x) / 2,
			(vPoints[i - 1].y + vPoints[i].y) / 2);
		vPrima.push_back(h1);

		//Añadir (3*pi/4)+(pi-1/8)+(pi+1/8) a P’
		glm::vec2 p((3 * vPoints[i].x / 4) + (vPoints[i - 1].x / 8) + (vPoints[i + 1].x / 8),
			(3 * vPoints[i].y / 4) + (vPoints[i - 1].y / 8) + (vPoints[i + 1].y / 8));
		vPrima.push_back(p);
	}

	//Añadir (pn-2+pn-1)/2 a P’
	glm::vec2 h2((vPoints[vPoints.size() - 2].x + vPoints[vPoints.size() - 1].x) / 2,
		(vPoints[vPoints.size() - 2].y + vPoints[vPoints.size() - 1].y) / 2);
	vPrima.push_back(h2);

	//Añadir pn-1 a P’
	vPrima.push_back(vPoints[vPoints.size() - 1]);

	return vPrima;

}

/**
 * @brief Devuelve el vector de puntos del perfil
 * @return vector de puntos
 */
std::vector <glm::vec2>& PagSubdivisionProfile::getVPoints() {
	return this->vPoints;
}

/**
 * @brief Devuelve si el perfil es válido en función del vector de puntos
 * @return true perfil válido, false perfil no válido
 */
bool PagSubdivisionProfile::getIsValidProfile() {
	return this->isValidProfile;
}

/**
 * @brief Devuelve si el objeto tiene tapa inferior en función del vector de puntos
 * @return true tiene tapa inferior, false no tiene
 */
bool PagSubdivisionProfile::getHasBottomFan() {
	return this->hasBottomFan;
}

/**
 * @brief Devuelve si el objeto tiene tapa superior en función del vector de puntos
 * @return true tiene tapa superior, false no tiene
 */
bool PagSubdivisionProfile::getHasTopFan() {
	return this->hasTopFan;
}

