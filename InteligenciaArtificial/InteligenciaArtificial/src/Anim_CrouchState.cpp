#include "Anim_CrouchState.h"
#include "Globals.h"

#include "Player.h"

Anim_CrouchState::Anim_CrouchState(std::vector<sf::IntRect> sequence, sf::Texture* atlasMap, float fps, bool repeat)
{
	m_sequenceRects = sequence;
	m_atlasMap = atlasMap;

	m_fps = fps;
	m_repeat = repeat;
}

Anim_CrouchState::~Anim_CrouchState()
{
}

void Anim_CrouchState::Enter(Player* player)
{
	Anim_State::Enter(player);
}

eANIM_TYPE Anim_CrouchState::Update(Player* player)
{
	Anim_State::Update(player);

	if (!gl::Input::GetKey(sf::Keyboard::LShift))
	{
		return eANIM_TYPE::IDLE;
	}
	if (gl::Input::GetKeyPressed(sf::Keyboard::Z))
	{
		return eANIM_TYPE::KICK;
	}

	return eANIM_TYPE::CROUCH;
}

void Anim_CrouchState::Exit(Player* player)
{
	Anim_State::Exit(player);
}
