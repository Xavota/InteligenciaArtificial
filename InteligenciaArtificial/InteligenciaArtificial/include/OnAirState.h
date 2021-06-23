#pragma once
#include "State.h"

class OnAirState : public State
{
public:
	OnAirState();
	~OnAirState();

	void Enter(Player* a);
	eSTATE_TYPE Update();
	void Exit();

private:
	
};

