#ifndef SRC_MISSION_HPP_
#define SRC_MISSION_HPP_

#include "GameObject.hpp"
#include <vector>
#include <memory>
#include <string>

class Mission {
public:
	Mission();
	Mission(Mission&&) = default;
	Mission& operator=(Mission&&) = default;
	virtual ~Mission();

	std::string GetInitialState();
	std::vector<std::unique_ptr<GameObject>> GetObjectStage();
	std::vector<std::unique_ptr<GameObject>> GetObjectHall();

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

	bool PopRequested();
	bool QuitRequested();

protected:
	bool popRequested, quitRequested;

	virtual void SetObjectStage() = 0;
	virtual void SetObjectHall() = 0;

	std::vector<std::unique_ptr<GameObject>> objectStage, objectHall;
	std::string initialState;
};

#endif /* SRC_MISSION_HPP_ */
