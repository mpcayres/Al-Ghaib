#ifndef SRC_MISSION4_HPP_
#define SRC_MISSION4_HPP_

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

class Mission4 : public Mission {
public:
	Mission4();
	~Mission4();

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
	Timer creepyEffect;
	bool paradoUrso, paradoGato;
	bool played, endMission;
	int meowcount, momcount, countBear, countCat, contCreepy;

};

#endif /* SRC_MISSION4_HPP_ */
