#include "MissionManager.hpp"
#include "Game.hpp"
#include "StageState.hpp"
#include "HallState.hpp"
#include "Mission1.hpp"

#include <iostream>

Player* MissionManager::player;

//Colocar nos objetos todas as condicoes deles, inclusive se estao abertos ou fechados

MissionManager::MissionManager() {
	numMission = 0;
	mission = nullptr;
	initStage = initHall = true;
}

MissionManager::~MissionManager() {
	objectStage.clear();
	objectHall.clear();
	if(mission != nullptr) delete mission;
	player = nullptr;
}

void MissionManager::SetObject(std::vector<std::unique_ptr<GameObject>> objNew, std::string orig){
	if(orig == "StageState"){
		std::vector<std::unique_ptr<GameObject>>().swap(objectStage);
		objectStage = std::move(objNew);
	} else if(orig == "HallState"){
		std::vector<std::unique_ptr<GameObject>>().swap(objectHall);
		objectHall = std::move(objNew);
	}
}

void MissionManager::SetState(std::string dest){
	//inicial serve para indicar se e a 1a vez que o State esta sendo construido
	if(dest == "StageState"){
		std::cout << "SS.1" << std::endl;
		std::cout << "SIZE: " << objectStage.size() << std::endl;
		Game::GetInstance().Push(new StageState(std::move(objectStage), initStage));
		initStage = false;
		std::cout << "SS.2" << std::endl;
	} else if(dest == "HallState"){
		std::cout << "HS.1" << std::endl;
		std::cout << "SIZE: " << objectStage.size() << std::endl;
		Game::GetInstance().Push(new HallState(std::move(objectHall), initHall));
		initHall = false;
		std::cout << "HS.2" << std::endl;
	}
}

//quando for chamar pelos estados para mudar de State, usar esse
void MissionManager::ChangeState(std::vector<std::unique_ptr<GameObject>> objNew, std::string orig, std::string dest){
	//std::cout << "1" << std::endl;
	SetObject(std::move(objNew), orig);
	//std::cout << "2" << std::endl;
	SetState(dest);
	//std::cout << "3" << std::endl;
}

void MissionManager::SetMission(){
	//Mission e um abstract para as Mission1,2,3...
	//if(mission != nullptr) delete mission;
	switch(numMission){
		case 1:
			mission = new Mission1();
			Game::GetInstance().storedMission = mission;
			break;
		default:
			break;
	}

	//SWAP efetivamente libera a memoria ao inves de clear, pq nao necessariamente estarao vazios
	//objectStage.clear(); objectHall.clear();
	std::vector<std::unique_ptr<GameObject>>().swap(objectStage);
	std::vector<std::unique_ptr<GameObject>>().swap(objectHall);
	//std::cout << "INI_MIS1: " << objectStage.size() << " " << objectHall.size() << std::endl;
	initStage = initHall = true;
	objectStage = std::move(mission->GetObjectStage());
	objectHall = std::move(mission->GetObjectHall());
	//std::cout << "INI_MIS2: " << objectStage.size() << " " << objectHall.size() << std::endl;
}
Mission *MissionManager::GetMission(){
	return mission;
}
//em caso de vitoria, especificado em cada missao
void MissionManager::ChangeMission(int num){
	player = new Player(0,0); //passar as informacoes do save
	numMission = num;
	SetMission();
	SetState(mission->GetInitialState());
}

//Ver para liberar memoria dos dados e do player quando vai para o Menu
void MissionManager::DeleteStates(){
	//delete player;
	//std::vector<std::unique_ptr<GameObject>>().swap(objectStage);
	//std::vector<std::unique_ptr<GameObject>>().swap(objectHall);
	std::cout << "Player NULL" << std::endl;
}
