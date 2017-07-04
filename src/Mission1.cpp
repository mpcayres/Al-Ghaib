#include "Mission1.hpp"
#include "PickUpObject.hpp"
#include "SceneObject.hpp"
#include "StealthObject.hpp"
#include "SceneDoor.hpp"
#include "Animation.hpp"

#include <iostream>

Mission1::Mission1() : Mission(), played(false), endMission(false) {
	num = 0;
	contPega = 0;
	peguei = false;
	initialState = "StageState";
	initialX = 400; initialY = 400;
	MissionManager::missionManager->SetPos(initialX, initialY);
	MissionManager::missionManager->randomStates = false;

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
			time.Set(3);
		}
		fadeIn = false;
		bloqBlack = true;
		alpha = TRANSPARENT;
		if(spFade.IsOpen()) {
			spFade.ChangeAlpha(alpha);
		}
	}
	time.Update(dt);
	cooldown.Update(dt);

	if(endMission && time.Get() > (12*0.25 + 0.5)){
		Game::GetInstance().GetCurrentState().ChangeMission(2);
	}

	if(MissionManager::player->lastPicked == "InventoryBear" && MissionManager::enemy->collidingPlayer && !endMission && peguei){
		//std::cout << "MOM DEAD 0" << std::endl;
		Camera::Unfollow();
		Camera::SetType(CAMERA_TYPE0);
		float x = MissionManager::enemy->box.x;
		float y = MissionManager::enemy->box.y;
		//MissionManager::enemy->show = false;


		//std::cout << "MOM DEAD 1" << std::endl;
		MissionManager::enemy->SetDead();
		//std::cout << "MOM DEAD 2" << std::endl;

		MissionManager::player->SetBlocked(true);
		MissionManager::player->DeleteInventory();
		//std::cout << "MOM DEAD 3" << std::endl;
		Game::GetInstance().GetCurrentState().AddObject(
				new Animation(x, y, 0,
						"img/sprite-mom-bear.png", 12, 0.25, true, 2, 2));
		ultimoTempo = time.Get();
		if(time.Get() > ultimoTempo + 4){
			showBox = true;
			falas.SetText("M: NADA DE TAIS BRINQUEDOS INFANTIS");
			falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
		}
		time.Restart();
		endMission = true;
		//std::cout << "MOM DEAD 4" << std::endl;
	} else if(MissionManager::enemy->collidingPlayer && MissionManager::enemy->show && !endMission){
		//Quando a mae te pega sem vc ter o urso, deixar mais suave
		Game::GetInstance().GetCurrentState().ChangeMission(1);
	} else{

		/* COMEÇO DO JOGO. QUARTO DA CRIANÇA. PRIMEIRA VEZ ENTRANDO PARA LEGENDAS INICIAIS*/
		if(MissionManager::missionManager->GetStage("StageState") &&
				MissionManager::missionManager->countStageState <= 1){
			//StageState++;
			//std::cout << "StageState" << std::endl;
			if(flagTimer == true && time.Get() > 25){
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
			if( time.Get() > 30 && trancada == false && cooldown.Get() > 3/* && ultimoTempo < 5.5*/){
				showBox = true;
				falas.SetText("ENCONTRE SEU AMIGO QUE O PROTEGE DOS PERIGOS DA NOITE");
				falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
				ultimoTempo = 30; //PARA CONSEGUIR VOLTAR PARA ESSA MENSAGEM NO CASO DA MENSAGEM DE PORTA TRANCADA E OUTRAS MENSAGENS QUE NÃO AFETAM A HISTORIA

				//flagTimer = true;
			}

			if( time.Get() > 35 && trancada == false && cooldown.Get() > 3/* && ultimoTempo < 7 && ultimoTempo > 5.5*/){
				falas.SetText(" "); //PARA FAZER TEXTO DESAPARECER. N PODE DEIXAR SEM ESPAÇO DENTRO QUE DÁ ERRO
				ultimoTempo = 35;
				showBox = false;
			}

			if( time.Get() > 50 && trancada == false && cooldown.Get() > 3/* && ultimoTempo < 7 && ultimoTempo > 5.5*/){
				falas.SetText("TENTE DESMONTAR ALGO PARA ABRIR A PORTA");
				falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
				ultimoTempo = 50;
				showBox = true;
			}
			if( time.Get() > 54 && trancada == false && cooldown.Get() > 3/* && ultimoTempo < 7 && ultimoTempo > 5.5*/){
				falas.SetText(" "); //PARA FAZER TEXTO DESAPARECER. N PODE DEIXAR SEM ESPAÇO DENTRO QUE DÁ ERRO
				ultimoTempo = 54;
				showBox = false;
			}

			if( time.Get() > 70 && trancada == false && cooldown.Get() > 3/* && ultimoTempo < 7 && ultimoTempo > 5.5*/){
				falas.SetText("TALVEZ ALGO QUE ESTEJA NO ALTO DE ALGUM LUGAR"); //PARA FAZER TEXTO DESAPARECER. N PODE DEIXAR SEM ESPAÇO DENTRO QUE DÁ ERRO
				falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
				ultimoTempo = 70;
				showBox = true;
			}
			if( time.Get() > 74 && trancada == false && cooldown.Get() > 3/* && ultimoTempo < 7 && ultimoTempo > 5.5*/){
				falas.SetText(" "); //PARA FAZER TEXTO DESAPARECER. N PODE DEIXAR SEM ESPAÇO DENTRO QUE DÁ ERRO
				ultimoTempo = 74;
				showBox = false;
			}

			if( time.Get() > 80 && trancada == false && cooldown.Get() > 3/* && ultimoTempo < 7 && ultimoTempo > 5.5*/){
				falas.SetText("PENA QUE VOCÊ É BAIXINHO"); //PARA FAZER TEXTO DESAPARECER. N PODE DEIXAR SEM ESPAÇO DENTRO QUE DÁ ERRO
				falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
				ultimoTempo = 80;
				showBox = true;
			}
			if( time.Get() > 84 && trancada == false && cooldown.Get() > 3/* && ultimoTempo < 7 && ultimoTempo > 5.5*/){
				falas.SetText(" "); //PARA FAZER TEXTO DESAPARECER. N PODE DEIXAR SEM ESPAÇO DENTRO QUE DÁ ERRO
				ultimoTempo = 84;
				showBox = false;
			}
			if( time.Get() > 90 && trancada == false && cooldown.Get() > 3/* && ultimoTempo < 7 && ultimoTempo > 5.5*/){
				falas.SetText("TALVEZ ESSA CADEIRA POSSA AJUDAR"); //PARA FAZER TEXTO DESAPARECER. N PODE DEIXAR SEM ESPAÇO DENTRO QUE DÁ ERRO
				falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
				ultimoTempo = 90;
				showBox = true;
			}
			if( time.Get() > 94 && trancada == false && cooldown.Get() > 3/* && ultimoTempo < 7 && ultimoTempo > 5.5*/){
				falas.SetText(" "); //PARA FAZER TEXTO DESAPARECER. N PODE DEIXAR SEM ESPAÇO DENTRO QUE DÁ ERRO
				ultimoTempo = 94;
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
				MissionManager::missionManager->player->box.x = 400;
				MissionManager::missionManager->player->box.y = 400;
				time.Restart();
			}
			if(trancada == false && cooldown.Get() > 4 && MissionManager::enemy->show == false)
				falas.SetText("CUIDADO");
				showBox = true;
				falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
				ultimoTempo = 4;
			if(time.Get() > 6 && trancada == false && cooldown.Get() > 3  && MissionManager::enemy->show == false){
				falas.SetText(" ");
				showBox = false;
				falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
				ultimoTempo = 6;
			}
			//MÃE APARECENDO NO CORREDOR
/*
			//COMEÇO MÃE TE PEGANDO  =  AGORA ISSO É NA SALA
			if(MissionManager::player->lastPicked == "InventoryBear"  && trancada == false && MissionManager::enemy->show == false){
				MissionManager::enemy->show = true;
				SceneDoor::count = ABRE;
				SceneDoor::ValorPassar = 4;
				//if(MissionManag+er::player->lastPicked == "InventoryBear"){
				//MissionManager::player->SetBlocked(true);
				Camera::Unfollow();
				Camera::Follow(MissionManager::enemy->enemy, CAMERA_TYPE1);
				Camera::Zoom(2, true);
				//if(trancada == false && cooldown.Get() > 3){
					showBox = true;
					//MissionManager::enemy->bloq = true;
					falas.SetText("M: COMO OUSA? NADA DE TAIS BRINQUEDOS INFANTIS!");
					falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
					ultimoTempo = time.Get();
					//std::cout << ultimoTempo << std::endl;
				//}
				if(time.Get() > (ultimoTempo + 5) && trancada == false && cooldown.Get() > 3){
					showBox = false;
					//MissionManager::enemy->bloq = false;
					falas.SetText(" ");
					falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
					ultimoTempo = ultimoTempo + 5;
				}
				//MissionManager::enemy->SetDestinationPath(Vec2(1500, 300));
				//MissionManager::enemy->SetDestinationPath(Vec2(1500, 300)); //4º DESTINO
				MissionManager::enemy->SetDestinationPath(Vec2(1100, 350)); //3º DESTINO
				MissionManager::enemy->SetDestinationPath(Vec2(970, 250)); //2º DESTINO
				MissionManager::enemy->SetDestinationPath(Vec2(970, 100)); //1º DESTINO
				//}
			}*/

			//FIM MÃE TE PEGANDO




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

			if(((time.Get() > 7 && (time.Get() < 9 || MissionManager::player->GetRuido()>90 ))&& trancada == false)
					/*&& MissionManager::enemy->show == false*/){
				MissionManager::enemy->show = true;
				//if(MissionManager::enemy->turn == 1)
				count ++;
				//SceneDoor::count = FECHA;
				//DEFINIR CAMINHO DA MÃE NA PRIMEIRA VEZ QUE CHAMA A FUNÇÃO UPDATE DE MISSION1 NO GAME LOOP
				if(count == 1){
					//MOVIMENTO É COLOCADO DE TRÁS PARA FRENTE

					SceneDoor::count = ABRE;
					SceneDoor::ValorPassar = 16;
					MissionManager::enemy->SetDestinationPath(Vec2(970, 100)); //4º DESTINO
					MissionManager::enemy->SetDestinationPath(Vec2(970, 140)); //3º DESTINO
					MissionManager::enemy->SetDestinationPath(Vec2(500, 140)); //2º DESTINO
					MissionManager::enemy->SetDestinationPath(Vec2(500, 110)); //1º DESTINO
				}
				//std::cout << trancada << std::endl;
				if(trancada == false){
					if(time.Get() > 8 && trancada == false && cooldown.Get() > 3){
						showBox = true;
						//MissionManager::enemy->bloq = true;
						SceneDoor::count = ABRE;
						SceneDoor::ValorPassar = 26;
						falas.SetText("M: É MELHOR QUE NÃO TENHA SAÍDO DA CAMA!!");
						falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
						if(played == false){
							Sound portaDestrancando = Sound ("audio/ghostly-whispers.wav");
							portaDestrancando.Play(0);
							played = true;
						}
						ultimoTempo = 8;
					if(time.Get() > 12 && trancada == false && cooldown.Get() > 3){
						showBox = false;
						//MissionManager::enemy->bloq = false;
						falas.SetText(" ");
						falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
						ultimoTempo = 12;
						//SceneDoor::count = ABRE;
					}
					if(MissionManager::enemy->box.Inside(Rect(970, 100, 20, 20))){
						//SceneDoor::count = FECHA;
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
		} else if((MissionManager::missionManager->GetStage("HallState") &&
				MissionManager::missionManager->countHallState > 1)){
			if(time.Get() < 4 && trancada == false && cooldown.Get() > 3){
				showBox = false;
				falas.SetText(" ");
				falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
			}

		}else if (MissionManager::missionManager->GetStage("LivingRoomState")){
			if(state != MissionManager::missionManager->changeState){
				MissionManager::player->SetPosition(230, 300);
				state = MissionManager::missionManager->changeState;
				time.Restart();
			}

			if(MissionManager::player->lastPicked == "InventoryBear"  && trancada == false && MissionManager::enemy->show == false){
				MissionManager::enemy->SetPosition(230, 175);
				MissionManager::enemy->show = true;

				//SceneDoor::count = ABRE;
				//SceneDoor::ValorPassar = 4;
				// tentativa fail de fazer mãe parar de andar
				peguei = true; //era da tentativa fail;
				MissionManager::enemy->SetDestinationPath(Vec2(230, 230));
/*
				contPega++;
				if(contPega == 0)
					num = (int)time.Get();
				if(num + 500 > time.Get()){
					time.Update(dt);
					MissionManager::enemy->SetDestinationPath(Vec2(230, 180));
					//std::cout << time.Get() << " e " << num << std::endl;
					MissionManager::player->SetBlocked(true);
					showBox = true;
					falas.SetText("M: NADA DE TAIS BRINQUEDOS INFANTIS");
					falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
				}
				else{
					peguei = true;
					showBox = false;
					falas.SetText(" ");
					MissionManager::enemy->SetDestinationPath(Vec2(230, 300));
					Camera::Zoom(2, true);
				}*/
				Camera::Zoom(2, true);
				//if(MissionManager::player->lastPicked == "InventoryBear"){
				//MissionManager::player->SetBlocked(true);
				//Camera::Unfollow();

				//Camera::Follow(MissionManager::enemy, CAMERA_TYPE1);

				//if(trancada == false && cooldown.Get() > 3){
				//showBox = true;
				//MissionManager::enemy->bloq = true;
				/*falas.SetText("M: COMO OUSA? NADA DE TAIS BRINQUEDOS INFANTIS!");
				falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
				ultimoTempo = time.Get();
				//std::cout << ultimoTempo << std::endl;
				//}
				if(time.Get() > (ultimoTempo + 5) && trancada == false && cooldown.Get() > 3){
					showBox = false;
					//MissionManager::enemy->bloq = false;
					falas.SetText(" ");
					falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
					ultimoTempo = ultimoTempo + 5;
				}*/
					//MissionManager::enemy->SetDestinationPath(Vec2(1500, 300));
					//MissionManager::enemy->SetDestinationPath(Vec2(1500, 300)); //4º DESTINO
					//MissionManager::enemy->SetDestinationPath(Vec2(350, 490)); //3º DESTINO
					//MissionManager::enemy->SetDestinationPath(Vec2(350, 300)); //2º DESTINO
					//MissionManager::enemy->SetDestinationPath(Vec2(230, 300)); //1º DESTINO
					//}
			}

		}
	}

	if(time.Get() >= 24 && fadeIn){
		UpdateVariable(dt, 80);
	}

	if(MissionManager::player->lastPicked == "InventoryBear" && !MissionManager::player->GetBloqInv()){
		PiscaPisca(dt, 20, 0.4);
		MissionManager::player->SetBloqInv(true);
	}

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

	if(((MissionManager::missionManager->GetStage("StageState") &&
			MissionManager::missionManager->countStageState <= 1 && time.Get() > 25) ||
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

	SceneDoor* Door = new SceneDoor(800, 200, "HallState");
	objectStage.emplace_back(Door);

	SceneObject* Bau = new SceneObject(300, 490,  "img/scene-bau-fechado.png",
			"img/scene-bau-aberto.png", 0, 1, 1, "InventoryKey", SceneObject::SAMEY_UP);
	objectStage.emplace_back(Bau);

	PickUpObject* Clown = new PickUpObject(462, 270, "InventoryClown",
			"img/object-caixa-sem-palhaco.png", true, 0.4, 0.4);
	objectStage.emplace_back(Clown);

	//MovingObject* Vaso = new MovingObject(900, 300,  "img/scene-vaso.png");
	//objectStage.emplace_back(Vaso);

	MovingObject* Cadeira = new MovingObject(700, 320, "img/scene-cadeira.png", true);
	objectStage.emplace_back(Cadeira);
}

void Mission1::SetObjectHall(){
	//SceneWindow* Window = new SceneWindow(350, 70);
	//objectHall.emplace_back(Window);

	SceneObject* CriadoMudo = new SceneObject(100, 160, "img/scene-criado-fechado.png", "img/scene-criado-aberto.png");
	objectHall.emplace_back(CriadoMudo);

	SceneDoor* DoorToMomRoom = new SceneDoor(970, 105, "StageState", true,
			"img/scene-door-closed.png", "img/scene-door-opened.png", -1);
	objectHall.emplace_back(DoorToMomRoom);

	StealthObject* Armario2 = new StealthObject(1400, 110, "img/scene-armario-corredor-fechado.png");
	objectHall.emplace_back(Armario2);

	PickUpObject* Key = new PickUpObject(1200, 500, "InventoryKey", "img/object-key.png");
	objectHall.emplace_back(Key);

	//PickUpObject* Bear = new PickUpObject(1000, 300, "InventoryBear", "img/object-bear.png",false, 1.5, 1.5);
	//objectHall.emplace_back(Bear);

	MovingObject* Vase = new MovingObject(1300, 450, "img/scene-vaso.png");
	objectHall.emplace_back(Vase);

	MovingObject* Banco = new MovingObject(100, 470, "img/moveis/sala/banquinho.png", true);
	objectHall.emplace_back(Banco);
}

void Mission1::SetObjectLivingRoom(){
	//PickUpObject* Bear = new PickUpObject(1500, 500, "InventoryBear", "img/object-bear.png",false, 1.5, 1.5);
	//objectLivingRoom.emplace_back(Bear);

	SceneObject* gatinho = new SceneObject(200, 500,"img/object-novelo.png", "img/object-novelo.png", true, 0.5, 0.5);
	objectLivingRoom.emplace_back(gatinho);

	SceneObject* Bau = new SceneObject(400, 500,  "img/scene-bau-fechado.png",
				"img/scene-bau-aberto.png", 0, 1, 1, "InventoryBear", SceneObject::SAMEY_UP);
	objectLivingRoom.emplace_back(Bau);

	MovingObject* Banco = new MovingObject(650, 370, "img/moveis/sala/banquinho.png", true);
	objectLivingRoom.emplace_back(Banco);


}
