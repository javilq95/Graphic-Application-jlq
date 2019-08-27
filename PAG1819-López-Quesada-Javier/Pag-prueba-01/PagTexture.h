/*
 * File:   PagTexture.h
 * Author: Javier López Quesada
 */
#pragma once
#include "lodepng.h"
#include <glm.hpp>
#include "PagShaderProgram.h"

/**
 * @class PagTexture
 * @brief Clase encargada de la textura
 */
class PagTexture
{
private:
	GLuint color = 0;
	GLuint shininess = 0;
	//GLuint bumpMap = 0;
	void invertImage(std::vector<unsigned char>& image, unsigned width, unsigned height);
	void texParameters(GLfloat texturesMode, GLfloat wrapS, GLfloat wrapT);
public:
	PagTexture(std::string file, GLfloat texturesMode, GLfloat wrapS, GLfloat wrapT);
	~PagTexture();
	GLuint getColor();
	GLuint getShininess();
};

