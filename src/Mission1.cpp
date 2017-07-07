#include "Mission1.hpp"
#include "PickUpObject.hpp"
#include "SceneObject.hpp"
#include "StealthObject.hpp"
#include "SceneDoor.hpp"
#include "Animation.hpp"
#include "HallState.hpp"
#include "LivingRoomState.hpp"

#include <iostream>

Mission1::Mission1() : Mission(), played(false), endMission(false) {
	countPega = countPega2 = 0;
	initialState = "StageState";
	initialX = 400; initialY = 400;
	MissionManager::missionManager->SetPos(initialX, initialY);
	MissionManager::missionManager->randomStates = false;

	SDL_Color redwine = SDL_Color();
	redwine.r = 102;
	redwine.g = 0;
	redwine.b = 0;

	SDL_Color white = SDL_Color();
	white.r = 255;
	white.g = 255;
	white.b = 255;

	//flagTimer = true; //stopMusic = false;
	//time = Timer();
	//cooldown = Timer();
	tx = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "MISSÃO 1", redwine, 0, 0);
	tx.SetPos(0, 0, true, true);
	creepy = Text("font/uwch.ttf", 30, Text::TextStyle::BLENDED, "  ", redwine, 0, 0);
	creepy.SetPos(0, Game::GetInstance().GetHeight()-220, true, false);
	creepy1 = Text("font/uwch.ttf", 28, Text::TextStyle::BLENDED, "\"Cobri vossos utensílios e amarrai vossos cantis", redwine, 0, 0);
	creepy1.SetPos(0, Game::GetInstance().GetHeight()-230, true, false);

	creepy2 = Text("font/uwch.ttf", 28, Text::TextStyle::BLENDED, "fechai as portas e mantende as crianças perto à noite.", redwine, 0, 0);
	creepy2.SetPos(0, Game::GetInstance().GetHeight()-200, true, false);

	creepy3 = Text("font/uwch.ttf", 28, Text::TextStyle::BLENDED, "Quando irdes dormir, apagai os candeeiros,", redwine, 0, 0);
	creepy3.SetPos(0, Game::GetInstance().GetHeight()-170, true, false);

	creepy4 = Text("font/uwch.ttf", 28, Text::TextStyle::BLENDED, "pois o maligno pode se apoderar da chama ", redwine, 0, 0);
	creepy4.SetPos(0, Game::GetInstance().GetHeight()-140, true, false);

	creepy5 = Text("font/uwch.ttf", 28, Text::TextStyle::BLENDED, " e atear fogo nos moradores da casa.\"", redwine, 0, 0);
	creepy5.SetPos(0, Game::GetInstance().GetHeight()-110, true, false);

	creepy6 = Text("font/uwch.ttf", 28, Text::TextStyle::BLENDED, "                 Hadith - Sahih Bukhari 4.533", redwine, 0, 0);
	creepy6.SetPos(0, Game::GetInstance().GetHeight()-70, true, false);

	falas = Text("font/AA_typewriter.ttf", 25, Text::TextStyle::BLENDED , "A NOITE É FRIA E PERIGOSA", white, 0, 0);
	falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);

	/*intro = Music("audio/menu-intro.wav");
	music = Music("audio/menu-loop.wav");
	intro.Play(1);
	Mix_HookMusicFinished(&TitleState::LinkMusic);*/

	SetObjectStage();
	SetObjectHall();
	SetObjectLivingRoom();

	MissionManager::enemy->SetPosition(500, 110);
}

Mission1::~Mission1() { }

void  Mission1::Pause(){ }

void  Mission1::Resume(){ }

