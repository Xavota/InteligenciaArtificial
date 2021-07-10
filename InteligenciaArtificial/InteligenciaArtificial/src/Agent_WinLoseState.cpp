#include "Agent_WinLoseState.h"
#include "Game.h"

void Agent_WinLoseState::Enter()
{
}

eAGENT_STATE_TYPE Agent_WinLoseState::Update(Agent* agent)
{
	Game* g = getGame();

	agent->m_force = 0.0f;

	if (g->m_restart)
	{
		agent->m_force = agent->m_maxForce;
		return eAGENT_STATE_TYPE::FOLLOW_FLAG;
	}

	return eAGENT_STATE_TYPE::WIN_LOSE;
}

void Agent_WinLoseState::Exit()
{
}
