#ifndef SRC_SCENEWINDOW_HPP_
#define SRC_SCENEWINDOW_HPP_

#include "SceneObject.hpp"

class SceneWindow : public SceneObject {
public:
	SceneWindow(float x, float y, std::string img, std::string img2);

	void NotifyCollision(GameObject& other);
	bool Is(std::string type);
};

#endif /* SRC_SCENEWINDOW_HPP_ */
