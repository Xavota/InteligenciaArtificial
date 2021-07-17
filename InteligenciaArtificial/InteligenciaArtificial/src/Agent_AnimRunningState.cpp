#include "Agent_AnimRunningState.h"
#include "Agent.h"
#include "Game.h"

Agent_AnimRunningState::Agent_AnimRunningState(std::vector<sf::IntRect> sequence, sf::Texture* atlasMap, float fps, bool repeat)
{
	m_sequenceRects = sequence;
	m_atlasMap = atlasMap;

	m_fps = fps;
	m_repeat = repeat;
}

Agent_AnimRunningState::~Agent_AnimRunningState()
{
}

void Agent_AnimRunningState::Enter(Agent* agent)
{
	Agent_AnimState::Enter(agent);
}

eAGENT_ANIM_STATE_TYPE Agent_AnimRunningState::Update(Agent* agent)
{
	Agent_AnimState::Update(agent);

	Game* g = getGame();

	if (g->m_restart)
	{
		return eAGENT_ANIM_STATE_TYPE::RUNNING;
	}

	eAGENT_STATE_TYPE funcState = agent->GetState();
	if (funcState == eAGENT_STATE_TYPE::HAS_FLAG)
	{
		return eAGENT_ANIM_STATE_TYPE::HAS_FLAG;
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

	return eAGENT_ANIM_STATE_TYPE::RUNNING;
}

void Agent_AnimRunningState::Exit(Agent* agent)
{
	Agent_AnimState::Exit(agent);
}
