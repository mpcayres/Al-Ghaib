#include "MissionManager.hpp"
#include "Game.hpp"
#include "StageState.hpp"
#include "HallState.hpp"
#include "Mission1.hpp"

#include <iostream>
int cont = 0;

//Colocar nos objetos todas as condicoes deles, inclusive se estao abertos ou fechados

MissionManager::MissionManager() {
	numMission = 0;
	mission = nullptr;
	initStage = initHall = true;
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

void MissionManager::SetState(std::string dest){
	//inicial serve para indicar se e a 1a vez que o State esta sendo construido
	if(dest == "StageState"){
		std::cout << "2.1" << std::endl;
		std::cout << "SIZE3: " << objectStage.size() << std::endl;
		Game::GetInstance().Push(new StageState(std::move(objectStage), initStage));
		initStage = false;
		std::cout << "2.2" << std::endl;
		cont++;
	} else if(dest == "HallState"){
		Game::GetInstance().Push(new HallState(std::move(objectHall), initHall));
		initHall = false;
	}
}

//quando for chamar pelos estados para mudar de State, usar esse
void MissionManager::ChangeState(std::vector<std::unique_ptr<GameObject>> objNew, std::string orig, std::string dest){
	std::cout << "1" << std::endl;
	SetObject(std::move(objNew), orig);
	std::cout << "2" << std::endl;
	SetState(dest);
	std::cout << "3" << std::endl;
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

	initStage = initHall = true;
	objectStage = std::move(mission->GetObjectStage());
	objectHall = std::move(mission->GetObjectHall());
}

//em caso de vitoria, especificado em cada missao
void MissionManager::ChangeMission(int num){
	numMission = num;
	SetMission();
	SetState(mission->GetInitialState());
}
