#include "Mission3.hpp"
#include "PickUpObject.hpp"
#include "StealthObject.hpp"
#include "SceneDoor.hpp"
#include "MissionManager.hpp"
#include "Geometry.hpp"
#include "HallState.hpp"
#include "LivingRoomState.hpp"

Music Mission3::music;

Mission3::Mission3() : Mission(), endMission(false) {
	initialState = "LivingRoomState"; // trocar para comeÃ§ar da sala?
	initialX = 230; initialY = 400;
	MissionManager::missionManager->SetPos(initialX, initialY);
	MissionManager::player->SetDirecao((int) Player::NORTE);
	MissionManager::missionManager->randomStates = true;

	atraidoNovelo = 0;
	atraidoTV = 0;
	drink = false;
	endMission = false;

	MissionManager::enemy->ChangeClothes(1);

	meowcount = 0;
	momcount = 0;
	momcount2 = 0;
	contador = 0;
	countCat = 0;
	contFala = 0;
	somGato = somPorta = false;

	SDL_Color redwine = SDL_Color();
	redwine.r = 102;
	redwine.g = 0;
	redwine.b = 0;

	SDL_Color white = SDL_Color();
	white.r = 255;
	white.g = 255;
	white.b = 255;

	tx = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "MISSÃO 3", redwine, 0, 0);
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

	miado = Timer();
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
	if(time.Get() < 100){
		time.Update(dt);
	}
	if(cooldown.Get() < 5){
		cooldown.Update(dt);
	}

	if(MissionManager::enemy->collidingPlayer && MissionManager::enemy->show && !endMission && !gameOver){
		gameOver = true;
		MissionManager::enemy->SetPosition(MissionManager::player->box.x, MissionManager::player->box.y);
		MissionManager::enemy->SetDestinationPath(Vec2(MissionManager::player->box.x, MissionManager::player->box.y));
		MissionManager::enemy->bloq=true;
		MissionManager::player->SetBlocked(true);
		MissionManager::player->SetBloqHUD(true);
		MissionManager::player->SetBloqInv(true);
		time.Restart();
		Camera::Follow(MissionManager::player, CAMERA_TYPE1);
		Camera::Zoom(2, true);
	}



	if(gameOver && time.Get() > 3){
		Game::GetInstance().GetCurrentState().ChangeMission(3);
	}

	if(endMission && drink){
		if(time.Get() > 47)
		Game::GetInstance().GetCurrentState().ChangeMission(4);
	}

	if(MissionManager::missionManager->IsState("LivingRoomState") &&
			MissionManager::missionManager->countLivingRoomState <= 1){

		if(momcount == 0){
			MissionManager::enemy->show = true;
			momcount++;
			MissionManager::enemy->SetPosition(700, 190);
			MissionManager::player->SetBlocked(true);

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
		if(time.Get() > 3 && contFala == 0){
			contFala++;
			tx.SetText(" ");
			showBox = false;
			creepy.SetText(" ");
			ImageProfileBox (6);
		}
		if(time.Get() > 5 && contFala == 1){
			contFala++;
			Sound sussurro = Sound ("audio/ghostly-whispers.wav");
			sussurro.Play(0);
			ImageProfileBox (4); //BOTA URSO
			falas.SetText("OLHA ESSA QUE CHAMAS DE MÃE");
			falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
			ultimoTempo = 5;
			showBox = true;
		}
		if(time.Get() > 10 && contFala == 2){
			contFala++;
			falas.SetText("O QUE É ESSA ROUPA?");
			falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
			ultimoTempo = 10;
			showBox = true;
		}
		if(time.Get() > 15 && trancada == false && cooldown.Get() > 3 && contFala == 3){
			contFala++;
			falas.SetText("AINDA É REALMENTE ELA POR BAIXO DESSE PANO NEGRO?");
			falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
			ultimoTempo = 15;
			showBox = true;
		}
		if(time.Get() > 20 && trancada == false && cooldown.Get() > 3 && contFala == 4){
			contFala++;
			falas.SetText("TEMOS QUE INVESTIGAR ISSO");
			falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
			ultimoTempo = 20;
			showBox = true;
			MissionManager::player->SetBlocked(false);
			MissionManager::enemy->show = false;
		}
		if(time.Get() > 25 && trancada == false && cooldown.Get() > 3 && contFala == 5){
			contFala++;
			falas.SetText(" ");
			falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
			ultimoTempo = 25;
			showBox = false;
			MissionManager::enemy->show = false;
		}
		MessageDoor(dt);
		//TROCANDO DE COMODO. ENTRANDO NO CORREDOR PELA PRIMEIRA VEZ
	}

	if(MissionManager::missionManager->IsState("HallState")){

		if(state != MissionManager::missionManager->changeState){
			state = MissionManager::missionManager->changeState;
			MissionManager::enemy->show = false;
			MissionManager::enemy->SetPosition(975,115);
			momcount = 0;
			time.Restart();
		}

		if(time.Get() < 3 && trancada == false && cooldown.Get() > 3){
			falas.SetText(" ");
			falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
			ultimoTempo = 3;
			showBox = false;
		}

		if(MissionManager::cat->attractedTV){
			MissionManager::cat->show = false;
		} else{
			MissionManager::cat->show = true;
		}
		countCat++;
		//if(count == 1){
		int dist = MissionManager::cat->box.DistanceRect(MissionManager::player->box);
		//std::cout << "dist" << dist << std::endl;
		if(countCat == 1  && atraidoNovelo == 0){
			MissionManager::cat->SetDestinationPath(Vec2(1000, 200));
			MissionManager::cat->SetDestinationPath(Vec2(900, 200));
			MissionManager::cat->SetDestinationPath(Vec2(1000, 200));
			MissionManager::cat->SetDestinationPath(Vec2(890, 200)); //4Âº DESTINO
			MissionManager::cat->SetDestinationPath(Vec2(970, 200)); //3Âº DESTINO
			MissionManager::cat->SetDestinationPath(Vec2(1000, 200)); //2Âº DESTINO
			MissionManager::cat->SetDestinationPath(Vec2(900, 200)); //1Âº DESTINO
		}
		if(time.Get() > 5  && atraidoNovelo == 0){
			MissionManager::cat->SetDestinationPath(Vec2(890, 200));
		}
		if(dist < 250 && atraidoNovelo == 0){
			MissionManager::cat->SetDestinationPath(Vec2(980, 200));
		}
		if(MissionManager::cat->attractedWool == false && dist > 200){
			MissionManager::cat->SetDestinationPath(Vec2(1000, 200));
			MissionManager::cat->SetDestinationPath(Vec2(900, 200));
		}

		if(dist < 100 && MissionManager::cat->show == true){
			Sound meow1 = Sound ("audio/cat-meow-1.wav");
			Sound meow2 = Sound ("audio/cat-meow-2.wav");
			Sound meow3 = Sound ("audio/cat-meow-3.wav");
			if(miado.Get() > 3){
				somGato = false;
				miado.Restart();
			} else{
				miado.Update(dt);
			}
			if(somGato == false){
				MissionManager::player->AddRuido(45);
				if(meowcount == 0)
					meow1.Play(0);
				else if(meowcount == 1)
					meow2.Play(0);
				else if(meowcount == 2){
					meow3.Play(0);
					meowcount = -1;
				}
				somGato = true;
				meowcount++;
			}
		}

		if(MissionManager::cat->attractedWool == true && MissionManager::cat->attractedTV == false){
			atraidoNovelo++;
			if(atraidoNovelo == 1){
				MissionManager::cat->PathFlush();
				MissionManager::cat->SetDestinationPath(Vec2(1350, 450));
				MissionManager::cat->SetDestinationPath(Vec2(980, 450));
				MissionManager::cat->SetDestinationPath(Vec2(980, 300));
				contador =  MissionManager::missionManager->countHallState;
			} else if (atraidoNovelo > 30){
				MissionManager::cat->SetDestinationPath(Vec2(1350, 450));
			}

		} else if(MissionManager::cat->attractedWool == true && MissionManager::cat->attractedTV == true){
			MissionManager::cat->attractedWool = false;
		}

		if(time.Get() > 7 && time.Get() < 7.5 && trancada == false && cooldown.Get() > 3){
			Sound portaDestrancando = Sound ("audio/meow-sample.wav");
			portaDestrancando.Play(0);
		}
		if (MissionManager::player->GetRuido() > 70 ){
			MissionManager::enemy->show = true;
			SceneDoor::count = ABRE;
			momcount++;
			gameOver = true;
			//std::cout << "momcount" << momcount << std::endl;
			/*if(MissionManager::enemy->seen && MissionManager::enemy->canPursuit){
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
				((HallState&) Game::GetInstance().GetCurrentState())
						.tileMap.PathFind(Vec2(posEnemyX,posEnemyY),
								Vec2(MissionManager::player->box.x+30,MissionManager::player->box.y+50) );
				MissionManager::enemy->SetDestinationPursuit(
						((HallState&) Game::GetInstance().GetCurrentState()).tileMap.GetPath());
			}*/

			if(MissionManager::enemy->show){
				if(momcount == 1){
					SceneDoor::ValorPassar = 15;
					ImageProfileBox(2);
					falas.SetText("O QUE JÃ FALEI SOBRE SAIR DA CAMA?");
					falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
					ultimoTempo = (int)time.Get();
					showBox = true;
				}
			}
			if(MissionManager::enemy->show && time.Get() > ultimoTempo + 2){
				SceneDoor::ValorPassar = 0;
			}
			if(MissionManager::enemy->show && time.Get() > ultimoTempo + 4 && showBox){
				falas.SetText(" ");
				ImageProfileBox (6);
				falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
				ultimoTempo = ultimoTempo + 4;
				showBox = false;
			}
		}


	} if(MissionManager::missionManager->IsState("LivingRoomState") &&
				MissionManager::missionManager->countLivingRoomState > 1){

		MissionManager::cat->show = false;
		MissionManager::enemy->show = false;
		if(state != MissionManager::missionManager->changeState){
			state = MissionManager::missionManager->changeState;
			MissionManager::cat->Reset();
			MissionManager::enemy->SetPosition(400,400);
			time.Restart();
		}

		if(MissionManager::cat->attractedTV == true && MissionManager::cat->attractedWool == false){
			MissionManager::cat->show = true;
			atraidoTV++;

			contador =  MissionManager::missionManager->countLivingRoomState;
			if(atraidoTV == 1){
				MissionManager::cat->PathFlush();
				MissionManager::cat->Reset();
				MissionManager::cat->SetPosition(230, 300);
				//MissionManager::missionManager->cat->box.x = 400;
				//MissionManager::missionManager->cat->box.y = 400;
				time.Restart();

				MissionManager::cat->SetDestinationPath(Vec2(640, 450));
				MissionManager::cat->SetDestinationPath(Vec2(640, 500));
				/*MissionManager::cat->SetDestinationPath(Vec2(500, 450));
				MissionManager::cat->SetDestinationPath(Vec2(400, 430));
				MissionManager::cat->SetDestinationPath(Vec2(400, 350));*/
				MissionManager::cat->SetDestinationPath(Vec2(230, 500));
			}
			if(time.Get()>4.3){
				MissionManager::cat->PathFlush();
				MissionManager::cat->Reset();
				MissionManager::cat->SetPosition(640, 450);
			}
		}


	}if(MissionManager::missionManager->IsState("MomRoomState")){

		MissionManager::enemy->show = false;
		if(state != MissionManager::missionManager->changeState){
			state = MissionManager::missionManager->changeState;
			MissionManager::enemy->SetPosition(225, 190);
			MissionManager::enemy->Reset();
			time.Restart();
		}

		Vec2 *covil = new Vec2(570, 470);
		float dist = 0;
		dist = covil->Distance(Vec2(MissionManager::player->box.x, MissionManager::player->box.y));
		if(dist < 120){
			bronca = true;
			SceneDoor::count = ABRE;
			SceneDoor::ValorPassar = 4;
			MissionManager::player->SetBlocked(true);
			MissionManager::enemy->show = true;

			if(time.Get() < 17 && momcount2 == 0){
				SetPiscaPisca(20, 0.4);
			}
			if(momcount2 == 0){
				momcount2++;
				time.Restart();
				MissionManager::enemy->SetDestinationPath(Vec2(225, 190));
			}
			if(time.Get() > 2 && time.Get() < 6 && momcount2 == 1){
				momcount2++;
				showBox = true;
				ImageProfileBox (2);
				falas.SetText("O QUE ESTÁ FAZENDO AQUI?");
				falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
			}
			if(time.Get() > 6 && time.Get() < 10 && momcount2 == 2){
				momcount2++;
				showBox = true;
				ImageProfileBox (2);
				falas.SetText("NÃO TOLERAREI ISSO!");
				falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
			}
			if(time.Get() > 10 && time.Get() < 14 && momcount2 == 3){
				momcount2++;
				showBox = true;
				ImageProfileBox (2);
				falas.SetText("JÁ PARA O QUARTO!");
				falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
			}
			if(time.Get() > 14 && time.Get() < 18 && momcount2 == 4){
				momcount2++;
				showBox = true;
				ImageProfileBox (2);
				falas.SetText("DEIXEI SEU LEITE LÁ!");
				falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
			}
			if(time.Get() > 18 && momcount2 == 5){
				momcount2++;
				showBox = false;
				ImageProfileBox (6);
				falas.SetText(" ");
				falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
			}
			if(time.Get() > 19){
				Game::GetInstance().GetCurrentState().ChangeState("MomRoomStage", "StageState");
			}
		}
	}
	if(MissionManager::missionManager->IsState("StageState") /*&& bronca*/){
		if(state != MissionManager::missionManager->changeState){
			//std::cout << time.Get() << std::endl;
			MissionManager::player->SetPosition(805, 260);
			state = MissionManager::missionManager->changeState;
			MissionManager::enemy->show = false;
			time.Restart();
			momcount2 = 0;
		}
		if(time.Get() > 8 && time.Get() < 12 && momcount2 == 0){
			momcount2++;
			showBox = true;
			ImageProfileBox (4);
			falas.SetText("É MELHOR BEBER SEU LEITE");
			falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
		}
		if(time.Get() > 12&& momcount2 == 1){
			momcount2++;
			showBox = false;
			ImageProfileBox (6);
			falas.SetText(" ");
			falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
		}

		if(time.Get() > 40 && time.Get() < 44&& momcount2 == 2){
			momcount2++;
			showBox = true;
			ImageProfileBox (4);
			falas.SetText("BEBAAAAAAAAAAAAAAAA");
			falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
		}
		if(time.Get() > 44 && momcount2 == 3){
			momcount2++;
			showBox = false;
			ImageProfileBox (6);
			falas.SetText(" ");
			falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
		}

		Vec2 *leite = new Vec2(255, 405);
		float dist = 0;
		dist = leite->Distance(Vec2(MissionManager::player->box.x, MissionManager::player->box.y));
		if(dist<80 && InputManager::GetInstance().KeyPress(Z_KEY)){
			time.Set(44);
			drink = true;
			endMission = true;
		}

	}

	if(time.Get() >= 4 && fadeIn){
		UpdateVariable(dt, 80);
	}

	PiscaPisca(dt);
}

