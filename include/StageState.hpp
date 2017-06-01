#ifndef INCLUDE_STAGESTATE_HPP_
#define INCLUDE_STAGESTATE_HPP_

#include "Sprite.hpp"
#include "TileSet.hpp"
#include "TileMap.hpp"
#include "State.hpp"
#include "Music.hpp"
#include "Timer.hpp"
#include "StateData.hpp"

class StageState : public State {
public:
	StageState();
	~StageState();

	void Pause();
	void Resume();

	void LoadAssets();

	void Update(float dt);
	void Render();

	void SetInitialObjectArray();
	Rect GetStateLimits();

	StateData stateData;

private:
	Rect limits;
	Sprite bg;
	TileSet tileSet;
	TileMap tileMap;
	Timer time;
	Music music;
	bool flagMorte;
};

#endif /* INCLUDE_STATE_HPP_ */
