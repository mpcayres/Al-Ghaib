#include "Animation.hpp"
#include "Camera.hpp"

Animation::Animation(float x, float y, float rotation, std::string sprite,
		int frameCount, float frameTime, bool ends){
	sp = Sprite(sprite, frameCount, frameTime);
	box.x = x;
	box.y = y;
	box.w = sp.GetWidth();
	box.h = sp.GetHeight();
	timeLimit = frameCount*frameTime;
	oneTimeOnly = ends;
	endTimer = Timer();
	this->rotation = rotation;
}

void Animation::Update(float dt){
	endTimer.Update(dt);
	sp.Update(dt,0,false);
}

void Animation::Render(){
	sp.Render(box.CenterX() - Camera::pos.x, box.CenterY() - Camera::pos.y, rotation);
}

bool Animation::IsDead(){
	return (oneTimeOnly && endTimer.Get()>= timeLimit);
}

bool Animation::NotifyCollision(GameObject& other){
	return false;
}

bool Animation::Is(std::string type){
	return(type == "Animation");
}
