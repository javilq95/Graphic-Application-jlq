/*
 * File:   Pag3DElement.h
 * Author: Javier López Quesada
 */
#pragma once
#include <glm.hpp>
#include"PagMaterial.h"
#include "PagTexture.h"
#include <gtc/matrix_transform.hpp>

/**
 * @class Pag3DElement
 * @brief Clase padre de los objetos 3D
 */
class Pag3DElement
{
private:
	glm::mat4 modelMatrix;
	PagMaterial *material;
public:
	/**
	* @brief Constructor por defecto de Pag3DElement
	*/
	Pag3DElement() {
		modelMatrix = glm::mat4(1.0f);
		material = new PagMaterial(glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5), 1.0);
	}

	/**
	* @brief Destructor de Pag3DElement
	*/
	~Pag3DElement() {
	}

	/**
	* @brief Dibuja en modo puntos
	*/
	virtual void drawAsPoints(PagShaderProgram *shader, glm::mat4 viewProject) = 0;

	/**
	* @brief Dibuja en modo mallas de triángulos
	*/
	virtual void drawAsTriangles(PagShaderProgram *shader, glm::mat4 viewProject, glm::mat4 view) = 0;

	/**
	* @brief Dibuja en modo alambres/líneas
	*/
	virtual void drawAsLines(PagShaderProgram *shader, glm::mat4 viewProject) = 0;

	/**
	* @brief Devuelve la matriz de modelado
	* @return modelMatrix
	*/
	glm::mat4 getModelMatrix() {
		return modelMatrix;
	}

	/**
	* @brief Devuelve el material del objeto
	* @return material
	*/
	PagMaterial &getMaterial() { 
		return *material;
	};

	/**
	* @brief Modifica el material del objeto
	* @param kd coeficiente difuso
	* @param ks coeficiente especular
	* @param shininess brillo
	*/
	void setMaterial(PagMaterial* _material) {
		material = _material;
	};

	/**
	* @brief Traslada el objeto
	* @param translation vector sobre el que se realiza la traslación
	*/
	void translate(const glm::vec3& translation) {
		modelMatrix = glm::translate(modelMatrix, translation);
	}

	/**
	* @brief Rota el objeto
	* @param rotation vector sobre el que se realiza la rotación
	* @param angle ángulo que deseamos aplicar
	*/
	void rotate(const glm::vec3& rotation, float angle) {
		modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), rotation);
	}

	/**
	* @brief Escala el objeto
	* @param scale vector sobre el que se realiza el escalado
	*/
	void scale(const glm::vec3& scale) {
		modelMatrix = glm::scale(modelMatrix, scale);
	}
};
