#include "Mission2.hpp"
#include "PickUpObject.hpp"
#include "StealthObject.hpp"
#include "SceneDoor.hpp"
#include "MissionManager.hpp"

 Music Mission2::music;

Mission2::Mission2() : Mission() {
	initialState = "StageState";
	initialX = 450; initialY = 400;
	MissionManager::missionManager->SetPos(initialX, initialY);

	SDL_Color auxcolor = SDL_Color();
	auxcolor.r = 102;
	auxcolor.g = 0;
	auxcolor.b = 0;

	tx = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "NOITE 2", auxcolor, 0, 0);
	tx.SetPos(0, 0, true, true);
	creepy = Text("font/uwch.ttf", 25, Text::TextStyle::BLENDED, "\"fechai as portas, mantende crianças por perto à  noite...\"", auxcolor, 0, 0);
	creepy.SetPos(0, Game::GetInstance().GetHeight()-30, true, false);

	//falas = Text("font/AA_typewriter.ttf", 30, Text::TextStyle::BLENDED , "A NOITE Ã‰ FRIA E PERIGOSA", auxcolor, 0, 0);
	//falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
	//ultimoTempo = 3;
		/*intro = Music("audio/menu-intro.wav");
		music = Music("audio/menu-loop.wav");
		intro.Play(1);
		Mix_HookMusicFinished(&TitleState::LinkMusic);*/

	//Sound intro("audio/boom.wav");
	//intro.Play(1);


	//Mix_HookMusicFinished(&Mission2::LinkMusic);
	SetObjectStage();
	SetObjectHall();
}

Mission2::~Mission2() {

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
		if(time.Get() < 3){
			time.Set(3);
			begin = false;
		}
		bloqBlack = true;
		fadeIn = false;
	}
	time.Update(dt);
	cooldown.Update(dt);
	//std::cout << "time: " << time.Get() << std::endl;
	if(time.Get() > 6){
		begin = false;
		fadeIn = false;
	}

	//URSO APARECE BATENDO NA PORTA. BOTAR SOM DE PORTA TENTANDO ABRIR ANTES DE ELE FALAR
	if(MissionManager::missionManager->GetStage("StageState") &&
			MissionManager::missionManager->countStageState <= 1){
			//StageState++;
			//std::cout << "StageState" << std::endl;
			if(flagTimer == true && time.Get() > 3){
				tx.SetText(" ");
				creepy.SetText(" ");
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
				ultimoTempo = 6.5; //PARA CONSEGUIR VOLTAR PARA ESSA MENSAGEM NO CASO DA MENSAGEM DE PORTA TRANCADA E OUTRAS MENSAGENS QUE NÃƒO AFETAM A HISTORIA

				//flagTimer = true;
			}

			if( time.Get() > 8 && trancada == false && cooldown.Get() > 2/* && ultimoTempo < 7 && ultimoTempo > 5.5*/){
				falas.SetText(" "); //PARA FAZER TEXTO DESAPARECER. N PODE DEIXAR SEM ESPAÃ‡O DENTRO QUE DÃ� ERRO
				ultimoTempo = 7;
			}
			if(trancada == true)
				std::cout << "porta destrancada" << std::endl;

			MessageDoor(dt);
			//TROCANDO DE COMODO. ENTRANDO NO CORREDOR PELA PRIMEIRA VEZ
	}

	if(time.Get() >= 3 && begin && fadeIn){
		UpdateVariable(dt, 80);
	}

	if(time.Get() >= 6){
		PiscaPisca(dt, 6, 0.6);
	}

}

void Mission2::Render(){
	if(time.Get() < 3 && begin){
		blackSquare.Render(0, 0, 0);
		tx.Render(0,0);
		creepy.Render(0,0);
	} else if((time.Get() >= 3 && begin && fadeIn) || !bloqBlack){
		spFade.Render(0,0,0);
	}
}

void Mission2::SetObjectStage(){
	SceneObject* Bau = new SceneObject(300, 480,  "img/scene-bau-fechado.png", "img/scene-bau-fechado.png");
	objectStage.emplace_back(Bau);
	MovingObject* Box = new MovingObject(400, 500, "img/box.png");
	objectStage.emplace_back(Box);
	MovingObject* Cadeira = new MovingObject(730, 300, "img/scene-cadeira.png");
	objectStage.emplace_back(Cadeira);
}

void Mission2::SetObjectHall(){
	SceneObject* Window = new SceneObject(350, 70, "img/closedwindow.png", "img/openwindow.png");
	objectHall.emplace_back(Window);
}

void Mission2::SetObjectRoom(){

}

void Mission2::Pause(){
	//stopMusic = true;
	//intro.Stop();
	music.Stop();
}

void Mission2::Resume(){
	//Game::GetInstance().GetMissionManager().DeleteStates();
	//stopMusic = false;
	//intro.Play(1);
	music.Play(-1);
}
