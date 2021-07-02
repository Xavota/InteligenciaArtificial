#include "Anim_PunchAState.h"
#include "Globals.h"

#include "Player.h"

Anim_PunchAState::Anim_PunchAState(std::vector<sf::IntRect> sequence, sf::Texture* atlasMap, float fps, bool repeat)
{
	m_sequenceRects = sequence;
	m_atlasMap = atlasMap;

	m_fps = fps;
	m_repeat = repeat;
}

Anim_PunchAState::~Anim_PunchAState()
{
}

void Anim_PunchAState::Enter(Player* player)
{
	Anim_State::Enter(player);
}

eANIM_TYPE Anim_PunchAState::Update(Player* player)
{
	Anim_State::Update(player);

	player->m_animPunchTimer += gl::DeltaTime::Time();
	if (player->m_animPunchTimer >= 1.0f)
	{
		player->m_animPunchTimer = 0;
		return eANIM_TYPE::IDLE;
	}
	else if (gl::Input::GetKeyPressed(sf::Keyboard::Z) && player->m_animPunchTimer >= 0.5f)
	{
		player->m_animPunchTimer = 0;
		return eANIM_TYPE::PUNCHB;
	}
	return eANIM_TYPE::PUNCHA;
}

void Anim_PunchAState::Exit(Player* player)
{
	Anim_State::Exit(player);
}
