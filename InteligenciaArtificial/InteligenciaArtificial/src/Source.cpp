#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Game_FP.h"
#include <time.h>

int main()
{
	srand(time(NULL));
	Game_FP* g = getGame_FP();
	g->Run();

	delete g;
	return 0;
}