#ifndef INCLUDE_STATE_HPP_
#define INCLUDE_STATE_HPP_

#include "GameObject.hpp"
#include <vector>
#include <memory>
#include <string>
#include <algorithm>

class State{
public:
	State();
	virtual ~State();

	virtual void AddObject(GameObject *object);

	bool PopRequested();
	bool QuitRequested();

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	void SetPlayer(int x, int y, int type, Rect limits);
	void RemovePlayer();
	void SetPopRequested();

protected:
	virtual void UpdateArray(float dt);
	virtual void RenderArray();

	bool quitRequested;
	bool popRequested;
	int posInvert;

	std::vector<std::unique_ptr<GameObject>> objectArray;
};

#endif /* INCLUDE_STATE_HPP_ */
