#include "Animation.hpp"
#include "Camera.hpp"

Animation::Animation(float x, float y, float rotation, std::string sprite,
		int frameCount, float frameTime, bool ends, float scaleX, float scaleY, bool back):  backgroundsquare("img/HUD/blackBack.jpg"), back(back){
	sp = Sprite(sprite, frameCount, frameTime);
	sp.SetScaleX(scaleX); sp.SetScaleY(scaleY);
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
	if(back)
		backgroundsquare.Render(0,0, 0);
	sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);

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
