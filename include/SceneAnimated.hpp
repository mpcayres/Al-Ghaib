#ifndef SRC_SCENEANIMATED_HPP_
#define SRC_SCENEANIMATED_HPP_

#include "GameObject.hpp"
#include "Sprite.hpp"

class SceneAnimated : public GameObject {
public:
	SceneAnimated(float x, float y, std::string img, std::string img2, float rot = 0, float scaleX = 1, float scaleY = 1);
	~SceneAnimated();

	void Update(float dt);
	void Render();
	bool IsDead();
	bool NotifyCollision(GameObject& other);
	bool Is(std::string type);
	void ChangeImage();

private:
	Sprite sp, sp2;
	bool estado;
	float offset;
};

#endif /* SRC_SCENEANIMATED_HPP_ */
