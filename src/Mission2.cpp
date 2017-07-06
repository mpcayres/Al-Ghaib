#include "Mission2.hpp"
#include "PickUpObject.hpp"
#include "StealthObject.hpp"
#include "SceneDoor.hpp"
#include "MissionManager.hpp"
#include "Animation.hpp"
#include "HallState.hpp"


 Music Mission2::music;

Mission2::Mission2() : Mission(), paradoUrso(false), paradoGato(false), endMission(false) {
	initialState = "StageState";
	initialX = 300; initialY = 400;
	MissionManager::missionManager->SetPos(initialX, initialY);
	MissionManager::player->SetDirecao((int) Player::LESTE);
	MissionManager::missionManager->randomStates = true;

	meowcount = 0;
	momcount = 0;
	countBear = -1;
	countCat = 0;

	SDL_Color redwine = SDL_Color();
	redwine.r = 102;
	redwine.g = 0;
	redwine.b = 0;

	SDL_Color white = SDL_Color();
	white.r = 255;
	white.g = 255;
	white.b = 255;

	tx = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "MISSÃO 2", redwine, 0, 0);
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

	destrancAudioFlag = false;
	sussurroAudioFlag = false;
	miadoAudioFlag = true;

	miado = Timer();
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

	if(MissionManager::enemy->seen && MissionManager::enemy->canPursuit){
		double posEnemyY = MissionManager::enemy->box.y+MissionManager::enemy->GetHeight();
		double posEnemyX = MissionManager::enemy->box.x;

		if(posEnemyY > MissionManager::player->limits.y+MissionManager::player->limits.h){
			posEnemyY = MissionManager::player->limits.y+MissionManager::player->limits.h - 10;
		}
		if(posEnemyY < MissionManager::player->limits.y){
			posEnemyY = MissionManager::player->limits.y+10;
		}
		if(posEnemyX > MissionManager::player->limits.x+MissionManager::player->limits.w){
			posEnemyX = MissionManager::player->limits.x+MissionManager::player->limits.w -10;
		}
		if(posEnemyX < MissionManager::player->limits.x){
			posEnemyX = MissionManager::player->limits.x + 10;
		}

		if(MissionManager::missionManager->IsState("HallState")){
			((HallState&) Game::GetInstance().GetCurrentState())
	 			.tileMap.PathFind(Vec2(posEnemyX,posEnemyY),
	 					Vec2(MissionManager::player->box.x+30,MissionManager::player->box.y+30) );
			MissionManager::enemy->SetDestinationPursuit(((HallState&) Game::GetInstance().
					GetCurrentState()).tileMap.GetPath());
			MissionManager::enemy->seen = false;
		}
	}





	if(endMission){
		Game::GetInstance().GetCurrentState().ChangeMission(3);
	}
	//URSO APARECE BATENDO NA PORTA. BOTAR SOM DE PORTA TENTANDO ABRIR ANTES DE ELE FALAR
	if(MissionManager::missionManager->IsState("StageState") &&
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
				Sound portaDestrancando = Sound ("audio/destrancando.wav");
				if(destrancAudioFlag == false){
					portaDestrancando.Play(0);
					destrancAudioFlag = true;
				}
			}
			if(time.Get() > 14 && trancada == false && cooldown.Get() > 2){
				if(countBear == -1){
					countBear++;
					Game::GetInstance().GetCurrentState().AddObject(
							new Animation(800, 260, 0,
									"img/sprite/bear-transformation.png", 17, 0.25, true, 2, 2));
				}
			}
			if(time.Get() > (14+4.25) && trancada == false && cooldown.Get() > 2){
				if(countBear == 0){
					Bear::bear->show = true;
					countBear++;
					Bear::bear->box.x = 805;
					Bear::bear->box.y = 250;
					SceneDoor::count = ABRE;
					SceneDoor::ValorPassar = 24;
					paradoUrso = true;
					Bear::bear->SetDestinationPath(Vec2(805, 450)); //2Âº DESTINO
					Bear::bear->SetDestinationPath(Vec2(805, 250)); //1Âº DESTINO
					ultimoTempo = 12;
				}

				if(time.Get() > 15+4.25){
					Bear::bear->SetDestinationPath(Vec2(805, 450));
					//Bear::bear->box.x = 810;
					//Bear::bear->box.y = 450;
				}

				if(time.Get() > 18+4.25 && countBear == 1){
					countBear++;
					sussurro.Play(0);
					showBox = true;
					ImageProfileBox(6); //BOTAR O URSO
					falas.SetText("U: OLHA O QUE FIZERAM COMIGO!");
					falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
					ultimoTempo = 14;
					showBox = true;
				}

				if(time.Get() > 22+4.25 && countBear == 3){
					countBear++;
					//Sound sussurro = Sound ("audio/ghostly-whispers.wav");
					//sussurro.Play(0);
					falas.SetText("U: ACHA QUE CONSEGUE ME REPARAR?");
					falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
					ultimoTempo = 18;
					showBox = true;
				}
				if(time.Get() > 24+4.25 && countBear == 4){
					countBear++;
					//Sound sussurro = Sound ("audio/ghostly-wspers.wav");
					//sussurro.Play(0);
					falas.SetText("U: VOU FICAR AQUI ESPERANDO");
					falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
					ultimoTempo = 22;
					showBox = true;
					MissionManager::player->SetBlocked(false);
				}
				if(time.Get() > 29+4.25 && countBear == 5){
					countBear++;
					//Sound sussurro = Sound ("audio/ghostly-whispers.wav");
					//sussurro.Play(0);
					//sussurro.Stop(); Tava dando erro ?!
					falas.SetText(" ");
					ImageProfileBox (6);
					falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
					ultimoTempo = 29;
					showBox = false;
					//parado = false;
					//Bear::seen = true; !!!!!!!!!
				}
			}

			MessageDoor(dt);
			//TROCANDO DE COMODO. ENTRANDO NO CORREDOR PELA PRIMEIRA VEZ
	}else if(MissionManager::missionManager->IsState("HallState") &&
							MissionManager::missionManager->countHallState <= 1){

		MissionManager::player->SetBlocked(false);
		//HallState++;

		if(state != MissionManager::missionManager->changeState){
			state = MissionManager::missionManager->changeState;
			//MissionManager::missionManager->player->box.x = 400;
			//MissionManager::missionManager->player->box.y = 400;
			MissionManager::enemy->show = false;
			time.Restart();
		}
		if(time.Get() < 2){
			falas.SetText(" ");
			falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
			ultimoTempo = 2;
			showBox = false;
		}

		MissionManager::cat->show = true;
		countCat++;
		//if(count == 1){
		//int dist = MissionManager::cat->box.DistanceRect(MissionManager::player->box);
		//std::cout << "dist" << dist << std::endl;

		//std::cout << "time" << time.Get() << std::endl;
		if(countCat == 1){
			//MOVIMENTO Ã‰ COLOCADO DE TRÃ�S PARA FRENTE
			MissionManager::cat->SetDestinationPath(Vec2(500, 300)); //ULTIMO DESTINO
			MissionManager::cat->SetDestinationPath(Vec2(500, 200));
			MissionManager::cat->SetDestinationPath(Vec2(900, 200));
			MissionManager::cat->SetDestinationPath(Vec2(900, 450));
			MissionManager::cat->SetDestinationPath(Vec2(900, 500));
			MissionManager::cat->SetDestinationPath(Vec2(900, 300));
			MissionManager::cat->SetDestinationPath(Vec2(800, 300));
			MissionManager::cat->SetDestinationPath(Vec2(700, 300));
			MissionManager::cat->SetDestinationPath(Vec2(800, 300));
			MissionManager::cat->SetDestinationPath(Vec2(500, 300));
			MissionManager::cat->SetDestinationPath(Vec2(500, 200));
			MissionManager::cat->SetDestinationPath(Vec2(900, 200));
			MissionManager::cat->SetDestinationPath(Vec2(900, 450));
			MissionManager::cat->SetDestinationPath(Vec2(900, 500));
			MissionManager::cat->SetDestinationPath(Vec2(900, 300)); //3Âº DESTINO
			MissionManager::cat->SetDestinationPath(Vec2(800, 300)); //2Âº DESTINO
			MissionManager::cat->SetDestinationPath(Vec2(700, 300)); //1Âº DESTINO
			//paradoGato = true;
		}
		if(time.Get()>5){
			MissionManager::cat->SetDestinationPath(Vec2(800, 300));
		}

		Sound meow1 = Sound ("audio/cat-meow-1.wav");
		Sound meow2 = Sound ("audio/cat-meow-2.wav");
		Sound meow3 = Sound ("audio/cat-meow-3.wav");
		if(miado.Get() > 3){
			miadoAudioFlag = false;
			miado.Restart();
		}else{
			miado.Update(dt);
		}
		if(miadoAudioFlag == false){
			//MissionManager::player->AddRuido(6);
			if(meowcount == 0)
				meow1.Play(0);
			else if(meowcount == 1)
				meow2.Play(0);
			else if(meowcount == 2){
				meow3.Play(0);
				meowcount = -1;
			}
			miadoAudioFlag = true;
			meowcount++;
		}


		if (MissionManager::player->GetRuido()>80 && MissionManager::enemy->show == false){
			MissionManager::enemy->seen = true;
			MissionManager::enemy->canPursuit = true;
			MissionManager::enemy->SetPosition(975,115);
			MissionManager::enemy->show = true;
			SceneDoor::count = ABRE;
			//if(MissionManager::enemy->turn == 1)
			momcount ++;
			if(momcount == 1){
			//MOVIMENTO Ã‰ COLOCADO DE TRÃ�S PARA FRENTE
				//MissionManager::enemy->SetDestinationPath(Vec2(970, 100)); //4Âº DESTINO
				MissionManager::enemy->SetDestinationPath(Vec2(800, 140)); //3Âº DESTINO
				MissionManager::enemy->SetDestinationPath(Vec2(500, 140)); //2Âº DESTINO
				MissionManager::enemy->SetDestinationPath(Vec2(500, 110)); //1Âº DESTINO
			}
		}
		if(MissionManager::enemy->show && time.Get() > ultimoTempo + 2){
			if(momcount == 1){
				falas.SetText("M: O QUE JÃ FALEI SOBRE SAIR DA CAMA?");
				ImageProfileBox(1);
				falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
				ultimoTempo = ultimoTempo + 2;
				showBox = true;
			}
		}
		if(MissionManager::enemy->show && time.Get() > ultimoTempo + 4){
			falas.SetText(" ");
			ImageProfileBox (6);
			falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
			ultimoTempo = ultimoTempo + 4;
			showBox = false;
		}
	}else if(MissionManager::missionManager->IsState("StageState") &&
			MissionManager::missionManager->countStageState > 1){
		if(state != MissionManager::missionManager->changeState){
			state = MissionManager::missionManager->changeState;
			time.Restart();
		}
		Bear::bear->show = true;
		Bear::bear->box.x = 300;
		Bear::bear->box.y = 380;
		count++;
		Bear::bear->retorno = true;
		if(time.Get() > 0){
				Bear::bear->SetDestinationPath(Vec2(300, 380));
				//Bear::bear->box.x = 810;
				//Bear::bear->box.y = 450;
		}
		if(count == 1){
			MissionManager::missionManager->player->box.x = 800;
			MissionManager::missionManager->player->box.y = 300;
		}

		if(Bear::bear->hasNeedle && Bear::bear->hasScissors && Bear::bear->hasCostura){
			Bear::bear->repair = true;
			time.Restart();
			ImageProfileBox(6); //BOTAR URSO
			falas.SetText("U: OBRIGADO!");
			falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
			ultimoTempo = (int)time.Get();
			showBox = true;
			if(time.Get()> ultimoTempo + 7){
				falas.SetText(" ");
				showBox = false;
				endMission = true;
				ImageProfileBox (6);
			}
		}
		Bear::bear->SetDestinationPath(Vec2(300, 400));

	}else if(MissionManager::missionManager->IsState("LivingRoomState") &&
					MissionManager::missionManager->countLivingRoomState > 1){

		MissionManager::player->SetBlocked(false);
		if(state != MissionManager::missionManager->changeState){
			MissionManager::enemy->show = false;
			MissionManager::enemy->SetPosition(975,115);
			state = MissionManager::missionManager->changeState;
			//MissionManager::missionManager->player->box.x = 400;
			//MissionManager::missionManager->player->box.y = 400;
			time.Restart();
		}

		MissionManager::cat->SetDestinationPath(Vec2(800, 200));

		if (MissionManager::player->GetRuido()>80 ){
			MissionManager::enemy->show = true;
			SceneDoor::count = ABRE;
			//if(MissionManager::enemy->turn == 1)
			momcount ++;
			//DEFINIR CAMINHO DA MÃƒE NA PRIMEIRA VEZ QUE CHAMA A FUNÃ‡ÃƒO UPDATE DE MISSION1 NO GAME LOOP
			if(momcount == 1){
			//MOVIMENTO Ã‰ COLOCADO DE TRÃ�S PARA FRENTE
			//MissionManager::enemy->SetDestinationPath(Vec2(970, 100)); //4Âº DESTINO
				MissionManager::enemy->SetDestinationPath(Vec2(800, 140)); //3Âº DESTINO
				MissionManager::enemy->SetDestinationPath(Vec2(500, 140)); //2Âº DESTINO
				MissionManager::enemy->SetDestinationPath(Vec2(500, 110)); //1Âº DESTINO
			}
		}
		if(MissionManager::enemy->show && time.Get() > ultimoTempo + 2){
			if(momcount == 1){
				falas.SetText("O QUE JÃ FALEI SOBRE SAIR DA CAMA?");
				ImageProfileBox(1);
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

	}else if(MissionManager::missionManager->IsState("LivingRoomState")){

		MissionManager::cat->show = false;

	}

	if(time.Get() >= 4 && fadeIn){
		UpdateVariable(dt, 80);
	}

}

void Mission2::Render(){
	if(time.Get() < 4 && fadeIn){
		blackSquare.Render(0, 0, 0);
		tx.Render(0,0);
		creepy.Render(0,0);
	} else if((time.Get() >= 4 && fadeIn) || !bloqBlack){
		spFade.Render(0,0,0);
	}

	if(((MissionManager::missionManager->IsState("StageState") &&
			MissionManager::missionManager->countStageState <= 1 && time.Get() > 4) ||
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

void Mission2::SetObjectStage(){
	SceneDoor* Door = new SceneDoor(800, 200, "HallState");
	objectStage.emplace_back(Door);

	Bear* bear = new Bear(810, 210);
	objectStage.emplace_back(bear);

	SceneObject* Bau = new SceneObject(300, 490, "img/cenario/geral/bau-fechado.png",
			"img/cenario/geral/bau-aberto.png", 0, 1, 1, "", SceneObject::SAMEY_UP);
	objectStage.emplace_back(Bau);

	MovingObject* Box = new MovingObject(400, 500, "img/cenario/sala/banquinho.png");
	objectStage.emplace_back(Box);

	//MovingObject* Cadeira = new MovingObject(650, 300, "img/cenario/geral/cadeira.png", true);
	//objectStage.emplace_back(Cadeira);
}

void Mission2::SetObjectHall(){
	//Bau = new SceneObject(300, 490,  "img/cenario/geral/bau-fechado.png",
	//		"img/cenario/geral/bau-aberto.png", 0, 1, 1, "InventoryKey", SceneObject::SAMEY_UP);

	SceneDoor* DoorToMomRoom = new SceneDoor(970, 105, "MomRoomState", true,
			"img/cenario/geral/door-closed.png", "img/cenario/geral/door-opened.png", -1);
	objectHall.emplace_back(DoorToMomRoom);

	//SceneObject* Armario2 = new SceneObject(1300, 110, "img/cenario/geral/armario-corredor-fechado.png",
	//		 "", 0, 1, 1, "InventoryWool", SceneObject::DEFAULT);
	//objectHall.emplace_back(Armario2);
	StealthObject* Armario2 = new StealthObject(1450, 150, "img/cenario/geral/armario-corredor-fechado.png");
		objectHall.emplace_back(Armario2);


	SceneObject* CriadoMudo = new SceneObject(100, 160,
			"img/cenario/filho/criado-fechado.png", "img/cenario/filho/criado-aberto.png",
			0, 1, 1, "InventoryWool", SceneObject::DEFAULT);
	objectHall.emplace_back(CriadoMudo);

	PickUpObject* Scissors = new PickUpObject(1475, 205, "InventoryScissors",
			"img/inventario/scissors.png", true, 0.5, 0.5, false, 90);
	objectHall.emplace_back(Scissors);

	MovingObject* Vase = new MovingObject(1300, 450, "img/cenario/geral/vaso.png");
	objectHall.emplace_back(Vase);

	MovingObject* Cadeira = new MovingObject(200, 420, "img/cenario/geral/cadeira.png", true);
	objectHall.emplace_back(Cadeira);

}

void Mission2::SetObjectLivingRoom(){
	PickUpObject* Agulha = new PickUpObject(670, 400, "InventoryNeedle", "img/inventario/needle.png", false, 0.5, 0.5);
	objectLivingRoom.emplace_back(Agulha);

	PickUpObject* Carretel = new PickUpObject(600, 420, "InventoryLine", "img/inventario/carretel.png", false, 0.5, 0.5);
	objectLivingRoom.emplace_back(Carretel);

	MovingObject* Banco = new MovingObject(650, 370, "img/cenario/sala/banquinho.png", true);
	objectLivingRoom.emplace_back(Banco);

	MovingObject* Cadeira = new MovingObject(750, 480, "img/cenario/geral/cadeira.png", true);
	objectLivingRoom.emplace_back(Cadeira);
}

void Mission2::SetObjectMomRoom(){

}
