#include "StateMachine.h"
#include "State.h"
#include "OnGroundState.h"
#include "CrouchState.h"
#include "PunchState.h"
#include "KickState.h"

#include "Globals.h"
#include "Player.h"

StateMachine::StateMachine()
{
}

StateMachine::~StateMachine()
{
}

void StateMachine::Init()
{
	for (int i = 0; i < (int)eSTATE_TYPE::COUNT; i++)
	{
		switch ((eSTATE_TYPE)i)
		{
		case eSTATE_TYPE::STAND:
			m_states.push_back(new OnGroundState());
			break;
		case eSTATE_TYPE::CROUCH:
			m_states.push_back(new CrouchState());
			break;
		case eSTATE_TYPE::PUNCH:
			m_states.push_back(new PunchState());
			break;
		case eSTATE_TYPE::KICK:
			m_states.push_back(new KickState());
			break;
		}
	}

	m_state = m_states[0];
}

void StateMachine::Update(Player* player)
{
	eSTATE_TYPE current = player->GetState();
	m_state = m_states[int(current)];

	eSTATE_TYPE next = m_state->Update(player);

	if (next != current)
	{
		m_state->Exit();
		m_state = m_states[int(next)];
		player->SetState(next);
		m_state->Enter();
	}


}

void StateMachine::Destroy()
{
	for (int i = 0; i < m_states.size(); i++)
	{
		delete m_states[i];
	}
	m_states.clear();
}
