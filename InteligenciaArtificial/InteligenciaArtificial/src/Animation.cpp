#include "Animation.h"
#include "Player.h"

#include "Anim_IdleState.h"
#include "Anim_CrouchState.h"
#include "Anim_PunchAState.h"
#include "Anim_PunchBState.h"
#include "Anim_PunchCState.h"
#include "Anim_KickState.h"

#include "Globals.h"

Animation::Animation()
{
}

Animation::~Animation()
{
}

void Animation::Init()
{
	for (int i = 0; i < (int)eANIM_TYPE::COUNT; i++)
	{
		switch ((eANIM_TYPE)i)
		{
		case eANIM_TYPE::IDLE:
			m_states.push_back(new Anim_IdleState({ {0,   0, 70, 57},
													{71,  0, 70, 57},
													{142, 0, 70, 57},
													{213, 0, 70, 57},
													{284, 0, 70, 57},
													{355, 0, 70, 57} }, 
													gl::CTexture::GetTexture("Player"), 12, true));
			break;
		case eANIM_TYPE::CROUCH:
			m_states.push_back(new Anim_CrouchState({ {0,   232, 70, 57} },
													  gl::CTexture::GetTexture("Player"), 12, true));
			break;
		case eANIM_TYPE::PUNCHA:
			m_states.push_back(new Anim_PunchAState({ {0,   58, 70, 57},
													  {71,  58, 70, 57},
													  {142, 58, 70, 57},
													  {213, 58, 70, 57},
													  {284, 58, 70, 57},
													  {355, 58, 70, 57} },
													  gl::CTexture::GetTexture("Player"), 12, false));
			break;
		case eANIM_TYPE::PUNCHB:
			m_states.push_back(new Anim_PunchBState({ {0,   116, 70, 57},
													  {71,  116, 70, 57},
													  {142, 116, 70, 57},
													  {213, 116, 70, 57},
													  {284, 116, 70, 57},
													  {355, 116, 70, 57} },
													  gl::CTexture::GetTexture("Player"), 12, false));
			break;
		case eANIM_TYPE::PUNCHC:
			m_states.push_back(new Anim_PunchCState({ {0,   174, 70, 57},
													  {71,  174, 70, 57},
													  {142, 174, 70, 57},
													  {213, 174, 70, 57},
													  {284, 174, 70, 57},
													  {355, 174, 70, 57} },
													  gl::CTexture::GetTexture("Player"), 12, false));
			break;
		case eANIM_TYPE::KICK:
			m_states.push_back(new Anim_KickState({ {0,   290, 70, 57},
													{71,  290, 70, 57},
													{142, 290, 70, 57},
													{213, 290, 70, 57}, },
													gl::CTexture::GetTexture("Player"), 20, false));
			break;
		}
	}

	m_state = nullptr;
}

void Animation::Update(Player* player)
{
	eANIM_TYPE current = player->m_animState;
	if (m_state == nullptr)
	{
		m_state = m_states[int(current)];
		m_state->Enter(player);
	}
	else
	{
		m_state = m_states[int(current)];
	}


	eANIM_TYPE next = m_state->Update(player);

	if (next != current)
	{
		m_state->Exit(player);
		m_state = m_states[int(next)];
		player->m_animState = next;
		m_state->Enter(player);
	}
}

void Animation::Destroy()
{
	for (int i = 0; i < m_states.size(); i++)
	{
		delete m_states[i];
	}

	m_states.clear();
}
