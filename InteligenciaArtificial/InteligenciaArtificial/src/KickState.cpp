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

State* KickState::Update()
{
	m_timer += gl::DeltaTime::Time();
	if (m_timer >= 1.0f)
	{
		return new CrouchState();
	}
	return this;
}

void KickState::Exit()
{
}
