#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Agent.h"
class AgentManager
{
public:
	AgentManager() = default;
	AgentManager(unsigned int agents, int maxX, int maxY, sf::Color color, eBEHAVIOUR behaviour);
	void Init(unsigned int agents, int maxX, int maxY, sf::Color color, eBEHAVIOUR behaviour);
	void Update();
	void Render(sf::RenderWindow* window);
	void Destroy();
	~AgentManager();
private:
	std::vector<Agent> m_agents;
};

