#include "Mission3.hpp"
#include "PickUpObject.hpp"
#include "StealthObject.hpp"
#include "SceneDoor.hpp"
#include "MissionManager.hpp"

 Music Mission3::music;

Mission3::Mission3() : Mission(), paradoUrso(false),paradoGato(false), endMission(false) {
	initialState = "LivingRoomState"; // trocar para comeÃ§ar da sala?
	initialX = 790; initialY = 500;
	MissionManager::missionManager->SetPos(initialX, initialY);
	MissionManager::missionManager->randomStates = true;

	MissionManager::enemy->ChangeClothes();

	meowcount = 0;
	momcount = 0;
	countBear = 0;
	countCat = 0;
	//bronca = false;

	SDL_Color redwine = SDL_Color();
	redwine.r = 102;
	redwine.g = 0;
	redwine.b = 0;

	SDL_Color white = SDL_Color();
	white.r = 255;
	white.g = 255;
	white.b = 255;

	tx = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "NOITE 3", redwine, 0, 0);
	tx.SetPos(0, 0, true, true);
	creepy = Text("font/uwch.ttf", 30, Text::TextStyle::BLENDED, "  ", redwine, 0, 0);
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

Mission3::~Mission3() {

}

void  Mission3::Pause(){ }

void  Mission3::Resume(){ }

