#include "SceneWindow.hpp"

SceneWindow::SceneWindow(float x, float y, std::string img, std::string img2) :
	SceneObject(x, y, img, img2) { }

bool SceneWindow::Is(std::string type){
	return (type == "SceneWindow" || type == "CollidableObject");
}
