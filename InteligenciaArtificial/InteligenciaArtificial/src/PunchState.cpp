#include "PunchState.h"

#include "Globals.h"
#include "Player.h"

#include <iostream>
#include <string>

#include "PunchA.h"
#include "PunchB.h"
#include "PunchC.h"
using std::cout;
using std::endl;

PunchState::PunchState()
{
}

PunchState::~PunchState()
{
}

void PunchState::Enter()
{
	if (m_punchStates.size() < 1)
	{
		for (int i = 0; i < (int)ePUNCH_TYPE::COUNT; i++)
		{
			switch ((ePUNCH_TYPE)i)
			{
			case ePUNCH_TYPE::PUNCHA:
				m_punchStates.push_back(new PunchA());
				break;
			case ePUNCH_TYPE::PUNCHB:
				m_punchStates.push_back(new PunchB());
				break;
			case ePUNCH_TYPE::PUNCHC:
				m_punchStates.push_back(new PunchC());
				break;
			}
		}
		m_punchState = m_punchStates[0];
	}
	system("cls");
	cout << "Punching" << endl;
}

eSTATE_TYPE PunchState::Update(Player* player)
{
	/*player->m_punchKickTimer += gl::DeltaTime::Time();
	if (player->m_punchKickTimer >= 1.0f)
	{
		player->m_punchKickTimer = 0;
		return eSTATE_TYPE::STAND;
	}/**/
	m_punchState = m_punchStates[int(player->GetPunchState())];

	ePUNCH_TYPE next = m_punchState->UpdatePunch(player);

	if (next != player->GetPunchState())
	{
		m_punchState->Exit();
		if (next == ePUNCH_TYPE::RETURN)
		{
			player->SetPunchState(ePUNCH_TYPE::PUNCHA);
			return eSTATE_TYPE::STAND;
		}
		m_punchState = m_punchStates[int(next)];
		player->SetPunchState(next);
		m_punchState->Enter();
	}/**/
	return eSTATE_TYPE::PUNCH;
}

void PunchState::Exit()
{
}
