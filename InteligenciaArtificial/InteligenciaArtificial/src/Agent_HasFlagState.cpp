#include "Agent_HasFlagState.h"
#include "Game.h"

void Agent_HasFlagState::Enter()
{
}

eAGENT_STATE_TYPE Agent_HasFlagState::Update(Agent* agent)
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
		if (a != agent && dist <= 100 && a->GetTeam() != agent->GetTeam())
		{
			agent->AddEvadeTarget(a->getPosition(), a->getVelocity());
		}
	}

	agent->AddSeekTarget(agent->GetBasePos());

	if (g->m_flag.GetCarrier() != nullptr)
	{
		if (g->m_flag.GetCarrier()->GetTeam() != agent->GetTeam())
		{
			return eAGENT_STATE_TYPE::FOLLOW_CARRIER;
		}
	}
	else
	{
		return eAGENT_STATE_TYPE::FOLLOW_FLAG;
	}

	return eAGENT_STATE_TYPE::HAS_FLAG;
}

void Agent_HasFlagState::Exit()
{
}
