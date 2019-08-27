/*
 * File:   PagMaterial.h
 * Author: Javier López Quesada
 */
#pragma once
#include"PagShaderProgram.h"
#include "PagTexture.h"
#include <vector>

/**
 * @class PagMaterial
 * @brief Clase encargada del material
 */
class PagMaterial
{
private:
	glm::vec3 Kd;
	glm::vec3 Ks;
	float shininess;
	PagTexture *texture;
public:
	PagMaterial(glm::vec3 _Kd, glm::vec3 _Ks, float _shininess);
	~PagMaterial();
	void shaderApplicator(PagShaderProgram *shader);
	void shaderApplicatorTexture(PagShaderProgram *shader);
	glm::vec3 getKd();
	void setKd(glm::vec3 _Kd);
	glm::vec3 getKs();
	void setKs(glm::vec3 _Ks);
	float getShininess();
	void setShininess(float _shininess);
	PagTexture* getTexture();
	void setTexture(PagTexture* t);
};