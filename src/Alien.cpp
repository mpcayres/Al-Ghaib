#include "Alien.h"
#include "Camera.h"
#include "Bullet.h"
#include "Game.h"
#include "Animation.h"
#include "Penguins.h"
#include "Sound.h"
#include <iostream>

#define SPEED		6
#define ANGSPEED	-360/60
#define DAMAGE		10
#define INIHP		30
#define RESTCD		1

int Alien::alienCount = 0;

Alien::Alien(float x, float y, int nMinions) : sp("img/alien.png") {
	box.x = x - sp.GetWidth()/2;
	box.y = y - sp.GetHeight()/2;
	box.w = sp.GetWidth();
	box.h = sp.GetHeight();
	hp = INIHP;
	alienCount++;
	state = RESTING;
	for(int i = 0; i < nMinions; i++){
		float scale = rand() % 6;
		scale = (scale/10.0) + 1.0;
		float angle = (float) (i*360/nMinions);

		Minion minion(this, angle, scale);
		minionArray.emplace_back(minion);
	}
}

Alien::~Alien() {
	minionArray.clear();
	alienCount--;
}

void Alien::Update(float dt){
	rotation += ANGSPEED*dt;

	if(Penguins::player != nullptr){
		if(state == RESTING){
			restTimer.Update(dt);
			if(restTimer.Get() >= RESTCD){
				destination = Penguins::player->box.CoordCentro();
				speed.x = (destination.x - box.CoordCentro().x)*dt;
				speed.y = (destination.y - box.CoordCentro().y)*dt;
				speed = speed.NormVec()*SPEED;
				state = MOVING;
			}
		} else if(state == MOVING){
			bool movX = abs(destination.x - box.CoordCentro().x) <= abs(speed.x);
			bool movY = abs(destination.y - box.CoordCentro().y) <= abs(speed.y);

			if(movX && movY){
				box.x += destination.x - box.CoordCentro().x;
				box.x += destination.y - box.CoordCentro().y;

				Vec2 pos = Penguins::player->box.CoordCentro();
				float minDist = 0;
				int minPos = 0;
				for(unsigned int i = 0; i < minionArray.size(); i++){
					float dist = pos.DistVec(Vec2(
							minionArray[i].box.CoordCentro().x,
							minionArray[i].box.CoordCentro().y));
					if(dist < minDist || i == 0){
						minDist = dist;
						minPos = i;
					}
				}
				minionArray[minPos].Shoot(pos);

				restTimer.Restart();
				state = RESTING;
			} else {
				if(!movX) box.x += speed.x;
				if(!movY) box.y += speed.y;
			}
		}
	}

	for(unsigned int i = 0; i < minionArray.size(); i++){
		minionArray[i].Update(dt);
	}

}

void Alien::Render(){
	sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
	for(unsigned int i = 0; i < minionArray.size(); i++){
		minionArray[i].Render();
	}
}

bool Alien::IsDead(){
	return (hp <= 0);
}

void Alien::NotifyCollision(GameObject& other){
	if(other.Is("Bullet")){
		if(!((Bullet&) other).targetsPlayer){
			hp -= DAMAGE;
			if(IsDead()){
				Game::GetInstance().GetCurrentState().AddObject(
						new Animation(box.x, box.y, rotation,
								"img/aliendeath.png", 4, 0.25, 4*0.25, true));
				for(unsigned int i = 0; i < minionArray.size(); i++){
					Game::GetInstance().GetCurrentState().AddObject(
							new Animation(minionArray[i].box.x,
									minionArray[i].box.y, rotation,
									"img/miniondeath.png", 4, 0.25, 4*0.25, true));
				}
				Sound s = Sound("audio/boom.wav");
				s.Play(0);
			}
		}
	}
}

bool Alien::Is(std::string type) {
	return (type == "Alien");
}
