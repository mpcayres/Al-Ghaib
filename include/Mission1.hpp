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
#include "Music.hpp"

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
	void SetObjectLivingRoom();
	void SetObjectMomRoom();

	bool played, endMission;
	Text creepy1, creepy2, creepy3, creepy4, creepy5, creepy6;
	int countPega, countPega2;

	Music music;
};


#endif /* SRC_MISSION1_HPP_ */
