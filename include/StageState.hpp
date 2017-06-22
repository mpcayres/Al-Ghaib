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
	StageState(std::vector<std::unique_ptr<GameObject>> obj, bool inicial, int x = -1, int y = -1);
	~StageState();

	void Pause();
	void Resume();

	void LoadAssets();

	void Update(float dt);
	void Render();

	void SetInitialObjectArray();

	StateData stateData;

private:
	Sprite bg;
	TileSet tileSet;
	TileMap tileMap;
	Timer time;
	Music music;
	bool flagMorte;
};

#endif /* INCLUDE_STATE_HPP_ */
