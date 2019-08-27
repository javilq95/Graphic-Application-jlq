/*
 * File:   PagRevolutionObject.h
 * Author: Javier López Quesada
 */
#pragma once
#include "PagEnumerations.h"
#include "PagStructures.h"
#include "PagSubdivisionProfile.h"
#include <GL/glew.h>
#include "PagVAO.h"
#include "Pag3DElement.h"

 /**
  * @class PagRevolutionObject
  * @brief Clase encargada de obtener un objeto de revolución
  */
class PagRevolutionObject : public Pag3DElement
{
private:
	PagSubdivisionProfile profile;

	//se crea un VAO por parte
	PagVAO* body;
	PagVAO* topFan;
	PagVAO* bottomFan;

public:
	PagRevolutionObject();
	PagRevolutionObject(const PagRevolutionObject &p);
	PagRevolutionObject(std::vector<glm::vec2> points, unsigned int subdivisions, unsigned int slices);
	~PagRevolutionObject();

	bool isValid();
	bool has(PagRevObjParts part);
	unsigned int getNPoints(PagRevObjParts part);
	virtual void drawAsPoints(PagShaderProgram *shader, glm::mat4 viewProject);
	virtual void drawAsTriangles(PagShaderProgram *shader, glm::mat4 viewProject, glm::mat4 view);
	virtual void drawAsLines(PagShaderProgram *shader, glm::mat4 viewProject);
};

