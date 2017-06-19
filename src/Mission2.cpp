#include "Mission2.hpp"
#include "PickUpObject.hpp"
#include "SceneWindow.hpp"
#include "StealthObject.hpp"
#include "SceneDoor.hpp"
#include "MissionManager.hpp"

Mission2::Mission2() : Mission() {
	initialState = "StageState";
	initialX = 450; initialY = 400;
	MissionManager::missionManager->SetPos(initialX, initialY);

	SDL_Color auxcolor = SDL_Color();
	auxcolor.r = 102;
	auxcolor.g = 0;
	auxcolor.b = 0;


	tx = Text("font/uwch.ttf", 80, Text::TextStyle::BLENDED, "MISSAO 2", auxcolor, 0, 0);
	tx.SetPos(0, 0, true, true);

	//falas = Text("font/AA_typewriter.ttf", 30, Text::TextStyle::BLENDED , "A NOITE É FRIA E PERIGOSA", auxcolor, 0, 0);
	//falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
	//ultimoTempo = 3;
		/*intro = Music("audio/menu-intro.wav");
		music = Music("audio/menu-loop.wav");
		intro.Play(1);
		Mix_HookMusicFinished(&TitleState::LinkMusic);*/

	SetObjectStage();
	SetObjectHall();
	state = MissionManager::missionManager->changeState;
}

Mission2::~Mission2() {

}

void Mission2::Pause(){

}

void Mission2::Resume(){

}

void Mission2::Update(float dt){

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

	//URSO APARECE BATENDO NA PORTA. BOTAR SOM DE PORTA TENTANDO ABRIR ANTES DE ELE FALAR
	if(MissionManager::missionManager->GetStage("StageState") &&
			MissionManager::missionManager->countStageState <= 1){
			//StageState++;
			//std::cout << "StageState" << std::endl;
			if(flagTimer == true && time.Get() > 3){
				tx.SetText(" ");
			}
			if(flagTimer == true && time.Get() > 4){

				falas.SetText("U: EI.... AQUI... ABRE PRA MIM.");
				falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
				ultimoTempo = 4;
				//time.Restart();
				flagTimer = false;
			}
			if( time.Get() > 6.5 && trancada == false && cooldown.Get() > 2/* && ultimoTempo < 5.5*/){
				falas.SetText("U: ME... AJUDA...");
				falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
				ultimoTempo = 6.5; //PARA CONSEGUIR VOLTAR PARA ESSA MENSAGEM NO CASO DA MENSAGEM DE PORTA TRANCADA E OUTRAS MENSAGENS QUE NÃO AFETAM A HISTORIA

				//flagTimer = true;
			}

			if( time.Get() > 8 && trancada == false && cooldown.Get() > 2/* && ultimoTempo < 7 && ultimoTempo > 5.5*/){
				falas.SetText(" "); //PARA FAZER TEXTO DESAPARECER. N PODE DEIXAR SEM ESPAÇO DENTRO QUE DÁ ERRO
				ultimoTempo = 7;
			}
			if(trancada == true)
				std::cout << "porta destrancada" << std::endl;

			MessageDoor(dt);
			//TROCANDO DE COMODO. ENTRANDO NO CORREDOR PELA PRIMEIRA VEZ
	}

}

void Mission2::Render(){

}

void Mission2::SetObjectStage(){
	MovingObject* Box = new MovingObject(400, 500, "img/box.png");
	objectStage.emplace_back(Box);

}

void Mission2::SetObjectHall(){

	SceneWindow* Window = new SceneWindow(350, 70);
	objectHall.emplace_back(Window);

}
