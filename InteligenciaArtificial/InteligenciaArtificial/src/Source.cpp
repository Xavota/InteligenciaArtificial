#include <SFML/Graphics.hpp>
#include "Game.h"
#include <time.h>

int main()
{
	srand(time(NULL));
	Game g;
	g.run();

	return 0;
}