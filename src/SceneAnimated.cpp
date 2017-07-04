#include "SceneAnimated.hpp"
#include "MissionManager.hpp"
#include "Camera.hpp"

SceneAnimated::SceneAnimated(float x, float y, std::string img, std::string img2,
		float rot, float scaleX, float scaleY) : sp(img), sp2(img2, 14, 0.1, 1) {
	sp.SetScaleX(scaleX); sp.SetScaleY(scaleY);
	sp2.SetScaleX(scaleX); sp2.SetScaleY(scaleY);
	estado = false;
	rotation = rot;
	box.x = x; box.y = y;
	box.w = sp.GetWidth();
	box.h = sp.GetHeight();
	offset = box.h/2.5;
}

SceneAnimated::~SceneAnimated() { }

void SceneAnimated::Update(float dt){
	if(estado){
		sp2.Update(dt);
	}
}

void SceneAnimated::Render(){
	if(estado) sp2.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
	else sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
}

bool SceneAnimated::IsDead(){
	return false;
}

bool SceneAnimated::NotifyCollision(GameObject& other){
	if(other.Is("Player")){
		return MissionManager::player->CollidingPlayer(box, offset);
	}

	if(other.Is("EmptyBox")){
		if(InputManager::GetInstance().KeyPress(Z_KEY)){
			ChangeImage();
		}
	}

	return false;
}

bool SceneAnimated::Is(std::string type){
	return (type == "SceneAnimated" || type == "SceneObject" || type == "CollidableObject");
}

void SceneAnimated::ChangeImage(){
	estado = !estado;
}
