#ifndef MISSION1_HPP
#define MISSION1_HPP

#include "Mission.hpp"
#include "InputManager.hpp"
#include "Text.hpp"
#include "Timer.hpp"
#include "Sprite.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Sound.hpp"

class Mission1 : public Mission {
public:
	Mission1();
	~Mission1();

	void Pause();
	void Resume();

	void Update(float dt);
	void Render();

protected:
	void SetObjectStage();
	void SetObjectHall();
	void SetObjectRoom();

	bool played, endMission;
};


#endif /* SRC_MISSION1_HPP_ */