void  Mission1::Update(float dt){
	InputManager instance = InputManager::GetInstance();
	bool trancada = false;
	if(instance.KeyPress(ESCAPE_KEY)){
		popRequested = true;
	}
	//quitRequested = instance.QuitRequested();
	if(instance.KeyPress(SPACE_KEY)){
		std::cout << "SPACE KEY PRESSED" << std::endl;
		if(time.Get() < 23){
			time.Set(23);
		}
		fadeIn = false;
		bloqBlack = true;
		alpha = TRANSPARENT;
		if(spFade.IsOpen()) {
			spFade.ChangeAlpha(alpha);
		}
	}
	//std::cout << time.Get() << std::endl;
	if(time.Get() < 100){
		time.Update(dt);
	}
	if(cooldown.Get() < 5){
		cooldown.Update(dt);
	}

	if(gameOver){
		if(time.Get() > 4){
			Game::GetInstance().GetCurrentState().ChangeMission(1);
		}
	} else{
		if(endMission && time.Get() > (12*0.25)){
			Game::GetInstance().GetCurrentState().ChangeMission(2);
		}

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
		 					Vec2(MissionManager::player->box.x+30,MissionManager::player->box.y+50) );
				MissionManager::enemy->SetDestinationPursuit(((HallState&) Game::GetInstance().
						GetCurrentState()).tileMap.GetPath());
				MissionManager::enemy->seen = false;
			}
			if(MissionManager::missionManager->IsState("LivingRoomState")){
				((LivingRoomState&) Game::GetInstance().GetCurrentState())
					.tileMapChao.PathFind(Vec2(posEnemyX,posEnemyY),
		 					Vec2(MissionManager::player->box.x+30,MissionManager::player->box.y+50) );
				MissionManager::enemy->SetDestinationPursuit(((LivingRoomState&) Game::GetInstance().
						GetCurrentState()).tileMapChao.GetPath());
				MissionManager::enemy->seen = false;
			}

		}

		if(MissionManager::player->lastPicked == "InventoryBear" && MissionManager::enemy->collidingPlayer && !endMission){
			Camera::Unfollow();
			Camera::SetType(CAMERA_TYPE3);
			float x = MissionManager::enemy->box.x;
			float y = MissionManager::enemy->box.y;
			MissionManager::enemy->SetDead();
			MissionManager::player->DeleteInventory();

			Game::GetInstance().GetCurrentState().AddObject(
					new Animation(x, y, 0,
							"img/sprite/mom-bear.png", 12, 0.25, true, 2, 2));
			Sound s = Sound("audio/rasgando.wav");
			s.Play(0);
			time.Restart();
			endMission = true;
		} else if(MissionManager::enemy->collidingPlayer && MissionManager::enemy->show && !endMission){
			//Quando a mae te pega sem vc ter o urso, deixar mais suave
			gameOver = true;
			MissionManager::player->SetBlocked(true);
			MissionManager::player->SetBloqHUD(true);
			MissionManager::player->SetBloqInv(true);
			time.Restart();
			Camera::Follow(MissionManager::player, CAMERA_TYPE1);
			Camera::Zoom(2, true);
		} else{

			/* COMEÇO DO JOGO. QUARTO DA CRIANÇA. PRIMEIRA VEZ ENTRANDO PARA LEGENDAS INICIAIS*/
			if(MissionManager::missionManager->IsState("StageState") &&
					MissionManager::missionManager->countStageState <= 1){

				if(flagTimer == true && time.Get() > 25 && countPega == 0){
					countPega++;
					tx.SetText(" ");
					creepy.SetText(" ");
					creepy1.SetText(" ");
					creepy2.SetText(" ");
					creepy3.SetText(" ");
					creepy4.SetText(" ");
					creepy5.SetText(" ");
					creepy6.SetText(" ");
					showBox = true;
					flagTimer = false;
				}
				if( time.Get() > 30 && trancada == false && cooldown.Get() > 3 && countPega == 1){
					countPega++;
					showBox = true;
					ImageProfileBox (6);
					falas.SetText("ENCONTRE SEU AMIGO QUE O PROTEGE DOS PERIGOS DA NOITE");
					falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
					ultimoTempo = 30; //PARA CONSEGUIR VOLTAR PARA ESSA MENSAGEM NO CASO DA MENSAGEM DE PORTA TRANCADA E OUTRAS MENSAGENS QUE NÃO AFETAM A HISTORIA
				}
				if( time.Get() > 35 && trancada == false && cooldown.Get() > 3 && countPega == 2){
					countPega++;
					falas.SetText(" "); //PARA FAZER TEXTO DESAPARECER. N PODE DEIXAR SEM ESPAÇO DENTRO QUE DÁ ERRO
					ultimoTempo = 35;
					showBox = false;
				}
				if( time.Get() > 50 && trancada == false && cooldown.Get() > 3 && countPega == 3){
					countPega++;
					falas.SetText("TENTE DESMONTAR ALGO PARA ABRIR A PORTA");
					ImageProfileBox (6);
					falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
					ultimoTempo = 50;
					showBox = true;
				}
				if( time.Get() > 54 && trancada == false && cooldown.Get() > 3 && countPega == 4){
					countPega++;
					falas.SetText(" "); //PARA FAZER TEXTO DESAPARECER. N PODE DEIXAR SEM ESPAÇO DENTRO QUE DÁ ERRO
					ultimoTempo = 54;
					showBox = false;
				}
				if( time.Get() > 70 && trancada == false && cooldown.Get() > 3 && countPega == 5){
					countPega++;
					falas.SetText("TALVEZ ALGO QUE ESTEJA NO ALTO DE ALGUM LUGAR"); //PARA FAZER TEXTO DESAPARECER. N PODE DEIXAR SEM ESPAÇO DENTRO QUE DÁ ERRO
					ImageProfileBox (6);
					falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
					ultimoTempo = 70;
					showBox = true;
				}
				if( time.Get() > 74 && trancada == false && cooldown.Get() > 3 && countPega == 6){
					countPega++;
					falas.SetText(" "); //PARA FAZER TEXTO DESAPARECER. N PODE DEIXAR SEM ESPAÇO DENTRO QUE DÁ ERRO
					ultimoTempo = 74;
					showBox = false;
				}
				if( time.Get() > 80 && trancada == false && cooldown.Get() > 3 && countPega == 7){
					countPega++;
					falas.SetText("PENA QUE VOCÊ É BAIXINHO"); //PARA FAZER TEXTO DESAPARECER. N PODE DEIXAR SEM ESPAÇO DENTRO QUE DÁ ERRO
					falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
					ImageProfileBox (6);
					ultimoTempo = 80;
					showBox = true;
				}
				if( time.Get() > 84 && trancada == false && cooldown.Get() > 3 && countPega == 8){
					countPega++;
					falas.SetText(" "); //PARA FAZER TEXTO DESAPARECER. N PODE DEIXAR SEM ESPAÇO DENTRO QUE DÁ ERRO
					ultimoTempo = 84;
					showBox = false;
				}
				if( time.Get() > 90 && trancada == false && cooldown.Get() > 3 && countPega == 9){
					countPega++;
					ImageProfileBox (6);
					falas.SetText("TALVEZ ESSA CADEIRA POSSA AJUDAR"); //PARA FAZER TEXTO DESAPARECER. N PODE DEIXAR SEM ESPAÇO DENTRO QUE DÁ ERRO
					falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
					ultimoTempo = 90;
					showBox = true;
				}
				if( time.Get() > 94 && trancada == false && cooldown.Get() > 3 && countPega == 10){
					countPega++;
					falas.SetText(" "); //PARA FAZER TEXTO DESAPARECER. N PODE DEIXAR SEM ESPAÇO DENTRO QUE DÁ ERRO
					ultimoTempo = 94;
					showBox = false;
				}
				MessageDoor(dt);

				//TROCANDO DE COMODO. ENTRANDO NO CORREDOR PELA PRIMEIRA VEZ
			} else if(MissionManager::missionManager->IsState("HallState") &&
					MissionManager::missionManager->countHallState <= 1){

				if(state != MissionManager::missionManager->changeState){
					state = MissionManager::missionManager->changeState;
					MissionManager::enemy->SetPosition(975,115);
					MissionManager::enemy->show = false;
					time.Restart();
					countPega = 0;
				}
				if(trancada == false && cooldown.Get() > 4 && MissionManager::enemy->show == false && countPega == 0){
					countPega++;
					falas.SetText("CUIDADO");
					showBox = true;
					falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
					ultimoTempo = 4;
				}
				if(time.Get() > 6 && trancada == false && cooldown.Get() > 3 && MissionManager::enemy->show == false && countPega == 1){
					countPega++;
					falas.SetText(" ");
					showBox = false;
					falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
					ultimoTempo = 6;
				}
				if(time.Get() > 5 && time.Get() < 6 && played == false){
					Sound portaDestrancando = Sound ("audio/destrancando.wav");
					portaDestrancando.Play(0);
					played = true;
				}
				if(time.Get() > 6 && time.Get() < 7 && played == true){
					Sound portaDestrancando = Sound ("audio/weird-door.wav");
					portaDestrancando.Play(0);
					played = false;
					//SceneDoor::count = ABRE;
				}

				if(((time.Get() > 7 || MissionManager::player->GetRuido() > 90 ) && trancada == false)){
					//DEFINIR CAMINHO DA MÃE NA PRIMEIRA VEZ QUE CHAMA A FUNÇÃO UPDATE DE MISSION1 NO GAME LOOP
					if(countPega2 == 0){
						countPega2++;
						MissionManager::enemy->show = true;
						//MOVIMENTO É COLOCADO DE TRÁS PARA FRENTE
						SceneDoor::count = ABRE;
						SceneDoor::ValorPassar = 16;
						//MissionManager::enemy->SetDestinationPath(Vec2(970, 100)); //4º DESTINO
						MissionManager::enemy->SetDestinationPath(Vec2(970, 140)); //3º DESTINO
						MissionManager::enemy->SetDestinationPath(Vec2(500, 140)); //2º DESTINO
						MissionManager::enemy->SetDestinationPath(Vec2(500, 110)); //1º DESTINO
					}
					if(time.Get() > 8 && trancada == false && cooldown.Get() > 3 && countPega2 == 1){
						countPega2++;
						showBox = true;
						SceneDoor::count = ABRE;
						SceneDoor::ValorPassar = 26;
						ImageProfileBox (1);
						falas.SetText("É MELHOR QUE NÃO TENHA SAÍDO DA CAMA!!");
						falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
						Sound portaDestrancando = Sound ("audio/ghostly-whispers.wav");
						portaDestrancando.Play(0);
						ultimoTempo = 8;
					}
					if(time.Get() > 12 && trancada == false && cooldown.Get() > 3 && countPega2 == 2){
						countPega2++;
						showBox = false;
						ImageProfileBox (6);
						falas.SetText(" ");
						falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
						ultimoTempo = 12;
						//SceneDoor::count = ABRE;
					}
					if(MissionManager::enemy->box.Inside(Rect(970, 100, 20, 20))){
						//SceneDoor::count = FECHA;
					}
				}
				MessageDoor(dt);

				//NO CASO DE JOGADOR VOLTAR PARA QUARTO DA CRIANÇA
			} else if(MissionManager::missionManager->IsState("StageState") &&
					MissionManager::missionManager->countStageState > 1){

				if(state != MissionManager::missionManager->changeState){
					state = MissionManager::missionManager->changeState;
					time.Restart();
					MissionManager::enemy->show = false;
					countPega = 0;
				}
				if(trancada == false && cooldown.Get() > 3 && countPega == 0){
					countPega++;
					showBox = true;
					ImageProfileBox (6);
					falas.SetText("CERTEZA QUE QUER PASSAR A NOITE SEM PROTEÇÃO?");
					falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
				}
				if(time.Get() > 7 && trancada == false && cooldown.Get() > 3 && countPega == 1){
					countPega++;
					showBox = false;
					falas.SetText(" ");
					falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
				}
				MessageDoor(dt);

			} else if((MissionManager::missionManager->IsState("HallState") &&
					MissionManager::missionManager->countHallState > 1)){

				if(state != MissionManager::missionManager->changeState){
					state = MissionManager::missionManager->changeState;
					time.Restart();
					countPega = 0;
				}
				if(time.Get() < 4 && trancada == false && cooldown.Get() > 3 && countPega == 0){
					countPega++;
					showBox = false;
					falas.SetText(" ");
					falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
				}

			} else if(MissionManager::missionManager->IsState("LivingRoomState")){

				if(state != MissionManager::missionManager->changeState){
					state = MissionManager::missionManager->changeState;
					time.Restart();
					MissionManager::enemy->show = false;
					countPega = 0;
				}
				if(MissionManager::player->lastPicked == "InventoryBear" && trancada == false && MissionManager::enemy->show == false){
					MissionManager::enemy->PathFlush();
					MissionManager::enemy->SetPosition(230, 175);
					MissionManager::enemy->show = true;
					time.Restart();
					MissionManager::player->SetBlocked(true);
					showBox = true;
					ImageProfileBox (1);
					falas.SetText("NADA DE TAIS BRINQUEDOS INFANTIS");
					falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
					MissionManager::player->SetBloqHUD(false);
				}
				if(time.Get() > 2 && MissionManager::enemy->show == true && countPega == 0){
					countPega++;
					MissionManager::player->SetBloqHUD(true);

					Camera::Follow(MissionManager::enemy, CAMERA_TYPE1);
					SceneDoor::count = ABRE;
					SceneDoor::ValorPassar = 4;
					((LivingRoomState&) Game::GetInstance().GetCurrentState())
							.tileMapChao.PathFind(Vec2(MissionManager::enemy->box.x,
								MissionManager::enemy->box.y+MissionManager::enemy->GetHeight()),
								Vec2(MissionManager::player->box.x,MissionManager::player->box.y) );
					MissionManager::enemy->SetDestinationPursuit(((LivingRoomState&) Game::GetInstance().
							GetCurrentState()).tileMapChao.GetPath());

					Camera::Zoom(2, true);
				}

			}
		}

		if(time.Get() >= 24 && fadeIn){
			UpdateVariable(dt, 80);
		}

		if(MissionManager::player->lastPicked == "InventoryBear" && !MissionManager::player->GetBloqInv()){
			SetPiscaPisca(16, 0.4);
			MissionManager::player->SetBloqInv(true);
		}
	}

	PiscaPisca(dt);
}

