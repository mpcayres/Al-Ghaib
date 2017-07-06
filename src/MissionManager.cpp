#include "MissionManager.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "InventoryObject.hpp"
#include "StageState.hpp"
#include "HallState.hpp"
#include "LivingRoomState.hpp"
#include "MomRoomState.hpp"
#include "HallFinalState.hpp"
#include "Mission1.hpp"
#include "Mission2.hpp"
#include "Mission3.hpp"
#include "Mission4.hpp"
#include "Mission5.hpp"
#include "Mission6.hpp"

#include <iostream>

Player* MissionManager::player = nullptr;
Enemy* MissionManager::enemy = nullptr;
Cat* MissionManager::cat = nullptr;
MissionManager* MissionManager::missionManager = nullptr;

MissionManager::MissionManager() {
	numMission = 0;
	mission = nullptr;
	initStage = initHall = initLivingRoom = initMomRoom = true;
	missionManager = this;
	countStageState = 0;
	countHallState = 0;
	countLivingRoomState = 0;
	countMomRoomState = 0;
	changeState = 0;
	xDest = yDest = -1;
	dirDest = -1;
	movingBox = false;
	randomStates = false;
	setObjectTile = false;
	factorZoom = 1.0;
}

MissionManager::~MissionManager() {
	objectStage.clear();
	objectHall.clear();
	objectLivingRoom.clear();
	objectMomRoom.clear();
	if(mission != nullptr) delete mission;
	delete player;
	delete enemy;
	delete cat;
	delete missionManager;
}

void MissionManager::SetObject(std::vector<std::unique_ptr<GameObject>> objNew, std::string orig){
	if(orig == "StageState"){
		std::vector<std::unique_ptr<GameObject>>().swap(objectStage);
		objectStage = std::move(objNew);
	} else if(orig == "HallState"){
		std::vector<std::unique_ptr<GameObject>>().swap(objectHall);
		objectHall = std::move(objNew);
	} else if(orig == "LivingRoomState"){
		std::vector<std::unique_ptr<GameObject>>().swap(objectLivingRoom);
		objectLivingRoom = std::move(objNew);
	} else if(orig == "MomRoomState"){
		std::vector<std::unique_ptr<GameObject>>().swap(objectMomRoom);
		objectMomRoom = std::move(objNew);
	}
}

void MissionManager::SetState(std::string dest){
	//inicial serve para indicar se e a 1a vez que o State esta sendo construido
	player->ResetWallLimits();
	factorZoom = 1;
	Camera::UpdateZoom();
	setObjectTile = true;
	previousState = state;
	if(dirDest != -1) player->SetDirecao(dirDest);
	if(dest == "StageState"){
		std::cout << "SS.1" << std::endl;
		//std::cout << "SIZE: " << objectStage.size() << std::endl;
		Game::GetInstance().Push(new StageState(std::move(objectStage), initStage, xDest, yDest));
		initStage = false;
		state = "StageState";
		countStageState++;
		//std::cout << countStageState << std::endl;
		changeState++;
		std::cout << "SS.2" << std::endl;
	} else if(dest == "HallState"){
		//std::cout << "HS.1" << std::endl;
		//std::cout << "SIZE: " << objectHall.size() << std::endl;
		Game::GetInstance().Push(new HallState(std::move(objectHall), initHall, xDest, yDest));
		initHall = false;
		state = "HallState";
		//std::cout << "HS.2" << std::endl;
		countHallState++;
		std::cout << countHallState << std::endl;
		changeState++;
	} else if(dest == "LivingRoomState"){
		//std::cout << "LRS.1" << std::endl;
		//std::cout << "SIZE: " << objectLivingRoom.size() << std::endl;
		Game::GetInstance().Push(new LivingRoomState(std::move(objectLivingRoom), initLivingRoom, xDest, yDest));
		initLivingRoom = false;
		state = "LivingRoomState";
		//std::cout << "LRS.2" << std::endl;
		countLivingRoomState++;
		changeState++;
	} else if(dest == "MomRoomState"){
		//std::cout << "MRS.1" << std::endl;
		//std::cout << "SIZE: " << objectMomRoom.size() << std::endl;
		Game::GetInstance().Push(new MomRoomState(std::move(objectMomRoom), initMomRoom, xDest, yDest));
		initMomRoom = false;
		state = "MomRoomState";
		//std::cout << "LRS.2" << std::endl;
		countMomRoomState++;
		changeState++;
	} else if(dest == "HallFinalState"){
		//std::cout << "HFS.1" << std::endl;
		Game::GetInstance().Push(new HallFinalState());
		state = "HallFinalState";
		//std::cout << "HFS.2" << std::endl;
		changeState++;
	}
}

//quando for chamar pelos estados para mudar de State, usar esse
void MissionManager::ChangeState(std::vector<std::unique_ptr<GameObject>> objNew, std::string orig, std::string dest, int x, int y, int dir){
	xDest = x; yDest = y; //setar o local do destino nas chamadas
	dirDest = dir;
	//std::cout << "1" << std::endl;
	SetObject(std::move(objNew), orig);
	//std::cout << "2" << std::endl;
	SetState(dest);
	//std::cout << "3" << std::endl;
}

