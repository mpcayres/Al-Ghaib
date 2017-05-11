#include "Bullet.h"
#include "Camera.h"

Bullet::Bullet(float x, float y, float angle, float speed,
		float maxDistance, std::string sprite,
		int frameCount, float frameTime, bool targetP) :
		sp(sprite, frameCount, frameTime),
		speed(Vec2::PolarVec(speed,angle*PI/180.0)),
		distanceLeft(maxDistance) {
	box.x = x - sp.GetWidth()/2;
	box.y = y - sp.GetHeight()/2;
	box.w = sp.GetWidth();
	box.h = sp.GetHeight();
	rotation = angle;
	targetsPlayer = targetP;
}

void Bullet::Update(float dt){
	box.x += dt*speed.x;
	box.y += dt*speed.y;
	distanceLeft -= speed.MagVec()*dt;
	sp.Update(dt);
}

void Bullet::Render(){
	sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
}

bool Bullet::IsDead(){
	return (distanceLeft <= 0);
}

void Bullet::NotifyCollision(GameObject& other){
	if((other.Is("Penguins") && targetsPlayer) ||
		(other.Is("Alien") && !targetsPlayer) ||
		(other.Is("Minion") && !targetsPlayer)){
		distanceLeft = 0;
	}
}

bool Bullet::Is(std::string type) {
	return (type == "Bullet");
}
