/*
 * File:   PagLibraryMaterial.h
 * Author: Javier López Quesada
 */
#pragma once
#include "PagMaterial.h"
#include <map>

/**
 * @class PagLibraryMaterial
 * @brief Clase encargada de crear una biblioteca de materiales
 */
class PagLibraryMaterial
{
private:
	PagLibraryMaterial();
	static PagLibraryMaterial *instance;
	std::map<std::string, PagMaterial*> materials;
public:
	~PagLibraryMaterial();
	static PagLibraryMaterial *getInstance();
	void insertMaterial(std::string s, PagMaterial *material);
	PagMaterial* getMaterial(std::string s);
};

