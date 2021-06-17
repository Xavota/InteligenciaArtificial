#include "IdleState.h"

#include "Globals.h"
#include "Player.h"

IdleState::IdleState()
{
}

IdleState::~IdleState()
{
}

void IdleState::Enter(Player* a)
{
	m_player = a;
}

State* IdleState::Update()
{
	return this;
}

void IdleState::Exit()
{
}
