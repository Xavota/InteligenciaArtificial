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

State* OnAirState::Update()
{
	return this;
}

void OnAirState::Exit()
{
}
