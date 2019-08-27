/*
 * File:   PagStructures.h
 * Author: Javier López Quesada
 */
#pragma once
#include <glm.hpp>
/**
 * @brief Para poder especificar un array con las posiciones y normales entrelazadas debemos definir esta estructura
 */
struct PagPosNorm {
	glm::vec3 position;
	glm::vec3 normal;
};