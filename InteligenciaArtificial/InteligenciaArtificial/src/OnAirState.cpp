#include "OnAirState.h"

#include "Globals.h"
#include "Player.h"

OnAirState::OnAirState()
{
}

OnAirState::~OnAirState()
{
}

void OnAirState::Enter(Player* a)
{
	m_player = a;
}

eSTATE_TYPE OnAirState::Update()
{
	return eSTATE_TYPE::NONE;
}

void OnAirState::Exit()
{
}
