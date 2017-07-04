#ifndef SRC_MISSION2_HPP_
#define SRC_MISSION2_HPP_

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

class Mission2 : public Mission {
public:
	Mission2();
	~Mission2();

	void Pause();
	void Resume();

	void Update(float dt);
	void Render();
private:
	void SetObjectStage();
	void SetObjectHall();
	void SetObjectLivingRoom();
	void SetObjectMomRoom();

	int ultimoCat;
	static Music music;
	bool paradoUrso, paradoGato;
	bool played, endMission;
	int meowcount, momcount,countBear = 0, countCat = 0;
	int contScissors=0, contNeedle=0, contLine =0 ;

	bool destrancAudioFlag;
};

#endif /* SRC_MISSION2_HPP_ */
