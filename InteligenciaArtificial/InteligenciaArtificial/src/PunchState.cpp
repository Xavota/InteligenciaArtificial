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

State* PunchState::Update()
{
	m_timer += gl::DeltaTime::Time();
	if (m_timer >= 1.0f)
	{
		return new OnGroundState();
	}
	return this;
}

void PunchState::Exit()
{
}
