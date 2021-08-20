#include "Agent_PathFindingWaitingAnimState.h"
#include "PathFindingAgent.h"
#include "Game_FP.h"

Agent_PathFindingWaitingAnimState::Agent_PathFindingWaitingAnimState(std::vector<sf::IntRect> sequence, sf::Texture* atlasMap, float fps, bool repeat)
{
	m_sequenceRects = sequence;
	m_atlasMap = atlasMap;

	m_fps = fps;
	m_repeat = repeat;
}

Agent_PathFindingWaitingAnimState::~Agent_PathFindingWaitingAnimState()
{
}

void Agent_PathFindingWaitingAnimState::Enter(PathFindingAgent* agent)
{
	Agent_PathFindingAnimState::Enter(agent);
}

eAGENT_PATH_FINDING_ANIM_STATE_TYPE Agent_PathFindingWaitingAnimState::Update(PathFindingAgent* agent)
{
	Agent_PathFindingAnimState::Update(agent);

	Game_FP* g = getGame_FP();

	if (agent->GetState() == eAGENT_PATH_FINDING_STATE_TYPE::FOLLIWING)
	{
		return eAGENT_PATH_FINDING_ANIM_STATE_TYPE::FOLLIWING_UP;
	}

	return eAGENT_PATH_FINDING_ANIM_STATE_TYPE::WAITING;
}

void Agent_PathFindingWaitingAnimState::Exit(PathFindingAgent* agent)
{
	Agent_PathFindingAnimState::Exit(agent);
}