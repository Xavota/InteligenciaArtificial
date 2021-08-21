#include "PathFindingAgentManager.h"

PathFindingAgentManager::PathFindingAgentManager()
{
}

PathFindingAgentManager::~PathFindingAgentManager()
{
}

void PathFindingAgentManager::Init(Agent_PathFindingStateMachine* stMachine, Agent_PathFindingAnimMachine* animMachine)
{
	m_agent.Init({0,0}, stMachine, animMachine);
}

void PathFindingAgentManager::Update()
{
	m_agent.Update();
}

void PathFindingAgentManager::Render(sf::RenderWindow* window)
{
	m_agent.Render(window);
}

void PathFindingAgentManager::Destroy()
{
	m_agent.Destroy();
}

void PathFindingAgentManager::SetAgentPosition(sf::Vector2f pos)
{
	m_agent.SetPosition(pos);
}

sf::Vector2f PathFindingAgentManager::GetAgentPosition()
{
	return m_agent.GetPosition();
}

void PathFindingAgentManager::SetAgentVelocity(float vel)
{
	m_agent.SetVelocity(vel);	
}
