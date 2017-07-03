#include "Mission2.hpp"
#include "PickUpObject.hpp"
#include "StealthObject.hpp"
#include "SceneDoor.hpp"
#include "MissionManager.hpp"

 Music Mission2::music;

Mission2::Mission2() : Mission(), paradoUrso(false),paradoGato(false), endMission(false) {
	initialState = "StageState";
	initialX = 300; initialY = 400;
	MissionManager::missionManager->SetPos(initialX, initialY);
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

	tx = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "NOITE 2", redwine, 0, 0);
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
}

Mission2::~Mission2() {

}

void  Mission2::Pause(){ }

void  Mission2::Resume(){ }

void Mission2::Update(float dt){

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
			begin = false;
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
	//std::cout << "time: " << time.Get() << std::endl;
	if(time.Get() > 6){
		begin = false;
		fadeIn = false;
	}

	if(endMission){
		Game::GetInstance().GetCurrentState().ChangeMission(3);
	}
	//URSO APARECE BATENDO NA PORTA. BOTAR SOM DE PORTA TENTANDO ABRIR ANTES DE ELE FALAR
	if(MissionManager::missionManager->GetStage("StageState") &&
			MissionManager::missionManager->countStageState <= 1){
		Sound sussurro = Sound ("audio/ghostly-whispers.wav");
			MissionManager::player->SetBlocked(true);
			if(flagTimer == true && time.Get() > 3){
				tx.SetText(" ");
				showBox = false;
				creepy.SetText(" ");
				flagTimer = false;
			}
			if(time.Get() > 7 && time.Get() < 8 && trancada == false && cooldown.Get() > 3){
				Sound portaDestrancando = Sound ("audio/weird-door.wav");
				portaDestrancando.Play(0);
			}
			if(time.Get() > 14 && trancada == false && cooldown.Get() > 2){
				Bear::show = true;
				countBear ++;
				//std::cout << "test 0 " << std::endl;
				if(countBear == 1){

					SceneDoor::count = ABRE;
					SceneDoor::ValorPassar = 24;
					paradoUrso = true;
					Bear::bear->SetDestinationPath(Vec2(810, 450)); //2º DESTINO
					Bear::bear->SetDestinationPath(Vec2(810, 220)); //1º DESTINO
					ultimoTempo = 12;
				}
				if(paradoUrso){
					Bear::bear->SetDestinationPath(Vec2(810, 450));
					Bear::bear->box.x = 810;
					Bear::bear->box.y = 450;
				}
				//std::cout << "test 1 " << std::endl;
				if(time.Get() > 18 ){

					sussurro.Play(0);
					showBox = true;
					falas.SetText("U: OLHA O QUE FIZERAM COMIGO!");
					falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
					ultimoTempo = 14;
					showBox = true;
				}
				//std::cout << "test 2 " << std::endl;
				if(time.Get() > 22 ){
					//Sound sussurro = Sound ("audio/ghostly-whispers.wav");
					//sussurro.Play(0);
					falas.SetText("U: ACHA QUE CONSEGUE ME REPARAR?");
					falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
					ultimoTempo = 18;
					showBox = true;
				}
				if(time.Get() > 24 ){
					//Sound sussurro = Sound ("audio/ghostly-whispers.wav");
					//sussurro.Play(0);
					falas.SetText("U: VOU FICAR AQUI ESPERANDO");
					falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
					ultimoTempo = 22;
					showBox = true;
					MissionManager::player->SetBlocked(false);
				}
				if(time.Get() > 29 ){
					//Sound sussurro = Sound ("audio/ghostly-whispers.wav");
					//sussurro.Play(0);
					sussurro.Stop();
					falas.SetText(" ");
					falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
					ultimoTempo = 29;
					showBox = false;
					//parado = false;
					Bear::seen = true;

				}
			}

			MessageDoor(dt);
			//TROCANDO DE COMODO. ENTRANDO NO CORREDOR PELA PRIMEIRA VEZ
	}else if(MissionManager::missionManager->GetStage("HallState") &&
							MissionManager::missionManager->countHallState <= 1){

		MissionManager::player->SetBlocked(false);
		//HallState++;

		if(state != MissionManager::missionManager->changeState){
						state = MissionManager::missionManager->changeState;
						MissionManager::missionManager->player->box.x = 400;
						MissionManager::missionManager->player->box.y = 400;
						time.Restart();
		}
		if(time.Get() < 2){
			falas.SetText(" ");
			falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
			ultimoTempo = 2;
			showBox = false;
		}

		Cat::show = true;
		countCat++;
		//if(count == 1){
		//int dist = Cat::cat->box.DistanceRect(MissionManager::player->box);
		//std::cout << "dist" << dist << std::endl;

		//std::cout << "time" << time.Get() << std::endl;
		if(countCat == 1){
			//MOVIMENTO É COLOCADO DE TRÁS PARA FRENTE
			Cat::cat->SetDestinationPath(Vec2(500, 300)); //ULTIMO DESTINO
			Cat::cat->SetDestinationPath(Vec2(500, 200));
			Cat::cat->SetDestinationPath(Vec2(900, 200));
			Cat::cat->SetDestinationPath(Vec2(900, 450));
			Cat::cat->SetDestinationPath(Vec2(900, 500));
			Cat::cat->SetDestinationPath(Vec2(900, 300));
			Cat::cat->SetDestinationPath(Vec2(800, 300));
			Cat::cat->SetDestinationPath(Vec2(700, 300));
			Cat::cat->SetDestinationPath(Vec2(800, 300));
			Cat::cat->SetDestinationPath(Vec2(500, 300));
			Cat::cat->SetDestinationPath(Vec2(500, 200));
			Cat::cat->SetDestinationPath(Vec2(900, 200));
			Cat::cat->SetDestinationPath(Vec2(900, 450));
			Cat::cat->SetDestinationPath(Vec2(900, 500));
			Cat::cat->SetDestinationPath(Vec2(900, 300)); //3º DESTINO
			Cat::cat->SetDestinationPath(Vec2(800, 300)); //2º DESTINO
			Cat::cat->SetDestinationPath(Vec2(700, 300)); //1º DESTINO
			//paradoGato = true;
		}
		if(time.Get()>5){
			Cat::cat->SetDestinationPath(Vec2(800, 300));
		}



		if(((int)time.Get())%5){
			Sound meow1 = Sound ("audio/cat-meow-1.wav");
			if(meowcount%2 && ((int)time.Get())%100){
				//MissionManager::player->AddRuido(6);

				meow1.Play(0);
			}
			//Sound meow2 = Sound ("audio/cat-meow-2.wav");
			//meow2.Play(0);
			meowcount++;
			meow1.Stop();
		}
		if(MissionManager::player->lastPicked == "InventoryNeedle"){
			contNeedle++;
		}
		if(MissionManager::player->lastPicked == "InventoryScissors"){
			contScissors++;
		}
		if(MissionManager::player->lastPicked == "InventoryWool"){
			contLine++;
		}


		if (MissionManager::player->GetRuido()>80 ){
			MissionManager::enemy->show = true;
			SceneDoor::count = ABRE;
			//if(MissionManager::enemy->turn == 1)
			momcount ++;
			//DEFINIR CAMINHO DA MÃE NA PRIMEIRA VEZ QUE CHAMA A FUNÇÃO UPDATE DE MISSION1 NO GAME LOOP
			if(momcount == 1){
			//MOVIMENTO É COLOCADO DE TRÁS PARA FRENTE
				//MissionManager::enemy->SetDestinationPath(Vec2(970, 100)); //4º DESTINO
				MissionManager::enemy->SetDestinationPath(Vec2(800, 140)); //3º DESTINO
				MissionManager::enemy->SetDestinationPath(Vec2(500, 140)); //2º DESTINO
				MissionManager::enemy->SetDestinationPath(Vec2(500, 110)); //1º DESTINO
			}
		}
		if(MissionManager::enemy->show && time.Get() > ultimoTempo + 2){
			if(momcount == 1){
				falas.SetText("M: O QUE JÁ FALEI SOBRE SAIR DA CAMA?");
				falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
				ultimoTempo = ultimoTempo + 2;
				showBox = true;
			}
		}
		if(MissionManager::enemy->show && time.Get() > ultimoTempo + 4){
			falas.SetText(" ");
			falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
			ultimoTempo = ultimoTempo + 4;
			showBox = false;
		}
	}else if(MissionManager::missionManager->GetStage("StageState") &&
			MissionManager::missionManager->countStageState > 1){
		if(state != MissionManager::missionManager->changeState){
			state = MissionManager::missionManager->changeState;
			time.Restart();
		}
		Bear::bear->box.x = 300;
		Bear::bear->box.y = 380;
		count++;
		std::cout << count << std::endl;
		if(count == 1){
			MissionManager::missionManager->player->box.x = 800;
			MissionManager::missionManager->player->box.y = 300;
		}

		//para cheat
		//contNeedle = 5;
		//contScissors = 5;
		//contLine = 5;
		if(contNeedle > 0 && contScissors > 0 && contLine>0){
			Bear::bear->repair = true;
			endMission = true;
		}
		Bear::bear->SetDestinationPath(Vec2(300, 400));

	}else if(MissionManager::missionManager->GetStage("HallState") &&
					MissionManager::missionManager->countHallState > 1){
		if(state != MissionManager::missionManager->changeState){
			state = MissionManager::missionManager->changeState;
			MissionManager::missionManager->player->box.x = 400;
			MissionManager::missionManager->player->box.y = 400;
			time.Restart();
		}

		Cat::cat->SetDestinationPath(Vec2(800, 200));

		if (MissionManager::player->GetRuido()>80 ){
			MissionManager::enemy->show = true;
			SceneDoor::count = ABRE;
			//if(MissionManager::enemy->turn == 1)
			momcount ++;
			//DEFINIR CAMINHO DA MÃE NA PRIMEIRA VEZ QUE CHAMA A FUNÇÃO UPDATE DE MISSION1 NO GAME LOOP
			if(momcount == 1){
			//MOVIMENTO É COLOCADO DE TRÁS PARA FRENTE
			//MissionManager::enemy->SetDestinationPath(Vec2(970, 100)); //4º DESTINO
				MissionManager::enemy->SetDestinationPath(Vec2(800, 140)); //3º DESTINO
				MissionManager::enemy->SetDestinationPath(Vec2(500, 140)); //2º DESTINO
				MissionManager::enemy->SetDestinationPath(Vec2(500, 110)); //1º DESTINO
			}
		}
		if(MissionManager::enemy->show && time.Get() > ultimoTempo + 2){
			if(momcount == 1){
				falas.SetText("M: O QUE JÁ FALEI SOBRE SAIR DA CAMA?");
				falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
				ultimoTempo = ultimoTempo + 2;
				showBox = true;
			}
		}
		if(MissionManager::enemy->show && time.Get() > ultimoTempo + 4){
			falas.SetText(" ");
			falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
			ultimoTempo = ultimoTempo + 4;
			showBox = false;
		}

	}
	if(time.Get() >= 4 && begin && fadeIn){
			UpdateVariable(dt, 80);
	}

	if(time.Get() >= 6){
		//PiscaPisca(dt, 6, 0.6);
	}

}

