#include "Game.h"
#include "TitleState.h"

int main (int argc, char** argv) {
	Game game = Game("Marcos Paulo - 14/0027131", WINDOW_W, WINDOW_H);
	game.Push(new TitleState());
	game.Run();

	return 0;
}
