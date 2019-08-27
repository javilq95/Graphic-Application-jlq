/*
 * File:   Pag3DGroup.cpp
 * Author: Javier López Quesada
 */
#include "Pag3DGroup.h"

/**
 * @brief Constructor por defecto de Pag3DGroup.
 */
Pag3DGroup::Pag3DGroup():elements()
{
}

/**
 * @brief Destructor de Pag3DGroup.
 */
Pag3DGroup::~Pag3DGroup()
{
	for (int i = 0; i < elements.size(); i++) {
		delete elements[i];
	}
}

/**
 * @brief Método para insertar un elemento en el vector
 * @param e elemento
 */
void Pag3DGroup::insertElement(Pag3DElement* e)
{
	elements.push_back(e);
}

/**
 * @brief Dibuja en modo puntos
 * @param shader shader aplicado
 * @param viewProject matriz visión proyección
 */
void Pag3DGroup::drawAsPoints(PagShaderProgram *shader, glm::mat4 viewProject)
{
	glm::mat4 viewProjMatrix;
	for (int i = 0; i < elements.size(); i++) {
		viewProjMatrix = viewProject * elements[i]->getModelMatrix();
		shader->setUniform("mModelViewProj", viewProjMatrix);
		elements[i]->drawAsPoints(shader, viewProjMatrix);
	}
}

/**
 * @brief Dibuja en modo mallas de triángulos
 * @param shader shader aplicado
 * @param viewProject matriz visión proyección
 * @param view matriz de visión
 */
void Pag3DGroup::drawAsTriangles(PagShaderProgram *shader, glm::mat4 viewProject, glm::mat4 view)
{
	glm::mat4 viewProjMatrix;
	glm::mat4 viewMatrix;

	for (int i = 0; i < elements.size(); i++) {
		viewProjMatrix = viewProject * elements[i]->getModelMatrix();
		viewMatrix = view * elements[i]->getModelMatrix();
		shader->setUniform("mModelViewProj", viewProjMatrix);
		shader->setUniform("mModelView", viewMatrix);
		elements[i]->getMaterial().shaderApplicator(shader);
		if(elements[i]->getMaterial().getTexture() != 0)
			elements[i]->getMaterial().shaderApplicatorTexture(shader);
		elements[i]->drawAsTriangles(shader, viewProject, view);
	}
}

/**
 * @brief Dibuja en modo alambres/líneas
 * @param shader shader aplicado
 * @param viewProject matriz visión proyección
 */
void Pag3DGroup::drawAsLines(PagShaderProgram *shader, glm::mat4 viewProject)
{
	glm::mat4 mvp;
	for (int i = 0; i < elements.size(); i++) {
		mvp = viewProject * elements[i]->getModelMatrix();
		shader->setUniform("mModelViewProj", mvp);
		elements[i]->drawAsLines(shader, mvp);
	}
}