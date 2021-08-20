#include "Agent_PathFindingStateMachine.h"

#include "PathFindingAgent.h"

#include "Agent_PathFindingWaitingState.h"
#include "Agent_PathFindingFolowingState.h"
#include "Agent_PathFindingArriveState.h"


Agent_PathFindingStateMachine::Agent_PathFindingStateMachine()
{
}

Agent_PathFindingStateMachine::~Agent_PathFindingStateMachine()
{
}

void Agent_PathFindingStateMachine::Init()
{
	for (int i = 0; i < (int)eAGENT_PATH_FINDING_STATE_TYPE::COUNT; i++)
	{
		switch ((eAGENT_PATH_FINDING_STATE_TYPE)i)
		{
		case eAGENT_PATH_FINDING_STATE_TYPE::WAITING:
			m_states.push_back(new Agent_PathFindingWaitingState());
			break;
		case eAGENT_PATH_FINDING_STATE_TYPE::FOLLIWING:
			m_states.push_back(new Agent_PathFindingFolowingState());
			break;
		case eAGENT_PATH_FINDING_STATE_TYPE::ARRIVE:
			m_states.push_back(new Agent_PathFindingArriveState());
			break;
		}
	}

	m_state = m_states[0];
}

void Agent_PathFindingStateMachine::Update(PathFindingAgent* agent)
{
	if (agent->GetState() == eAGENT_PATH_FINDING_STATE_TYPE::NONE)
	{
		agent->SetState(eAGENT_PATH_FINDING_STATE_TYPE::WAITING);
		m_state = m_states[(int)eAGENT_PATH_FINDING_STATE_TYPE::WAITING];
		m_state->Enter(agent);
	}

	eAGENT_PATH_FINDING_STATE_TYPE current = agent->GetState();
	m_state = m_states[int(current)];

	eAGENT_PATH_FINDING_STATE_TYPE next = m_state->Update(agent);

	if (next != current)
	{
		m_state->Exit(agent);
		m_state = m_states[int(next)];
		agent->SetState(next);
		m_state->Enter(agent);
	}
}

void Agent_PathFindingStateMachine::Destroy()
{
	for (int i = 0; i < m_states.size(); i++)
	{
		delete m_states[i];
	}
	m_states.clear();
}