#ifndef INCLUDE_INPUTMANAGER_HPP_
#define INCLUDE_INPUTMANAGER_HPP_

#ifdef __APPLE__
	#include <SDL2.h>
	#include <SDL_imagem/SDL_image.h>
#elif __linux__
    #include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
#elif _WIN32
	#include "SDL.h"
	#include "SDL_image.h"
#endif

#include <unordered_map>

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN

#define ESCAPE_KEY SDLK_ESCAPE

#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT

#define SPACE_KEY SDLK_SPACE
#define ENTER_KEY SDLK_RETURN
#define LCTRL_KEY SDLK_LCTRL
#define LSHIFT_KEY SDLK_LSHIFT

#define W_KEY SDLK_w
#define A_KEY SDLK_a
#define S_KEY SDLK_s
#define D_KEY SDLK_d
#define Z_KEY SDLK_z
#define X_KEY SDLK_x
#define I_KEY SDLK_i
#define G_KEY SDLK_g

class InputManager{
public:
	InputManager();
	~InputManager();

	void Update();

	bool KeyPress(int key);
	bool KeyRelease(int key);
	bool IsKeyDown(int key);

	bool MousePress(int button);
	bool MouseRelease(int button);
	bool IsMouseDown(int button);

	int GetMouseX();
	int GetMouseY();

	bool QuitRequested();

	static InputManager& GetInstance();

private:
	bool mouseState[6];
	int mouseUpdate[6];

	std::unordered_map<int, bool> keyState;
	std::unordered_map<int, int> keyUpdate;

	bool quitRequested;
	int updateCounter;

	int mouseX;
	int mouseY;
};

#endif /* INCLUDE_INPUTMANAGER_HPP_ */
