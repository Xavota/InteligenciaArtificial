#include "PunchB.h"

#include "Globals.h"
#include "Player.h"

#include <iostream>
#include <string>
using std::cout;
using std::endl;

PunchB::PunchB()
{
}

PunchB::~PunchB()
{
}

void PunchB::Enter()
{
	system("cls");
	cout << "PunchB" << endl;
}

ePUNCH_TYPE PunchB::UpdatePunch(Player* player)
{
	player->m_punchKickTimer += gl::DeltaTime::Time();
	if (player->m_punchKickTimer >= 1.0f)
	{
		player->m_punchKickTimer = 0;
		return ePUNCH_TYPE::RETURN;
	}
	else if (gl::Input::GetKeyPressed(sf::Keyboard::Z))
	{
		player->m_punchKickTimer = 0;
		return ePUNCH_TYPE::PUNCHC;
	}
	return ePUNCH_TYPE::PUNCHB;
}

void PunchB::Exit()
{
}
