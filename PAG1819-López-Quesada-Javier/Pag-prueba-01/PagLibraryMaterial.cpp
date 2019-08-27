/*
 * File:   PagLibraryMaterial.cpp
 * Author: Javier López Quesada
 */
#include "PagLibraryMaterial.h"

//Inicialización singleton
PagLibraryMaterial * PagLibraryMaterial::instance = nullptr;

/**
 * @brief Constructor por defecto privado de la clase PagLibraryMaterial
 */
PagLibraryMaterial::PagLibraryMaterial() {
}

/**
 * @brief Destructor de la clase PagLibraryMaterial
 */
PagLibraryMaterial::~PagLibraryMaterial() {
	for (std::map<std::string, PagMaterial*>::iterator it = materials.begin(); it != materials.end(); it++)
		delete it->second;
}

/**
 * @brief Devuelve la instancia del singleton
 * @return instance
 */
PagLibraryMaterial * PagLibraryMaterial::getInstance() {
	if (!instance) {
		instance = new PagLibraryMaterial();
	}
	return instance;
}

/**
 * @brief Inserta el material en el mapa de materiales
 * @param s clave del mapa
 * @param material material insertado
 */
void PagLibraryMaterial::insertMaterial(std::string s, PagMaterial *material) {
	materials[s] = material;
}

/**
 * @brief Devuelve la textura que corresponde a la clave
 * @param s clave del mapa
 * @return PagMaterial
 */
PagMaterial* PagLibraryMaterial::getMaterial(std::string s) {
	return materials[s];
}