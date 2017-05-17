#include "TitleState.hpp"
#include "Game.hpp"
#include "StageState.hpp"
#include "InputManager.hpp"

TitleState::TitleState() : menu(50, 50) {
	SDL_Color auxcolor = SDL_Color();
	auxcolor.r = 0;
	auxcolor.g = 70;
	auxcolor.b = 150;

	flagTimer = true;
	time = Timer();
	bg = Sprite("img/title.jpg");
	tx = Text("font/Call me maybe.ttf", 64, Text::TextStyle::BLENDED, "Press space to continue", auxcolor, 0, 0);
	tx.SetPos(0, 0, true, true);
}

void TitleState::Update(float dt){
	InputManager instance = InputManager::GetInstance();

	if(instance.KeyPress(ESCAPE_KEY)) quitRequested = true;
	else quitRequested = instance.QuitRequested();

	time.Update(dt);

	if(time.Get()> 0.15 && flagTimer == true){
		tx.SetText(" ");
		time.Restart();
		flagTimer = false;
	}
	if(time.Get()> 0.15 && flagTimer == false){
		tx.SetText("Press space to continue");
		time.Restart();
		flagTimer = true;
	}

	menu.Update(dt);
	if(menu.IsSelected()){
		menu.SetSelected(false);
		switch(menu.GetOption()){
			case MENU_START:
				Game::GetInstance().Push(new StageState());
				break;
			case MENU_CONTINUE:
				Game::GetInstance().Push(new StageState());
				// em uma missão salva
				break;
			case MENU_OPTIONS:
				//popRequested = true;
				//push na tela de opções
				break;
		}
	}

}

void TitleState::Render(){
	bg.Render(0,0,0);
	tx.Render(0,0);
	menu.Render();
}

void TitleState::Pause(){

}

void TitleState::Resume(){

}
