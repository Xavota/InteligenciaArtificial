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

void CrouchState::Enter()
{
	system("cls");
	cout << "Crouching" << endl;
}

eSTATE_TYPE CrouchState::Update(Player* player)
{
	if (!gl::Input::GetKey(sf::Keyboard::LShift))
	{
		return eSTATE_TYPE::STAND;
	}
	if (gl::Input::GetKeyPressed(sf::Keyboard::Z))
	{
		return eSTATE_TYPE::KICK;
	}
	return eSTATE_TYPE::CROUCH;
}

void CrouchState::Exit()
{
}
