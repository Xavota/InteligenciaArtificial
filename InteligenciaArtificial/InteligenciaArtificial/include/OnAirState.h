#pragma once
#include "State.h"

class OnAirState : public State
{
public:
	OnAirState();
	~OnAirState();

	void Enter();
	eSTATE_TYPE Update(Player* player);
	void Exit();

private:
	
};

