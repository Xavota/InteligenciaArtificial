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

void OnGroundState::Enter()
{
	system("cls");
	cout << "On ground" << endl;
}

eSTATE_TYPE OnGroundState::Update(Player* player)
{
	if (gl::Input::GetKey(sf::Keyboard::LShift))
	{
		return eSTATE_TYPE::CROUCH;
	}
	if (gl::Input::GetKeyPressed(sf::Keyboard::Z))
	{
		return eSTATE_TYPE::PUNCH;
	}
	return eSTATE_TYPE::STAND;
}

void OnGroundState::Exit()
{
}
