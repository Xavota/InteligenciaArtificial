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

eSTATE_TYPE IdleState::Update()
{
	return eSTATE_TYPE::NONE;
}

void IdleState::Exit()
{
}
