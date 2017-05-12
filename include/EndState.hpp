/*
 * EndState.hpp
 *
 *  Created on: 11 de mai de 2017
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
#include "Music.hpp"
#include "StateData.hpp"

#ifndef INCLUDE_ENDSTATE_HPP_
#define INCLUDE_ENDSTATE_HPP_


class EndState : public State{
public:
	EndState(StateData stateData);
	void Update(float dt);
	void Render();

	void Pause();
	void Resume();
private:
	Sprite bg;
	Music music;
	Text instruction;
};



#endif /* INCLUDE_ENDSTATE_HPP_ */
