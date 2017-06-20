#include "Mission1.hpp"
#include "PickUpObject.hpp"
#include "SceneWindow.hpp"
#include "StealthObject.hpp"
#include "SceneDoor.hpp"

#include <iostream>

Mission1::Mission1() : Mission() {
	initialState = "StageState";
	initialX = 600; initialY = 400;
	MissionManager::missionManager->SetPos(initialX, initialY);

	MissionManager::missionManager->countHallState = 0;
	MissionManager::missionManager->countStageState = 0;

	//StageState = 0;
	//HallState = 0;
	//trancada = false;
	//begin = true;
	//count = 0;

	SDL_Color auxcolor = SDL_Color();
	auxcolor.r = 102;
	auxcolor.g = 0;
	auxcolor.b = 0;

	//flagTimer = true; //stopMusic = false;
	//time = Timer();
	//cooldown = Timer();
	tx = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "NOITE 1", auxcolor, 0, 0);
	tx.SetPos(0, 0, true, true);
	creepy = Text("font/uwch.ttf", 30, Text::TextStyle::BLENDED, "\"Cobri vossos utensílios e amarrai vossos cantis...\"", auxcolor, 0, 0);
	creepy.SetPos(0, Game::GetInstance().GetHeight()-40, true, false);

	falas = Text("font/AA_typewriter.ttf", 30, Text::TextStyle::BLENDED , "A NOITE É FRIA E PERIGOSA", auxcolor, 0, 0);
	falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
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

void Mission1::SetObjectStage(){
	SceneWindow* Window = new SceneWindow(350, 200);
	objectStage.emplace_back(Window);
	StealthObject* Stealth = new StealthObject(700, 500, "img/scene-escrivaninha-fechado.png");
	objectStage.emplace_back(Stealth);
	PickUpObject* PO = new PickUpObject(700, 300, "InventoryKey", "img/minionbullet1.png");
	objectStage.emplace_back(PO);
	PickUpObject* Clown = new PickUpObject(400, 400, "InventoryClown", "img/key.png");
	objectStage.emplace_back(Clown);
	MovingObject* Box = new MovingObject(400, 500, "img/scene-cadeira.png");
	objectStage.emplace_back(Box);
}

void Mission1::SetObjectHall(){
	SceneWindow* Window = new SceneWindow(350, 70);
	objectHall.emplace_back(Window);
	PickUpObject* PO = new PickUpObject(500, 400, "InventoryKey", "img/minionbullet1.png");
	objectHall.emplace_back(PO);
	Enemy* E = new Enemy(500, 110);
	objectHall.emplace_back(E);
	PickUpObject* Bear = new PickUpObject(100, 200, "InventoryBear", "img/object-bear.png");
	objectHall.emplace_back(Bear);
}

void Mission1::SetObjectRoom(){

}

