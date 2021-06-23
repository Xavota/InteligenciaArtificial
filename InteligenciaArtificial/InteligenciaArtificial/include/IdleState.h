#pragma once
#include "State.h"

class IdleState : public State
{
public:
	IdleState();
	~IdleState();

	void Enter(Player* a);
	eSTATE_TYPE Update();
	void Exit();

private:

};

