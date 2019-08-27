/*
 * File:   PagVAO.cpp
 * Author: Javier López Quesada
 */
#include "PagVAO.h"
#include <fstream>

/**
 * @brief Constructor por defecto de PagVAO. Inicializa vao, vbo e ibo
 */
PagVAO::PagVAO()
{
	glGenVertexArrays(1, &vao);
	// - Siempre que se quiere usar un VAO, hay que activarlo con esta orden.
	glBindVertexArray(vao);

	// - Se genera el VBO y se activa
	glGenBuffers(1, &vbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	// - Se describe cómo es la geometría que hay en ese array
	// - Aquí se indica que uno de los elementos del array entrelazado va asociado con el
	// layout (location=0) en el shader, en concreto la posición
	glEnableVertexAttribArray(0);
	// - Aquí se describen las características del puntero que permite a la GPU acceder a las
	// posiciones
	glVertexAttribPointer(0, sizeof(glm::vec3) / sizeof(GLfloat),
		GL_FLOAT, GL_FALSE, sizeof(PagPosNorm),
		((GLubyte *)NULL + (0)));
	// - Como es un array entrelazado, hay que repetir el proceso para los demás elementos,
	// en este caso para la normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, sizeof(glm::vec3) / sizeof(GLfloat),
		GL_FLOAT, GL_FALSE, sizeof(PagPosNorm),
		((GLubyte *)NULL + (sizeof(glm::vec3))));

	glGenBuffers(1, &vbo[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, sizeof(glm::vec2) / sizeof(GLfloat),
		GL_FLOAT, GL_FALSE, sizeof(glm::vec2),
		((GLubyte *)NULL + (0)));

	glGenBuffers(1, &vbo[2]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, sizeof(glm::vec3) / sizeof(GLfloat),
		GL_FLOAT, GL_FALSE, sizeof(glm::vec3),
		((GLubyte *)NULL + (0)));

	glGenBuffers(1, &ibo[0]);
	glGenBuffers(1, &ibo[1]);
	glGenBuffers(1, &ibo[2]);
}

/**
 * @brief Constructor de copia de PagVAO.
 */
PagVAO::PagVAO(const PagVAO &p) : vao(p.vao), vPosNorm(p.vPosNorm), vCoordText(p.vCoordText), vTang(p.vTang),
vPointsIndex(p.vPointsIndex), vLinesIndex(p.vLinesIndex) {
	for (int i = 0; i < 3; i++) {
		vbo[i] = p.vbo[i];
		ibo[i] = p.ibo[i];
	}
}

/**
 * @brief Destructor de PagVAO.
 */
PagVAO::~PagVAO()
{
}

/**
 * @brief Método para insertar un PagPosNorm en su vector correspondiente
 * @param p PagPosNorm
 */
void PagVAO::insertPosNorm(PagPosNorm p) {
	vPosNorm.push_back(p);
}

/**
 * @brief Método para insertar una coordenada de textura en su vector correspondiente
 * @param v vec2 (coordText)
 */
void PagVAO::insertCoordText(glm::vec2 v) {
	vCoordText.push_back(v);
}

/**
 * @brief Método para insertar una tangente en su vector correspondiente
 * @param v vec3 (tang)
 */
void PagVAO::insertTang(glm::vec3 v) {
	vTang.push_back(v);
}

/**
 * @brief Método para insertar un índice de puntos en su vector correspondiente
 * @param i índice puntos
 */
void PagVAO::insertPointsIndex(GLuint i) {
	vPointsIndex.push_back(i);
}

/**
 * @brief Método para insertar un índice de líneas en su vector correspondiente
 * @param i índice líneas
 */
void PagVAO::insertLinesIndex(GLuint i) {
	vLinesIndex.push_back(i);
}

/**
 * @brief Método para insertar un índice de triángulos en su vector correspondiente
 * @param i índice líneas
 */
void PagVAO::insertTrianglesIndex(GLuint i) {
	vTrianglesIndex.push_back(i);
}

/**
 * @brief Devuelve el tamaño
 * @return número de puntos
 */
unsigned int PagVAO::size() {
	return vPosNorm.size();
}

/**
 * @brief Método para visualizar el objeto mediante triángulos
 */
void PagVAO::drawAsTriangles(PagRevObjParts part) {
	// - Se activa el VAO
	glBindVertexArray(vao);
	// - Se activa el IBO que contiene los índices adecuados al modo de dibujo que se quiera
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo[0]);
	// - Se dibuja la malla
	if (PAG_BODY == part)
		glDrawElements(GL_TRIANGLE_STRIP, vTrianglesIndex.size(), GL_UNSIGNED_INT, NULL);
	else
		glDrawElements(GL_TRIANGLE_FAN, vTrianglesIndex.size(), GL_UNSIGNED_INT, NULL);
}

/**
 * @brief Método para visualizar el objeto mediante nube de puntos
 */
void PagVAO::drawAsPoints() {
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo[1]);
	glDrawElements(GL_POINTS, vPointsIndex.size(), GL_UNSIGNED_INT, NULL);
}

/**
 * @brief Método para visualizar el objeto mediante líneas
 */
void PagVAO::drawAsLines() {
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo[2]);
	glDrawElements(GL_LINE_STRIP, vLinesIndex.size(), GL_UNSIGNED_INT, NULL);
}

std::vector<PagPosNorm> PagVAO::getVPosNorm() {
	return vPosNorm;
}

void PagVAO::fillGeometry() {
	// - Se activa el VAO que contiene al VBO que se quiere rellenar con su array de geometría
	glBindVertexArray(vao);
	// - Se activa el VBO que se quiere rellenar
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	// - Se le pasa el array que contiene los datos
	glBufferData(GL_ARRAY_BUFFER, vPosNorm.size() * sizeof(PagPosNorm), vPosNorm.data(), GL_STATIC_DRAW);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, vCoordText.size() * sizeof(glm::vec2), vCoordText.data(), GL_STATIC_DRAW);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, vTang.size() * sizeof(glm::vec3), vTang.data(), GL_STATIC_DRAW);

	//IBO
	// - Se activa el VAO que contiene al IBO que se quiere rellenar con su array de topología
	glBindVertexArray(vao);
	// - Se activa el IBO que se quiere rellenar
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo[0]);
	// - Se le pasa el array que contiene los índices
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vTrianglesIndex.size() * sizeof(GLuint),
		vTrianglesIndex.data(), GL_STATIC_DRAW);

	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vPointsIndex.size() * sizeof(GLuint),
		vPointsIndex.data(), GL_STATIC_DRAW);

	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vLinesIndex.size() * sizeof(GLuint),
		vLinesIndex.data(), GL_STATIC_DRAW);
}