#include "Agent_PathFindingAnimMachine.h"
#include "Globals.h"
#include "PathFindingAgent.h"

#include "Agent_PathFindingWaitingAnimState.h"
#include "Agent_PathFindingFollowingUpAnimState.h"
#include "Agent_PathFindingFollowingRightAnimState.h"
#include "Agent_PathFindingFollowingDownAnimState.h"
#include "Agent_PathFindingFollowingLeftAnimState.h"
#include "Agent_PathFindingArriveAnimState.h"


Agent_PathFindingAnimMachine::Agent_PathFindingAnimMachine()
{
}

Agent_PathFindingAnimMachine::~Agent_PathFindingAnimMachine()
{
}

void Agent_PathFindingAnimMachine::Init()
{
	for (int i = 0; i < (int)eAGENT_PATH_FINDING_ANIM_STATE_TYPE::COUNT; i++)
	{
		switch ((eAGENT_PATH_FINDING_ANIM_STATE_TYPE)i)
		{
		case eAGENT_PATH_FINDING_ANIM_STATE_TYPE::WAITING:
			m_states.push_back(new Agent_PathFindingWaitingAnimState(
													  {
													  	  {144, 1, 48, 48}
													  }, 
													  gl::CTexture::GetTexture("Anim"), 4, true));
			break;
		case eAGENT_PATH_FINDING_ANIM_STATE_TYPE::FOLLIWING_UP:
			m_states.push_back(new Agent_PathFindingFollowingUpAnimState(
													{
														{144, 145, 48, 48},
														{192, 145, 48, 48},
														{240, 145, 48, 48},
														{192, 145, 48, 48}
													},
													gl::CTexture::GetTexture("Anim"), 4, true));
			break;
		case eAGENT_PATH_FINDING_ANIM_STATE_TYPE::FOLLIWING_RIGHT:
			m_states.push_back(new Agent_PathFindingFollowingRightAnimState(
													{
														{144, 97, 48, 48},
														{192, 97, 48, 48},
														{240, 97, 48, 48},
														{192, 97, 48, 48}
													},
													gl::CTexture::GetTexture("Anim"), 4, true));
			break;
		case eAGENT_PATH_FINDING_ANIM_STATE_TYPE::FOLLIWING_DOWN:
			m_states.push_back(new Agent_PathFindingFollowingDownAnimState(
													{
														{144, 1, 48, 48},
														{192, 1, 48, 48},
														{240, 1, 48, 48},
														{192, 1, 48, 48}
													},
													gl::CTexture::GetTexture("Anim"), 4, true));
			break;
		case eAGENT_PATH_FINDING_ANIM_STATE_TYPE::FOLLIWING_LEFT:
			m_states.push_back(new Agent_PathFindingFollowingLeftAnimState(
				{
					{144, 49, 48, 48},
					{192, 49, 48, 48},
					{240, 49, 48, 48},
					{192, 49, 48, 48}
				},
				gl::CTexture::GetTexture("Anim"), 4, true));
			break;
		case eAGENT_PATH_FINDING_ANIM_STATE_TYPE::ARRIVE:
			m_states.push_back(new Agent_PathFindingArriveAnimState(
				{
					{144, 1, 48, 48}
				},
				gl::CTexture::GetTexture("Anim"), 4, true));
			break;
		}
	}

	m_state = nullptr;
}

void Agent_PathFindingAnimMachine::Update(PathFindingAgent* agent)
{
	if (agent->GetAnimState() == eAGENT_PATH_FINDING_ANIM_STATE_TYPE::NONE)
	{
		agent->SetAnimState(eAGENT_PATH_FINDING_ANIM_STATE_TYPE::WAITING);
		m_state = m_states[(int)eAGENT_PATH_FINDING_ANIM_STATE_TYPE::WAITING];
		m_state->Enter(agent);
	}

	eAGENT_PATH_FINDING_ANIM_STATE_TYPE current = agent->GetAnimState();
	m_state = m_states[int(current)];

	eAGENT_PATH_FINDING_ANIM_STATE_TYPE next = m_state->Update(agent);

	if (next != current)
	{
		m_state->Exit(agent);
		m_state = m_states[int(next)];
		agent->SetAnimState(next);
		m_state->Enter(agent);
	}
}

void Agent_PathFindingAnimMachine::Destroy()
{
	for (int i = 0; i < m_states.size(); i++)
	{
		delete m_states[i];
	}

	m_states.clear();
}