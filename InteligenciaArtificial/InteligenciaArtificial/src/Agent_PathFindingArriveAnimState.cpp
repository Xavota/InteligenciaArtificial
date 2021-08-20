#include "Agent_PathFindingArriveAnimState.h"
#include "PathFindingAgent.h"
#include "Game_FP.h"

Agent_PathFindingArriveAnimState::Agent_PathFindingArriveAnimState(std::vector<sf::IntRect> sequence, sf::Texture* atlasMap, float fps, bool repeat)
{
	m_sequenceRects = sequence;
	m_atlasMap = atlasMap;

	m_fps = fps;
	m_repeat = repeat;
}

Agent_PathFindingArriveAnimState::~Agent_PathFindingArriveAnimState()
{
}

void Agent_PathFindingArriveAnimState::Enter(PathFindingAgent* agent)
{
	Agent_PathFindingAnimState::Enter(agent);
}

eAGENT_PATH_FINDING_ANIM_STATE_TYPE Agent_PathFindingArriveAnimState::Update(PathFindingAgent* agent)
{
	Agent_PathFindingAnimState::Update(agent);

	Game_FP* g = getGame_FP();

	if (agent->GetState() == eAGENT_PATH_FINDING_STATE_TYPE::WAITING)
	{
		return eAGENT_PATH_FINDING_ANIM_STATE_TYPE::WAITING;
	}

	return eAGENT_PATH_FINDING_ANIM_STATE_TYPE::ARRIVE;
}

void Agent_PathFindingArriveAnimState::Exit(PathFindingAgent* agent)
{
	Agent_PathFindingAnimState::Exit(agent);
}
