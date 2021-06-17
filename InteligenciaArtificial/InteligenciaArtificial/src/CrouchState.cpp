#include "CrouchState.h"
#include "OnGroundState.h"
#include "KickState.h"

#include "Globals.h"
#include "Player.h"

#include <iostream>
#include <string>
using std::cout;
using std::endl;

CrouchState::CrouchState()
{
}

CrouchState::~CrouchState()
{
}

void CrouchState::Enter(Player* a)
{
	m_player = a;
	cout << "Crouching" << endl;
}

State* CrouchState::Update()
{
	if (!gl::Input::GetKey(sf::Keyboard::LShift))
	{
		return new OnGroundState();
	}
	if (gl::Input::GetKeyPressed(sf::Keyboard::Z))
	{
		return new KickState();
	}
	return this;
}

void CrouchState::Exit()
{
}
