#include "Agent_FollowCarrierState.h"
#include "Game.h"

void Agent_FollowCarrierState::Enter()
{
}

eAGENT_STATE_TYPE Agent_FollowCarrierState::Update(Agent* agent)
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

	Agent* carrier = g->m_flag.GetCarrier();
	if (carrier != nullptr)
	{
		agent->AddPursuitTarget(carrier->getPosition(), carrier->getVelocity());

		if (carrier->GetTeam() == agent->GetTeam())
		{
			return eAGENT_STATE_TYPE::PROTECT_FALG;
		}

		float distance = Agent::distanceVector(g->m_flag.GetPosition(), agent->getPosition());
		if (g->m_flag.CanBePickedUp() && carrier->GetTeam() != agent->GetTeam() && distance < g->m_flag.GetRadious())
		{
			g->m_flag.SetCarrier(agent);
			return eAGENT_STATE_TYPE::HAS_FLAG;
		}
	}
	else
	{
		return eAGENT_STATE_TYPE::FOLLOW_FLAG;
	}

	return eAGENT_STATE_TYPE::FOLLOW_CARRIER;
}

void Agent_FollowCarrierState::Exit()
{
}
