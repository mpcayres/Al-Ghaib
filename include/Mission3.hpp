#ifndef SRC_MISSION3_HPP_
#define SRC_MISSION3_HPP_

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

class Mission3 : public Mission {
public:
	Mission3();
	~Mission3();

	void Pause();
	void Resume();

	void Update(float dt);
	void Render();
private:
	void SetObjectStage();
	void SetObjectHall();
	void SetObjectLivingRoom();

	static Music music;
	bool paradoUrso, paradoGato;
	bool played, endMission;
	int meowcount, momcount,countBear = 0, countCat = 0;
	bool bronca;
	int atraidoNovelo, atraidoTV;
};

#endif /* SRC_MISSION3_HPP_ */
