#include "Agent_ProtectFlagState.h"
#include "Game.h"

void Agent_ProtectFlagState::Enter()
{
}

eAGENT_STATE_TYPE Agent_ProtectFlagState::Update(Agent* agent)
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
		agent->AddPursuitTarget(carrier->getPosition(), -carrier->getVelocity() * .5f);

		if (carrier->GetTeam() != agent->GetTeam())
		{
			return eAGENT_STATE_TYPE::FOLLOW_CARRIER;
		}
	}
	else
	{
		return eAGENT_STATE_TYPE::FOLLOW_FLAG;
	}

	return eAGENT_STATE_TYPE::PROTECT_FALG;
}

void Agent_ProtectFlagState::Exit()
{
}
