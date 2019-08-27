/*
 * File:   PagSubdivisionProfile.cpp
 * Author: Javier López Quesada
 */
#pragma once
#include "PagRevolutionObject.h"
#include <fstream>
#include <gtc\matrix_transform.hpp>

const float EPSILON = glm::epsilon<double>();
const float PI = glm::pi<double>();

/**
 * @brief Constructor por defecto de PagRevolutionObject
 */
PagRevolutionObject::PagRevolutionObject()
{
}

/**
 * @brief Constructor de copia de PagRevolutionObject
 * @param p perfil copiado
 */
PagRevolutionObject::PagRevolutionObject(const PagRevolutionObject &p) : profile(p.profile)
{
}

/**
 * @brief Constructor parametrizado de PagRevolutionObject
 * @param points puntos del perfil
 * @param subdivisions número de subdivisiones
 * @param slices número de cortes longitudinales
 */
PagRevolutionObject::PagRevolutionObject(std::vector<glm::vec2> points, unsigned int subdivisions, unsigned int slices)
	:profile(points)
{
	body = new PagVAO();
	topFan = new PagVAO();
	bottomFan = new PagVAO();

	if (profile.getIsValidProfile()) {

		profile = profile.subdivide(subdivisions);

		//se crea una copia del vector definitivo
		std::vector <glm::vec2> vPoints(profile.getVPoints());

		//Número de puntos del perfil
		int numProfilePoints = vPoints.size();

		//CÁLCULO PREVIO DE NORMALES Y DISTANCIAS
		std::vector<glm::vec2> vNorm;
		std::vector<float> vDistance;
		float totalDistance = 0.0;
		float distance = 0.0;
		//La normal de la tapa superior apunta hacia abajo (y negativa)
		if (profile.getHasBottomFan()) {
			vNorm.push_back(glm::vec2(0, -1));
		}
		else {
			glm::vec2 v = vPoints[1] - vPoints[0];
			v.x = -v.x;
			v = normalize(v);
			vNorm.push_back(v);
		}

		for (int i = 1; i < numProfilePoints - 1; i++) {
			//Calculamos vi = pi+1 - pi y vi-1 = pi - pi-1
			glm::vec2 v = vPoints[i + 1] - vPoints[i];
			glm::vec2 vAnt = vPoints[i] - vPoints[i - 1];
			//Insertamos la distancia
			distance = glm::distance(vAnt, v);
			totalDistance += distance;
			vDistance.push_back(totalDistance);
			//Rotamos para obtener un vector perpendicular
			v.x = -v.x;
			vAnt.x = -vAnt.x;
			std::swap(v.x, v.y);
			std::swap(vAnt.x, vAnt.y);
			//Calculamos el vector intermedio
			glm::vec2 vFinal((v.x + vAnt.x) / 2, (v.y + vAnt.y) / 2);
			//Normalizamos el resultado, dividiendo entre el valor absoluto de vFinal
			vFinal = normalize(vFinal);
			vNorm.push_back(vFinal);
		}

		//Normal y distancia del último punto (ya que queda excluido del bucle anterior)
		glm::vec2 v = vPoints[numProfilePoints - 1] - vPoints[numProfilePoints - 2];
		v.x = -v.x;
		std::swap(v.x, v.y);
		v = normalize(v);
		vNorm.push_back(v);
		vDistance.push_back(totalDistance);

		//La normal de la tapa superior apunta hacia arriba (y positiva)
		if (profile.getHasTopFan()) {
			vNorm.push_back(glm::vec2(0, 1));
		}
		else {
			glm::vec2 v = vPoints[numProfilePoints - 1] - vPoints[numProfilePoints - 2];
			v.x = -v.x;
			v = normalize(v);
			vNorm.push_back(v);
		} 

		//Se calcula el vector de texturas en y
		std::vector<float> vTextY;
		vTextY.push_back(0.0);
		for (int i = 0; i < vDistance.size(); i++) {
			vTextY.push_back(vDistance[i] / totalDistance);
		}

		//CÁLCULO DE NORMALES, COORDENADAS DE TEXTURA Y TANGENTES POR REVOLUCIÓN
		//Variables para evitar la revolución de tapas
		bool bottomFanIntroduced = false;
		bool topFanIntroduced = false;

		//delta se calcula dividiendo 360º entre el número de cortes longitudinales (360º = 2pi radianes)
		float delta = 2 * PI / slices;
		for (int i = 0; i < numProfilePoints; i++) {
			for (int s = 0; s <= slices; s++) {
				//Calcular el ángulo a = s * delta
				float a = s * delta;
				//Cálculo de posiciones pi = (xi * cos(a), yi, -xi * sin(a))
				float x = vPoints[i].x * cos(a);
				float y = vPoints[i].y;
				float z = -(vPoints[i].x) * sin(a);
				glm::vec3 posicion(x, y, z);
				//Cálculo de normales de revolución ni = (nxi * cos(a), nyi, -nxi * sin(a))
				float xNorm = vNorm[i].x * cos(a);
				float yNorm = vNorm[i].y;
				float zNorm = -(vNorm[i].x) * sin(a);
				glm::vec3 normal(xNorm, yNorm, zNorm);
				PagPosNorm posNorm;
				posNorm.position = posicion;
				posNorm.normal = normal;

				//Fórmula para el cálculo de la tangente t(i) = (-sin(a), 0, -cos(a))
				glm::vec3 tangent(-sin(a), 0, -cos(a));

				//Se identifica si tiene tapa inferior (formada en i=0 e i=1, si la hubiera)
				if (i <= 1 && profile.getHasBottomFan()) {
					if (i == 0 && bottomFanIntroduced == false) {
						glm::vec3 posicionI(vPoints[i].x, vPoints[i].y, 0);
						glm::vec3 normalI(vNorm[i].x, vNorm[i].y, 0);
						PagPosNorm posNormI;
						posNormI.position = posicionI;
						posNormI.normal = normalI;
						glm::vec2 texturaI(0.5, 0.5);
						glm::vec3 tangenteI(1, 0, 0);
						bottomFan->insertPosNorm(posNormI);
						bottomFan->insertCoordText(texturaI);
						bottomFan->insertTang(tangenteI);
						bottomFanIntroduced = true;
					}
					if (i == 1) {
						glm::vec2 texturaI(((sin(a)) / 2) + 0.5, ((cos(a)) / 2) + 0.5);
						bottomFan->insertPosNorm(posNorm);
						bottomFan->insertCoordText(texturaI);
						bottomFan->insertTang(tangent);
					}
				}

				//Se identifica si tiene tapa superior (formada en i=penúltimo e i=último, si la hubiera)
				if (i >= numProfilePoints - 2 && profile.getHasTopFan()) {
					if (i == numProfilePoints - 2) {
						glm::vec2 texturaS(((sin(a)) / 2) + 0.5, ((cos(a)) / 2) + 0.5);
						topFan->insertPosNorm(posNorm);
						topFan->insertCoordText(texturaS);
						topFan->insertTang(tangent);
					}
					if (i == numProfilePoints - 1 && topFanIntroduced == false) {
						glm::vec3 posicionS(vPoints[i].x, vPoints[i].y, 0);
						glm::vec3 normalS(vNorm[i].x, vNorm[i].y, 0);
						PagPosNorm posNormS;
						posNormS.position = posicionS;
						posNormS.normal = normalS;
						glm::vec2 texturaS(0.5, 0.5);
						glm::vec3 tangenteS(1, 0, 0);
						topFan->insertPosNorm(posNormS);
						topFan->insertCoordText(texturaS);
						topFan->insertTang(tangenteS);
						topFanIntroduced = true;
					}
				}

				//Excluye tanto los casos en que i=0 y hay tapa inferior, como los que i=tam-1 y hay tapa superior
				if (!(i == 0 && profile.getHasBottomFan()) && !(i == numProfilePoints - 1 && profile.getHasTopFan())) {
					//Fórmula para el cálculo de coordenada de textura
					glm::vec2 texture(s / (slices*1.0), vTextY[i]);
					body->insertPosNorm(posNorm);
					body->insertCoordText(texture);
					body->insertTang(tangent);
				}
			}
		}

		//se calcula la altura del perfil
		int height = numProfilePoints;
		if (profile.getHasBottomFan()) {
			height--;
		}
		if (profile.getHasTopFan()) {
			height--;
		}

		//TOPOLOGÍA TAPA INFERIOR
		if (profile.getHasBottomFan()) {
			//puntos
			for (int i = 0; i < bottomFan->size() - 1; i++)
				bottomFan->insertPointsIndex(i);
			//mallas
			for (int s = 1; s <= slices; s++) {
				bottomFan->insertTrianglesIndex(0);
				bottomFan->insertTrianglesIndex(s + 1);
				bottomFan->insertTrianglesIndex(s);
				bottomFan->insertTrianglesIndex(0xFFFF);
			}
			//alambres
			for (int i = 1; i <= slices; i++) {
				bottomFan->insertLinesIndex(0);
				bottomFan->insertLinesIndex(i);
				bottomFan->insertLinesIndex(0xFFFF);
			}
			for (int i = 1; i <= slices + 1; i++) {
				bottomFan->insertLinesIndex(i);
			}
		}

		//TOPOLOGÍA CUERPO

		//Puntos
		for (int i = 0; i < height; i++) {
			for (int s = 0; s <= slices; s++) {
				body->insertPointsIndex(i * (slices + 1) + s);
			}
		}

		//Mallas de triangulos
		for (int s = 0; s < slices; s++) {
			for (int i = 0; i < height - 1; i++) {
				body->insertTrianglesIndex(s + (slices + 1) * i);
				body->insertTrianglesIndex(s + 1 + (slices + 1) * i);
				body->insertTrianglesIndex(s + (slices + 1) * (i + 1));
				body->insertTrianglesIndex(0xFFFF);

				body->insertTrianglesIndex(s + (slices + 1) * i + 1);
				body->insertTrianglesIndex(s + (slices + 1) * (i + 1) + 1);
				body->insertTrianglesIndex(s + (slices + 1) * (i + 1));
				body->insertTrianglesIndex(0xFFFF);
			}
		}

		//Alambres horizontales
		for (int i = 0; i < height; i++) {
			for (int s = 0; s <= slices; s++) {
				body->insertLinesIndex(i*(slices + 1) + s);
			}
			body->insertLinesIndex(0xFFFF);
		}
		//Alambres verticales
		for (int s = 0; s <= slices; s++) {
			for (int i = 0; i < height; i++) {
				body->insertLinesIndex(i*(slices + 1) + s);
			}
			body->insertLinesIndex(0xFFFF);
		}

		//TOPOLOGÍA TAPA SUPERIOR
		if (profile.getHasTopFan()) {
			//puntos
			for (int i = 1; i < topFan->size(); i++)
				topFan->insertPointsIndex(i);
			//mallas
			for (int s = 0; s <= slices; s++) {
				topFan->insertTrianglesIndex(slices + 1);
				topFan->insertTrianglesIndex(s);
				topFan->insertTrianglesIndex(s + 1);
				topFan->insertTrianglesIndex(0xFFFF);
			}
			//alambres
			for (int i = 0; i <= slices; i++) {
				topFan->insertLinesIndex(slices + 1);
				topFan->insertLinesIndex(i);
				topFan->insertLinesIndex(0xFFFF);
			}
			for (int i = 0; i <= slices; i++) {
				topFan->insertLinesIndex(i);
			}
		}
		//Se rellena la geometría
		bottomFan->fillGeometry();
		body->fillGeometry();
		topFan->fillGeometry();
	}
	else {
		std::cout << "The profile isn't valid" << std::endl;
	}
}

