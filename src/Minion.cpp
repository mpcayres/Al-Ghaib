#include "Minion.h"
#include "Camera.h"
#include "Bullet.h"
#include "Game.h"
#include <math.h>

#define SPEED 50
#define BSPEED 700
#define BDIST 400

Minion::Minion(GameObject* minionCenter, float arcOffset, float scale)
	: center(minionCenter), sp("img/minion.png"), arc(arcOffset)  {
	sp.SetScaleX(scale);
	sp.SetScaleY(scale);
	rotation = arc + (PI/2);

	Vec2 mov = Vec2(0, center->box.h).RotateVec(arc);
	box.x = center->box.x + center->box.w - mov.x - sp.GetWidth()/2;
	box.y = center->box.y + center->box.h - mov.y - sp.GetHeight()/2;
	box.w = sp.GetWidth();
	box.h = sp.GetHeight();

}

//Minion::~Minion() { }

void Minion::Update(float dt){
	arc += SPEED*dt;
	rotation = arc + (PI/2);
	Vec2 mov = Vec2(0, center->box.h).RotateVec(arc);
	box.x = center->box.x + center->box.w/2 - mov.x - sp.GetWidth()/2;
	box.y = center->box.y + center->box.h/2 - mov.y - sp.GetHeight()/2;
}

void Minion::Render(){
	sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
}

bool Minion::IsDead(){
	return false;
}

void Minion::Shoot(Vec2 pos){
	Vec2 inc = pos - Vec2(box.CoordCentro().x, box.CoordCentro().y);
	Bullet* bullet = new Bullet(box.CoordCentro().x, box.CoordCentro().y,
			inc.IncVec()*180.0/PI, BSPEED, BDIST, "img/minionbullet2.png", 3, 1.0, true);
	Game::GetInstance().GetCurrentState().AddObject(bullet);
}

void Minion::NotifyCollision(GameObject& other){
	if(other.Is("Bullet")){
		if(!((Bullet&) other).targetsPlayer){
			//??
		}
	}
}

bool Minion::Is(std::string type) {
	return (type == "Minion");
}
