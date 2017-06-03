#ifndef SRC_MISSIONMANAGER_HPP_
#define SRC_MISSIONMANAGER_HPP_

#include "GameObject.hpp"
#include "Mission.hpp"
#include "Player.hpp"
#include <vector>
#include <memory>
#include <string>

class Player;

class MissionManager {
public:
	MissionManager();
	MissionManager(MissionManager&&) = default;
	MissionManager& operator=(MissionManager&&) = default;
	~MissionManager();

	void SetObject(std::vector<std::unique_ptr<GameObject>> objNew, std::string orig);
	void SetState(std::string dest);
	void ChangeState(std::vector<std::unique_ptr<GameObject>> objNew, std::string orig, std::string dest);
	void SetMission();
	void ChangeMission(int num);
	//static void DeletePlayer();

	static Player* player;

private:
	std::vector<std::unique_ptr<GameObject>> objectStage, objectHall;
	Mission *mission;
	int numMission;
	bool initStage, initHall;
};

#endif /* SRC_MISSIONMANAGER_HPP_ */
