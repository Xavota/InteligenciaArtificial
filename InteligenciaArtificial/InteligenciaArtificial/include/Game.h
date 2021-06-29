#pragma once
#include <SFML/Graphics.hpp>
#include "AgentManager.h"
#include "Flag.h"

#include "Player.h"
#include "StateMachine.h"

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
	void Restart();

private:
	sf::RenderWindow* m_window;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);

	/*AgentManager m_manager;
	Flag m_flag;

	int m_leftPoints = 0;
	int m_rightPoints = 0;

	sf::Text m_pointsText;

	bool m_Finished = false;

	sf::RectangleShape m_stage;*/

	Player m_player;
	StateMachine m_stateMachine;
};

sf::RenderWindow* getGameWindow(int x = 500, int y = 500);