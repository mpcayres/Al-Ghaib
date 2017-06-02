#ifndef SRC_HALLSTATE_HPP_
#define SRC_HALLSTATE_HPP_

#include "State.hpp"
#include "Sprite.hpp"
#include "Player.hpp"
#include "SceneDoor.hpp"

class HallState : public State {
public:
	HallState(std::vector<std::unique_ptr<GameObject>> obj, bool inicial);
	~HallState();

	void Pause();
	void Resume();

	void LoadAssets();

	void Update(float dt);
	void Render();

	void SetInitialObjectArray();

private:
	Sprite background;
	Sprite bg;

	Player* P;
	SceneDoor* Door;
};

#endif /* SRC_HALLSTATE_HPP_ */
