#include "AgentManager.h"
#include "Game.h"
#include "Globals.h"
#include <iostream>

AgentManager::AgentManager(unsigned int agents, int maxX, int maxY, sf::Color color, eBEHAVIOUR behaviour)
{
	Init(agents, maxX, maxY, color, behaviour);
}

void AgentManager::Init(unsigned int agents, int maxX, int maxY, sf::Color color, eBEHAVIOUR behaviour)
{
	for (int i = 0; i < agents; i++)
	{
		m_agents.push_back(Agent(rand() % maxX + 5, rand() % maxY + 5, color, behaviour));
	}
}

void AgentManager::Update()
{
	sf::Vector2i pos = sf::Mouse::getPosition(*getGameWindow());
	m_agents[0].MoveTo(sf::Vector2f(pos));
	for (int i = 1; i < m_agents.size(); i++)
	{
		m_agents[i].MoveTo(m_agents[i - 1].getPosition());
	}
	for (Agent& a : m_agents)
	{
		//a.MoveTo(sf::Vector2f(pos));
		a.Update();
	}
}

void AgentManager::Render(sf::RenderWindow* window)
{
	for (Agent& a : m_agents)
	{
		a.Render(window);
	}
}

void AgentManager::Destroy()
{
	m_agents.clear();
}

AgentManager::~AgentManager()
{
	Destroy();
}
