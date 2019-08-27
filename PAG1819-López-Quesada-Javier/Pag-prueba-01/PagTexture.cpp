/*
 * File:   PagTexture.cpp
 * Author: Javier López Quesada
 */
#include "PagTexture.h"

 /**
  * @brief Invierte la imagen
  * @param image imagen a invertir
  * @param width anchura de imagen
  * @param height altura de imagen
  */
void PagTexture::invertImage(std::vector<unsigned char>& image, unsigned width, unsigned height) {
	// La textura se carga del revés, así que vamos a darle la vuelta
	unsigned char *imgPtr = &image[0];
	int numColorComponents = 4;
	int wInc = width * 4; //width in char
	unsigned char* top = nullptr;
	unsigned char* bot = nullptr;
	unsigned char temp = 0;
	for (int i = 0; i < height / 2; i++)
	{
		top = imgPtr + i * wInc;
		bot = imgPtr + (height - i - 1) * wInc;
		for (int j = 0; j < wInc; j++)
		{
			temp = *top;
			*top = *bot;
			*bot = temp;
			++top;
			++bot;
		}
	}
}

/**
 * @brief Se aplican los parámetros de textura
 */
void PagTexture::texParameters(GLfloat texturesMode, GLfloat wrapS, GLfloat wrapT) {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texturesMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texturesMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
}


PagTexture::PagTexture(std::string file, GLfloat texturesMode, GLfloat wrapS, GLfloat wrapT)
{
	//COLOR DE TEXTURA
	glGenTextures(1, &color);

	std::string fileColor = file + ".png";
	const char* filename = fileColor.c_str();

	/** Carga un png de disco https://lodev.org/lodepng/ */
	std::vector<unsigned char> image; // Los píxeles de la imagen
	unsigned width, height;
	unsigned error = lodepng::decode(image, width, height, filename);
	if (error)
	{
		std::cout << filename << " cannot be loaded" << std::endl;
		return;
	}

	invertImage(image, width, height);

	glBindTexture(GL_TEXTURE_2D, color);

	texParameters(texturesMode, wrapS, wrapT);

	// Finalmente, pasamos la textura a OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
	glGenerateMipmap(GL_TEXTURE_2D);

	// BRILLO DE TEXTURA
	glGenTextures(1, &shininess);

	std::string fileShininess = file + "_gris.png";
	filename = fileShininess.c_str();
	image.clear();

	error = lodepng::decode(image, width, height, filename);
	if (error)
	{
		std::cout << filename << " cannot be loaded" << std::endl;
		return;
	}

	invertImage(image, width, height);

	glBindTexture(GL_TEXTURE_2D, shininess);

	texParameters(texturesMode, wrapS, wrapT);

	// Finalmente, pasamos la textura a OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
	glGenerateMipmap(GL_TEXTURE_2D);
}

/**
 * @brief Destructor de PagTexture
 */
PagTexture::~PagTexture()
{
}

/**
 * @brief Devuelve el color de textura
 * @return color
 */
GLuint PagTexture::getColor() {
	return color;
}

/**
 * @brief Devuelve el brillo de textura
 * @return shininess
 */
GLuint PagTexture::getShininess() {
	return shininess;
}
