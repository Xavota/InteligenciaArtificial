#include "Agent_PathFindingFollowingLeftAnimState.h"
#include "PathFindingAgent.h"
#include "Game_FP.h"

Agent_PathFindingFollowingLeftAnimState::Agent_PathFindingFollowingLeftAnimState(
	std::vector<sf::IntRect> sequence, sf::Texture* atlasMap, float fps, bool repeat)
{
	m_sequenceRects = sequence;
	m_atlasMap = atlasMap;

	m_fps = fps;
	m_repeat = repeat;
}

Agent_PathFindingFollowingLeftAnimState::~Agent_PathFindingFollowingLeftAnimState()
{
}

void Agent_PathFindingFollowingLeftAnimState::Enter(PathFindingAgent* agent)
{
	Agent_PathFindingAnimState::Enter(agent);
}

eAGENT_PATH_FINDING_ANIM_STATE_TYPE Agent_PathFindingFollowingLeftAnimState::Update(
	PathFindingAgent* agent)
{
	std::cout << "LEFT" << std::endl;

	Agent_PathFindingAnimState::Update(agent);

	Game_FP* g = getGame_FP();

	if (agent->GetState() == eAGENT_PATH_FINDING_STATE_TYPE::ARRIVE)
	{
		return eAGENT_PATH_FINDING_ANIM_STATE_TYPE::ARRIVE;
	}
	if (agent->GetState() == eAGENT_PATH_FINDING_STATE_TYPE::WAITING)
	{
		return eAGENT_PATH_FINDING_ANIM_STATE_TYPE::WAITING;
	}

	sf::Vector2f orientation = agent->GetOrientation();
	if (abs(orientation.x) > abs(orientation.y))
	{
		if (orientation.x < 0)
		{
			return eAGENT_PATH_FINDING_ANIM_STATE_TYPE::FOLLIWING_LEFT;
		}
		else
		{
			return eAGENT_PATH_FINDING_ANIM_STATE_TYPE::FOLLIWING_RIGHT;
		}
	}
	else
	{
		if (orientation.y < 0)
		{
			return eAGENT_PATH_FINDING_ANIM_STATE_TYPE::FOLLIWING_UP;
		}
		else
		{
			return eAGENT_PATH_FINDING_ANIM_STATE_TYPE::FOLLIWING_DOWN;
		}
	}

	return eAGENT_PATH_FINDING_ANIM_STATE_TYPE::FOLLIWING_LEFT;
}

void Agent_PathFindingFollowingLeftAnimState::Exit(PathFindingAgent* agent)
{
	Agent_PathFindingAnimState::Exit(agent);
}
