#include "Anim_KickState.h"
#include "Globals.h"

#include "Player.h"

Anim_KickState::Anim_KickState(std::vector<sf::IntRect> sequence, sf::Texture* atlasMap, float fps, bool repeat)
{
	m_sequenceRects = sequence;
	m_atlasMap = atlasMap;

	m_fps = fps;
	m_repeat = repeat;
}

Anim_KickState::~Anim_KickState()
{
}

void Anim_KickState::Enter(Player* player)
{
	Anim_State::Enter(player);
}

eANIM_TYPE Anim_KickState::Update(Player* player)
{
	Anim_State::Update(player);

	player->m_animPunchTimer += gl::DeltaTime::Time();
	if (player->m_animPunchTimer >= 0.25f)
	{
		player->m_animPunchTimer = 0;
		return eANIM_TYPE::IDLE;
	}
	return eANIM_TYPE::KICK;
}

void Anim_KickState::Exit(Player* player)
{
	Anim_State::Exit(player);
}
