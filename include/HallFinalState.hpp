#ifndef SRC_HALLFINALSTATE_HPP_
#define SRC_HALLFINALSTATE_HPP_

#include "State.hpp"
#include "Sprite.hpp"
#include "Geometry.hpp"
#include "TileSet.hpp"
#include "TileMap.hpp"

class HallFinalState : public State {
public:
	HallFinalState();
	~HallFinalState();

	void Pause();
	void Resume();

	void LoadAssets();

	void Update(float dt);
	void Render();

	void SetInitialObjectArray();

private:
	Sprite background;
	Sprite bg;
	TileSet tileSet;

public:
	TileMap tileMap;
};

#endif /* SRC_HALLFINALSTATE_HPP_ */