void  Mission1::Update(float dt){

	InputManager instance = InputManager::GetInstance();
	bool trancada = false;
	if(instance.KeyPress(ESCAPE_KEY)){
		popRequested = true;
	}
	//quitRequested = instance.QuitRequested();
	if(instance.KeyPress(SPACE_KEY)){
		std::cout << "SPACE KEY PRESSED" << std::endl;
		if(time.Get() < 3 ){
			time.Set(3);
			begin = false;
		}
	}
	time.Update(dt);
	cooldown.Update(dt);
	//std::cout << "time: " << time.Get() << std::endl;
	if(time.Get() > 3 ){
		begin = false;
	}

	/* COMEÇO DO JOGO. QUARTO DA CRIANÇA. PRIMEIRA VEZ ENTRANDO PARA LEGENDAS INICIAIS*/
	if(MissionManager::missionManager->GetStage("StageState") &&
			MissionManager::missionManager->countStageState <= 1){
		//StageState++;
		//std::cout << "StageState" << std::endl;
		if(flagTimer == true && time.Get() > 3){
			tx.SetText(" ");
			creepy.SetText(" ");
			//time.Restart();
			flagTimer = false;
		}
		if( time.Get() > 5.5 && trancada == false && cooldown.Get() > 2/* && ultimoTempo < 5.5*/){
			falas.SetText("ENCONTRE SEU AMIGO QUE O PROTEGE DOS PERIGOS DA NOITE");
			falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
			ultimoTempo = 5.5; //PARA CONSEGUIR VOLTAR PARA ESSA MENSAGEM NO CASO DA MENSAGEM DE PORTA TRANCADA E OUTRAS MENSAGENS QUE NÃO AFETAM A HISTORIA

			//flagTimer = true;
		}

		if( time.Get() > 7 && trancada == false && cooldown.Get() > 2/* && ultimoTempo < 7 && ultimoTempo > 5.5*/){
			falas.SetText(" "); //PARA FAZER TEXTO DESAPARECER. N PODE DEIXAR SEM ESPAÇO DENTRO QUE DÁ ERRO
			ultimoTempo = 7;
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
		if(trancada == false && cooldown.Get() > 2)
			falas.SetText("CUIDADO");
			falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
			ultimoTempo = 0;
		if(time.Get() > 3 && trancada == false && cooldown.Get() > 2){
			falas.SetText(" ");
			falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
			ultimoTempo = 3;
		}
		//MÃE APARECENDO NO CORREDOR
		if((time.Get()>6 && (time.Get() < 8 || MissionManager::player->GetRuido()>85 ))&& trancada == false){
			Enemy::show = true;
			//if(Enemy::turn == 1)
			count ++;
			//DEFINIR CAMINHO DA MÃE NA PRIMEIRA VEZ QUE CHAMA A FUNÇÃO UPDATE DE MISSION1 NO GAME LOOP
			if(count == 1){
				//MOVIMENTO É COLOCADO DE TRÁS PARA FRENTE
				Enemy::enemy->SetDestinationPath(Vec2(900, 100)); //4º DESTINO
				Enemy::enemy->SetDestinationPath(Vec2(900, 140)); //3º DESTINO
				Enemy::enemy->SetDestinationPath(Vec2(500, 140)); //2º DESTINO
				Enemy::enemy->SetDestinationPath(Vec2(500, 110)); //1º DESTINO
			}
			if(trancada == false)
				if(time.Get() > 7 && trancada == false && cooldown.Get() > 2){
					falas.SetText("M: É MELHOR QUE NÃO TENHA SAÍDO DA CAMA!!");
					falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
					ultimoTempo = 7;
				if(time.Get() > 8 && trancada == false && cooldown.Get() > 2){
					falas.SetText(" ");
					falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
					ultimoTempo = 8;
				}
			}
		}

		MessageDoor(dt);
		//NO CASO DE JOGADOR VOLTAR PARA QUARTO DA CRIANÇA
	} else if(MissionManager::missionManager->GetStage("StageState") &&
			MissionManager::missionManager->countStageState > 1){
		if(state != MissionManager::missionManager->changeState){
					state = MissionManager::missionManager->changeState;
					time.Restart();
		}
		if(trancada == false && cooldown.Get() > 2){
			falas.SetText("CERTEZA QUE QUER PASSAR A NOITE SEM PROTEÇÃO?");
			falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
		}
		if(time.Get() > 3 && trancada == false && cooldown.Get() > 2){
			falas.SetText(" ");
			falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
		}
		MessageDoor(dt);
	}

}
//MENSAGEM DE PORTA TRANCADA
/*void Mission1::MessageDoor(float dt){
	if(MissionManager::player->GetDoor() && trancada == false){
				falas.SetText("ESTÁ TRANCADA");
				falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
				trancada = true;
				MissionManager::player->SetDoor(false);
				cooldown.Restart();
				time.Restart();
				while(time.Get()< ultimoTempo){
					time.Update(dt);
				}
			}


			if(cooldown.Get() > 2 && trancada == true){
				//cooldown.Restart();
				falas.SetText(" ");
				trancada = false;
				cooldown.Restart();
				time.Restart();
				while(time.Get()< ultimoTempo){
					time.Update(dt);
				}
			}

}*/
void  Mission1::Render(){
	//printf("teste2 \n");
	if(time.Get() < 3 && begin ){
		blackSquare.Render(0, 0, 0);
		tx.Render(0,0);
		creepy.Render(0,0);
	}

	if(MissionManager::missionManager->GetStage("StageState") &&
			MissionManager::missionManager->countStageState <= 1 && time.Get() > 4){
		falas.Render(0,0);
	}
	if((MissionManager::missionManager->GetStage("StageState") &&
			MissionManager::missionManager->countStageState > 1)
		||MissionManager::missionManager->GetStage("HallState")){
		falas.Render(0,0);
	}

}

void  Mission1::Pause(){
}

void  Mission1::Resume(){
}
