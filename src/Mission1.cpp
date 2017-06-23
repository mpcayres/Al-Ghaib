#include "Mission1.hpp"
#include "PickUpObject.hpp"
#include "SceneObject.hpp"
#include "StealthObject.hpp"
#include "SceneDoor.hpp"
#include "Animation.hpp"

#include <iostream>

Mission1::Mission1() : Mission(), played(false), endMission(false) {
	initialState = "StageState";
	initialX = 600; initialY = 400;
	MissionManager::missionManager->SetPos(initialX, initialY);

	//StageState = 0;
	//HallState = 0;
	//trancada = false;
	//begin = true;
	//count = 0;

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
	tx = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "NOITE 1", redwine, 0, 0);
	tx.SetPos(0, 0, true, true);
	creepy = Text("font/uwch.ttf", 30, Text::TextStyle::BLENDED, "\"Cobri vossos utensílios e amarrai vossos cantis...\"", redwine, 0, 0);
	creepy.SetPos(0, Game::GetInstance().GetHeight()-120, true, false);

	falas = Text("font/AA_typewriter.ttf", 25, Text::TextStyle::BLENDED , "A NOITE É FRIA E PERIGOSA", white, 0, 0);
	falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
	/*intro = Music("audio/menu-intro.wav");
	music = Music("audio/menu-loop.wav");
	intro.Play(1);
	Mix_HookMusicFinished(&TitleState::LinkMusic);*/

	SetObjectStage();
	SetObjectHall();

	//std::cout << "INIT_MIS1" << std::endl;
}

