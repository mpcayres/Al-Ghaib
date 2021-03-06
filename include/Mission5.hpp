#ifndef SRC_MISSION5_HPP_
#define SRC_MISSION5_HPP_

#include "Mission.hpp"
#include "InputManager.hpp"
#include "Text.hpp"
#include "Timer.hpp"
#include "Sprite.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Bear.hpp"
#include "Music.hpp"
#include "Sound.hpp"
#include "Cat.hpp"

class Mission5 : public Mission {
public:
	Mission5();
	~Mission5();

	void Pause();
	void Resume();

	void Update(float dt);
	void Render();
private:
	void SetObjectStage();
	void SetObjectHall();
	void SetObjectLivingRoom();
	void SetObjectMomRoom();

	static Music music;
	bool paradoUrso, paradoGato;
	bool endMission;
	int momcount, contFala;
};

#endif /* SRC_MISSION5_HPP_ */
