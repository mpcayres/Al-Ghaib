#include "EndState.hpp"
#include "StageState.hpp"
#include "Game.hpp"
#include "StateData.hpp"
#include "InputManager.hpp"

EndState::EndState(StateData stateData){
	SDL_Color color;
	color.r = 0;
	color.g = 70;
	color.b = 160;
	instruction = Text("font/Call me maybe.ttf", 50, Text::TextStyle::SOLID,
					"Press ESC to menu or space to try again", color, 0, 0);
	instruction.SetPos(0,0,true,true);
	if(stateData.playerVictory == true){
		bg = Sprite("img/win.jpg");
		music = Music("audio/endStateWin.ogg");
	}else{
		bg = Sprite("img/lose.jpg");
		music = Music("audio/endStateLose.ogg");
	}

}

void EndState::Update(float dt){
	InputManager instance = InputManager::GetInstance();
		//Input();
	if(instance.KeyPress(ESCAPE_KEY)){
		music.Stop();
		popRequested = true;
	}
	if(instance.KeyPress(SPACE_KEY)){
		music.Stop();
		popRequested = true;
		//Game::GetInstance().Push(new StageState());
	}

	quitRequested = instance.QuitRequested();

}

void EndState::Render(){
	bg.Render(0,0,0);
	instruction.Render(0,0);
}

void EndState::Resume(){
	music.Play(-1);
}

void EndState::Pause(){
	music.Stop();
}
