#include "Game.hpp"
#include "TitleState.hpp"

int main(int argc, char* argv[]) {
	Game game = Game("Whispers", 1024, 600);
	game.Push(new TitleState());
	game.Run();

    return 0;
}
