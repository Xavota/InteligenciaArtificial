#include "Agent_AnimWinState.h"
#include "Agent.h"
#include "Game.h"

Agent_AnimWinState::Agent_AnimWinState(std::vector<sf::IntRect> sequence, sf::Texture* atlasMap, float fps, bool repeat)
{
	m_sequenceRects = sequence;
	m_atlasMap = atlasMap;

	m_fps = fps;
	m_repeat = repeat;
}

Agent_AnimWinState::~Agent_AnimWinState()
{
}

void Agent_AnimWinState::Enter(Agent* agent)
{
	Agent_AnimState::Enter(agent);
}

eAGENT_ANIM_STATE_TYPE Agent_AnimWinState::Update(Agent* agent)
{
	Agent_AnimState::Update(agent);

	Game* g = getGame();

	if (g->m_restart)
	{
		return eAGENT_ANIM_STATE_TYPE::RUNNING;
	}

	return eAGENT_ANIM_STATE_TYPE::WIN;
}

void Agent_AnimWinState::Exit(Agent* agent)
{
}
