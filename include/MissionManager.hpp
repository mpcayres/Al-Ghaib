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
	void ChangeState(std::vector<std::unique_ptr<GameObject>> objNew, std::string orig, std::string dest, int x = -1, int y = -1);
	void SetMission();
	void ChangeMission(int num, int oldInHand = -1, std::vector<std::string> oldInventory = std::vector<std::string>());
	void DeleteStates();
	void LoadMission(int num = 0);
	void SaveMission();
	Mission *GetMission();
	bool GetStage(std::string type);
	void SetPos(int x, int y, std::string local);

	static Player* player;
	static MissionManager* missionManager;

	static int CountStageState;
	static int CountHallState;

	static int changeState;

private:
	std::vector<std::unique_ptr<GameObject>> objectStage, objectHall;
	Mission *mission;
	std::string stage;
	int numMission;
	bool initStage, initHall;
	int xStage, yStage, xHall, yHall;
};

#endif /* SRC_MISSIONMANAGER_HPP_ */
