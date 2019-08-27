/*
 * File:   PagShaderProgram.h
 * Author: Javier López Quesada
 */
#pragma once
#include <iostream>
#include <GL\glew.h>
#include <fstream>
#include <sstream>
#include "glm.hpp"

 /**
  * @class PagShaderProgram
  * @brief Clase encargada de encapsular la carga, compilación, enlazado y uso de un shader program.
		   Los shader programs son piezas de código que se cargan y ejecutan directamente en la GPU 
		   y permiten variar el pipeline de rendering 3D según las necesidades del programador.
  */
class PagShaderProgram
{
public:
	PagShaderProgram();
	~PagShaderProgram();
	// - Crea un shader program a partir del código fuente que se pasa en
	// los archivos cuyo nombre genérico se pasa en el argumento filename.
	// Este método, busca entre los recursos de la aplicación un archivo
	// cuyo nombre sea [filename]-vert.glsl y otro cuyo nombre sea [filename]-frag.glsl
	// y con ellos crea el shader program.
	GLuint createShaderProgram(const char *filename);
	// - Activa el shader program. A partir de ese momento y hasta que no se
	// active un shader program distinto, las órdenes de dibujo se
	// procesarán siguiendo las instrucciones de este programa.
	bool use();
	// - Los siguientes métodos están sobrecargados. Permiten asignar
	// parámetros de tipo uniform al shader.
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
	// ultima operación sobre el shader.
	std::string logString;
	// - Método privado que compila cada una de las partes del shader
	// program (vert y frag). Es llamado por createShaderProgram dos veces.
	GLuint compileShader(const char *filename, GLenum shaderType);
	// - Método auxiliar para comprobar si un archivo de recursos está
	// presente.
	bool fileExists(const std::string & fileName);
};