void Mission2::Render(){
	if(time.Get() < 4 && begin){
		blackSquare.Render(0, 0, 0);
		tx.Render(0,0);
		creepy.Render(0,0);
	} else if((time.Get() >= 4 && begin && fadeIn) || !bloqBlack){
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

void Mission2::SetObjectStage(){
	Bear* bear = new Bear(810, 210);
	objectStage.emplace_back(bear);
	SceneObject* Bau = new SceneObject(300, 490,  "img/scene-bau-fechado.png",
			"img/scene-bau-aberto.png", 0, 1, 1, "", SceneObject::SAMEY_UP);
	objectStage.emplace_back(Bau);
	MovingObject* Box = new MovingObject(400, 500, "img/box.png");
	objectStage.emplace_back(Box);
	//MovingObject* Cadeira = new MovingObject(650, 300, "img/scene-cadeira.png", true);
	//objectStage.emplace_back(Cadeira);
}

void Mission2::SetObjectHall(){
	//SceneWindow* Window = new SceneWindow(350, 70);
	//objectHall.emplace_back(Window);
	//* Bau = new SceneObject(300, 490,  "img/scene-bau-fechado.png",
		//		"img/scene-bau-aberto.png", 0, 1, 1, "InventoryKey", SceneObject::SAMEY_UP);

	SceneObject* Armario2 = new SceneObject(1400, 110, "img/scene-armario-corredor-fechado.png",
			 "img/scene-armario-corredor-fechado.png", 0, 1, 1, "InventoryWool", SceneObject::SAMEY_UP);
	objectHall.emplace_back(Armario2);

	PickUpObject* Scissors = new PickUpObject(600, 325, "InventoryScissors", "img/object-scissors.png", true, 0.5, 0.5);
	objectHall.emplace_back(Scissors);

	MovingObject* Vase = new MovingObject(1300, 450, "img/scene-vaso.png");
	objectHall.emplace_back(Vase);

	Cat* gatinho = new Cat(1000, 200);
	objectHall.emplace_back(gatinho);

	MovingObject* Cadeira = new MovingObject(280, 303, "img/scene-cadeira.png", true);
		objectHall.emplace_back(Cadeira);

}

void Mission2::SetObjectLivingRoom(){

	PickUpObject* Agulha = new PickUpObject(670, 400, "InventoryNeedle", "img/object-needle.png", false, 0.5, 0.5);
	objectLivingRoom.emplace_back(Agulha);

	MovingObject* Banco = new MovingObject(650, 370, "img/moveis/sala/banquinho.png", true);
	objectLivingRoom.emplace_back(Banco);

}
