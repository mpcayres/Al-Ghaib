#include "TitleState.h"
#include "StageState.h"
#include "InputManager.h"
#include "Game.h"

TitleState::TitleState() : bg("img/title.jpg"), text("font/Call me maybe.ttf", 40, 
	Text::BLENDED, "Press space to start...", { 0, 0, 0, 0 }) {
	text.SetPos(WINDOW_W/2, WINDOW_H/1.2, true, true);
	timer = Timer();
	textShow = true;
}

void TitleState::Update(float dt){
	if(SDL_QuitRequested() || InputManager::GetInstance().QuitRequested()){
		quitRequested = true;
	}
	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
		popRequested = true;
	}

	if(InputManager::GetInstance().KeyPress(SPACE_KEY)){
		Game::GetInstance().Push(new StageState());
	}
	timer.Update(dt);
	if(timer.Get() > 2){
		textShow = !textShow;
		timer.Restart();
	}
}

void TitleState::Render(){
	bg.Render(0, 0);
	if(textShow){
		text.Render(0,0);
	}
}

void TitleState::Pause(){

}

void TitleState::Resume(){

}
