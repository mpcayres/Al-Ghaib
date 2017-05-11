#include "Penguins.h"
#include "Camera.h"
#include "Game.h"
#include "Bullet.h"
#include "Animation.h"
#include "Sound.h"
#include <math.h>

#define ACELERA		100
#define MAXSPEED	300
#define ANGSPEED	75
#define BSPEED		700
#define BDIST		400
#define DCENTER		50
#define DAMAGE		10
#define INIHP		30
#define SHOOTCD		0.5

Penguins* Penguins::player = nullptr;

Penguins::Penguins(float x, float y) :
	bodySp("img/penguin.png"), cannonSp("img/cubngun.png") {
	player = this;
	box.x = x - bodySp.GetWidth()/2;
	box.y = y - bodySp.GetHeight()/2;
	box.w = bodySp.GetWidth();
	box.h = bodySp.GetHeight();
	linearSpeed = 0;
	cannonAngle = 0;
	hp = INIHP;
}

Penguins::~Penguins(){
	player = nullptr;
	Camera::Unfollow();
}

void Penguins::Update(float dt){
	timer.Update(dt);
	InputManager &inputManager(InputManager::GetInstance());

	Vec2 pos(inputManager.GetMouseX() + Camera::pos.x,
			inputManager.GetMouseY() + Camera::pos.y);
	cannonAngle = pos.IncReta(Vec2(box.x, box.y))*180.0/PI;

	if(inputManager.IsKeyDown(W_KEY) && !inputManager.IsKeyDown(S_KEY)) {
		linearSpeed += ACELERA*dt;
		if(linearSpeed > MAXSPEED) linearSpeed = MAXSPEED;
	} else if(inputManager.IsKeyDown(S_KEY) && !inputManager.IsKeyDown(W_KEY)) {
		linearSpeed -= ACELERA*dt;
		if(linearSpeed < -MAXSPEED) linearSpeed = -MAXSPEED;
	}
	if(inputManager.IsKeyDown(D_KEY) && !inputManager.IsKeyDown(A_KEY)) {
		float angle = ANGSPEED*dt;
		rotation += angle;
	} else if(inputManager.IsKeyDown(A_KEY) && !inputManager.IsKeyDown(D_KEY)) {
		float angle = ANGSPEED*dt;
		rotation -= angle;
	}
	speedSp = Vec2::PolarVec(linearSpeed,rotation*PI/180.0);
	box.x += speedSp.x*dt;
	box.y += speedSp.y*dt;

	if(inputManager.MousePress(LEFT_MOUSE_BUTTON)) Shoot();

	Vec2 posBox = box.CoordCentro();

	if(posBox.x < 0){
		box.x -= posBox.x;
	} else if(posBox.x > MAPLIMIT_W){
		box.x += MAPLIMIT_W - posBox.x;
	}

	if(posBox.y < 0){
		box.y -= posBox.y;
	} else if(posBox.y > MAPLIMIT_H){
		box.y += MAPLIMIT_H - posBox.y;
	}
}

void Penguins::Render(){
	bodySp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
	cannonSp.Render(box.x - Camera::pos.x + box.w/2 - cannonSp.GetWidth()/2,
			box.y - Camera::pos.y + box.h/2 - cannonSp.GetHeight()/2, cannonAngle);
}

bool Penguins::IsDead(){
	return (hp <= 0);
}

void Penguins::Shoot(){
	if(timer.Get() >= SHOOTCD){
		Bullet* bullet = new Bullet(box.CoordCentro().x + DCENTER * cos(cannonAngle*PI/180.0),
				box.CoordCentro().y + DCENTER * sin(cannonAngle*PI/180.0),
				cannonAngle, BSPEED, BDIST, "img/penguinbullet.png", 4, 0.75);
		Game::GetInstance().GetCurrentState().AddObject(bullet);
		timer.Restart();
	}
}

void Penguins::NotifyCollision(GameObject& other){
	if(other.Is("Bullet")){
		if(((Bullet&) other).targetsPlayer){
			hp -= DAMAGE;
			if(IsDead()){
				Game::GetInstance().GetCurrentState().AddObject(
						//?? box
						new Animation(box.x, box.y - box.h/2, rotation,
								"img/penguindeath.png", 5, 0.25, 5*0.25, true));
				Sound s = Sound("audio/boom.wav");
				s.Play(0);
			}
		}
	}
}

bool Penguins::Is(std::string type) {
	return (type == "Penguins");
}
