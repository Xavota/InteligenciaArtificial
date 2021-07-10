#include "AgentManager.h"
#include "Game.h"
#include "Globals.h"
#include <iostream>


void AgentManager::Init(Agent_StateMachine* stMachine, Agent_AnimMachine* animMachine)
{
	m_stateMachine = stMachine;
	m_animMachine = animMachine;
}

void AgentManager::Restart()
{
	for (AgentStruct& a : m_agents)
	{
		for (TeamsInfo& t : m_teams)
		{
			if (t.m_teamName == a.m_teamName)
			{
				float posX = rand() % t.m_aperanceRange.width + t.m_aperanceRange.left;
				float posY = rand() % t.m_aperanceRange.height + t.m_aperanceRange.top;
				a.m_agent.Init(posX, posY, t.m_color, t.m_teamName, t.m_basePos, m_stateMachine, m_animMachine);
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

void AgentManager::AddAgents(unsigned int agents, sf::IntRect aperanceRange, sf::Color color, std::string teamName, sf::Vector2f basePos)
{
	bool teamExist = false;
	for (TeamsInfo& t : m_teams)
	{
		if (t.m_teamName == teamName)
		{
			teamExist = true;
			break;
		}
	}

	if (!teamExist)
		m_teams.push_back({ teamName, basePos, aperanceRange, color });

	for (int i = 0; i < agents; i++)
	{
		float posX = rand() % aperanceRange.width + aperanceRange.left;
		float posY = rand() % aperanceRange.height + aperanceRange.top;
		m_agents.push_back(AgentStruct{Agent(posX, posY, color, teamName, basePos, m_stateMachine, m_animMachine), teamName, sf::Vector2f{posX, posY}});
	}
}

void AgentManager::RemoveAgents(unsigned int agents, std::string teamName)
{
	for (int i = 0; i < agents; i++)
	{
		for (list<AgentStruct>::iterator it = m_agents.begin(); it != m_agents.end(); ++it)
		{
			if (it->m_teamName == teamName)
			{
				m_agents.erase(it);
				break;
			}
		}
	}
}

void AgentManager::RemoveAgent(unsigned int agentIndex)
{
	if (agentIndex < m_agents.size())
	{
		list<AgentStruct>::iterator it = m_agents.begin();
		advance(it, agentIndex);
		m_agents.erase(it);
	}
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

void AgentManager::UpdateTeamAperianceRange(std::string teamName, sf::IntRect range)
{
	for (TeamsInfo& t : m_teams)
	{
		if (t.m_teamName == teamName)
		{
			t.m_aperanceRange = range;
		}
	}
}

void AgentManager::UpdateTeamBasePos(std::string teamName, sf::Vector2f pos)
{
	for (AgentStruct& a : m_agents)
	{
		if (a.m_teamName == teamName)
		{
			a.m_agent.UpdateBasePos(pos);
		}
	}

	for (TeamsInfo& t : m_teams)
	{
		if (t.m_teamName == teamName)
		{
			t.m_basePos = pos;
		}
	}
}

void AgentManager::UpdateTeamColor(std::string teamName, sf::Color color)
{
	for (AgentStruct& a : m_agents)
	{
		if (a.m_teamName == teamName)
		{
			a.m_agent.UpdateColor(color);
		}
	}

	for (TeamsInfo& t : m_teams)
	{
		if (t.m_teamName == teamName)
		{
			t.m_color = color;
		}
	}
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

void AgentManager::SetFlockingBehaviours()
{
	vector<AgentStruct*> m_flockingAgents;
	for (AgentStruct& a : m_agents)
	{
		if (a.m_agent.IsFlocking())
			m_flockingAgents.push_back(&a);
	}
	for (AgentStruct& a : m_agents)
	{
		if (a.m_agent.IsFlocking())
		{
			vector<Agent*> groupAgents;
			for (int j = 0; j < m_flockingAgents.size(); j++)
			{
				if (Agent::distanceVector(a.m_agent.getPosition(), m_flockingAgents[j]->m_agent.getPosition()) <= a.m_agent.GetFlockingGroupRadious() 
				&& a.m_teamName == m_flockingAgents[j]->m_teamName)
				{
					groupAgents.push_back(&m_flockingAgents[j]->m_agent);
				}
			}
			a.m_agent.SetFlockingAgentsGroup(groupAgents);
		}
	}
	m_flockingAgents.clear();
}

AgentManager::~AgentManager()
{
	Destroy();
}
