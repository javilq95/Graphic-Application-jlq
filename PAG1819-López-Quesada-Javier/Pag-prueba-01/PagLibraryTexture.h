/*
 * File:   PagLibraryTexture.h
 * Author: Javier López Quesada
 */
#pragma once

#include "PagTexture.h"
#include <map>

/**
 * @class PagLibraryTexture
 * @brief Clase encargada de crear una biblioteca de texturas
 */
class PagLibraryTexture {
private:
	PagLibraryTexture();
	static PagLibraryTexture *instance;
	std::map<std::string, PagTexture*> textures;
public:
	~PagLibraryTexture();
	static PagLibraryTexture *getInstance();
	void insertTexture(std::string s, PagTexture *texture);
	PagTexture* getTexture(std::string s);
};