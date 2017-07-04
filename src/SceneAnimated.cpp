#include "SceneAnimated.hpp"
#include "MissionManager.hpp"
#include "Camera.hpp"

SceneAnimated::SceneAnimated(float x, float y, std::string img, std::string img2,
		float rot, float scaleX, float scaleY) : sp(img) {
	sp.SetScaleX(scaleX); sp.SetScaleY(scaleY);
	change1 = img;
	change2 = img2;
	estado = false;
	rotation = rot;
	box.x = x; box.y = y;
	box.w = sp.GetWidth();
	box.h = sp.GetHeight();
	offset = box.h/3;
}

SceneAnimated::~SceneAnimated() { }

void SceneAnimated::Update(float dt){
	if(estado){
		sp.Update(dt);
	}
}

void SceneAnimated::Render(){
	sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
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
	if(estado){
		sp.Open(change2, 14, 0.1, 1);
	} else{
		sp.Open(change1);
	}
}