void  Mission1::Render(){
	//printf("teste2 \n");
	if(time.Get() < 24 && fadeIn){
		blackSquare.Render(0, 0, 0);
		tx.Render(0,0);
		creepy.Render(0,0);
		creepy1.Render(0,0);
		creepy2.Render(0,0);
		creepy3.Render(0,0);
		creepy4.Render(0,0);
		creepy5.Render(0,0);
		creepy6.Render(0,0);
	} else if((time.Get() >= 24 && fadeIn) || !bloqBlack){
		spFade.Render(0, 0, 0);
	}

	if(((MissionManager::missionManager->IsState("StageState") &&
			MissionManager::missionManager->countStageState <= 1 && time.Get() > 25) ||
		((MissionManager::missionManager->IsState("StageState") &&
			MissionManager::missionManager->countStageState > 1) ||
			MissionManager::missionManager->IsState("HallState")||
			MissionManager::missionManager->IsState("LivingRoomState"))) &&
		!MissionManager::player->GetBloqHUD()){

		if(showBox){
			falasBox.Render(falasBoxRect.x, falasBoxRect.y, 0);
			profileBox.Render(profileBoxX, profileBoxY, 0);
			//printf("renderizando");
		}
		falas.Render(0,0);
	}

}


//!!!!!!!!! Colocar MovingObject por ultimo em todos os casos
void Mission1::SetObjectStage(){
	SceneDoor* Door = new SceneDoor(800, 200, "HallState");
	objectStage.emplace_back(Door);

	SceneObject* Bau = new SceneObject(370, 490, "img/cenario/geral/bau-fechado.png",
			"img/cenario/geral/bau-aberto.png", 0, 1, 1, "", SceneObject::SAMEY_UP);
	objectStage.emplace_back(Bau);

	PickUpObject* Clown = new PickUpObject(462, 270, "InventoryClown",
			"img/cenario/geral/palhaco-dentro-caixa.png", true, 0.4, 0.4);
	objectStage.emplace_back(Clown);

	MovingObject* Banco1 = new MovingObject(860, 450, "img/cenario/sala/banquinho.png", true);
	objectStage.emplace_back(Banco1);

	MovingObject* Cadeira = new MovingObject(665, 350, "img/cenario/geral/cadeira.png", true);
	objectStage.emplace_back(Cadeira);
}

