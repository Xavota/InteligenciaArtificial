#include "Agent_StateMachine.h"

#include "Agent.h"

#include "Agent_FollowFlagState.h"
#include "Agent_FollowCarrierState.h"
#include "Agent_ProtectFlagState.h"
#include "Agent_HasFlagState.h"
#include "Agent_WinLoseState.h"

Agent_StateMachine::Agent_StateMachine()
{
}

Agent_StateMachine::~Agent_StateMachine()
{
}

void Agent_StateMachine::Init()
{
	for (int i = 0; i < (int)eAGENT_STATE_TYPE::COUNT; i++)
	{
		switch ((eAGENT_STATE_TYPE)i)
		{
		case eAGENT_STATE_TYPE::FOLLOW_FLAG:
			m_states.push_back(new Agent_FollowFlagState());
			break;
		case eAGENT_STATE_TYPE::FOLLOW_CARRIER:
			m_states.push_back(new Agent_FollowCarrierState());
			break;
		case eAGENT_STATE_TYPE::PROTECT_FALG:
			m_states.push_back(new Agent_ProtectFlagState());
			break;
		case eAGENT_STATE_TYPE::HAS_FLAG:
			m_states.push_back(new Agent_HasFlagState());
			break;
		case eAGENT_STATE_TYPE::WIN_LOSE:
			m_states.push_back(new Agent_WinLoseState());
			break;
		}
	}

	m_state = m_states[0];
}

void Agent_StateMachine::Update(Agent* agent)
{
	if (agent->GetState() == eAGENT_STATE_TYPE::NONE)
	{
		agent->SetState(eAGENT_STATE_TYPE::FOLLOW_FLAG);
		m_state = m_states[(int)eAGENT_STATE_TYPE::FOLLOW_FLAG];
		m_state->Enter();
	}

	eAGENT_STATE_TYPE current = agent->GetState();
	m_state = m_states[int(current)];

	eAGENT_STATE_TYPE next = m_state->Update(agent);

	if (next != current)
	{
		m_state->Exit();
		m_state = m_states[int(next)];
		agent->SetState(next);
		m_state->Enter();
	}
}

void Agent_StateMachine::Destroy()
{
	for (int i = 0; i < m_states.size(); i++)
	{
		delete m_states[i];
	}
	m_states.clear();
}
