#include "PunchState.h"
#include "OnGroundState.h"

#include "Globals.h"
#include "Player.h"

#include <iostream>
#include <string>
using std::cout;
using std::endl;

PunchState::PunchState()
{
}

PunchState::~PunchState()
{
}

void PunchState::Enter(Player* a)
{
	m_player = a;
	cout << "Punching" << endl;
}

eSTATE_TYPE PunchState::Update()
{
	m_timer += gl::DeltaTime::Time();
	if (m_timer >= 1.0f)
	{
		return eSTATE_TYPE::STAND;
	}
	return eSTATE_TYPE::PUNCH;
}

void PunchState::Exit()
{
	m_timer = 0;
}
