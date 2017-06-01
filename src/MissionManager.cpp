#include "MissionManager.hpp"
#include "Game.hpp"
#include "StageState.hpp"
#include "HallState.hpp"
#include "Mission1.hpp"

//Colocar nos objetos todas as condicoes deles, inclusive se estao abertos ou fechados

MissionManager::MissionManager() {
	numMission = 0;
	mission = nullptr;
}

MissionManager::~MissionManager() {
	if(mission != nullptr) delete mission;
}

void MissionManager::SetObject(std::vector<std::unique_ptr<GameObject>> objNew, std::string orig){
	if(orig == "StageState"){
		objectStage = std::move(objNew);
	} else if(orig == "HallState"){
		objectHall = std::move(objNew);
	}
}

void MissionManager::SetState(std::string dest, bool inicial){
	//inicial serve para indicar se e a 1a vez que o State esta sendo construido
	if(dest == "StageState"){
		//popRequested = true;
		Game::GetInstance().Push(new StageState(std::move(objectStage), inicial));
	} else if(dest == "HallState"){
		//popRequested = true;
		Game::GetInstance().Push(new HallState(std::move(objectHall), inicial));
	}
}

//quando for chamar pelos estados para mudar de State, usar esse
void MissionManager::ChangeState(std::vector<std::unique_ptr<GameObject>> objNew, std::string orig, std::string dest){
	SetObject(std::move(objNew), orig);
	SetState(dest);
}

void MissionManager::SetMission(){
	//Mission é um abstract para as Mission1,2,3...
	if(mission != nullptr) delete mission;
	switch(numMission){
		case 1:
			mission = new Mission1();
			break;
		default:
			break;
	}

	objectStage = std::move(mission->GetObjectStage());
	objectHall = std::move(mission->GetObjectHall());
}

//em caso de vitoria, especificado em cada missao
void MissionManager::ChangeMission(int num){
	numMission = num;
	SetMission();
	SetState(mission->GetInitialState(), true);
}
