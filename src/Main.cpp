#include "Game.hpp"
#include "TitleState.hpp"

int main(int argc, char* argv[]) {
	Game game = Game("Whispers",  SCREEN_SIZE_W, SCREEN_SIZE_H);
	game.Push(new TitleState());
	game.Run();

    return 0;
}