Mission1::~Mission1() {

}

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
		if(time.Get() < 3){
			time.Set(3);
			begin = false;
		}
		fadeIn = false;
		bloqBlack = true;
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

	if(endMission && time.Get() > (12*0.25 + 0.5)){
		MissionManager::player->SetBlocked(false);
		Game::GetInstance().GetCurrentState().SetPopRequested();
		Game::GetInstance().GetMissionManager().ChangeMission(2);
	}

	if(MissionManager::player->lastPicked == "InventoryBear" && Enemy::collidingPlayer){
		Camera::Unfollow();
		Camera::SetType(CAMERA_TYPE0);
		Enemy::SetDead();
		MissionManager::player->SetBlocked(true);
		Game::GetInstance().GetCurrentState().AddObject(
				new Animation(MissionManager::player->box.x + MissionManager::player->box.w + 5,
						MissionManager::player->box.y - 10, 0,
						"img/sprite-mom-bear.png", 12, 0.25, true, 2, 2));
		ultimoTempo = time.Get();
		if(time.Get()>ultimoTempo + 4){
			showBox = true;
			falas.SetText("M: NADA DE TAIS BRINQUEDOS INFANTIS");
			falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
		}
		time.Restart();
		endMission = true;
	} else{

		/* COMEÇO DO JOGO. QUARTO DA CRIANÇA. PRIMEIRA VEZ ENTRANDO PARA LEGENDAS INICIAIS*/
		if(MissionManager::missionManager->GetStage("StageState") &&
				MissionManager::missionManager->countStageState <= 1){
			//StageState++;
			//std::cout << "StageState" << std::endl;
			if(flagTimer == true && time.Get() > 5){
				tx.SetText(" ");
				creepy.SetText(" ");
				showBox = true;
				flagTimer = false;
			}
			if( time.Get() > 8 && trancada == false && cooldown.Get() > 3/* && ultimoTempo < 5.5*/){
				showBox = true;
				falas.SetText("ENCONTRE SEU AMIGO QUE O PROTEGE DOS PERIGOS DA NOITE");
				falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
				ultimoTempo = 8; //PARA CONSEGUIR VOLTAR PARA ESSA MENSAGEM NO CASO DA MENSAGEM DE PORTA TRANCADA E OUTRAS MENSAGENS QUE NÃO AFETAM A HISTORIA

				//flagTimer = true;
			}

			if( time.Get() > 12 && trancada == false && cooldown.Get() > 3/* && ultimoTempo < 7 && ultimoTempo > 5.5*/){
				falas.SetText(" "); //PARA FAZER TEXTO DESAPARECER. N PODE DEIXAR SEM ESPAÇO DENTRO QUE DÁ ERRO
				ultimoTempo = 9;
				showBox = false;
			}

			if( time.Get() > 30 && trancada == false && cooldown.Get() > 3/* && ultimoTempo < 7 && ultimoTempo > 5.5*/){
				falas.SetText("TENTE DESMONTAR ALGO PARA ABRIR A PORTA"); //PARA FAZER TEXTO DESAPARECER. N PODE DEIXAR SEM ESPAÇO DENTRO QUE DÁ ERRO
				falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
				ultimoTempo = 30;
				showBox = true;
			}
			if( time.Get() > 34 && trancada == false && cooldown.Get() > 3/* && ultimoTempo < 7 && ultimoTempo > 5.5*/){
				falas.SetText(" "); //PARA FAZER TEXTO DESAPARECER. N PODE DEIXAR SEM ESPAÇO DENTRO QUE DÁ ERRO
				ultimoTempo = 34;
				showBox = false;
			}

			MessageDoor(dt);
			//TROCANDO DE COMODO. ENTRANDO NO CORREDOR PELA PRIMEIRA VEZ
		} else if(MissionManager::missionManager->GetStage("HallState") &&
				MissionManager::missionManager->countHallState <= 1){
			//HallState++;
			//std::cout << "HallState" << std::endl;
			if(state != MissionManager::missionManager->changeState){
				state = MissionManager::missionManager->changeState;
				time.Restart();
			}
			if(trancada == false && cooldown.Get() > 4 && Enemy::show == false)
				falas.SetText("CUIDADO");
				showBox = true;
				falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
				ultimoTempo = 0;
			if(time.Get() > 6 && trancada == false && cooldown.Get() > 3  && Enemy::show == false){
				falas.SetText(" ");
				showBox = false;
				falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
				ultimoTempo = 3;
			}
			//MÃE APARECENDO NO CORREDOR
			if(MissionManager::player->lastPicked == "InventoryBear"  && trancada == false && Enemy::show == false){
				Enemy::show = true;
				//if(MissionManager::player->lastPicked == "InventoryBear"){
				//MissionManager::player->SetBlocked(true);
				Camera::Unfollow();
				Camera::Follow(Enemy::enemy, CAMERA_TYPE1);
				Camera::Zoom(2, true);
				//if(trancada == false && cooldown.Get() > 3){
					showBox = true;
					falas.SetText("M: COMO OUSA? NADA DE TAIS BRINQUEDOS INFANTIS!");
					falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
					ultimoTempo = time.Get();
					std::cout << ultimoTempo << std::endl;
				//}
				if(time.Get() > (ultimoTempo + 5) && trancada == false && cooldown.Get() > 3){
					showBox = false;
					falas.SetText(" ");
					falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
					ultimoTempo = ultimoTempo + 5;
				}
				//Enemy::SetDestinationPath(Vec2(1500, 300));
				//Enemy::SetDestinationPath(Vec2(1500, 300)); //4º DESTINO
				Enemy::enemy->SetDestinationPath(Vec2(1100, 350)); //3º DESTINO
				Enemy::enemy->SetDestinationPath(Vec2(970, 250)); //2º DESTINO
				Enemy::enemy->SetDestinationPath(Vec2(970, 100)); //1º DESTINO
				//}
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
			}

			if(((time.Get() > 7 && (time.Get() < 9 || MissionManager::player->GetRuido()>90 ))&& trancada == false)
					/*&& Enemy::show == false*/){
				Enemy::show = true;
				//if(Enemy::turn == 1)
				count ++;
				//DEFINIR CAMINHO DA MÃE NA PRIMEIRA VEZ QUE CHAMA A FUNÇÃO UPDATE DE MISSION1 NO GAME LOOP
				if(count == 1){
					//MOVIMENTO É COLOCADO DE TRÁS PARA FRENTE
					Enemy::enemy->SetDestinationPath(Vec2(970, 100)); //4º DESTINO
					Enemy::enemy->SetDestinationPath(Vec2(970, 140)); //3º DESTINO
					Enemy::enemy->SetDestinationPath(Vec2(500, 140)); //2º DESTINO
					Enemy::enemy->SetDestinationPath(Vec2(500, 110)); //1º DESTINO
				}
				//std::cout << trancada << std::endl;
				if(trancada == false){
					if(time.Get() > 8 && trancada == false && cooldown.Get() > 3){
						showBox = true;
						falas.SetText("M: É MELHOR QUE NÃO TENHA SAÍDO DA CAMA!!");
						falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
						if(played == false){
							Sound portaDestrancando = Sound ("audio/ghostly-whispers.wav");
							portaDestrancando.Play(0);
							played = true;
						}
						ultimoTempo = 8;
					if(time.Get() > 11 && trancada == false && cooldown.Get() > 3){
						showBox = false;
						falas.SetText(" ");
						falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
						ultimoTempo = 12;
					}
				}
				}
			}

			MessageDoor(dt);
			//NO CASO DE JOGADOR VOLTAR PARA QUARTO DA CRIANÇA
		} else if(MissionManager::missionManager->GetStage("StageState") &&
				MissionManager::missionManager->countStageState > 1){
			//std::cout << MissionManager::missionManager->GetStage("StageState") << std::endl;
			if(state != MissionManager::missionManager->changeState){
						state = MissionManager::missionManager->changeState;
						time.Restart();
			}
			if(trancada == false && cooldown.Get() > 3){
				showBox = true;
				falas.SetText("CERTEZA QUE QUER PASSAR A NOITE SEM PROTEÇÃO?");
				falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
			}
			if(time.Get() > 7 && trancada == false && cooldown.Get() > 3){
				showBox = false;
				falas.SetText(" ");
				falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
			}
			MessageDoor(dt);
		}
		if((MissionManager::missionManager->GetStage("HallState") &&
				MissionManager::missionManager->countHallState > 1)){
			if(time.Get() < 4 && trancada == false && cooldown.Get() > 3){
				showBox = false;
				falas.SetText(" ");
				falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
			}
			if(MissionManager::player->lastPicked == "InventoryBear"  && trancada == false && Enemy::show == false){
				Enemy::show = true;
				//if(MissionManager::player->lastPicked == "InventoryBear"){
				//MissionManager::player->SetBlocked(true);
				Camera::Unfollow();
				Camera::Follow(Enemy::enemy, CAMERA_TYPE1);
				Camera::Zoom(2, true);
				if(time.Get() > 4 && trancada == false && cooldown.Get() > 3){
						showBox = true;
						falas.SetText("M: COMO OUSA? NADA DE TAIS BRINQUEDOS DE CRIANÇA!");
						falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
						ultimoTempo = 3;
				}
				if(time.Get() > 8 && trancada == false && cooldown.Get() > 3){
					showBox = false;
					falas.SetText(" ");
					falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
					ultimoTempo = 6;
				}
				//Enemy::SetDestinationPath(Vec2(1500, 300));
				//Enemy::SetDestinationPath(Vec2(1500, 300)); //4º DESTINO
				Enemy::enemy->SetDestinationPath(Vec2(1100, 350)); //3º DESTINO
				Enemy::enemy->SetDestinationPath(Vec2(970, 140)); //2º DESTINO
				Enemy::enemy->SetDestinationPath(Vec2(970, 100)); //1º DESTINO
				//}
			}
		}
	}

	if(time.Get() >= 4 && begin && fadeIn){
		UpdateVariable(dt, 80);
	}
	if(MissionManager::player->lastPicked == "InventoryBear"){
		//PiscaPisca(dt, 20, 0.4);
	}

}

