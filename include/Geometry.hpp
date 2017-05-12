/*
 * Geometry.hpp
 *
 *  Created on: 20 de mar de 2017
 *      Author: renne
 *
 *
 * Aluno: Renne Ruan Alves Oliveira
 * Matricula: 14/0030930
 *  Introducao ao Desenvolvimento de Jogos 1/2017
 */
#ifdef __APPLE__
	#include <SDL2.h>
	#include <SDL_imagem/SDL_image.h>
#elif __linux__
    	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
#elif _WIN32
	#include "SDL.h"
	#include "SDL_image.h"
#else

#endif

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#ifndef INCLUDE_GEOMETRY_HPP_
#define INCLUDE_GEOMETRY_HPP_

class Vec2;
class Rect;

class Vec2 {
public:
	float x, y;

	Vec2();
	Vec2(float x, float y);
	Vec2 Soma(Vec2 vector);
	Vec2 Sub(Vec2 vector);
	Vec2 Mult(int escalar);
	Vec2 Rotate(float angle);
	Vec2 Normalize();

	float Abs();
	float Distance(Vec2 vector);
	float Angle();
	float Inclination(Vec2 vector);
	Vec2 operator+(const Vec2& rhs) const;
	Vec2 operator-(const Vec2& rhs) const;
	Vec2 operator*(const float rhs) const;

};

class Rect {
public:
	float x, y, w, h;

	Rect();
	Rect(float x1, float y1, float w1, float h1);
	void SomaVec2(Vec2 vector);
	Vec2 Center();
	float CenterX();
	float CenterY();
	float DistanceRect(Rect rectangle2);
	bool Inside(float x, float y);
};


#endif /* INCLUDE_GEOMETRY_HPP_ */
