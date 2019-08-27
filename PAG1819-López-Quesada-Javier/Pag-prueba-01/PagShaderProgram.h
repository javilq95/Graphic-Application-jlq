/*
 * File:   PagShaderProgram.h
 * Author: Javier L�pez Quesada
 */
#pragma once
#include <iostream>
#include <GL\glew.h>
#include <fstream>
#include <sstream>
#include "glm.hpp"

 /**
  * @class PagShaderProgram
  * @brief Clase encargada de encapsular la carga, compilaci�n, enlazado y uso de un shader program.
		   Los shader programs son piezas de c�digo que se cargan y ejecutan directamente en la GPU 
		   y permiten variar el pipeline de rendering 3D seg�n las necesidades del programador.
  */
class PagShaderProgram
{
public:
	PagShaderProgram();
	~PagShaderProgram();
	// - Crea un shader program a partir del c�digo fuente que se pasa en
	// los archivos cuyo nombre gen�rico se pasa en el argumento filename.
	// Este m�todo, busca entre los recursos de la aplicaci�n un archivo
	// cuyo nombre sea [filename]-vert.glsl y otro cuyo nombre sea [filename]-frag.glsl
	// y con ellos crea el shader program.
	GLuint createShaderProgram(const char *filename);
	// - Activa el shader program. A partir de ese momento y hasta que no se
	// active un shader program distinto, las �rdenes de dibujo se
	// procesar�n siguiendo las instrucciones de este programa.
	bool use();
	// - Los siguientes m�todos est�n sobrecargados. Permiten asignar
	// par�metros de tipo uniform al shader.
	bool setUniform(std::string name, GLfloat value);
	bool setUniform(std::string name, GLint value);
	bool setUniform(std::string name, glm::mat4 value);
	bool setUniform(std::string name, glm::vec3 value);
private:
	// - Identificador del shader program que permite referenciarlo
	// en la GPU.
	GLuint handler;
	// - Bandera que indica si el shader program se ha enlazado
	// correctamente.
	bool linked;
	// - Cadena de caracteres que contiene el mensaje de error de la
	// ultima operaci�n sobre el shader.
	std::string logString;
	// - M�todo privado que compila cada una de las partes del shader
	// program (vert y frag). Es llamado por createShaderProgram dos veces.
	GLuint compileShader(const char *filename, GLenum shaderType);
	// - M�todo auxiliar para comprobar si un archivo de recursos est�
	// presente.
	bool fileExists(const std::string & fileName);
};
