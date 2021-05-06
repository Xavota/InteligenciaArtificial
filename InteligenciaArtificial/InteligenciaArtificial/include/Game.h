#pragma once
#include <SFML/Graphics.hpp>
class Game
{
public:
	void run();

	sf::RenderWindow* getWindow() { return m_window; }

	Game() = default;
	~Game() = default;
private:

	void init();
	void update();
	void processEvents();
	void render();
	void destroy();

private:
	sf::RenderWindow* m_window;

	sf::CircleShape m_shape;

	sf::Time timePerFrame = sf::seconds(1.f / 60.f);;
};

