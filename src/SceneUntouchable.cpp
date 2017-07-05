#include "SceneUntouchable.hpp"
#include "MissionManager.hpp"
#include "Sound.hpp"

SceneUntouchable::SceneUntouchable(float x, float y, std::string img,
		float rot, float scaleX, float scaleY) : sp(img) {
	sp.SetScaleX(scaleX); sp.SetScaleY(scaleY);

	rotation = rot;
	box.x = x; box.y = y;
	box.w = sp.GetWidth();
	box.h = sp.GetHeight();

}

bool SceneUntouchable::IsDead(){
	return false;
}

void SceneUntouchable::Update(float dt){

}

void SceneUntouchable::Render(){
	sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
}

bool SceneUntouchable::NotifyCollision(GameObject& other){

	return false;
}

bool SceneUntouchable::Is(std::string type){
	return (type == "SceneUntouchable");
}
