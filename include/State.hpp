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
	void RemoveAll();
	void RemoveEnemy();
	void SetPopRequested();
	Rect GetStateLimits();
	void RandomState();
	int GetPositionArray(std::string obj);
	void AccessAnimated(int pos);
	void EndState();
	void ChangeState(std::string orig, std::string dest, int x = -1, int y = -1, int dir = -1);
	void ChangeMission(int num);
	std::vector<std::pair<int,int>> GetPosVector();

protected:
	virtual void UpdateArray(float dt);
	virtual void RenderArray();

	Rect limits;
	bool quitRequested;
	bool popRequested;
	int posInvert;

	std::vector<std::unique_ptr<GameObject>> objectArray;
};

#endif /* INCLUDE_STATE_HPP_ */
