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

void StateMachine::Init(Player* player)
{
	m_player = player;	

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
	m_current = (eSTATE_TYPE)0;
}

void StateMachine::Update()
{
	eSTATE_TYPE next = m_state->Update();

	if (next != m_current)
	{
		m_state->Exit();
		m_state = m_states[int(next)];
		m_current = next;
		m_state->Enter(m_player);
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
