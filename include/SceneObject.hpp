#ifndef SRC_SCENEOBJECT_HPP_
#define SRC_SCENEOBJECT_HPP_

#include <string>

#include "GameObject.hpp"
#include "Sprite.hpp"

class SceneObject : public GameObject {
public:
	SceneObject(float x, float y, int id, std::string img, std::string img2, bool alinha);

	void Update(float dt);
	void Render();
	bool IsEstado();
	bool IsDead();
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);

private:
	int id;
	Sprite sp;
	bool estado;
	std::string change1, change2;
	bool alinhaCentro; // pode virar inteiro se tiver outros possíveis alinhamentos
};

#endif  /* SCENEOBJECT_H_ */
