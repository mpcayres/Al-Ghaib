#include "Mission5.hpp"
#include "PickUpObject.hpp"
#include "StealthObject.hpp"
#include "SceneDoor.hpp"
#include "MissionManager.hpp"

Music Mission5::music;

Mission5::Mission5() : Mission(), paradoUrso(false), paradoGato(false) {
	initialState = "HallFinalState";
	initialX = 450; initialY = 400;
	MissionManager::missionManager->SetPos(initialX, initialY);
	MissionManager::missionManager->randomStates = false;

	time = Timer();

	endMission = false;
	momcount = 0;
	contFala = 0;

	SDL_Color redwine = SDL_Color();
	redwine.r = 102;
	redwine.g = 0;
	redwine.b = 0;

	SDL_Color white = SDL_Color();
	white.r = 255;
	white.g = 255;
	white.b = 255;

	tx = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "MISSÃO 5", redwine, 0, 0);
	tx.SetPos(0, 0, true, true);
	creepy = Text("font/uwch.ttf", 30, Text::TextStyle::BLENDED, " ", redwine, 0, 0);
	creepy.SetPos(0, Game::GetInstance().GetHeight()-120, true, false);

	falas = Text("font/AA_typewriter.ttf", 25, Text::TextStyle::BLENDED , " ", white, 0, 0);
	falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
	showBox = false;

	/*intro = Music("audio/menu-intro.wav");
	music = Music("audio/menu-loop.wav");
	intro.Play(1);
	Mix_HookMusicFinished(&TitleState::LinkMusic);*/

	//Sound intro("audio/boom.wav");
	//intro.Play(1);

	MissionManager::enemy->ChangeClothes(2);
	MissionManager::enemy->SetPosition(0,0);
}

Mission5::~Mission5() {

}

void  Mission5::Pause(){ }

void  Mission5::Resume(){ }

void Mission5::Update(float dt){

	InputManager instance = InputManager::GetInstance();

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
	if(time.Get() < 50){
		time.Update(dt);
	}

	if(gameOver && time.Get() > 4){
		Game::GetInstance().GetCurrentState().ChangeMission(5);
	} else if(endMission && time.Get() > 25){
		Game::GetInstance().GetCurrentState().ChangeMission(6);
	} else if(endMission && time.Get() > 15){
		UpdateVariable(dt, 50, true);
	}
	//URSO APARECE BATENDO NA PORTA. BOTAR SOM DE PORTA TENTANDO ABRIR ANTES DE ELE FALAR
	//std::cout << MissionManager::player->box.x << " X " << MissionManager::player->box.y << std::endl;

	if(momcount == 1 && MissionManager::missionManager->IsState("StageState") && !gameOver && !endMission) {
		MissionManager::enemy->show = false;
		MissionManager::player->drogado = false;
		endMission = true;
		time.Restart();
		alpha = alphaAux = TRANSPARENT;
	}

	if(MissionManager::missionManager->IsState("HallFinalState") && !gameOver && !endMission){

		if(time.Get() > 4 && momcount == 0 && contFala == 0){
			contFala++;
			ImageProfileBox (6);
			showBox = true;
			falas.SetText("CORRA!");
			falas.SetPos(0, Game::GetInstance().GetHeight()-65, true, false);
		}

		if(MissionManager::player->box.x > 170 && momcount == 0){
			momcount++;
			MissionManager::enemy->show = true;
			SceneDoor::count = ABRE;
			SceneDoor::ValorPassar = 15;
			MissionManager::enemy->SetPosition(30, 300);
			MissionManager::enemy->SetDestinationPath(Vec2(4750, 300));
			MissionManager::enemy->SetDestinationPath(Vec2(5800, 300));
			MissionManager::enemy->SetDestinationPath(Vec2(4750, 300));
			MissionManager::enemy->SetDestinationPath(Vec2(5800, 300));
			MissionManager::enemy->SetDestinationPath(Vec2(4750, 300));
			MissionManager::enemy->SetDestinationPath(Vec2(5800, 300));
			MissionManager::enemy->SetDestinationPath(Vec2(4750, 300));
			MissionManager::enemy->SetDestinationPath(Vec2(5800, 300));
			MissionManager::enemy->SetDestinationPath(Vec2(4750, 300));
			MissionManager::enemy->SetDestinationPath(Vec2(5800, 300));
			MissionManager::enemy->SetDestinationPath(Vec2(4750, 300));
			MissionManager::enemy->SetDestinationPath(Vec2(5800, 300));
			MissionManager::enemy->SetDestinationPath(Vec2(6000, 300));
		}

		if(MissionManager::enemy->collidingPlayer && MissionManager::enemy->show == true){
			MissionManager::player->SetBlocked(true);
			MissionManager::player->SetBloqHUD(true);
			MissionManager::player->SetBloqInv(true);
			time.Restart();
			Camera::Zoom(2, true);
			MissionManager::enemy->bloq = true;
			gameOver = true;
		}

		if(time.Get() > 15 && contFala == 1){
			contFala++;
			ImageProfileBox (6);
			showBox = false;
			falas.SetText(" ");
			falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
		}

		if(time.Get() > 10 && time.Get() < 11){
			MissionManager::player->drogado = false;
		}

		if(time.Get() > 20 && time.Get() < 21){
			SetPiscaPisca(10, 0.4);
			MissionManager::player->drogado = true;
			time.Restart();
		}
	}

	if(time.Get() >= 4 && fadeIn){
		UpdateVariable(dt, 80);
	}

	PiscaPisca(dt);

}

void Mission5::Render(){
	if(time.Get() < 4 && fadeIn){
		blackSquare.Render(0, 0, 0);
		tx.Render(0,0);
		creepy.Render(0,0);
	} else if((time.Get() >= 4 && fadeIn) || !bloqBlack){
		spFade.Render(0,0,0);
	}

	if(showBox && !MissionManager::player->GetBloqHUD()){
		falasBox.Render(falasBoxRect.x, falasBoxRect.y, 0);
		profileBox.Render(profileBoxX, profileBoxY, 0);
		falas.Render(0,0);
	}
}

void Mission5::SetObjectStage(){
	SceneDoor* Door = new SceneDoor(800, 200, "HallState");
		objectStage.emplace_back(Door);

}

void Mission5::SetObjectHall(){

}

void Mission5::SetObjectLivingRoom(){

}

void Mission5::SetObjectMomRoom(){

}