void Mission3::Update(float dt){

	InputManager instance = InputManager::GetInstance();
	bool trancada = false;
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

	/*if(endMission){
		Game::GetInstance().GetCurrentState()..ChangeMission(4);
	}*/
	//TROCAR PARA SALA DE ESTAR COMO COMODO INICIAL ////////////////////////////////////////////////////////////////////
	if(MissionManager::missionManager->GetStage("LivingRoomState") &&
			MissionManager::missionManager->countLivingRoomState <= 1){
		MissionManager::enemy->show = true;


			momcount ++;

		if(momcount == 1 ){
			MissionManager::enemy->SetPosition(700, 190);
			std::cout << "mae?" << std::endl;

			MissionManager::enemy->SetDestinationPath(Vec2(220, 165));
			MissionManager::enemy->SetDestinationPath(Vec2(220, 190));
			MissionManager::enemy->SetDestinationPath(Vec2(620, 190));
			MissionManager::enemy->SetDestinationPath(Vec2(660, 190));
			MissionManager::enemy->SetDestinationPath(Vec2(620, 190));
			MissionManager::enemy->SetDestinationPath(Vec2(730, 190));
			MissionManager::enemy->SetDestinationPath(Vec2(620, 190));
			MissionManager::enemy->SetDestinationPath(Vec2(730, 190));
			MissionManager::enemy->SetDestinationPath(Vec2(620, 190));
			MissionManager::enemy->SetDestinationPath(Vec2(730, 190));
			MissionManager::enemy->SetDestinationPath(Vec2(620, 190));
			MissionManager::enemy->SetDestinationPath(Vec2(730, 190));
		}

		MissionManager::player->SetBlocked(true);
		if(flagTimer == true && time.Get() > 3){
			tx.SetText(" ");
			showBox = false;
			creepy.SetText(" ");
			flagTimer = false;
		}

		if(time.Get() > 5){
			Sound sussurro = Sound ("audio/ghostly-whispers.wav");
			sussurro.Play(0);
			falas.SetText("U: OLHA ESSA QUE CHAMAS DE MÃE");
			falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
			ultimoTempo = 5;
			showBox = true;
		}
		if(time.Get() > 10){
			falas.SetText("U: O QUE É ESSA ROUPA?");
			falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
			ultimoTempo = 10;
			showBox = true;
		}
		if(time.Get() > 15 && trancada == false && cooldown.Get() > 3){
			falas.SetText("U: AINDA É REALMENTE ELA POR BAIXO DESSE PANO NEGRO?");
			falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
			ultimoTempo = 15;
			showBox = true;

		}
		if(time.Get() > 20 && trancada == false && cooldown.Get() > 3){
			falas.SetText("U: TEMOS QUE INVESTIGAR ISSO");
			falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
			ultimoTempo = 20;
			showBox = true;
			MissionManager::player->SetBlocked(false);
			MissionManager::enemy->show = false;
		}
		if(time.Get() > 25 && trancada == false && cooldown.Get() > 3){
			falas.SetText(" ");
			falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
			ultimoTempo = 25;
			showBox = false;
			MissionManager::enemy->show = false;
		}
			MessageDoor(dt);
			//TROCANDO DE COMODO. ENTRANDO NO CORREDOR PELA PRIMEIRA VEZ
	}else if(MissionManager::missionManager->GetStage("HallState") &&
							MissionManager::missionManager->countHallState <= 1){
		MissionManager::player->SetBlocked(false);
		//HallState++;
		std::cout << MissionManager::missionManager->countHallState << std::endl;
		std::cout << "HallState" << std::endl;
		if(state != MissionManager::missionManager->changeState){
			state = MissionManager::missionManager->changeState;
			MissionManager::missionManager->player->box.x = 510;
			MissionManager::missionManager->player->box.y = 200;
			time.Restart();
		}
		if(time.Get() < 3 && trancada == false && cooldown.Get() > 3){
			falas.SetText(" ");
			falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
			ultimoTempo = 3;
			showBox = false;
		}


		MissionManager::cat->show = true;
		countCat++;
		//if(count == 1){
		int dist = MissionManager::cat->box.DistanceRect(MissionManager::player->box);
		std::cout << "dist" << dist << std::endl;
		/*if(dist < 250)
			MissionManager::cat->SetDestinationPath(Vec2(980, 200));
		if(dist >= 250){
			std::cout << "maior que 250" << std::endl;
			//MissionManager::cat->SetDestinationPath(Vec2(1000, 200)); //4Âº DESTINO
			MissionManager::cat->SetDestinationPath(Vec2(940, 200)); //3Âº DESTINO
			MissionManager::cat->SetDestinationPath(Vec2(1000, 200));
			MissionManager::cat->SetDestinationPath(Vec2(900, 200)); //2Âº DESTINO
		}*/
		//}
		//if(MissionManager::enemy->turn == 1)

		if(countCat == 1){
					//MOVIMENTO Ã‰ COLOCADO DE TRÃ�S PARA FRENTE
			MissionManager::cat->SetDestinationPath(Vec2(1000, 200));
			MissionManager::cat->SetDestinationPath(Vec2(900, 200));
			MissionManager::cat->SetDestinationPath(Vec2(1000, 200));
			MissionManager::cat->SetDestinationPath(Vec2(890, 200)); //4Âº DESTINO
			MissionManager::cat->SetDestinationPath(Vec2(970, 200)); //3Âº DESTINO
			MissionManager::cat->SetDestinationPath(Vec2(1000, 200)); //2Âº DESTINO
			MissionManager::cat->SetDestinationPath(Vec2(900, 200)); //1Âº DESTINO
					//paradoGato = true;
		}
		if(time.Get()>5){
			MissionManager::cat->SetDestinationPath(Vec2(890, 200));
		}
		if( dist < 250){
			MissionManager::cat->SetDestinationPath(Vec2(980, 200));
		}

		if( dist < 250){
				MissionManager::cat->SetDestinationPath(Vec2(980, 200));
		}
		if(dist < 100){
			if(meowcount%2 && ((int)time.Get())%5){
				MissionManager::player->AddRuido(6);
				Sound meow1 = Sound ("audio/cat-meow-1.wav");
				meow1.Play(0);
			}
			//Sound meow2 = Sound ("audio/cat-meow-2.wav");
			//meow2.Play(0);
			meowcount++;
		}

		// FALTA, DISTRAIR O GATO
		// CAIXINHA DE AREIA + NOVELO
		// OU
		// TV + CONTROLE DA TV
		//std::shared_ptr<InventoryObject> inHand = MissionManager::player->GetInHand();
		//if(inHand->IsObject("InventoryWool")){

		//}

		if(time.Get() > 7 && time.Get() < 7.5 && trancada == false && cooldown.Get() > 3){
			Sound portaDestrancando = Sound ("audio/meow-sample.wav");
			portaDestrancando.Play(0);
		}
		if (MissionManager::player->GetRuido()>70 ){
			MissionManager::enemy->show = true;
			SceneDoor::count = ABRE;
			//if(MissionManager::enemy->turn == 1)
			momcount ++;
			std::cout << "momcount" << momcount << std::endl;
			if(MissionManager::enemy->show){
				if(momcount == 1){

					SceneDoor::ValorPassar = 15;
					falas.SetText("M: O QUE JÃ� FALEI SOBRE SAIR DA CAMA?");
					falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
					ultimoTempo = (int)time.Get();
					showBox = true;
				}
			}
			if(MissionManager::enemy->show && time.Get() > ultimoTempo + 2){
				SceneDoor::ValorPassar = 0;
			}
			if(MissionManager::enemy->show && time.Get() > ultimoTempo + 4){

				falas.SetText(" ");
				falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
				ultimoTempo = ultimoTempo + 4;
				showBox = false;
			}
		}

		//////////////// TROCAR PARA QUARTO DA MÃƒE 1
		//else if(MissionManager::missionManager->GetStage("MomState") &&
		//						MissionManager::missionManager->countMomState > 1){
			//PEGAR PROXIMIDADE AO ALÃ‡APÃƒO
			// SE PERTO DEMAIS, MÃƒE APARECE

			//MANDA IR PARA O QUARTO DORMIR


		//}else if(MissionManager::missionManager->GetStage("StageState") &&
		//						bronca){
			//PEGAR PROXIMIDADE AO ALÃ‡APÃƒO
			// SE PERTO DEMAIS, MÃƒE APARECE

			//MANDA IR PARA O QUARTO DORMIR


		//}
	}
	if(time.Get() >= 4 && fadeIn){
		UpdateVariable(dt, 80);
	}

	if(time.Get() >= 6){
		//PiscaPisca(dt, 6, 0.6);
	}

}

