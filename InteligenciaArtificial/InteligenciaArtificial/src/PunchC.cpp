#include "PunchC.h"

#include "Globals.h"
#include "Player.h"

#include <iostream>
#include <string>
using std::cout;
using std::endl;

PunchC::PunchC()
{
}

PunchC::~PunchC()
{
}

void PunchC::Enter()
{
	system("cls");
	cout << "PunchC" << endl;
}

ePUNCH_TYPE PunchC::UpdatePunch(Player* player)
{
	player->m_punchKickTimer += gl::DeltaTime::Time();
	if (player->m_punchKickTimer >= 1.0f)
	{
		player->m_punchKickTimer = 0;
		return ePUNCH_TYPE::RETURN;
	}
	return ePUNCH_TYPE::PUNCHC;
}

void PunchC::Exit()
{
}