void Mission1::SetObjectHall(){
	SceneObject* CriadoMudo = new SceneObject(100, 160,
			"img/cenario/filho/criado-fechado.png", "img/cenario/filho/criado-aberto.png");
	objectHall.emplace_back(CriadoMudo);

	SceneDoor* DoorToMomRoom = new SceneDoor(970, 105, "MomRoomState", true,
			"img/cenario/geral/door-closed.png", "img/cenario/geral/door-opened.png", -1);
	objectHall.emplace_back(DoorToMomRoom);

	StealthObject* Armario2 = new StealthObject(1400, 110, "img/cenario/geral/armario-corredor-fechado.png");
	objectHall.emplace_back(Armario2);

	//PickUpObject* Key = new PickUpObject(1200, 500, "InventoryKey", "img/inventario/key.png");
	//objectHall.emplace_back(Key);

	//PickUpObject* Bear = new PickUpObject(1000, 300, "InventoryBear", "img/inventario/bear.png",false, 1.5, 1.5);
	//objectHall.emplace_back(Bear);

	MovingObject* Vase = new MovingObject(1300, 450, "img/cenario/geral/vaso.png");
	objectHall.emplace_back(Vase);

	MovingObject* Banco = new MovingObject(100, 470, "img/cenario/sala/banquinho.png", true);
	objectHall.emplace_back(Banco);

	SceneObject* PoteRacao = new SceneObject(80, 300,
				"img/cenario/corredor/pote-com-racao.png", "img/cenario/corredor/pote-com-racao.png");
	objectHall.emplace_back(PoteRacao);
	SceneObject* PoteAgua = new SceneObject(80, 350,
					"img/cenario/corredor/pote-sem-racao.png", "img/cenario/corredor/pote-sem-racao.png");
		objectHall.emplace_back(PoteAgua);
}

void Mission1::SetObjectLivingRoom(){
	SceneObject* gatinho = new SceneObject(200, 500,"img/inventario/novelo.png", "", true, 0.5, 0.5);
	objectLivingRoom.emplace_back(gatinho);

	SceneObject* Bau = new SceneObject(250, 500, "img/cenario/geral/bau-fechado.png",
			"img/cenario/geral/bau-aberto.png", 0, 1, 1, "InventoryBear", SceneObject::SAMEY_UP);
	objectLivingRoom.emplace_back(Bau);

	MovingObject* Banco1 = new MovingObject(510, 470, "img/cenario/sala/banquinho.png", true);
	objectLivingRoom.emplace_back(Banco1);

	MovingObject* Banco2 = new MovingObject(570, 470, "img/cenario/sala/banquinho.png", true);
	objectLivingRoom.emplace_back(Banco2);
}

void Mission1::SetObjectMomRoom(){

}
