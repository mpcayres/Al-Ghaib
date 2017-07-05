#include "Mission.hpp"

#include <iostream>

Mission::Mission() : blackSquare("img/blacksquare.png"), spFade("img/blacksquare2.png", 1, 1, 1, true), falasBox("img/box-frases.png"), showBox(true) {
	popRequested = quitRequested = false;
	initialX = initialY = -1;

	doorSound = false;
	trancada = false;
	bloqBlack = false;
	fadeIn = true;
	gameOver = false;
	count = 0;

	flagTimer = true; //stopMusic = false;
	time = Timer();
	timerPisca = Timer();
	cooldown = Timer();
	contPisca = 0;
	maxPisca = 0;
	timePisca = 0;

	ultimoTempo = 3;
	state = MissionManager::missionManager->changeState;
	alpha = OPAQUE; alphaAux = OPAQUE;

	MissionManager::missionManager->countHallState = 0;
	MissionManager::missionManager->countStageState = 0;
	MissionManager::missionManager->countLivingRoomState = 0;

	falasBox.SetScaleX(1.1);
	falasBox.SetScaleY(0.4);

	falasBoxRect.x = 25; falasBoxRect.y = 500;
	falasBoxRect.w = falasBox.GetScaledWidth();
	falasBoxRect.h = falasBox.GetScaledHeight();

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

std::vector<std::unique_ptr<GameObject>> Mission::GetObjectMomRoom(){
	return std::move(objectMomRoom);
}

bool Mission::PopRequested(){
	return popRequested;
}

bool Mission::QuitRequested(){
	return quitRequested;
}

void Mission::MessageDoor(float dt){
	if(MissionManager::player->GetDoor() && trancada == false){
		showBox = true;
		falas.SetText("ESTÃ� TRANCADA");
		falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
		Sound portaDestrancando = Sound ("audio/portagrande.wav");
		portaDestrancando.Play(0);
		trancada = true;
		MissionManager::player->SetDoor(false);
		cooldown.Restart();
		time.Restart();
		while(time.Get()< ultimoTempo){
			time.Update(dt);
		}
	}

	if(cooldown.Get() > 3 && trancada == true){
		showBox = false;
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
			spFade.ChangeAlpha(alpha);
			fadeIn = false;
		}
    } else{
    	if (alpha > TRANSPARENT) {
			alphaAux -= dt * speed;
			alpha = alphaAux;
		} else{
			alphaAux = (float) TRANSPARENT;
			alpha = TRANSPARENT;
			spFade.ChangeAlpha(alpha);
			fadeIn = false;
		}
    }
}

//Setar uma vez e na missao que for chamar ter o PiscaPisca ao final do Update
//Para nao manter a tela preta, o valor max deve ser par
void Mission::SetPiscaPisca(int max, float time){
	maxPisca = max;
	timePisca = time;
}

void Mission::PiscaPisca(float dt){
	//std::cout << "PISCA " << contPisca << " " << maxPisca << "" << timerPisca.Get() << std::endl;
	if(maxPisca != 0 && timePisca != 0){
		if(contPisca >= maxPisca){
			bloqBlack = true;
			timerPisca.Restart();
		} else{
			bloqBlack = false;
			if(timerPisca.Get() >= timePisca){
				if (spFade.IsOpen()) {
					if((contPisca % 2) == 0) spFade.ChangeAlpha(OPAQUE);
					else spFade.ChangeAlpha(TRANSPARENT);
					contPisca++;
				}
				timerPisca.Restart();
			}
			timerPisca.Update(dt);
		}
		if(contPisca == maxPisca) maxPisca = timePisca = contPisca = 0;
	}
}
