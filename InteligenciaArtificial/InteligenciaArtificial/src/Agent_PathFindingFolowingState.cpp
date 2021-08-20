#include "Agent_PathFindingFolowingState.h"
#include "Game_FP.h"
#include "Globals.h"

void Agent_PathFindingFolowingState::Enter(PathFindingAgent* agent)
{
	Game_FP* g = getGame_FP();

	std::vector<Node*> nodePath = g->m_grid.GetPathToEnd();

	m_path.clear();
	for (int i = 0; i < nodePath.size(); i++)
	{
		m_path.push_back(nodePath[i]->GetPosition());
	}

	agent->SetPathFollowPoints(m_path);
	agent->CanMove(true);
}

eAGENT_PATH_FINDING_STATE_TYPE Agent_PathFindingFolowingState::Update(PathFindingAgent* agent)
{
	Game_FP* g = getGame_FP();

	agent->IsFollowing();

	float distance = gl::MathF::distanceVector(agent->GetPosition(), m_path[m_path.size() - 1]);
	if (distance < 16.0f)
	{
		return eAGENT_PATH_FINDING_STATE_TYPE::ARRIVE;
	}

	if (!g->m_grid.GetHasFound())
	{
		return eAGENT_PATH_FINDING_STATE_TYPE::WAITING;
	}

	return eAGENT_PATH_FINDING_STATE_TYPE::FOLLIWING;
}

void Agent_PathFindingFolowingState::Exit(PathFindingAgent* agent)
{
}