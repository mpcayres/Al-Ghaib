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
	MissionManager::missionManager->randomStates = true;

	meowcount = 0;
	momcount = 0;
	countBear = 0;
	countCat = 0;

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
	//ultimoTempo = 3;
	/*intro = Music("audio/menu-intro.wav");
	music = Music("audio/menu-loop.wav");
	intro.Play(1);
	Mix_HookMusicFinished(&TitleState::LinkMusic);*/

	//Sound intro("audio/boom.wav");
	//intro.Play(1);

	MissionManager::enemy->ChangeClothes(2);


	MissionManager::enemy->SetPosition(30, 300);


}

Mission5::~Mission5() {

}

void  Mission5::Pause(){ }

void  Mission5::Resume(){ }

void Mission5::Update(float dt){

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
	if(time.Get()<100)
		time.Update(dt);
	cooldown.Update(dt);

	if(gameOver){
			Game::GetInstance().GetCurrentState().ChangeMission(5);
	}
	else if(endMission && time.Get() > 4){
			Game::GetInstance().GetCurrentState().ChangeMission(6);
	}
	//URSO APARECE BATENDO NA PORTA. BOTAR SOM DE PORTA TENTANDO ABRIR ANTES DE ELE FALAR
	std::cout << MissionManager::player->box.x << "e" << MissionManager::player->box.y << std::endl;

	if(time.Get()>0 && time.Get()<1)
		MissionManager::player->drogado = true;
	if(time.Get() > 8 && momcount == 0){
		momcount++;
		MissionManager::enemy->show = true;
		SceneDoor::count = ABRE;
		SceneDoor::ValorPassar = 15;
		MissionManager::enemy->SetPosition(30, 300);
		MissionManager::enemy->SetDestinationPath(Vec2(4550, 300));
		MissionManager::enemy->SetDestinationPath(Vec2(4500, 300));
		MissionManager::enemy->SetDestinationPath(Vec2(5800, 300));
	}
	if(MissionManager::missionManager->IsState("StageState")) {
		endMission = true;
	}

	if(MissionManager::enemy->collidingPlayer && MissionManager::enemy->show == true ){
		gameOver = true;
	}
	if(time.Get()>4 && momcount == 0){
			ImageProfileBox (6);
			showBox = true;
			falas.SetText("CORRA!");
			falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
	}

	if(time.Get()>15 ){
		ImageProfileBox (6);

		showBox = false;
		falas.SetText(" ");
		falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
	}

	if(time.Get()>10 && time.Get()<11)
		MissionManager::player->drogado =false;
	if(time.Get()>20 && time.Get()<21)
			MissionManager::player->drogado=true;

	if(time.Get()>25 && time.Get()<26)
		MissionManager::player->drogado =false;
	if(time.Get()>64 && time.Get()<65)
		MissionManager::player->drogado=true;
	if(time.Get()>70 && time.Get()<71)
			MissionManager::player->drogado=false;
	SetPiscaPisca(10, 0.4);


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

	if(showBox){
			falasBox.Render(falasBoxRect.x /*- Camera::pos.x*/, falasBoxRect.y /*- Camera::pos.y*/, 0);
			profileBox.Render(profileBoxX, profileBoxY, 0);
		}
		falas.Render(0,0);
}

void Mission5::SetObjectStage(){

}

void Mission5::SetObjectHall(){

}

void Mission5::SetObjectLivingRoom(){

}

void Mission5::SetObjectMomRoom(){

}

