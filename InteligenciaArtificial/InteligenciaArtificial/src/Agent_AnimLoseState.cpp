#include "Agent_AnimLoseState.h"
#include "Agent.h"
#include "Game.h"

Agent_AnimLoseState::Agent_AnimLoseState(std::vector<sf::IntRect> sequence, sf::Texture* atlasMap, float fps, bool repeat)
{
	m_sequenceRects = sequence;
	m_atlasMap = atlasMap;

	m_fps = fps;
	m_repeat = repeat;
}

Agent_AnimLoseState::~Agent_AnimLoseState()
{
}

void Agent_AnimLoseState::Enter(Agent* agent)
{
	Agent_AnimState::Enter(agent);
}

eAGENT_ANIM_STATE_TYPE Agent_AnimLoseState::Update(Agent* agent)
{
	Agent_AnimState::Update(agent);

	Game* g = getGame();

	if (g->m_restart)
	{
		return eAGENT_ANIM_STATE_TYPE::RUNNING;
	}

	return eAGENT_ANIM_STATE_TYPE::LOSE;
}

void Agent_AnimLoseState::Exit(Agent* agent)
{
}