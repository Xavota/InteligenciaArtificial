#include "Anim_IdleState.h"
#include "Globals.h"

#include "Player.h"

Anim_IdleState::Anim_IdleState(std::vector<sf::IntRect> sequence, sf::Texture* atlasMap, float fps, bool repeat)
{
	m_sequenceRects = sequence;
	m_atlasMap = atlasMap;

	m_fps = fps;
	m_repeat = repeat;
}

Anim_IdleState::~Anim_IdleState()
{
}

void Anim_IdleState::Enter(Player* player)
{
	Anim_State::Enter(player);
}

eANIM_TYPE Anim_IdleState::Update(Player* player)
{
	Anim_State::Update(player);

	if (gl::Input::GetKey(sf::Keyboard::LShift))
	{
		return eANIM_TYPE::CROUCH;
	}
	if (gl::Input::GetKeyPressed(sf::Keyboard::Z))
	{
		return eANIM_TYPE::PUNCHA;
	}

	return eANIM_TYPE::IDLE;
}

void Anim_IdleState::Exit(Player* player)
{
	Anim_State::Exit(player);
}
