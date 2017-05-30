#ifndef SRC_HALLSTATE_HPP_
#define SRC_HALLSTATE_HPP_

#include "State.hpp"
#include "Sprite.hpp"

class HallState : public State {
public:
	HallState();
	~HallState();

	void Pause();
	void Resume();

	void LoadAssets();

	void Update(float dt);
	void Render();

private:
	Sprite background;
	Sprite bg;
};

#endif /* SRC_HALLSTATE_HPP_ */
