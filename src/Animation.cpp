#include "Animation.h"
#include "Camera.h"

Animation::Animation(float x, float y, float rotation, std::string sprite,
		int frameCount, float frameTime, float timeLimit, bool ends) :
		sp(sprite, frameCount, frameTime),
		timeLimit(timeLimit), oneTimeOnly(ends) {
	box.x = x;
	box.y = y;
	box.w = sp.GetWidth();
	box.h = sp.GetHeight();
	this->rotation = rotation;
}

void Animation::Update(float dt){
	endTimer.Update(dt);
	sp.Update(dt);
}

void Animation::Render(){
	sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
}

bool Animation::IsDead(){
	if(!oneTimeOnly) return false;
	return (endTimer.Get() >= timeLimit);
}

void Animation::NotifyCollision(GameObject& other){ }

bool Animation::Is(std::string type){
	return (type == "Animation");
}
