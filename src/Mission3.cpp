#include "Mission3.hpp"
#include "PickUpObject.hpp"
#include "StealthObject.hpp"
#include "SceneDoor.hpp"
#include "MissionManager.hpp"

 Music Mission3::music;

Mission3::Mission3() : Mission(), paradoUrso(false),paradoGato(false) {
	initialState = "StageState";
	initialX = 450; initialY = 400;
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

	tx = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "NOITE 3", redwine, 0, 0);
	tx.SetPos(0, 0, true, true);
	creepy = Text("font/uwch.ttf", 30, Text::TextStyle::BLENDED, "\"...\"", redwine, 0, 0);
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

	/*if(endMission && time.Get() > (12*0.25 + 0.5)){
		MissionManager::player->SetBlocked(false);
		Game::GetInstance().GetCurrentState().SetPopRequested();
		Game::GetInstance().GetMissionManager().ChangeMission(2);
	}*/
	//URSO APARECE BATENDO NA PORTA. BOTAR SOM DE PORTA TENTANDO ABRIR ANTES DE ELE FALAR
	if(MissionManager::missionManager->GetStage("StageState") &&
			MissionManager::missionManager->countStageState <= 1){


			MessageDoor(dt);
			//TROCANDO DE COMODO. ENTRANDO NO CORREDOR PELA PRIMEIRA VEZ
	}else if(MissionManager::missionManager->GetStage("HallState") &&
							MissionManager::missionManager->countHallState <= 1){
		//HallState++;
		std::cout << MissionManager::missionManager->countHallState << std::endl;
		std::cout << "HallState" << std::endl;
		if(state != MissionManager::missionManager->changeState){
				state = MissionManager::missionManager->changeState;
				time.Restart();
		}

		Cat::show = true;
		countCat++;
		//if(count == 1){
		int dist = Cat::cat->box.DistanceRect(MissionManager::player->box);
		std::cout << "dist" << dist << std::endl;
		/*if(dist < 250)
			Cat::cat->SetDestinationPath(Vec2(980, 200));
		if(dist >= 250){
			std::cout << "maior que 250" << std::endl;
			//Cat::cat->SetDestinationPath(Vec2(1000, 200)); //4º DESTINO
			Cat::cat->SetDestinationPath(Vec2(940, 200)); //3º DESTINO
			Cat::cat->SetDestinationPath(Vec2(1000, 200));
			Cat::cat->SetDestinationPath(Vec2(900, 200)); //2º DESTINO
		}*/
		//}
		//if(Enemy::turn == 1)

		std::cout << "coutCat" << countCat << std::endl;
		if(countCat == 1 && dist > 250){
			//MOVIMENTO É COLOCADO DE TRÁS PARA FRENTE
			std::cout << "ka" << std::endl;
			Cat::cat->SetDestinationPath(Vec2(1000, 200)); //4º DESTINO
			Cat::cat->SetDestinationPath(Vec2(900, 200)); //3º DESTINO
			Cat::cat->SetDestinationPath(Vec2(1000, 200)); //2º DESTINO
			Cat::cat->SetDestinationPath(Vec2(890, 200)); //4º DESTINO
			Cat::cat->SetDestinationPath(Vec2(970, 200)); //3º DESTINO
			Cat::cat->SetDestinationPath(Vec2(1000, 200)); //2º DESTINO
			Cat::cat->SetDestinationPath(Vec2(900, 200)); //1º DESTINO
			//paradoGato = true;
		}
		/*if(dist > 250){
			std::cout << "dist > 250" << std::endl;
			Cat::cat->SetDestinationPath(Vec2(1100, 200)); //2º DESTINO
			Cat::cat->SetDestinationPath(Vec2(940, 200)); //1º DESTINO
		}
		if(dist < 250){
			paradoGato = true;
		}*/
		if( dist < 250){
				Cat::cat->SetDestinationPath(Vec2(980, 200));
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

		if(time.Get() > 7 && time.Get() < 7.5 && trancada == false && cooldown.Get() > 3){
			Sound portaDestrancando = Sound ("audio/meow-sample.wav");
			portaDestrancando.Play(0);
		}
		if (MissionManager::player->GetRuido()>70 ){
			Enemy::show = true;
			SceneDoor::count = ABRE;
			//if(Enemy::turn == 1)
			momcount ++;
			//DEFINIR CAMINHO DA MÃE NA PRIMEIRA VEZ QUE CHAMA A FUNÇÃO UPDATE DE MISSION1 NO GAME LOOP
			if(momcount == 1){
			//MOVIMENTO É COLOCADO DE TRÁS PARA FRENTE
				//Enemy::enemy->SetDestinationPath(Vec2(970, 100)); //4º DESTINO
				Enemy::enemy->SetDestinationPath(Vec2(800, 140)); //3º DESTINO
				Enemy::enemy->SetDestinationPath(Vec2(500, 140)); //2º DESTINO
				Enemy::enemy->SetDestinationPath(Vec2(500, 110)); //1º DESTINO
			}
		}
		if(Enemy::show && time.Get() > ultimoTempo + 2){
			if(momcount == 1){
				falas.SetText("M: O QUE JÁ FALEI SOBRE SAIR DA CAMA?");
				falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
				ultimoTempo = ultimoTempo + 2;
				showBox = true;
			}
		}
		if(Enemy::show && time.Get() > ultimoTempo + 4){
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

void Mission3::Render(){
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

void Mission3::SetObjectStage(){

	SceneObject* Bau = new SceneObject(300, 490,  "img/scene-bau-fechado.png",
			"img/scene-bau-aberto.png", 0, 1, 1, "", SceneObject::SAMEY_UP);
	objectStage.emplace_back(Bau);
	MovingObject* Box = new MovingObject(400, 500, "img/box.png");
	objectStage.emplace_back(Box);
	MovingObject* Cadeira = new MovingObject(730, 300, "img/scene-cadeira.png");
	objectStage.emplace_back(Cadeira);
}

void Mission3::SetObjectHall(){

	Enemy* E = new Enemy(500, 110,"img/sprite-mom-chador.png");
	objectHall.emplace_back(E);
	MovingObject* Vase = new MovingObject(1300, 450, "img/scene-vaso.png");
	objectHall.emplace_back(Vase);
	Cat* gatinho = new Cat(1000, 200);
	objectHall.emplace_back(gatinho);
}

void Mission3::SetObjectRoom(){

}