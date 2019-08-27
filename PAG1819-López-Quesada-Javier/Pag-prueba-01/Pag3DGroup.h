/*
 * File:   Pag3DGroup.h
 * Author: Javier López Quesada
 */
#pragma once
#include "Pag3DElement.h"
#include <vector>

/**
 * @class Pag3DGroup
 * @brief Clase que almacena un grupo de objetos 3D
 */
class Pag3DGroup : public Pag3DElement
{
private:
	std::vector<Pag3DElement*> elements;
public:
	Pag3DGroup();
	~Pag3DGroup();
	void insertElement(Pag3DElement* e);
	virtual void drawAsPoints(PagShaderProgram *shader, glm::mat4 viewProject);
	virtual void drawAsTriangles(PagShaderProgram *shader, glm::mat4 viewProject, glm::mat4 view);
	virtual void drawAsLines(PagShaderProgram *shader, glm::mat4 viewProject);
};