/**
  * @brief Destructor de PagRevolutionObject
 */
PagRevolutionObject::~PagRevolutionObject()
{
	delete body;
	delete topFan;
	delete bottomFan;
}

/**
  * @brief Devuelve si el perfil en el que se basa ese objeto de revolución es válido (número de puntos suficiente...)
  * @return true si es válido, false si no lo es
 */
bool PagRevolutionObject::isValid()
{
	return profile.getIsValidProfile();
}

/**
  * @brief Devuelve si el objeto de revolución tiene la parte dada
  * @param part parte (cuerpo, tapa superior y tapa inferior) que se pasa como parámetro
  * @return true coinciden las partes, false si no coinciden
 */
bool PagRevolutionObject::has(PagRevObjParts part)
{
	if (this->isValid()) {
		if (part == PAG_BODY) {
			return true;
		}
		else {
			if (part == PAG_BOTTOM_FAN) {
				return profile.getHasBottomFan();
			}
			if (part == PAG_TOP_FAN) {
				return profile.getHasTopFan();
			}
		}
	}
	else {
		std::cout << "The profile isn't valid" << std::endl;
		return false;
	}
}

/**
  * @brief Devuelve el número de elementos de la parte dada
  * @param part parte (cuerpo, tapa superior y tapa inferior) que se pasa como parámetro
  * @return número de elementos
 */
