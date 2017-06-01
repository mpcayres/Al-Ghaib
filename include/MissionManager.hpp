#ifndef SRC_MISSIONMANAGER_HPP_
#define SRC_MISSIONMANAGER_HPP_

#include "GameObject.hpp"
#include "Mission.hpp"
#include <vector>
#include <memory>
#include <string>

class MissionManager {
public:
	MissionManager();
	MissionManager(MissionManager&&) = default;
	MissionManager& operator=(MissionManager&&) = default;
	~MissionManager();

	void SetObject(std::vector<std::unique_ptr<GameObject>> objNew, std::string orig);
	void SetState(std::string dest, bool inicial = false);
	void ChangeState(std::vector<std::unique_ptr<GameObject>> objNew, std::string orig, std::string dest);
	void SetMission();
	void ChangeMission(int num);

private:
	std::vector<std::unique_ptr<GameObject>> objectStage, objectHall;
	Mission *mission;
	int numMission;
};

#endif /* SRC_MISSIONMANAGER_HPP_ */
