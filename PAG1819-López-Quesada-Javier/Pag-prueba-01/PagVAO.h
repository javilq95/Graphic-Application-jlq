/*
 * File:   PagVAO.h
 * Author: Javier López Quesada
 */
#pragma once
#include "PagStructures.h"
#include "PagSubdivisionProfile.h"
#include <GL/glew.h>

 /**
  * @class PagVAO
  * @brief Clase encargada de agrupar los vectores usando VBOs e IBOs
  */
class PagVAO
{
private:
	GLuint vao;
	GLuint vbo[3] = { 0, 0, 0 };
	GLuint ibo[3] = { 0, 0, 0 };
	std::vector<PagPosNorm> vPosNorm;
	std::vector<glm::vec2> vCoordText;
	std::vector<glm::vec3> vTang;
	std::vector<GLuint> vPointsIndex;
	std::vector<GLuint> vTrianglesIndex;
	std::vector<GLuint> vLinesIndex;
public:
	PagVAO();
	PagVAO(const PagVAO &p);
	~PagVAO();
	void insertPosNorm(PagPosNorm p);
	void insertCoordText(glm::vec2 v);
	void insertTang(glm::vec3 v);
	void insertPointsIndex(GLuint i);
	void insertTrianglesIndex(GLuint i);
	void insertLinesIndex(GLuint i);
	unsigned int size();
	void drawAsPoints();
	void drawAsTriangles(PagRevObjParts part);
	void drawAsLines();
	std::vector<PagPosNorm> getVPosNorm();
	void fillGeometry();
};
