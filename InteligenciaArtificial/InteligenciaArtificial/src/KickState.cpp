#include "KickState.h"
#include "CrouchState.h"	

#include "Globals.h"
#include "Player.h"

#include <iostream>
#include <string>
using std::cout;
using std::endl;

KickState::KickState()
{
}

KickState::~KickState()
{
}

void KickState::Enter(Player* a)
{
	m_player = a;
	cout << "Kicking" << endl;
}

eSTATE_TYPE KickState::Update()
{
	m_timer += gl::DeltaTime::Time();
	if (m_timer >= 1.0f)
	{
		return eSTATE_TYPE::CROUCH;
	}
	return eSTATE_TYPE::KICK;
}

void KickState::Exit()
{
	m_timer = 0;
}
