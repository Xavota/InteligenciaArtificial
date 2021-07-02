#include "Anim_State.h"
#include "Globals.h"

#include "Player.h"

void Anim_State::Enter(Player* player)
{
	player->m_animFrame = 0;
	player->m_animTimer = 0;

	player->m_shape.setTexture(m_atlasMap);
	player->m_shape.setTextureRect(m_sequenceRects[0]);
}

eANIM_TYPE Anim_State::Update(Player* player)
{
	player->m_animTimer += gl::DeltaTime::Time();

	if (player->m_animTimer > 1 / m_fps)
	{
		player->m_animFrame = m_repeat 
						        ? ((player->m_animFrame + 1) % m_sequenceRects.size()) 
								: (player->m_animFrame < (m_sequenceRects.size() - 1) 
								  ? player->m_animFrame + 1 
								  : player->m_animFrame);

		player->m_shape.setTextureRect(m_sequenceRects[player->m_animFrame]);

		player->m_animTimer = 0;
	}

	return eANIM_TYPE::NONE;
}

void Anim_State::Exit(Player* player)
{
	player->m_animFrame = 0;
	player->m_animTimer = 0;
}
