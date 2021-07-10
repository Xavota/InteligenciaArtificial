#include "Agent_FollowFlagState.h"
#include "Game.h"

void Agent_FollowFlagState::Enter()
{
}

eAGENT_STATE_TYPE Agent_FollowFlagState::Update(Agent* agent)
{
	Game* g = getGame();

	if (g->m_restart)
	{
		return eAGENT_STATE_TYPE::FOLLOW_FLAG;
	}

	if (g->m_finished)
	{
		return eAGENT_STATE_TYPE::WIN_LOSE;
	}

	std::vector<Agent*> agents = g->m_manager.GetAgents();
	for (Agent* a : agents)
	{
		float dist = Agent::distanceVector(a->getPosition(), agent->getPosition());
		if (a != agent && dist <= 50 && a->GetState() != eAGENT_STATE_TYPE::HAS_FLAG)
		{
			agent->AddFleeTarget(a->getPosition());
		}
	}

	agent->AddSeekTarget(g->m_flag.GetPosition());

	if (g->m_flag.GetCarrier() != nullptr)
	{	
		if (g->m_flag.GetCarrier()->GetTeam() == agent->GetTeam())
		{
			return eAGENT_STATE_TYPE::PROTECT_FALG;
		}
		return eAGENT_STATE_TYPE::FOLLOW_CARRIER;
	}
	
	float distance = Agent::distanceVector(g->m_flag.GetPosition(), agent->getPosition());
	if (g->m_flag.CanBePickedUp() && distance < g->m_flag.GetRadious())
	{
		g->m_flag.SetCarrier(agent);
		return eAGENT_STATE_TYPE::HAS_FLAG;
	}
	return eAGENT_STATE_TYPE::FOLLOW_FLAG;
}

void Agent_FollowFlagState::Exit()
{
}
