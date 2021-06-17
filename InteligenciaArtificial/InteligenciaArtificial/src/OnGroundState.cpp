#include "OnGroundState.h"
#include "CrouchState.h"
#include "PunchState.h"

#include "Globals.h"
#include "Player.h"

#include <iostream>
#include <string>
using std::cout;
using std::endl;

OnGroundState::OnGroundState()
{
}

OnGroundState::~OnGroundState()
{
}

void OnGroundState::Enter(Player* a)
{
	m_player = a;
	cout << "On ground" << endl;
}

State* OnGroundState::Update()
{
	if (gl::Input::GetKey(sf::Keyboard::LShift))
	{
		return new CrouchState();
	}
	if (gl::Input::GetKeyPressed(sf::Keyboard::Z))
	{
		return new PunchState();
	}
	return this;
}

void OnGroundState::Exit()
{
}
