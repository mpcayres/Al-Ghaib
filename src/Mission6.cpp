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
	MissionManager::player->SetDirecao((int) Player::LESTE);
	MissionManager::missionManager->randomStates = true;

	countMom = 0;
	countTitle = 0;
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

	if(time.Get() > 0.5 && countTitle == 0){
		countTitle++;
		tx = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "FI", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get() > 0.7 && countTitle == 1){
		countTitle++;
		tx = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "  ", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get() > 0.9 && countTitle == 2){
		countTitle++;
		tx = Text("font/uwch.ttf", 100, Text::TextStyle::BLENDED, "FI", redwine, 0, 0);
		tx.SetPos(Game::GetInstance().GetWidth()-POSY_FALA/2,0, false, true);
	}
	if(time.Get() > 1.1 && countTitle == 3){
		countTitle++;
		tx = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "FIM", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get() > 1.3 && countTitle == 4){
		countTitle++;
		tx = Text("font/AlfredDrake.ttf", 50, Text::TextStyle::BLENDED, "FIM", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get() > 1.5 && countTitle == 5){
		countTitle++;
		tx = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "FIM", redwine, 0, 0);
		tx.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
	}
	if(time.Get() > 1.7 && countTitle == 6){
		countTitle++;
		tx = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "FIM D", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get() > 2 && countTitle == 7){
		countTitle++;
		tx = Text("font/AlfredDrake.ttf", 100, Text::TextStyle::BLENDED, "FIM D", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get() > 2.2 && countTitle == 8){
		countTitle++;
		tx = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "FIM DE", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get() > 2.4 && countTitle == 9){
		countTitle++;
		tx = Text("font/AlfredDrake.ttf", 50, Text::TextStyle::BLENDED, " ", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get() > 2.6 && countTitle == 10){
		countTitle++;
		tx = Text("font/AlfredDrake.ttf", 50, Text::TextStyle::BLENDED, "FIM DE J", redwine, 0, 0);
		tx.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
	}
	if(time.Get() > 2.8 && countTitle == 11){
		countTitle++;
		tx = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "FIM DE J", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get() > 3 && countTitle == 12){
		countTitle++;
		tx = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, " ", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get() > 3.2 && countTitle == 13){
		countTitle++;
		tx = Text("font/AlfredDrake.ttf", 50, Text::TextStyle::BLENDED, "#IIM DE J", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get() > 3.4 && countTitle == 14){
		countTitle++;
		tx = Text("font/AlfredDrake.ttf", 80, Text::TextStyle::BLENDED, "#IM DE J", redwine, 0, 0);
		tx.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
	}
	if(time.Get() > 3.8 && countTitle == 15){
		countTitle++;
		tx = Text("font/AlfredDrake.ttf", 80, Text::TextStyle::BLENDED, "#@M DE J", redwine, 0, 0);
		tx.SetPos(Game::GetInstance().GetHeight()-POSY_FALA, Game::GetInstance().GetHeight()-POSY_FALA, false, true);
	}
	if(time.Get() > 4 && countTitle == 16){
		countTitle++;
		tx = Text("font/AlfredDrake.ttf", 80, Text::TextStyle::BLENDED, "M@* DE J", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get() > 4.2 && countTitle == 17){
		countTitle++;
		tx = Text("font/AlfredDrake.ttf", 80, Text::TextStyle::BLENDED, " ", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get() > 4.4 && countTitle == 18){
		countTitle++;
		tx = Text("font/AlfredDrake.ttf", 80, Text::TextStyle::BLENDED, "MI*$DE J", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get() > 4.6 && countTitle == 19){
		countTitle++;
		tx = Text("font/AlfredDrake.ttf", 50, Text::TextStyle::BLENDED, "MIS$*E J", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get() > 4.8 && countTitle == 20){
		countTitle++;
		tx = Text("font/AlfredDrake.ttf", 50, Text::TextStyle::BLENDED, "MISS&% J", redwine, 0, 0);
		tx.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
	}
	if(time.Get() > 5 && countTitle == 21){
		countTitle++;
		tx = Text("font/AlfredDrake.ttf", 50, Text::TextStyle::BLENDED, "MISSA%*J", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get() > 5.2 && countTitle == 22){
		countTitle++;
		tx = Text("font/AlfredDrake.ttf", 50, Text::TextStyle::BLENDED, "MISSAO*&", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get() > 5.4 && countTitle == 23){
		countTitle++;
		tx = Text("font/AlfredDrake.ttf", 50, Text::TextStyle::BLENDED, "MISSAO &", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get() > 5.6 && countTitle == 24){
		countTitle++;
		tx = Text("font/AlfredDrake.ttf", 80, Text::TextStyle::BLENDED, "MISSAO 6", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get() > 6 && countTitle == 25){
		countTitle++;
		tx = Text("font/AlfredDrake.ttf", 80, Text::TextStyle::BLENDED, " ISSAO 6", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get() > 6.2 && countTitle == 26){
		countTitle++;
		tx = Text("font/AlfredDrake.ttf", 80, Text::TextStyle::BLENDED, "  SSAO 6", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get() > 6.4 && countTitle == 27){
		countTitle++;
		tx = Text("font/AlfredDrake.ttf", 80, Text::TextStyle::BLENDED, "   SAO 6", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get() > 6.4 && countTitle == 28){
		countTitle++;
		tx = Text("font/AlfredDrake.ttf", 80, Text::TextStyle::BLENDED, "    AO 6", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get() > 6.8 && countTitle == 29){
		countTitle++;
		tx = Text("font/AlfredDrake.ttf", 80, Text::TextStyle::BLENDED, "     O 6", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get() > 7 && countTitle == 30){
		countTitle++;
		tx = Text("font/AlfredDrake.ttf", 100, Text::TextStyle::BLENDED, "       6", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get() > 7.3 && countTitle == 31){
		countTitle++;
		tx = Text("font/AlfredDrake.ttf", 120, Text::TextStyle::BLENDED, "      66", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get() > 7.6 && countTitle == 32){
		countTitle++;
		tx = Text("font/AlfredDrake.ttf", 140, Text::TextStyle::BLENDED, "     666", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}
	if(time.Get() > 8 && countTitle == 33){
		countTitle++;
		tx = Text("font/AlfredDrake.ttf", 80, Text::TextStyle::BLENDED, "      ", redwine, 0, 0);
		tx.SetPos(0, 0, true, true);
	}

	if(MissionManager::missionManager->IsState("StageState")){
		if(state != MissionManager::missionManager->changeState){
			SetPiscaPisca(104, 0.4);
			state = MissionManager::missionManager->changeState;
			MissionManager::enemy->show = false;
			MissionManager::enemy->SetPosition(800, 210);
			MissionManager::enemy->Reset();
			time.Restart();
			MissionManager::player->SetBlocked(true);
		}

		if(time.Get() > 8 && countMom == 0){
			countMom++;
			MissionManager::enemy->show = true;
			SceneDoor::count = ABRE;
			SceneDoor::ValorPassar = 15;
			MissionManager::enemy->SetPosition(800, 210);
			MissionManager::enemy->SetDestinationPath(Vec2(750, 350));
			MissionManager::enemy->SetDestinationPath(Vec2(800, 350));
			MissionManager::enemy->SetDestinationPath(Vec2(800, 210));
		}
		/*if(MissionManager::enemy->show == true){
			MissionManager::enemy->SetDestinationPath(Vec2(780, 350));
		}*/

		if(time.Get() > 10 && countMom == 1){
			countMom++;
			showBox = true;
			ImageProfileBox (3);
			falas.SetText("ACHOU QUE PODERIA ESCAPAR ASSIM?");
			falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
		}
		if(time.Get() > 14 && countMom == 2){
			countMom++;
			showBox = true;
			ImageProfileBox (3);
			falas.SetText("NÃO ADIANTA FUGIR");
			falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
		}
		if(time.Get() > 18 && countMom == 3){
			countMom++;
			showBox = true;
			ImageProfileBox (4);
			falas.SetText("VOCÊ É PARTE DE MIM");
			falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
		}
		if(time.Get() > 22 && countMom == 4){
			countMom++;
			showBox = true;
			ImageProfileBox (3);
			falas.SetText("VOCÊ É PARTE DE NÓS");
			falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
		}
		if(time.Get() > 26 && countMom == 5){
			countMom++;
			showBox = true;
			ImageProfileBox (4);
			falas.SetText("EU SOU QUEM VOCÊ ABRAÇAVA TODAS AS NOITES");
			falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
		}
		if(time.Get() > 30 && countMom == 6){
			countMom++;
			showBox = true;
			ImageProfileBox (3);
			falas.SetText("EM CADA MOMENTO DE DESESPERO");
			falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
		}
		if(time.Get() > 34 && countMom == 7){
			countMom++;
			showBox = true;
			ImageProfileBox (4);
			falas.SetText("SOU A ORIGEM DOS SEUS PESADELOS MAIS SOMBRIOS");
			falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
		}
		if(time.Get() > 38 && countMom == 8){
			countMom++;
			showBox = true;
			ImageProfileBox (3);
			falas.SetText("SOU OS SUSSURROS QUE CONTROLAM SUA MENTE");
			falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
		}
		if(time.Get() > 42 && countMom == 9){
			countMom++;
			showBox = true;
			ImageProfileBox (4);
			falas.SetText("SOU O FOGO QUE TE CERCA");
			falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
		}

		if(time.Get() > 46 && countMom == 10){
			countMom++;
			showBox = true;
			ImageProfileBox (3);
			falas.SetText("EU SOU O DJINN");
			falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
		}
		if(time.Get() > 50 && countMom == 11){
			countMom++;
			showBox = false;
			ImageProfileBox (3);
			falas.SetText(" ");
			falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
		}
		if(time.Get() > 52 && countMom == 12){
			countMom++;
			creepy = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "TODO MUNDO NASCE COM UM DJINN", redwine, 0, 0);
			creepy.SetPos(0, 0, true, true);
		}
		if(time.Get() > 56 && countMom == 13){
			countMom++;
			creepy = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "POR MAIS QUE VOCÊ NÃO OS OUÇA", redwine, 0, 0);
			creepy.SetPos(0, 0, true, true);
		}
		if(time.Get() > 60 && countMom == 14){
			countMom++;
			creepy = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "ELES SÃO SUA CONSCI�NCIA", redwine, 0, 0);
			creepy.SetPos(0, 0, true, true);
		}
		if(time.Get() > 64 && countMom == 15){
			countMom++;
			creepy = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "VOC� TEM CERTEZA DE QUEM �?", redwine, 0, 0);
			creepy.SetPos(0, 0, true, true);
		}
		if(time.Get() > 68 && countMom == 16){
			countMom++;
			creepy = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "NEM TUDO É O QUE PARECE SER", redwine, 0, 0);
			creepy.SetPos(0, 0, true, true);

		}
		if(time.Get() > 72 && countMom == 17){
			countMom++;
			Game::GetInstance().GetCurrentState().EndState();
		}
	}

	if(time.Get() >= 8 && fadeIn){
		UpdateVariable(dt, 80);
	}

	PiscaPisca(dt);

}

void Mission6::Render(){
	if((time.Get() < 8.5 && fadeIn) || time.Get()>50){
		blackSquare.Render(0, 0, 0);
		tx.Render(0,0);
		creepy.Render(0,0);
	} else if((time.Get() >= 8.5 && fadeIn) || !bloqBlack){
		spFade.Render(0,0,0);
	}

	if(((MissionManager::missionManager->IsState("StageState") &&
			MissionManager::missionManager->countStageState <= 1 && time.Get() > 8.5) ||
		((MissionManager::missionManager->IsState("StageState") &&
			MissionManager::missionManager->countStageState > 1) ||
			MissionManager::missionManager->IsState("HallState"))) &&
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
