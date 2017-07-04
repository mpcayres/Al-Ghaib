#ifndef SRC_MOMROOMSTATE_HPP_
#define SRC_MOMROOMSTATE_HPP_

#include "State.hpp"
#include "Sprite.hpp"
#include "Geometry.hpp"
#include "TileSet.hpp"
#include "TileMap.hpp"

class MomRoomState : public State {
public:
	MomRoomState(std::vector<std::unique_ptr<GameObject>> obj, bool inicial, int x, int y);
	~MomRoomState();

	void Pause();
	void Resume();

	void LoadAssets();

	void Update(float dt);
	void Render();

	void SetInitialObjectArray();

private:
	Sprite background;
	Sprite bg;
	TileSet tileSetChao;
	TileSet tileSetParede;
	TileMap tileMapChao;
	TileMap tileMapParede;
};

#endif /* SRC_MOMROOMSTATE_HPP_ */
