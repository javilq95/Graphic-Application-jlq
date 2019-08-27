/*
 * File:   PagEnumerations.h
 * Author: Javier López Quesada
 */
#pragma once
/**
 * @brief Cada objeto se divide en Cuerpo (triangle strips), tapa superior y tapa inferior (triangle fan). 
 *        Para codificar eso en código de forma sencilla usaremos una enumeración llamada PagRevObjParts
 */
enum PagRevObjParts : int {
	PAG_BODY = 0,
	PAG_TOP_FAN = 1,
	PAG_BOTTOM_FAN = 2
};