unsigned int PagRevolutionObject::getNPoints(PagRevObjParts part)
{
	if (this->isValid()) {
		if (part == PAG_BODY) {
			return body->size();
		}
		else {
			if (part == PAG_BOTTOM_FAN) {
				return bottomFan->size();
			}
			if (part == PAG_TOP_FAN) {
				return topFan->size();
			}
		}
	}
	else {
		std::cout << "The profile isn't valid" << std::endl;
		return -1;
	}
}

/**
  * @brief Dibuja en modo puntos
 */
void PagRevolutionObject::drawAsPoints(PagShaderProgram *shader, glm::mat4 viewProject) {
	if (has(PAG_BODY))
		body->drawAsPoints();
	if (has(PAG_BOTTOM_FAN))
		bottomFan->drawAsPoints();
	if (has(PAG_TOP_FAN))
		topFan->drawAsPoints();
}

/**
  * @brief Dibuja en modo mallas de triángulos
 */
void PagRevolutionObject::drawAsTriangles(PagShaderProgram *shader, glm::mat4 viewProject, glm::mat4 view){
	if (has(PAG_BODY))
		body->drawAsTriangles(PAG_BODY);
	if (has(PAG_BOTTOM_FAN))
		bottomFan->drawAsTriangles(PAG_BOTTOM_FAN);
	if (has(PAG_TOP_FAN))
		topFan->drawAsTriangles(PAG_TOP_FAN);
}

/**
  * @brief Dibuja en modo alambres/líneas
 */
void PagRevolutionObject::drawAsLines(PagShaderProgram *shader, glm::mat4 viewProject) {
	if (has(PAG_BODY))
		body->drawAsLines();
	if (has(PAG_BOTTOM_FAN))
		bottomFan->drawAsLines();
	if (has(PAG_TOP_FAN))
		topFan->drawAsLines();
}