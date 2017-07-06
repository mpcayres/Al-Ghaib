#include "Mission6.hpp"
#include "PickUpObject.hpp"
#include "StealthObject.hpp"
#include "SceneDoor.hpp"
#include "MissionManager.hpp"
#include "Geometry.hpp"

 Music Mission6::music;

Mission6::Mission6() : Mission(), paradoUrso(false),paradoGato(false) {
	initialState = "StageState";
	initialX = 450; initialY = 400;
	MissionManager::missionManager->SetPos(initialX, initialY);
	MissionManager::missionManager->randomStates = true;

	meowcount = 0;
	momcount = 0;
	countBear = 0;
	countCat = 0;
	MissionManager::enemy->ChangeClothes(2);

	SDL_Color redwine = SDL_Color();
	redwine.r = 102;
	redwine.g = 0;
	redwine.b = 0;

	SDL_Color white = SDL_Color();
	white.r = 255;
	white.g = 255;
	white.b = 255;

	tx = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "F", redwine, 0, 0);
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

	MissionManager::enemy->SetPosition(800, 200);
	MissionManager::cat->SetPosition(1000, 200);
}

Mission6::~Mission6() {

}

void  Mission6::Pause(){ }

void  Mission6::Resume(){ }

void Mission6::Update(float dt){

	InputManager instance = InputManager::GetInstance();
	//bool trancada = false;
	if(instance.KeyPress(ESCAPE_KEY)){
		popRequested = true;
	}
	//quitRequested = instance.QuitRequested();

	SDL_Color redwine = SDL_Color();
	redwine.r = 102;
	redwine.g = 0;
	redwine.b = 0;
	time.Update(dt);
	cooldown.Update(dt);

	if(instance.KeyPress(SPACE_KEY)){
		std::cout << "SPACE KEY PRESSED" << std::endl;
		if(time.Get() < 8){
			time.Set(8);
		}
		bloqBlack = true;
		fadeIn = false;
		alpha = TRANSPARENT;
		if (spFade.IsOpen()) {
			spFade.ChangeAlpha(alpha);
		}
	}

	/*if(endMission && time.Get() > (12*0.25 + 0.5)){
		Game::GetInstance().GetCurrentState().ChangeMission(2);
	}*/
	if(time.Get()>0.5){
		tx = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "FI", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get()>0.7){
		tx = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "  ", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get()>0.9){
		tx = Text("font/uwch.ttf", 100, Text::TextStyle::BLENDED, "FI", redwine, 0, 0);
		tx.SetPos(Game::GetInstance().GetWidth()-POSY_FALA/2,0, false, true);
	}
	if(time.Get()>1.1){
		tx = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "FIM", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get()>1.3){
		tx = Text("font/AlfredDrake.ttf", 50, Text::TextStyle::BLENDED, "FIM", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get()>1.5){
		tx = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "FIM", redwine, 0, 0);
		tx.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
	}
	if(time.Get()>1.7){
		tx = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "FIM D", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get()>2){
		tx = Text("font/AlfredDrake.ttf", 100, Text::TextStyle::BLENDED, "FIM D", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get()>2.2){
		tx = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "FIM DE", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get()>2.4){
		tx = Text("font/AlfredDrake.ttf", 50, Text::TextStyle::BLENDED, " ", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get()>2.6){
		tx = Text("font/AlfredDrake.ttf", 50, Text::TextStyle::BLENDED, "FIM DE J", redwine, 0, 0);
		tx.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
	}
	if(time.Get()>2.8){
		tx = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "FIM DE J", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get()>3){
		tx = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, " ", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get()>3.2){
		tx = Text("font/AlfredDrake.ttf", 50, Text::TextStyle::BLENDED, "#IIM DE J", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get()>3.4){
		tx = Text("font/AlfredDrake.ttf", 80, Text::TextStyle::BLENDED, "#IM DE J", redwine, 0, 0);
		tx.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
	}
	if(time.Get()>3.8){
		tx = Text("font/AlfredDrake.ttf", 80, Text::TextStyle::BLENDED, "#@M DE J", redwine, 0, 0);
		tx.SetPos(Game::GetInstance().GetHeight()-POSY_FALA, Game::GetInstance().GetHeight()-POSY_FALA, false, true);
	}
	if(time.Get()>4){
		tx = Text("font/AlfredDrake.ttf", 80, Text::TextStyle::BLENDED, "M@* DE J", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get()>4.2){
		tx = Text("font/AlfredDrake.ttf", 80, Text::TextStyle::BLENDED, " ", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get()>4.4){
		tx = Text("font/AlfredDrake.ttf", 80, Text::TextStyle::BLENDED, "MI*$DE J", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get()>4.6){
		tx = Text("font/AlfredDrake.ttf", 50, Text::TextStyle::BLENDED, "MIS$*E J", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get()>4.8){
		tx = Text("font/AlfredDrake.ttf", 50, Text::TextStyle::BLENDED, "MISS&% J", redwine, 0, 0);
		tx.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
	}
	if(time.Get()>5){
		tx = Text("font/AlfredDrake.ttf", 50, Text::TextStyle::BLENDED, "MISSA%*J", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get()>5.2){
		tx = Text("font/AlfredDrake.ttf", 50, Text::TextStyle::BLENDED, "MISSAO*&", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get()>5.4){
		tx = Text("font/AlfredDrake.ttf", 50, Text::TextStyle::BLENDED, "MISSAO &", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get()>5.6){
		tx = Text("font/AlfredDrake.ttf", 80, Text::TextStyle::BLENDED, "MISSAO 6", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get()>6){
		tx = Text("font/AlfredDrake.ttf", 80, Text::TextStyle::BLENDED, " ISSAO 6", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get()>6.2){
		tx = Text("font/AlfredDrake.ttf", 80, Text::TextStyle::BLENDED, "  SSAO 6", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get()>6.4){
		tx = Text("font/AlfredDrake.ttf", 80, Text::TextStyle::BLENDED, "   SAO 6", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get()>6.4){
		tx = Text("font/AlfredDrake.ttf", 80, Text::TextStyle::BLENDED, "    AO 6", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get()>6.8){
		tx = Text("font/AlfredDrake.ttf", 80, Text::TextStyle::BLENDED, "     O 6", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get()>7){
		tx = Text("font/AlfredDrake.ttf", 100, Text::TextStyle::BLENDED, "       6", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get()>7.3){
		tx = Text("font/AlfredDrake.ttf", 120, Text::TextStyle::BLENDED, "      66", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get()>7.6){
		tx = Text("font/AlfredDrake.ttf", 140, Text::TextStyle::BLENDED, "     666", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get()>8){
		tx = Text("font/AlfredDrake.ttf", 80, Text::TextStyle::BLENDED, "      ", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}



	if(MissionManager::missionManager->GetStage("StageState")){
		SetPiscaPisca(20, 0.4);
		if(state != MissionManager::missionManager->changeState){
			state = MissionManager::missionManager->changeState;
			MissionManager::enemy->show = false;
			//MissionManager::missionManager->player->box.x = 400;
			//MissionManager::missionManager->player->box.y = 400;
			MissionManager::enemy->SetPosition(800, 210);
			MissionManager::enemy->Reset();
			time.Restart();
		}

		MissionManager::player->SetBlocked(false);
		MissionManager::enemy->show = true;
		if(time.Get() > 8){
			momcount ++;
			if(momcount == 1 ){
				MissionManager::enemy->show = true;
				SceneDoor::count = ABRE;
				SceneDoor::ValorPassar = 15;
				MissionManager::enemy->SetPosition(800, 210);
				MissionManager::enemy->SetDestinationPath(Vec2(750, 350));
				MissionManager::enemy->SetDestinationPath(Vec2(800, 350));
				MissionManager::enemy->SetDestinationPath(Vec2(800, 210));
			}
		}
		/*if(MissionManager::enemy->show == true){
			MissionManager::enemy->SetDestinationPath(Vec2(780, 350));
		}*/

		if(time.Get() > 12 && time.Get() < 14){
			showBox = true;
			//ImageProfileBox (2);
			falas.SetText("NÃO TOLERAREI ISSO!");
			falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
		}
	}
	if(time.Get() >= 8 && fadeIn){
			UpdateVariable(dt, 80);
	}

	PiscaPisca(dt);

}

void Mission6::Render(){
	if(time.Get() < 8.5 && fadeIn){
		blackSquare.Render(0, 0, 0);
		tx.Render(0,0);
		creepy.Render(0,0);
	} else if((time.Get() >= 8.5 && fadeIn) || !bloqBlack){
		spFade.Render(0,0,0);
	}

	if(((MissionManager::missionManager->GetStage("StageState") &&
			MissionManager::missionManager->countStageState <= 1 && time.Get() > 8.5) ||
		((MissionManager::missionManager->GetStage("StageState") &&
			MissionManager::missionManager->countStageState > 1) ||
			MissionManager::missionManager->GetStage("HallState"))) &&
		!MissionManager::player->GetBloqHUD()){
		if(showBox){
			falasBox.Render(falasBoxRect.x /*- Camera::pos.x*/, falasBoxRect.y /*- Camera::pos.y*/, 0);
			profileBox.Render(profileBoxX, profileBoxY, 0);
		}
		falas.Render(0,0);
	}
}

void Mission6::SetObjectStage(){
	SceneDoor* Door = new SceneDoor(800, 200, "HallState", false);
	objectStage.emplace_back(Door);

	SceneObject* Bau = new SceneObject(300, 490,  "img/cenario/geral/bau-fechado.png",
			"img/cenario/geral/bau-aberto.png", 0, 1, 1, "", SceneObject::SAMEY_UP);
	objectStage.emplace_back(Bau);

	//MovingObject* Box = new MovingObject(400, 500, "img/inventario/box.png");
	//objectStage.emplace_back(Box);

	MovingObject* Cadeira = new MovingObject(730, 300, "img/cenario/geral/cadeira.png");
	objectStage.emplace_back(Cadeira);

	SceneObject* Urso = new SceneObject(400,500, "img/inventario/bear-fixed.png", "img/inventario/bear-fixed.png", 0, 2, 2);
	objectStage.emplace_back(Urso);
}

void Mission6::SetObjectHall(){
	SceneDoor* DoorToMomRoom = new SceneDoor(970, 105, "MomRoomState", true,
			"img/cenario/geral/door-closed.png", "img/cenario/geral/door-opened.png", -1);
	objectHall.emplace_back(DoorToMomRoom);

	MovingObject* Vase = new MovingObject(1300, 450, "img/cenario/geral/vaso.png");
	objectHall.emplace_back(Vase);
}

void Mission6::SetObjectLivingRoom(){

}

void Mission6::SetObjectMomRoom(){

}
