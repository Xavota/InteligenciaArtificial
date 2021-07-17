#include "Agent_AnimHasFlagState.h"
#include "Agent.h"
#include "Game.h"

Agent_AnimHasFlagState::Agent_AnimHasFlagState(std::vector<sf::IntRect> sequence, sf::Texture* atlasMap, float fps, bool repeat)
{
	m_sequenceRects = sequence;
	m_atlasMap = atlasMap;

	m_fps = fps;
	m_repeat = repeat;
}

Agent_AnimHasFlagState::~Agent_AnimHasFlagState()
{
}

void Agent_AnimHasFlagState::Enter(Agent* agent)
{
	Agent_AnimState::Enter(agent);
}

eAGENT_ANIM_STATE_TYPE Agent_AnimHasFlagState::Update(Agent* agent)
{
	Agent_AnimState::Update(agent);

	Game* g = getGame();

	if (g->m_restart)
	{
		return eAGENT_ANIM_STATE_TYPE::RUNNING;
	}

	eAGENT_STATE_TYPE funcState = agent->GetState();
	if (funcState == eAGENT_STATE_TYPE::FOLLOW_CARRIER || funcState == eAGENT_STATE_TYPE::FOLLOW_FLAG
	 || funcState == eAGENT_STATE_TYPE::PROTECT_FALG)
	{
		return eAGENT_ANIM_STATE_TYPE::RUNNING;
	}

	if (funcState == eAGENT_STATE_TYPE::WIN_LOSE)
	{
		if (g->m_winnerTeam == agent->GetTeam())
		{
			return eAGENT_ANIM_STATE_TYPE::WIN;
		}
		else
		{
			return eAGENT_ANIM_STATE_TYPE::LOSE;
		}
	}

	return eAGENT_ANIM_STATE_TYPE::HAS_FLAG;
}

void Agent_AnimHasFlagState::Exit(Agent* agent)
{
	Agent_AnimState::Exit(agent);
}
