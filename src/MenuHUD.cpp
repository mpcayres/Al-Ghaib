#include "MenuHUD.hpp"
#include "InputManager.hpp"

MenuHUD::MenuHUD(float x, float y) /*: sp("img/fundoMenu.png")*/ {
	box.x = x;// - sp.GetWidth()/2;
	box.y = y;// - sp.GetHeight()/2;
	//box.h = sp.GetHeight();
	//box.w = sp.GetWidth();
	selected = false;
	optSelected = 0;
	buttons.emplace_back(Sprite("img/new-game.png"));
	buttons.emplace_back(Sprite("img/load-game.png"));
	buttons.emplace_back(Sprite("img/option.png"));
	buttons.emplace_back(Sprite("img/sair.png"));
	buttonsSelected.emplace_back(Sprite("img/new-game-select.png"));
	buttonsSelected.emplace_back(Sprite("img/load-game-select.png"));
	buttonsSelected.emplace_back(Sprite("img/option-select.png"));
	buttonsSelected.emplace_back(Sprite("img/sair-select.png"));
}

MenuHUD::~MenuHUD() { }

void MenuHUD::Update(float dt){
	InputManager instance = InputManager::GetInstance();

	if(instance.KeyPress(UP_ARROW_KEY)){
		optSelected -= 1;
		if(optSelected == -1) optSelected = buttons.size()-1;
	} else if(instance.KeyPress(DOWN_ARROW_KEY)){
		optSelected += 1;
		if(optSelected == (int) buttons.size()) optSelected = 0;
	}
	if(instance.KeyPress(ENTER_KEY) || instance.KeyPress(SPACE_KEY)){
		selected = true;
	}
}

void MenuHUD::Render(){
	//sp.Render(box.x, box.y, 0);
	for(unsigned int i = 0; i < buttons.size(); i++){
		if((int) i == optSelected){
			buttonsSelected[i].Render(box.x + 10,
					box.y + i*buttonsSelected[0].GetHeight() + 10, 0);
		} else{
			buttons[i].Render(box.x + 10,
					box.y + i*buttons[0].GetHeight() + 10, 0);
		}
	}

}

int MenuHUD::GetOption(){
	return optSelected;
}

bool MenuHUD::IsSelected(){
	return selected;
}

void MenuHUD::SetSelected(bool s){
	selected = s;
}
