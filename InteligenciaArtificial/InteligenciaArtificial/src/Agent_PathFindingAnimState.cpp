#include "Agent_PathFindingAnimState.h"
#include "Globals.h"
#include "PathFindingAgent.h"

void Agent_PathFindingAnimState::Enter(PathFindingAgent* agent)
{
	agent->m_animFrame = 0;
	agent->m_animTimer = 0;

	agent->m_shape.setTexture(m_atlasMap);
	agent->m_shape.setTextureRect(m_sequenceRects[0]);
}

eAGENT_PATH_FINDING_ANIM_STATE_TYPE Agent_PathFindingAnimState::Update(PathFindingAgent* agent)
{
	agent->m_animTimer += gl::DeltaTime::Time();

	if (agent->m_animTimer > 1 / m_fps)
	{
		agent->m_animFrame = m_repeat
			? ((agent->m_animFrame + 1) % m_sequenceRects.size())
			: (agent->m_animFrame < (m_sequenceRects.size() - 1)
				? agent->m_animFrame + 1
				: agent->m_animFrame);

		agent->m_shape.setTextureRect(m_sequenceRects[agent->m_animFrame]);

		agent->m_animTimer = 0;
	}

	return eAGENT_PATH_FINDING_ANIM_STATE_TYPE::NONE;
}

void Agent_PathFindingAnimState::Exit(PathFindingAgent* agent)
{
	agent->m_animFrame = 0;
	agent->m_animTimer = 0;
}