#include "Agent_PathFindingArriveState.h"
#include "Game_FP.h"

void Agent_PathFindingArriveState::Enter(PathFindingAgent* agent)
{
	agent->CanMove(false);
}

eAGENT_PATH_FINDING_STATE_TYPE Agent_PathFindingArriveState::Update(PathFindingAgent* agent)
{
	Game_FP* g = getGame_FP();

	if (!g->m_grid.GetHasFound())
	{
		return eAGENT_PATH_FINDING_STATE_TYPE::WAITING;
	}

	return eAGENT_PATH_FINDING_STATE_TYPE::ARRIVE;
}

void Agent_PathFindingArriveState::Exit(PathFindingAgent* agent)
{
}
