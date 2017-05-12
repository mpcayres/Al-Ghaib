/*
 * TitleState.hpp
 *
 *  Created on: 10 de mai de 2017
 *      Author: renne
 *
 *
 * Aluno: Renne Ruan Alves Oliveira
 * Matricula: 14/0030930
 * Introducao ao Desenvolvimento de Jogos 1/2017
 */

#include "State.hpp"
#include "Sprite.hpp"
#include "Text.hpp"
#include "Timer.hpp"

#ifndef INCLUDE_TITLESTATE_HPP_
#define INCLUDE_TITLESTATE_HPP_

class TitleState : public State{
public:
	TitleState();
	void Update(float dt);
	void Render();

	void Pause();
	void Resume();
private:
	Sprite bg;
	Text tx;
	Timer time;
	bool flagTimer;
};




#endif /* INCLUDE_TITLESTATE_HPP_ */
