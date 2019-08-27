/*
 * File:   PagSubdivisionProfile.h
 * Author: Javier López Quesada
 */
#pragma once
#include <glm.hpp>
#include <vector>
#include "PagEnumerations.h"
#include "PagStructures.h"
#include <gtc/epsilon.hpp>
#include <iostream>

 /**
  * @class PagSubdivisionProfile
  * @brief Clase encargada de generar un perfil de subdivisión
  */
class PagSubdivisionProfile
{
private:

	//vector de los puntos de perfil
	std::vector <glm::vec2> vPoints;
	bool isValidProfile = true;
	bool hasBottomFan = false;
	bool hasTopFan = false;
	std::vector<glm::vec2> subdivision(std::vector<glm::vec2> v);

public:
	PagSubdivisionProfile();
	PagSubdivisionProfile(std::vector<glm::vec2> points);
	~PagSubdivisionProfile();

	PagSubdivisionProfile subdivide(unsigned int times);
	std::vector <glm::vec2>& getVPoints();
	bool getIsValidProfile();
	bool getHasBottomFan();
	bool getHasTopFan();
};