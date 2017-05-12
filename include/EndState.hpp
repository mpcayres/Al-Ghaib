#ifndef INCLUDE_ENDSTATE_HPP_
#define INCLUDE_ENDSTATE_HPP_

#include "State.hpp"
#include "Sprite.hpp"
#include "Text.hpp"
#include "Music.hpp"
#include "StateData.hpp"

class EndState : public State {
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
