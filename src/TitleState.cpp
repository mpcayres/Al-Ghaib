#include "TitleState.hpp"
#include "Game.hpp"
#include "StageState.hpp"
#include "InputManager.hpp"

TitleState::TitleState() : menu(50, 50) {
	SDL_Color auxcolor = SDL_Color();
	auxcolor.r = 255;
	auxcolor.g = 10;
	auxcolor.b = 10;

	flagTimer = true;
	time = Timer();
	bg = Sprite("img/title.jpg");
	bg.SetScaleX(1.7); bg.SetScaleY(1.5);
	tx = Text("font/Call me maybe.ttf", 64, Text::TextStyle::BLENDED, "AL-GHAIB", auxcolor, 0, 0);
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
		tx.SetText("AL GHAIB");
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
				// em uma missao salva
				break;
			case MENU_OPTIONS:
				//popRequested = true;
				//push na tela de opcoees
				break;
			case MENU_EXIT:
				quitRequested = true;
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
