#include "Mission1.hpp"
#include "SceneWindow.hpp"

#include <iostream>

Mission1::Mission1() {
	initialState = "StageState";

	SDL_Color auxcolor = SDL_Color();
	auxcolor.r = 205;
	auxcolor.g = 0;
	auxcolor.b = 240;

	flagTimer = true; //stopMusic = false;
	time = Timer();
	tx = Text("font/uwch.ttf", 80, Text::TextStyle::BLENDED, "MISSAO 1", auxcolor, 0, 0);
	tx.SetPos(0, 0, true, true);
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
	SceneWindow* Window = new SceneWindow(350, 200, "img/closedwindow.png", "img/openwindow.png");
	objectStage.emplace_back(Window);
}

void Mission1::SetObjectHall(){
	SceneWindow* Window = new SceneWindow(350, 70, "img/closedwindow.png", "img/openwindow.png");
	objectHall.emplace_back(Window);
}

void  Mission1::Update(float dt){

	InputManager instance = InputManager::GetInstance();

	if(instance.KeyPress(ESCAPE_KEY)){
		popRequested = true;
	}
	//quitRequested = instance.QuitRequested();

	//printf("teste \n");
	time.Update(dt);
	if(time.Get()> 2 && flagTimer == true){
		tx.SetText(" ");
		//time.Restart();
		flagTimer = false;
	}
	/*if(time.Get()> 3 && flagTimer == false){
		tx.SetText("MISSION 1");
		//time.Restart();
		flagTimer = true;
	}*/

}

void  Mission1::Render(){
	//printf("teste2 \n");
	tx.Render(0,0);

}

void  Mission1::Pause(){
}

void  Mission1::Resume(){
}