void MissionManager::SetMission(){
	//Mission e um abstract para as Mission1,2,3...
	if(mission != nullptr) free(mission);
	switch(numMission){
		case 1:
			mission = new Mission1();
			break;
		case 2:
			mission = new Mission2();
			break;
		case 3:
			mission = new Mission3();
			break;
		case 4:
			mission = new Mission4();
			break;
		case 5:
			mission = new Mission5();
			break;
		case 6:
			mission = new Mission6();
			break;
		default:
			break;
	}

	Game::GetInstance().storedMission = mission;

	//SWAP efetivamente libera a memoria ao inves de clear, pq nao necessariamente estarao vazios
	//objectStage.clear(); objectHall.clear();
	std::vector<std::unique_ptr<GameObject>>().swap(objectStage);
	std::vector<std::unique_ptr<GameObject>>().swap(objectHall);
	std::vector<std::unique_ptr<GameObject>>().swap(objectLivingRoom);
	std::vector<std::unique_ptr<GameObject>>().swap(objectMomRoom);
	//std::cout << "INI_MIS1: " << objectStage.size() << " " << objectHall.size() << std::endl;
	initStage = initHall = initLivingRoom = initMomRoom = true;
	objectStage = std::move(mission->GetObjectStage());
	objectHall = std::move(mission->GetObjectHall());
	objectLivingRoom = std::move(mission->GetObjectLivingRoom());
	objectMomRoom = std::move(mission->GetObjectMomRoom());
	//std::cout << "INI_MIS2: " << objectStage.size() << " " << objectHall.size() << std::endl;
}

Mission *MissionManager::GetMission(){
	return mission;
}

//em caso de vitoria, especificado em cada missao
void MissionManager::ChangeMission(int num, int oldInHand, std::vector<std::string> oldInventory){
	bool firstPlay = true;
	numMission = num;
	xDest = yDest = -1;
	dirDest = -1;
	if(player != nullptr){
		firstPlay = false;
		SaveMission();
	}
	player = new Player(0, 0, oldInHand, oldInventory);
	enemy = new Enemy(0, 0); //se for outra imagem, ver a missao e colocar aqui
	cat = new Cat(0, 0);
	oldInventory.clear();
	SetMission();
	SetState(mission->GetInitialState());
	if(firstPlay){
		SaveMission();
	}
}

//Ver para liberar memoria dos dados e do player quando vai para o Menu
void MissionManager::DeleteStates(){
	std::cout << "Player NULL 1" << std::endl;
	//free(player); -> no Ubuntu da ruim
	player = nullptr;
	enemy = nullptr;
	cat = nullptr;
	std::vector<std::unique_ptr<GameObject>>().swap(objectStage);
	std::vector<std::unique_ptr<GameObject>>().swap(objectHall);
	std::vector<std::unique_ptr<GameObject>>().swap(objectLivingRoom);
	std::vector<std::unique_ptr<GameObject>>().swap(objectMomRoom);
	factorZoom = 1;
	Camera::UpdateZoom();
	std::cout << "Player NULL 2" << std::endl;
}

void MissionManager::LoadMission(int num){
	std::fstream load;
	std::string name = "saves/save";
	if(num != 0) name.append(std::to_string(num));
	name.append(".txt");
	load.open(name, std::fstream::in);
	if(load.is_open()){
		int numLoadMission, oldInHand;
		load >> numLoadMission;
		load >> oldInHand;
		std::vector<std::string> inventory;
		while(!load.eof()){
			std::string obj;
			load >> obj;
			if(!obj.empty()){
				inventory.emplace_back(obj);
			}
		}
		Game::GetInstance().GetMissionManager().ChangeMission(numLoadMission, oldInHand, inventory);
		inventory.clear();
		load.close();
	} else std::cout << "Nao foi possivel abrir o arquivo." << std::endl;
}

//Salva a missao ao comeca-la, guardando seu estado inicial
void MissionManager::SaveMission(){
	std::fstream save, saveMission;
	save.open("saves/save.txt", std::fstream::out);
	saveMission.open("saves/save" + std::to_string(numMission) + ".txt", std::fstream::out);
	if(save.is_open() && saveMission.is_open()){
		save << numMission << std::endl;
		saveMission << numMission << std::endl;
		save << player->GetInHandIndex() << std::endl;
		saveMission << player->GetInHandIndex() << std::endl;std::vector<std::shared_ptr<InventoryObject>> inventory = player->GetInventory();
		for(unsigned int i = 0; i < inventory.size(); i++){
			save << inventory[i]->GetObject() << std::endl;
			saveMission << inventory[i]->GetObject() << std::endl;
		}
		save.close();
		saveMission.close();
	} else std::cout << "Nao foi possivel abrir o arquivo." << std::endl;
}

int MissionManager::GetNumMission(){
	return numMission;
}

bool MissionManager::IsState(std::string type){
	return (type == state);
}

bool MissionManager::IsPreviousState(std::string type){
	return (type == previousState);
}

void MissionManager::SetPos(int x, int y){
	xDest = x; yDest = y;
}
