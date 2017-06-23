#include "Mission.hpp"

#include <iostream>

Mission::Mission() : blackSquare("img/blacksquare.png"), spFade("img/blacksquare2.png", 1, 1, 1, true) {
	popRequested = quitRequested = false;
	initialX = initialY = -1;

	doorSound = false;
	trancada = false;
	begin = true;
	bloqBlack = false;
	fadeIn = true;
	count = 0;

	flagTimer = true; //stopMusic = false;
	time = Timer();
	timerPisca = Timer();
	cooldown = Timer();
	contPisca = 0;

	ultimoTempo = 3;
	state = MissionManager::missionManager->changeState;
	alpha = OPAQUE; alphaAux = OPAQUE;

	MissionManager::missionManager->countHallState = 0;
	MissionManager::missionManager->countStageState = 0;
	MissionManager::missionManager->countLivingRoomState = 0;
}

Mission::~Mission() {

}

std::string Mission::GetInitialState(){
	return initialState;
}

int Mission::GetInitialX(){
	return initialX;
}

int Mission::GetInitialY(){
	return initialY;
}

std::vector<std::unique_ptr<GameObject>> Mission::GetObjectStage(){
	return std::move(objectStage);
}

std::vector<std::unique_ptr<GameObject>> Mission::GetObjectHall(){
	return std::move(objectHall);
}

std::vector<std::unique_ptr<GameObject>> Mission::GetObjectLivingRoom(){
	return std::move(objectLivingRoom);
}

bool Mission::PopRequested(){
	return popRequested;
}

bool Mission::QuitRequested(){
	return quitRequested;
}

void Mission::MessageDoor(float dt){
	if(MissionManager::player->GetDoor() && trancada == false){
		falas.SetText("ESTÁ TRANCADA");
		falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
		Sound portaDestrancando = Sound ("audio/destrancando.wav");
		portaDestrancando.Play(0);
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

}

void Mission::UpdateVariable(float dt, float speed, bool turnOpaque){
    if (spFade.IsOpen()) {
        spFade.ChangeAlpha(alpha);
    }

    //std::cout << "Update " << alpha << std::endl;
    if(turnOpaque){
    	if (alpha < OPAQUE) {
			alphaAux += dt * speed;
			alpha = alphaAux;
		} else{
			alphaAux = (float) OPAQUE;
			alpha = OPAQUE;
			fadeIn = false;
		}
    } else{
    	if (alpha > TRANSPARENT) {
			alphaAux -= dt * speed;
			alpha = alphaAux;
		} else{
			alphaAux = (float) TRANSPARENT;
			alpha = TRANSPARENT;
			fadeIn = false;
		}
    }
}

void Mission::PiscaPisca(float dt, int max, float time){
	//std::cout << "PISCA " << contPisca << " " << timerPisca.Get() << std::endl;
	if(contPisca >= max){
		bloqBlack = true;
		timerPisca.Restart();
	} else{
		bloqBlack = false;
		if(timerPisca.Get() >= time){
			if (spFade.IsOpen()) {
				if((contPisca % 2) == 0) spFade.ChangeAlpha(OPAQUE);
				else spFade.ChangeAlpha(TRANSPARENT);
				contPisca++;
			}
			timerPisca.Restart();
		}
		timerPisca.Update(dt);
	}
}
