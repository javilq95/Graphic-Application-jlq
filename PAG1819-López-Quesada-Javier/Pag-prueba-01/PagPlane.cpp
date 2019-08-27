/*
 * File:   PagPlane.cpp
 * Author: Javier L�pez Quesada
 */
#include "PagPlane.h"

/**
 * @brief Constructor parametrizado de PagRevolutionObject
 * @param points puntos del perfil
 * @param subdivisions n�mero de subdivisiones
 * @param slices n�mero de cortes longitudinales
 */
PagPlane::PagPlane(float _width, float _height, int _verticalSquares, int _horizontalSquares):
	width(_width), height(_height), verticalSquares(_verticalSquares), horizontalSquares(_horizontalSquares)
{
	plane = new PagVAO();
	float sizeSquareX = width / horizontalSquares;
	float sizeSquareY = height / verticalSquares;

	//calculo de coordenadas de textura y tangentes
	for (int i = 0; i <= horizontalSquares; i++) {
		for (int j = 0; j <= verticalSquares; j++) {
			plane->insertCoordText(glm::vec2(i / (1.0 * verticalSquares), j / (1.0 * horizontalSquares)));
			plane->insertTang(glm::vec3(1.0, 0.0, 0.0));
		}
	}

	//calculo de posiciones y normales
	for (float i = 0.0; i <= width; i += sizeSquareX) {
		for (float j = 0.0; j <= height; j += sizeSquareY) {
			glm::vec3 posicion(j, 0, i);
			glm::vec3 normal(0, 1, 0);
			PagPosNorm posNorm;
			posNorm.position = posicion;
			posNorm.normal = normal;
			plane->insertPosNorm(posNorm);

		}
	}

	//Topolog�a de puntos
	for (int j = 0; j < plane->getVPosNorm().size(); j++) {
		plane->insertPointsIndex(j);
	}
	
	//Topolog�a de mallas y alambres
	for (int i = 0; i <= verticalSquares; i++) {
		for (int j = 0; j < horizontalSquares; j++) {
			plane->insertLinesIndex(i * (horizontalSquares + 1) + j);
			plane->insertLinesIndex(i * (horizontalSquares + 1) + j + 1);
			plane->insertLinesIndex(0xFFFF);
		}
	}

	for (int i = 0; i < verticalSquares; i++) {
		for (int j = 0; j <= horizontalSquares; j++) {
			plane->insertLinesIndex(i * (horizontalSquares + 1) + j);
			plane->insertLinesIndex(i * (horizontalSquares + 1) + (horizontalSquares + 1) + j);
			plane->insertLinesIndex(0xFFFF);
		}
	}

	for (int i = 0; i < verticalSquares; i++) {
		for (int j = 0; j < horizontalSquares; j++) {
			plane->insertTrianglesIndex(i * (horizontalSquares + 1) + j);
			plane->insertTrianglesIndex(i * (horizontalSquares + 1) + j + (horizontalSquares +1) + 1);
			plane->insertTrianglesIndex(i * (horizontalSquares + 1) + j + 1);
			plane->insertTrianglesIndex(0xFFFF);

			plane->insertTrianglesIndex(i * (horizontalSquares + 1) + j);
			plane->insertTrianglesIndex(i * (horizontalSquares + 1) + j + (horizontalSquares + 1));
			plane->insertTrianglesIndex(i * (horizontalSquares + 1) + j + (horizontalSquares + 1) + 1);
			plane->insertTrianglesIndex(0xFFFF);
		}
	}
	//se rellena el VAO
	plane->fillGeometry();
}

/**
  * @brief Destructor de PagPlane
 */
PagPlane::~PagPlane()
{
	delete plane;
}

/**
  * @brief Dibuja en modo puntos
 */
void PagPlane::drawAsPoints(PagShaderProgram *shader, glm::mat4 viewProject)
{
	plane->drawAsPoints();
}

/**
  * @brief Dibuja en modo mallas de tri�ngulos
 */
void PagPlane::drawAsTriangles(PagShaderProgram *shader, glm::mat4 viewProject, glm::mat4 view)
{
	plane->drawAsTriangles(PAG_BODY);
}

/**
  * @brief Dibuja en modo alambres/l�neas
 */
void PagPlane::drawAsLines(PagShaderProgram *shader, glm::mat4 viewProject)
{
	plane->drawAsLines();
}