void Mission3::Render(){
	if(time.Get() < 4 && fadeIn){
		blackSquare.Render(0, 0, 0);
		tx.Render(0,0);
		creepy.Render(0,0);
	} else if((time.Get() >= 4 && fadeIn) || !bloqBlack){
		spFade.Render(0,0,0);
	}

	if((((MissionManager::missionManager->IsState("LivingRoomState") && MissionManager::missionManager->countLivingRoomState <= 1 && time.Get() > 4) ||
		((MissionManager::missionManager->IsState("LivingRoomState") && MissionManager::missionManager->countLivingRoomState > 1) ||
			MissionManager::missionManager->IsState("HallState"))) && !MissionManager::player->GetBloqHUD()) || 	MissionManager::missionManager->IsState("MomRoomState")){
		if(showBox){
			falasBox.Render(falasBoxRect.x, falasBoxRect.y, 0);
			profileBox.Render(profileBoxX, profileBoxY, 0);
		}
		falas.Render(0,0);
	}
}

void Mission3::SetObjectStage(){
	SceneDoor* Door = new SceneDoor(800, 200, "HallState");
	objectStage.emplace_back(Door);

	StealthObject* Armario2 = new StealthObject(1400, 110, "img/cenario/geral/armario-corredor-fechado.png");
	objectStage.emplace_back(Armario2);

	SceneObject* Bau = new SceneObject(300, 490,  "img/cenario/geral/bau-fechado.png",
			"img/cenario/geral/bau-aberto.png", 0, 1, 1, "", SceneObject::SAMEY_UP);
	objectStage.emplace_back(Bau);

	MovingObject* Cadeira = new MovingObject(730, 300, "img/cenario/geral/cadeira.png");
	objectStage.emplace_back(Cadeira);

	PickUpObject* Copo = new PickUpObject(255, 405, "img/inventario/copo-cheio.png", "img/inventario/copo-cheio.png", false, 0.5, 0.5, true);
	objectStage.emplace_back(Copo);

}

