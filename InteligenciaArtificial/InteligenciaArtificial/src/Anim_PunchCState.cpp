#include "Anim_PunchCState.h"
#include "Globals.h"

#include "Player.h"

Anim_PunchCState::Anim_PunchCState(std::vector<sf::IntRect> sequence, sf::Texture* atlasMap, float fps, bool repeat)
{
	m_sequenceRects = sequence;
	m_atlasMap = atlasMap;

	m_fps = fps;
	m_repeat = repeat;
}

Anim_PunchCState::~Anim_PunchCState()
{
}

void Anim_PunchCState::Enter(Player* player)
{
	Anim_State::Enter(player);
}

eANIM_TYPE Anim_PunchCState::Update(Player* player)
{
	Anim_State::Update(player);

	player->m_animPunchTimer += gl::DeltaTime::Time();
	if (player->m_animPunchTimer >= 1.0f)
	{
		player->m_animPunchTimer = 0;
		return eANIM_TYPE::IDLE;
	}
	return eANIM_TYPE::PUNCHC;
}

void Anim_PunchCState::Exit(Player* player)
{
	Anim_State::Exit(player);
}
