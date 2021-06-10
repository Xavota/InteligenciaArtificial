#include "AgentManager.h"
#include "Game.h"
#include "Globals.h"
#include <iostream>


void AgentManager::Init()
{
}

void AgentManager::Restart()
{
	for (AgentStruct& a : m_agents)
	{
		for (TeamsInfo& t : m_teams)
		{
			if (t.teamName == a.m_teamName)
			{
				float posX = rand() % t.aperanceRange.width + t.aperanceRange.left;
				float posY = rand() % t.aperanceRange.height + t.aperanceRange.top;
				a.m_agent.Init(posX, posY, t.color, t.teamName);
			}
		}
	}
}

void AgentManager::Update()
{
	SetFlockingBehaviours();

	for (AgentStruct& a : m_agents)
	{
		a.m_agent.Update();
	}
}

void AgentManager::Render(sf::RenderWindow* window)
{
	for (AgentStruct& a : m_agents)
	{
		a.m_agent.Render(window);
	}
}

void AgentManager::Destroy()
{
	m_agents.clear();
}

void AgentManager::AddAgents(unsigned int agents, sf::IntRect aperanceRange, sf::Color color, std::string teamName)
{
	for (int i = 0; i < agents; i++)
	{
		float posX = rand() % aperanceRange.width + aperanceRange.left;
		float posY = rand() % aperanceRange.height + aperanceRange.top;
		m_agents.push_back(AgentStruct{Agent(posX, posY, color, teamName), teamName, sf::Vector2f{posX, posY}});
	}
	m_teams.push_back({teamName, aperanceRange, color});
}

std::vector<Agent*> AgentManager::GetAgents(std::string teamName)
{	
	std::vector<Agent*> agents;
	if (teamName != "All")
	{
		for (AgentStruct& a : m_agents)
		{
			if (a.m_teamName == teamName)
			{
				agents.push_back(&a.m_agent);
			}
		}
	}
	else
	{
		for (AgentStruct& a : m_agents)
		{
			agents.push_back(&a.m_agent);
		}
	}

	return agents;
}

void AgentManager::AddSeekTarget(sf::Vector2f target, std::vector<Agent*> agents)
{
	for (Agent* a : agents)
	{
		a->AddSeekTarget(target);
	}
}

void AgentManager::AddFleeTarget(sf::Vector2f target, std::vector<Agent*> agents)
{
	for (Agent* a : agents)
	{
		a->AddFleeTarget(target);
	}
}

void AgentManager::AddWanderBehaviour(std::vector<Agent*> agents)
{
	for (Agent* a : agents)
	{
		a->AddWanderBehaviour();
	}
}

void AgentManager::AddPursuitTarget(sf::Vector2f target, sf::Vector2f velocity, std::vector<Agent*> agents)
{
	for (Agent* a : agents)
	{
		a->AddPursuitTarget(target, velocity);
	}
}

void AgentManager::AddEvadeTarget(sf::Vector2f target, sf::Vector2f velocity, std::vector<Agent*> agents)
{
	for (Agent* a : agents)
	{
		a->AddEvadeTarget(target, velocity);
	}
}

void AgentManager::AddObstacleToAvoid(sf::Vector2f obstacle, float radious, std::vector<Agent*> agents)
{
	for (Agent* a : agents)
	{
		a->AddObstacleToAvoid(obstacle, radious);
	}
}

void AgentManager::AddFollowPathPoint(sf::Vector2f point, std::vector<Agent*> agents)
{
	for (Agent* a : agents)
	{
		a->AddFollowPathPoint(point);
	}
}

void AgentManager::SetFollowPathMode(ePATH_FOLLOWING_TYPE type, std::vector<Agent*> agents)
{
	for (Agent* a : agents)
	{
		a->SetFollowPathMode(type);
	}
}

void AgentManager::AddFlockingBehaviour(std::vector<Agent*> agents)
{
	for (Agent* a : agents)
	{
		a->AddFlockingBehaviour();
	}
}

std::string AgentManager::GetTeamName(Agent* agent)
{
	for (AgentStruct a : m_agents)
	{
		if (&(a.m_agent) == agent)
		{
			return a.m_teamName;
		}
	}
	return "";
}

void AgentManager::SetFlockingBehaviours()
{
	vector<AgentStruct*> m_flockingAgents;
	for (int i = 0; i < m_agents.size(); i++)
	{
		if (m_agents[i].m_agent.IsFlocking())
			m_flockingAgents.push_back(&m_agents[i]);
	}
	for (int i = 0; i < m_agents.size(); i++)
	{
		if (m_agents[i].m_agent.IsFlocking())
		{
			vector<Agent*> groupAgents;
			for (int j = 0; j < m_flockingAgents.size(); j++)
			{
				if (Agent::distanceVector(m_agents[i].m_agent.getPosition(), m_flockingAgents[j]->m_agent.getPosition()) <= m_agents[i].m_agent.GetFlockingGroupRadious() 
				&& m_agents[i].m_teamName == m_flockingAgents[j]->m_teamName)
				{
					groupAgents.push_back(&m_flockingAgents[j]->m_agent);
				}
			}
			m_agents[i].m_agent.SetFlockingAgentsGroup(groupAgents);
		}
	}
	m_flockingAgents.clear();
}

AgentManager::~AgentManager()
{
	Destroy();
}
