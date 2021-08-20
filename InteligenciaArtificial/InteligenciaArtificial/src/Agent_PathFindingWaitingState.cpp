#include "Agent_PathFindingWaitingState.h"
#include "Game_FP.h"

void Agent_PathFindingWaitingState::Enter(PathFindingAgent* agent)
{
	agent->CanMove(false);
}

eAGENT_PATH_FINDING_STATE_TYPE Agent_PathFindingWaitingState::Update(PathFindingAgent* agent)
{
	Game_FP* g = getGame_FP();

	if (g->m_grid.GetHasFound())
	{
		return eAGENT_PATH_FINDING_STATE_TYPE::FOLLIWING;
	}

	return eAGENT_PATH_FINDING_STATE_TYPE::WAITING;
}

void Agent_PathFindingWaitingState::Exit(PathFindingAgent* agent)
{
}
