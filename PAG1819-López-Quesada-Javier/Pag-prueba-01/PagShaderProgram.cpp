/*
 * File:   PagShaderProgram.cpp
 * Author: Javier López Quesada
 */
#include "PagShaderProgram.h"
PagShaderProgram::PagShaderProgram() {
	handler = 0;
	linked = false;
	logString = "";
}
PagShaderProgram::~PagShaderProgram() {
	glDeleteProgram(handler); // - Liberamos recursos en la GPU
	linked = false;
	logString = "";
}
GLuint PagShaderProgram::createShaderProgram(const char *fileName) {
	// - Creamos el shader program y almacenamos su identificador
	if (handler <= 0) {
		handler = glCreateProgram();
		if (handler == 0) {
			fprintf(stderr, "Cannot create shader program: %s.\n", fileName);
			return 0;
		}
	}
	// - Cargamos y compilamos cada uno de los shader objects que componen este
	// shader program
	char fileNameComplete[256];
	strcpy_s(fileNameComplete, fileName);
	strcat_s(fileNameComplete, "-vert.glsl");
	GLuint vertexShaderObject = compileShader(fileNameComplete, GL_VERTEX_SHADER);
	if (vertexShaderObject == 0) {
		return 0;
	}
	strcpy_s(fileNameComplete, fileName);
	strcat_s(fileNameComplete, "-frag.glsl");
	GLuint fragmentShaderObject = compileShader(fileNameComplete, GL_FRAGMENT_SHADER);
	if (fragmentShaderObject == 0) {
		return 0;
	}
	// - Asociamos los shader objects compilados sin errores al shader program
	glAttachShader(handler, vertexShaderObject);
	glAttachShader(handler, fragmentShaderObject);
	// - Enlazamos el shader program y comprobamos si hay errores
	glLinkProgram(handler);
	GLint linkSuccess = 0;
	glGetProgramiv(handler, GL_LINK_STATUS, &linkSuccess);
	if (linkSuccess == GL_FALSE) {
		GLint logLen = 0;
		glGetProgramiv(handler, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0) {
			char * cLogString = new char[logLen];
			GLint written = 0;
			glGetProgramInfoLog(handler, logLen, &written, cLogString);
			logString.assign(cLogString);
			delete[] cLogString;
			std::cout << "Cannot link shader " << fileName << std::endl
				<< logString << std::endl;
		}
		return 0;
	}
	else {
		linked = true;
	}
	return handler;
}
bool PagShaderProgram::use() {
	// - Antes de activar un shader program para su uso, hay que comprobar
	// si se ha creado bien y se ha enlazado bien
	if ((handler > 0) && (linked)) {
		glUseProgram(handler);
		return true;
	}
	else {
		std::cout << "Cannot use shader program";
		return false;
	}
}
bool PagShaderProgram::setUniform(std::string name, GLint value) {
	// - Para asignar valor a un uniform, primero hay que buscar si en el shader
	// program existe alguna variable de tipo uniform cuyo nombre coincida con
	// el que pasamos como argumento
	GLint location = glGetUniformLocation(handler, name.c_str());
	// - Si location es un valor positivo, es que existe el uniform y podemos
	// asignarlo
	if (location >= 0) {
		// - Aquí usamos la función glUniform que recibe un argumento de tipo GLint
		glUniform1i(location, value);
		return true;
	}
	else {
		std::cout << "Cannot find localization for: " << name << std::endl;
		return false;
	}
}
bool PagShaderProgram::setUniform(std::string name, GLfloat value) {
	GLint location = glGetUniformLocation(handler, name.c_str());
	if (location >= 0) {
		// - Aquí usamos la función glUniform que recibe un argumento de tipo GLfloat
		glUniform1f(location, value);
		return true;
	}
	else {
		std::cout << "Cannot find localization for: " << name << std::endl;
		return false;
	}
}
bool PagShaderProgram::setUniform(std::string name, glm::mat4 value) {
	GLint location = glGetUniformLocation(handler, name.c_str());
	if (location >= 0) {
		// - Aquí usamos la función glUniform que recibe un argumento de tipo
		// mat4 con valores GLfloat y expresado como un array
		glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
		return true;
	}
	else {
		std::cout << "Cannot find localization for: " << name << std::endl;
		return false;
	}
}
bool PagShaderProgram::setUniform(std::string name, glm::vec3 value) {
	GLint location = glGetUniformLocation(handler, name.c_str());
	if (location >= 0) {
		// - Aquí usamos la función glUniform que recibe un argumento de tipo
		// vec3 con valores GLfloat y expresado como un array
		glUniform3fv(location, 1, &value[0]);
		return true;
	}
	else {
		std::cout << "Cannot find localization for: " << name << std::endl;
		return false;
	}
}
GLuint PagShaderProgram::compileShader(const char *filename, GLenum shaderType) {
	// - Comprobamos si en la solución existe algún archivo de recursos con el
	// nombre que se pasa como argumento
	if (!fileExists(filename)) {
		fprintf(stderr, "Shader source file %s not found.\n", filename);
		return 0;
	}
	// - Si existe se lee en una cadena de caracteres que contiene el listado
	// completo del shader source
	std::ifstream shaderSourceFile;
	shaderSourceFile.open(filename);
	if (!shaderSourceFile) {
		fprintf(stderr, "Cannot open shader source file.\n");
		return 0;
	}
	std::stringstream shaderSourceStream;
	shaderSourceStream << shaderSourceFile.rdbuf();
	std::string shaderSourceString = shaderSourceStream.str();
	shaderSourceFile.close();
	// - Creamos un shader object para ese archivo que se ha leído
	GLuint shaderHandler = glCreateShader(shaderType);
	if (shaderHandler == 0) {
		fprintf(stderr, "Cannot create shader object.\n");
		return 0;
	}
	// - Le asignamos el código fuente leído y lo compilamos
	const char * shaderSourceCString = shaderSourceString.c_str();
	glShaderSource(shaderHandler, 1, &shaderSourceCString, NULL);
	glCompileShader(shaderHandler);
	// - Se comprueba si la compilación se ha realizado con éxito
	GLint compileResult;
	glGetShaderiv(shaderHandler, GL_COMPILE_STATUS, &compileResult);
	if (compileResult == GL_FALSE) {
		GLint logLen = 0;
		logString = "";
		glGetShaderiv(shaderHandler, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0) {
			char * cLogString = new char[logLen];
			GLint written = 0;
			glGetShaderInfoLog(shaderHandler, logLen, &written, cLogString);
			logString.assign(cLogString);
			delete[] cLogString;
			std::cout << "Cannot compile shader " << shaderType << std::endl
				<< logString << std::endl;
		}
	}
	return shaderHandler;
}
bool PagShaderProgram::fileExists(const std::string & fileName)
{
	struct stat info;
	int ret = -1;
	ret = stat(fileName.c_str(), &info);
	return 0 == ret;
}