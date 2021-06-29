#include "PunchA.h"

#include "Globals.h"
#include "Player.h"

#include <iostream>
#include <string>
using std::cout;
using std::endl;

PunchA::PunchA()
{
}

PunchA::~PunchA()
{
}

void PunchA::Enter()
{
	system("cls");
	cout << "PunchA" << endl;
}

ePUNCH_TYPE PunchA::UpdatePunch(Player* player)
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
		return ePUNCH_TYPE::PUNCHB;
	}
	return ePUNCH_TYPE::PUNCHA;
}

void PunchA::Exit()
{
}
