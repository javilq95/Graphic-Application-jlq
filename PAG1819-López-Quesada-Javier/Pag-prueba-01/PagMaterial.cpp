/*
 * File:   PagMaterial.cpp
 * Author: Javier López Quesada
 */
#include "PagMaterial.h"

/**
 * @brief Constructor parametrizado de PagMaterial
 * @param _kd color difuso
 * @param _ks color especular
 * @param _shininess brillo
 */
PagMaterial::PagMaterial(glm::vec3 _Kd, glm::vec3 _Ks, float _shininess)
: Kd(_Kd), Ks(_Ks), shininess(_shininess), texture(0)
{
}

/**
 * @brief Destructor de la clase PagMaterial
 */
PagMaterial::~PagMaterial()
{
	if(texture != 0)
		delete texture;
}

/**
 * @brief Función encargada de mandar los uniform que corresponden al material
 * @param shader shader aplicado
 */
void PagMaterial::shaderApplicator(PagShaderProgram *shader) {
	shader->setUniform("Kd", Kd);
	shader->setUniform("Ks", Ks);
	shader->setUniform("shininess", shininess);
}

/**
 * @brief Función encargada de aplicar la textura
 * @param shader shader aplicado
 */
void PagMaterial::shaderApplicatorTexture(PagShaderProgram *shader) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getColor());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture->getShininess());
}

/**
 * @brief Devuelve el color difuso
 * @return Kd
 */
glm::vec3 PagMaterial::getKd()
{
	return Kd;
}

/**
 * @brief Modifica el color difuso
 * @param _Kd color difuso
 */
void PagMaterial::setKd(glm::vec3 _Kd)
{
	Kd = _Kd;
}

/**
 * @brief Devuelve el color especular
 * @return Ks
 */
glm::vec3 PagMaterial::getKs()
{
	return Ks;
}

/**
 * @brief Modifica el color especular
 * @param _Ks color especular
 */
void PagMaterial::setKs(glm::vec3 _Ks)
{
	Ks = _Ks;
}

/**
 * @brief Devuelve el brillo
 * @return shininess
 */
float PagMaterial::getShininess()
{
	return shininess;
}

/**
 * @brief Modifica el brillo
 * @param _shininess brillo
 */
void PagMaterial::setShininess(float _shininess)
{
	shininess = _shininess;
}

/**
 * @brief Devuelve la textura
 * @return Puntero a PagTexture
 */
PagTexture* PagMaterial::getTexture() {
	return texture;
}

/**
 * @brief Modifica la textura
 * @param Puntero a PagTexture
 */
void PagMaterial::setTexture(PagTexture* t) {
	texture = t;
}