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

void KickState::Enter()
{
	system("cls");
	cout << "Kicking" << endl;
}

eSTATE_TYPE KickState::Update(Player* player)
{
	player->m_punchKickTimer += gl::DeltaTime::Time();
	if (player->m_punchKickTimer >= 1.0f)
	{
		player->m_punchKickTimer = 0;
		return eSTATE_TYPE::CROUCH;
	}
	return eSTATE_TYPE::KICK;
}

void KickState::Exit()
{
}