#include "AgentManager.h"
#include "Game.h"
#include "Globals.h"
#include <iostream>

AgentManager::AgentManager(unsigned int agents, int maxX, int maxY, sf::Color color)
{
	Init(agents, maxX, maxY, color);
}

void AgentManager::Init(unsigned int agents, int maxX, int maxY, sf::Color color)
{
	for (int i = 0; i < agents; i++)
	{
		m_agents.push_back(Agent(rand() % maxX + 5, rand() % maxY + 5, color));
		//m_agents.push_back(Agent(960, 540, color));
	}
}

void AgentManager::Update()
{
	sf::Vector2i pos = sf::Mouse::getPosition(*getGameWindow());
	m_agents[0].AddWanderBehaviour();
	//m_agents[0].AddSeekTarget(sf::Vector2f(pos));
	//m_agents[0].AddSeekTarget({ 500, 500 });
	//m_agents[0].AddFleeTarget({ 750, 750 });
	m_agents[1].AddPursuitTarget(m_agents[0].getPosition(), m_agents[0].getVelocity());
	/*for (int i = 1; i < m_agents.size(); i++)
	{
		m_agents[i].AddSeekTarget({ 500, 500 });
		m_agents[i].AddSeekTarget({ 1000, 500 });
		m_agents[i].AddSeekTarget({ 1000, 1000 });
		m_agents[i].AddSeekTarget({ 500, 1000 });
		m_agents[i].AddFleeTarget({ 750, 750 });
		//m_agents[i].AddSeekTarget(sf::Vector2f(pos));
		//getGameWindow()->setView(sf::View(m_agents[i].getPosition(), {1920, 1080}));
	}*/
	for (Agent& a : m_agents)
	{
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
