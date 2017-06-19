#include "Mission.hpp"

Mission::Mission():blackSquare("img/blacksquare.png")  {
	popRequested = quitRequested = false;
	initialX = initialY = -1;

	trancada = false;
	begin = true;
	count = 0;

	flagTimer = true; //stopMusic = false;
	time = Timer();
	cooldown = Timer();
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


bool Mission::PopRequested(){
	return popRequested;
}

bool Mission::QuitRequested(){
	return quitRequested;
}

/*bool Mission::GetDoor(){
	return door;
}

void Mission::SetDoor(bool value){
	door = value;
}*/

void Mission::MessageDoor(float dt){
	if(MissionManager::player->GetDoor() && trancada == false){
				falas.SetText("ESTÁ TRANCADA");
				falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
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
