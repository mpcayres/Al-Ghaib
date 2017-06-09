#ifndef SRC_MISSIONMANAGER_HPP_
#define SRC_MISSIONMANAGER_HPP_

#include "GameObject.hpp"
#include "Mission.hpp"
#include "Player.hpp"
#include <vector>
#include <memory>
#include <string>
#include <fstream>

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
	void ChangeMission(int num, int oldInHand = -1, std::vector<std::string> oldInventory = std::vector<std::string>());
	void DeleteStates();
	void LoadMission();
	void SaveMission();
	Mission *GetMission();
	bool GetStage(std::string type);

	static Player* player;
	static MissionManager* missionManager;

private:
	std::vector<std::unique_ptr<GameObject>> objectStage, objectHall;
	Mission *mission;
	std::string stage;
	int numMission;
	bool initStage, initHall;
	std::fstream save;
};

#endif /* SRC_MISSIONMANAGER_HPP_ */
