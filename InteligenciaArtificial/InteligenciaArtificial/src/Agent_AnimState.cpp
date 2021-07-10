#include "Agent_AnimState.h"
#include "Globals.h"
#include "Agent.h"

void Agent_AnimState::Enter(Agent* agent)
{
	agent->m_animFrame = 0;
	agent->m_animTimer = 0;

	agent->m_shape.setTexture(m_atlasMap);
	agent->m_shape.setTextureRect(m_sequenceRects[0]);
}

eAGENT_ANIM_STATE_TYPE Agent_AnimState::Update(Agent* agent)
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

	return eAGENT_ANIM_STATE_TYPE::NONE;
}

void Agent_AnimState::Exit(Agent* agent)
{
	agent->m_animFrame = 0;
	agent->m_animTimer = 0;
}
