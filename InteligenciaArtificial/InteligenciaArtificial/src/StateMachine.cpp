#include "StateMachine.h"
#include "State.h"
#include "OnGroundState.h"

#include "Globals.h"
#include "Player.h"

StateMachine::StateMachine()
{
}

StateMachine::~StateMachine()
{
}

void StateMachine::Init(Player* p)
{
	m_pl = p;
	m_state = new OnGroundState();
}

void StateMachine::Update()
{
	State* s = nullptr;
	s = m_state->Update();

	if (s != m_state)
	{
		m_state->Exit();
		delete m_state;
		m_state = s;
		m_state->Enter(m_pl);
	}


}

void StateMachine::Destroy()
{
}
