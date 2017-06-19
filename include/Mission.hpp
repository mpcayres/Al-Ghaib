#ifndef SRC_MISSION_HPP_
#define SRC_MISSION_HPP_

#include "GameObject.hpp"
#include <vector>
#include <memory>
#include <string>
#include "Text.hpp"
#include "Timer.hpp"
#include "Sprite.hpp"
#include "InputManager.hpp"
#include "MissionManager.hpp"

class Mission {
public:
	Mission();
	Mission(Mission&&) = default;
	Mission& operator=(Mission&&) = default;
	virtual ~Mission();

	std::string GetInitialState();
	int GetInitialX();
	int GetInitialY();
	std::vector<std::unique_ptr<GameObject>> GetObjectStage();
	std::vector<std::unique_ptr<GameObject>> GetObjectHall();

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

	bool PopRequested();
	bool QuitRequested();

	//bool GetDoor();
	//void SetDoor(bool value);

	void MessageDoor(float dt);
	bool tried;


protected:
	bool popRequested, quitRequested;
	//bool door;

	virtual void SetObjectStage() = 0;
	virtual void SetObjectHall() = 0;

	std::vector<std::unique_ptr<GameObject>> objectStage, objectHall;
	std::string initialState;
	int initialX, initialY;


	Text tx;
	Text creepy;
	Text falas;
	Timer cooldown;
	Timer time;
	Sprite blackSquare;
	float ultimoTempo;
	bool flagTimer;
	bool trancada;
	bool begin;
	int state;
	int count;
};

#endif /* SRC_MISSION_HPP_ */
