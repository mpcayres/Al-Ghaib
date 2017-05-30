#ifndef SRC_MENUHUD_HPP_
#define SRC_MENUHUD_HPP_

#include <vector>

#include "Sprite.hpp"
#include "Geometry.hpp"

class MenuHUD {
public:
	MenuHUD(float x, float y);
	~MenuHUD();

	void Update(float dt);
	void Render();

	int GetOption();
	bool IsSelected();
	void SetSelected(bool s);

private:
	//Sprite sp;
	Rect box;
	std::vector<Sprite> buttons;
	std::vector<Sprite> buttonsSelected;
	int optSelected;
	bool selected;
};

#endif /* SRC_MENUHUD_HPP_ */