void Mission3::SetObjectHall(){
	SceneDoor* DoorToMomRoom = new SceneDoor(970, 105, "MomRoomState", true,
			"img/cenario/geral/door-closed.png", "img/cenario/geral/door-opened.png", 0);
	objectHall.emplace_back(DoorToMomRoom);

	SceneObject* CriadoMudo = new SceneObject(100, 160,
			"img/cenario/filho/criado-fechado.png", "img/cenario/filho/criado-aberto.png");
	objectHall.emplace_back(CriadoMudo);

	SceneObject* Apple = new SceneObject(1355, 325, "img/cenario/geral/maca.png", "", 0, 0.3, 0.3);
	objectHall.emplace_back(Apple);

	SceneObject* CaixaDeAreia = new SceneObject(1400, 450,
			"img/cenario/corredor/caixa-areia.png", "img/cenario/corredor/caixa-novelo.png", 0, 1, 1, "", 3, true);
	objectHall.emplace_back(CaixaDeAreia);

	SceneObject* CamaGato = new SceneObject(90, 440,
				"img/cenario/corredor/cama-gato.png", "img/cenario/corredor/cama-gato.png");
	objectHall.emplace_back(CamaGato);

	SceneObject* PoteRacao = new SceneObject(80, 500,
				"img/cenario/corredor/pote-com-racao.png", "img/cenario/corredor/pote-com-racao.png");
	objectHall.emplace_back(PoteRacao);

	SceneObject* PoteAgua = new SceneObject(135, 500,
				"img/cenario/corredor/pote-sem-racao.png", "img/cenario/corredor/pote-sem-racao.png");
	objectHall.emplace_back(PoteAgua);

	MovingObject* Vase = new MovingObject(1000, 450, "img/cenario/geral/vaso.png");
	objectHall.emplace_back(Vase);
}

void Mission3::SetObjectLivingRoom(){
	MovingObject* Banco1 = new MovingObject(510, 470, "img/cenario/sala/banquinho.png", true);
	objectLivingRoom.emplace_back(Banco1);

	MovingObject* Banco2 = new MovingObject(570, 470, "img/cenario/sala/banquinho.png", true);
	objectLivingRoom.emplace_back(Banco2);
}

void Mission3::SetObjectMomRoom(){

}