void Mission3::Render(){
	if(time.Get() < 4 && fadeIn){
		blackSquare.Render(0, 0, 0);
		tx.Render(0,0);
		creepy.Render(0,0);
	} else if((time.Get() >= 4 && fadeIn) || !bloqBlack){
		spFade.Render(0,0,0);
	}

	if(((MissionManager::missionManager->GetStage("LivingRoomState") &&
			MissionManager::missionManager->countLivingRoomState <= 1 && time.Get() > 4) ||
		((MissionManager::missionManager->GetStage("LivingRoomState") &&
			MissionManager::missionManager->countLivingRoomState > 1) ||
			MissionManager::missionManager->GetStage("HallState"))) &&
		!MissionManager::player->GetBloqHUD()){
		if(showBox){
			falasBox.Render(falasBoxRect.x /*- Camera::pos.x*/, falasBoxRect.y /*- Camera::pos.y*/, 0);
			//printf("renderizando");
		}
		falas.Render(0,0);
	}
}

void Mission3::SetObjectStage(){
	SceneDoor* Door = new SceneDoor(800, 200, "HallState", false);
	objectStage.emplace_back(Door);

	StealthObject* Armario2 = new StealthObject(1400, 110, "img/scene-armario-corredor-fechado.png");
	objectStage.emplace_back(Armario2);

	SceneObject* Bau = new SceneObject(300, 490,  "img/scene-bau-fechado.png",
			"img/scene-bau-aberto.png", 0, 1, 1, "", SceneObject::SAMEY_UP);
	objectStage.emplace_back(Bau);

	MovingObject* Box = new MovingObject(400, 500, "img/box.png");
	objectStage.emplace_back(Box);

	MovingObject* Cadeira = new MovingObject(730, 300, "img/scene-cadeira.png");
	objectStage.emplace_back(Cadeira);
}

void Mission3::SetObjectHall(){
	SceneDoor* DoorToMomRoom = new SceneDoor(970, 105, "StageState", true,
			"img/scene-door-closed.png", "img/scene-door-opened.png", 0);
	objectHall.emplace_back(DoorToMomRoom);

	SceneObject* CriadoMudo = new SceneObject(100, 160, "img/scene-criado-fechado.png", "img/scene-criado-aberto.png");
	objectHall.emplace_back(CriadoMudo);

	MovingObject* Vase = new MovingObject(1000, 450, "img/scene-vaso.png");
	objectHall.emplace_back(Vase);

	SceneObject* Apple = new SceneObject(350, 330, "img/object-maca.png", "img/object-maca.png", 0, 0.3, 0.3);
	objectHall.emplace_back(Apple);

	SceneObject* CaixaDeAreia = new SceneObject(1400, 450, "img/box.png", "img/box-select.png", 0, 0.3, 0.3);
	objectHall.emplace_back(CaixaDeAreia);
}

void Mission3::SetObjectLivingRoom(){

}
