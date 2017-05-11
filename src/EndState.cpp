#include "EndState.h"
#include "InputManager.h"
#include "Game.h"
#include "StageState.h"

EndState::EndState(StateData stateData) : bg(stateData.playerVictory ? "img/win.jpg" : "img/lose.jpg"), 
	instruction("font/Call me maybe.ttf", 30, Text::SOLID, " ", {255, 255, 255, 255}){
	if (stateData.playerVictory) {
		music.Open("audio/endStateWin.ogg");
		instruction.SetText("You have won! Press space to try again or esc to return to the menu");
	} else {
		music.Open("audio/endStateLose.ogg");
		instruction.SetText("You have lost! Press space to try again or esc to return to the menu");
	}
	instruction.SetPos(WINDOW_W/2, WINDOW_H/10, true, true);
}

void EndState::Update(float dt){
	popRequested = InputManager::GetInstance().KeyPress(ESCAPE_KEY);
	quitRequested = InputManager::GetInstance().QuitRequested();

	if (InputManager::GetInstance().KeyPress(SPACE_KEY)) {
		popRequested = true;
		Game::GetInstance().Push(new StageState());
	}
}

void EndState::Render(){
	bg.Render(0,0);
	instruction.Render();
}

void EndState::Pause(){
	music.Stop();
}

void EndState::Resume(){
	music.Play(-1);
}