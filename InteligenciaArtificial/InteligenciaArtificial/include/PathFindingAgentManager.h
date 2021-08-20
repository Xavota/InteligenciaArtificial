#pragma once
#include "PathFindingAgent.h"

class PathFindingAgentManager
{
public:
	PathFindingAgentManager();
	~PathFindingAgentManager();

	void Init(Agent_PathFindingStateMachine* stMachine, Agent_PathFindingAnimMachine* animMachine);
	void Update();
	void Render(sf::RenderWindow* window);
	void Destroy();

	void SetAgentPosition(sf::Vector2f pos);
	sf::Vector2f GetAgentPosition();

private:
	PathFindingAgent m_agent;
};

