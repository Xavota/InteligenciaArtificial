#pragma once
#include "State.h"

class OnAirState : public State
{
public:
	OnAirState();
	~OnAirState();

	void Enter(Player* a);
	State* Update();
	void Exit();

private:
	
};