void  Mission1::Render(){
	//printf("teste2 \n");
	if(time.Get() < 4 && begin){
		blackSquare.Render(0, 0, 0);
		tx.Render(0,0);
		creepy.Render(0,0);
	} else if((time.Get() >= 4 && begin && fadeIn) || !bloqBlack){
		spFade.Render(0, 0, 0);
	}

	if(((MissionManager::missionManager->GetStage("StageState") &&
			MissionManager::missionManager->countStageState <= 1 && time.Get() > 5) ||
		((MissionManager::missionManager->GetStage("StageState") &&
			MissionManager::missionManager->countStageState > 1) ||
			MissionManager::missionManager->GetStage("HallState"))) &&
		!MissionManager::player->bloqHUD){

		if(showBox){
			falasBox.Render(falasBoxRect.x /*- Camera::pos.x*/, falasBoxRect.y /*- Camera::pos.y*/, 0);
			//printf("renderizando");
		}
		falas.Render(0,0);
	}
	if(endMission == true){
		falasBox.Render(falasBoxRect.x /*- Camera::pos.x*/, falasBoxRect.y /*- Camera::pos.y*/, 0);
		falas.Render(0,0);
	}

}

//!!!!!!!!! Colocar MovingObject por ultimo em todos os casos
void Mission1::SetObjectStage(){
	//StealthObject* Escrivaninha = new StealthObject(700, 400, "img/scene-escrivaninha-fechado.png");
	//objectStage.emplace_back(Escrivaninha);

	/*PickUpObject* PO = new PickUpObject(700, 300, "InventoryKey", "img/minionbullet1.png");
	objectStage.emplace_back(PO);*/

	//SceneObject* Armario =  new SceneObject(400, 260, "img/scene-armario-quarto-fechado.png", "img/scene-armario-quarto-fechado.png");
	//objectStage.emplace_back(Armario);

	SceneObject* Bau = new SceneObject(300, 490,  "img/scene-bau-fechado.png", "img/scene-bau-fechado.png", 0, 1, 1, "InventoryKey");
	objectStage.emplace_back(Bau);

	PickUpObject* Clown = new PickUpObject(430, 270, "InventoryClown", "img/key.png", true, 0.5, 0.5);
	objectStage.emplace_back(Clown);

	//MovingObject* Vaso = new MovingObject(900, 300,  "img/scene-vaso.png");
	//objectStage.emplace_back(Vaso);

	MovingObject* Cadeira = new MovingObject(730, 320, "img/scene-cadeira.png");
	objectStage.emplace_back(Cadeira);
}

void Mission1::SetObjectHall(){
	//SceneWindow* Window = new SceneWindow(350, 70);
	//objectHall.emplace_back(Window);
	PickUpObject* Key = new PickUpObject(1200, 500, "InventoryKey", "img/minionbullet1.png");
	objectHall.emplace_back(Key);
	Enemy* E = new Enemy(500, 110);
	objectHall.emplace_back(E);
	PickUpObject* Bear = new PickUpObject(1000, 300, "InventoryBear", "img/object-bear.png",false, 1.5, 1.5);
	objectHall.emplace_back(Bear);
	MovingObject* Vase = new MovingObject(1300, 450, "img/scene-vaso.png");
	objectHall.emplace_back(Vase);
}

void Mission1::SetObjectRoom(){

	PickUpObject* Bear = new PickUpObject(1500, 500, "InventoryBear", "img/object-bear.png",false, 1.5, 1.5);
	objectLivingRoom.emplace_back(Bear);

}
