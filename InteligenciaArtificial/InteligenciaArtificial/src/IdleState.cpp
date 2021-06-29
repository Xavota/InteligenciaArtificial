#include "IdleState.h"

#include "Globals.h"
#include "Player.h"

IdleState::IdleState()
{
}

IdleState::~IdleState()
{
}

void IdleState::Enter()
{
}

eSTATE_TYPE IdleState::Update(Player* player)
{
	return eSTATE_TYPE::NONE;
}

void IdleState::Exit()
{
}
