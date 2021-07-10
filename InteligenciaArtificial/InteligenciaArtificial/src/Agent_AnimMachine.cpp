#include "Agent_AnimMachine.h"
#include "Globals.h"
#include "Agent.h"

#include "Agent_AnimRunningState.h"
#include "Agent_AnimHasFlagState.h"
#include "Agent_AnimWinState.h"
#include "Agent_AnimLoseState.h"

Agent_AnimMachine::Agent_AnimMachine()
{
}

Agent_AnimMachine::~Agent_AnimMachine()
{
}

void Agent_AnimMachine::Init()
{
	for (int i = 0; i < (int)eAGENT_ANIM_STATE_TYPE::COUNT; i++)
	{
		switch ((eAGENT_ANIM_STATE_TYPE)i)
		{
		case eAGENT_ANIM_STATE_TYPE::RUNNING:
			m_states.push_back(new Agent_AnimRunningState({ {11,  1, 49, 68},
															{76,  3, 49, 68},
															{146, 3, 49, 68},
															{216, 3, 49, 68},
															{287, 3, 49, 68},
															{358, 3, 49, 68},
															{429, 3, 49, 68},
															{497, 3, 49, 68},
															{569, 3, 49, 68} },
				gl::CTexture::GetTexture("Agent"), 18, true));
			break;
		case eAGENT_ANIM_STATE_TYPE::HAS_FLAG:
			m_states.push_back(new Agent_AnimHasFlagState({ {578, 211, 49, 68},
															{649, 213, 49, 68},
															{716, 212, 49, 68},
															{786, 211, 49, 68} },
				gl::CTexture::GetTexture("Agent"), 18, true));
			break;
		case eAGENT_ANIM_STATE_TYPE::WIN:
			m_states.push_back(new Agent_AnimWinState({ {10,  352, 49, 68},
														{81,  352, 49, 68},
														{153, 352, 49, 68},
														{222, 352, 49, 68},
														{292, 352, 49, 68},
														{364, 352, 49, 68} },
				gl::CTexture::GetTexture("Agent"), 8, true));
			break;
		case eAGENT_ANIM_STATE_TYPE::LOSE:
			m_states.push_back(new Agent_AnimLoseState({ {10,  209, 49, 68},
														 {78,  209, 49, 68},
														 {151, 209, 49, 68},
														 {223, 209, 49, 68},
														 {292, 209, 49, 68},
														 {360, 209, 49, 68},
														 {433, 209, 49, 68},
														 {505, 209, 49, 68} },
				gl::CTexture::GetTexture("Agent"), 8, true));
			break;
		}
	}

	m_state = nullptr;
}

void Agent_AnimMachine::Update(Agent* agent)
{
	if (agent->GetAnimState() == eAGENT_ANIM_STATE_TYPE::NONE)
	{
		agent->SetAnimState(eAGENT_ANIM_STATE_TYPE::RUNNING);
		m_state = m_states[(int)eAGENT_ANIM_STATE_TYPE::RUNNING];
		m_state->Enter(agent);
	}

	eAGENT_ANIM_STATE_TYPE current = agent->GetAnimState();
	m_state = m_states[int(current)];

	eAGENT_ANIM_STATE_TYPE next = m_state->Update(agent);

	if (next != current)
	{
		m_state->Exit(agent);
		m_state = m_states[int(next)];
		agent->SetAnimState(next);
		m_state->Enter(agent);
	}
}

void Agent_AnimMachine::Destroy()
{
	for (int i = 0; i < m_states.size(); i++)
	{
		delete m_states[i];
	}

	m_states.clear();
}
