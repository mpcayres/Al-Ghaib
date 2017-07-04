#include "Mission4.hpp"
#include "PickUpObject.hpp"
#include "StealthObject.hpp"
#include "SceneDoor.hpp"
#include "MissionManager.hpp"

 Music Mission4::music;

Mission4::Mission4() : Mission(), paradoUrso(false),paradoGato(false) {
	initialState = "StageState";
	initialX = 350; initialY = 300;
	MissionManager::missionManager->SetPos(initialX, initialY);
	MissionManager::missionManager->randomStates = true;

	meowcount = 0;
	momcount = 0;
	countBear = 0;
	countCat = 0;

	MissionManager::player->drogado = true;

	SDL_Color redwine = SDL_Color();
	redwine.r = 102;
	redwine.g = 0;
	redwine.b = 0;

	SDL_Color white = SDL_Color();
	white.r = 255;
	white.g = 255;
	white.b = 255;

	tx = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "NOITE 4", redwine, 0, 0);
	tx.SetPos(0, 0, true, true);
	creepy = Text("font/uwch.ttf", 30, Text::TextStyle::BLENDED, " ", redwine, 0, 0);
	creepy.SetPos(0, Game::GetInstance().GetHeight()-120, true, false);

	falas = Text("font/AA_typewriter.ttf", 25, Text::TextStyle::BLENDED , " ", white, 0, 0);
	falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
	showBox = false;
	//ultimoTempo = 3;
	/*intro = Music("audio/menu-intro.wav");
	music = Music("audio/menu-loop.wav");
	intro.Play(1);
	Mix_HookMusicFinished(&TitleState::LinkMusic);*/

	//Sound intro("audio/boom.wav");
	//intro.Play(1);

	SetObjectStage();
	SetObjectHall();
	SetObjectLivingRoom();

	MissionManager::cat->SetPosition(1000, 200);
}

Mission4::~Mission4() {

}

void  Mission4::Pause(){ }

void  Mission4::Resume(){ }

void Mission4::Update(float dt){

	InputManager instance = InputManager::GetInstance();
	//bool trancada = false;
	if(instance.KeyPress(ESCAPE_KEY)){
		popRequested = true;
	}
	//quitRequested = instance.QuitRequested();
	if(instance.KeyPress(SPACE_KEY)){
		std::cout << "SPACE KEY PRESSED" << std::endl;
		if(time.Get() < 3){
			time.Set(3);
		}
		bloqBlack = true;
		fadeIn = false;
		alpha = TRANSPARENT;
		if (spFade.IsOpen()) {
			spFade.ChangeAlpha(alpha);
		}
	}
	time.Update(dt);
	cooldown.Update(dt);
	/*if(endMission && time.Get() > (12*0.25 + 0.5)){
		Game::GetInstance().GetCurrentState().ChangeMission(2);
	}*/
	//URSO APARECE BATENDO NA PORTA. BOTAR SOM DE PORTA TENTANDO ABRIR ANTES DE ELE FALAR
	if(MissionManager::missionManager->GetStage("StageState") &&
			MissionManager::missionManager->countStageState <= 1){


			MessageDoor(dt);
			//TROCANDO DE COMODO. ENTRANDO NO CORREDOR PELA PRIMEIRA VEZ
	}else if(MissionManager::missionManager->GetStage("HallState") &&
							MissionManager::missionManager->countHallState <= 1){

		if(state != MissionManager::missionManager->changeState){
				state = MissionManager::missionManager->changeState;
				time.Restart();
		}

	}
	if(time.Get() >= 4 && fadeIn){
			UpdateVariable(dt, 80);
	}

	if(time.Get() >= 6){
		//PiscaPisca(dt, 6, 0.6);
	}

}

void Mission4::Render(){
	if(time.Get() < 4 && fadeIn){
		blackSquare.Render(0, 0, 0);
		tx.Render(0,0);
		creepy.Render(0,0);
	} else if((time.Get() >= 4 && fadeIn) || !bloqBlack){
		spFade.Render(0,0,0);
	}

	if(((MissionManager::missionManager->GetStage("StageState") &&
			MissionManager::missionManager->countStageState <= 1 && time.Get() > 4) ||
		((MissionManager::missionManager->GetStage("StageState") &&
			MissionManager::missionManager->countStageState > 1) ||
			MissionManager::missionManager->GetStage("HallState"))) &&
		!MissionManager::player->GetBloqHUD()){
		if(showBox){
			falasBox.Render(falasBoxRect.x /*- Camera::pos.x*/, falasBoxRect.y /*- Camera::pos.y*/, 0);
			//printf("renderizando");
		}
		falas.Render(0,0);
	}
}

void Mission4::SetObjectStage(){
	SceneDoor* Door = new SceneDoor(800, 200, "HallState", false);
	objectStage.emplace_back(Door);

	SceneObject* Bau = new SceneObject(300, 490,  "img/scene-bau-fechado.png",
			"img/scene-bau-aberto.png", 0, 1, 1, "", SceneObject::SAMEY_UP);
	objectStage.emplace_back(Bau);

	MovingObject* Box = new MovingObject(400, 500, "img/box.png");
	objectStage.emplace_back(Box);

	MovingObject* Cadeira = new MovingObject(730, 300, "img/scene-cadeira.png");
	objectStage.emplace_back(Cadeira);
}

void Mission4::SetObjectHall(){
	SceneDoor* DoorToMomRoom = new SceneDoor(970, 105, "StageState", true,
			"img/scene-door-closed.png", "img/scene-door-opened.png", 1);
	objectHall.emplace_back(DoorToMomRoom);

	SceneObject* Bau = new SceneObject(1000, 490,  "img/scene-bau-fechado.png",
			"img/scene-bau-aberto.png", 0, 1, 1, "InventoryKey", SceneObject::SAMEY_UP);
	objectHall.emplace_back(Bau);

	MovingObject* Vase = new MovingObject(1300, 450, "img/scene-vaso.png");
	objectHall.emplace_back(Vase);
}

void Mission4::SetObjectLivingRoom(){

}
