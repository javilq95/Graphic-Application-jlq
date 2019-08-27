/*
 * File:   PagLibraryTexture.cpp
 * Author: Javier López Quesada
 */
#include "PagLibraryTexture.h"

 //Inicialización singleton
PagLibraryTexture * PagLibraryTexture::instance = nullptr;

/**
 * @brief Constructor por defecto privado de PagLibraryTexture
 */
PagLibraryTexture::PagLibraryTexture() {
}

/**
 * @brief Destructor de la clase PagLibraryTexture
 */
PagLibraryTexture::~PagLibraryTexture() {
	for (std::map<std::string, PagTexture*>::iterator it = textures.begin(); it != textures.end(); it++)
		delete it->second;
}

/**
 * @brief Devuelve la instancia del singleton
 * @return instance
 */
PagLibraryTexture * PagLibraryTexture::getInstance() {
	if (!instance) {
		instance = new PagLibraryTexture();
	}
	return instance;
}

/**
 * @brief Inserta la textura en el mapa de texturas
 * @param s clave del mapa
 * @param texture textura insertada
 */
void PagLibraryTexture::insertTexture(std::string s, PagTexture* texture) {
	textures[s] = texture;
}

/**
 * @brief Devuelve la textura que corresponde a la clave
 * @param s clave del mapa
 * @return PagTexture
 */
PagTexture* PagLibraryTexture::getTexture(std::string s) {
	return textures[s];
}