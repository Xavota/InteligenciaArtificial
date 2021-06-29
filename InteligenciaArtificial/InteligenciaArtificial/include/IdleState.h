#pragma once
#include "State.h"

class IdleState : public State
{
public:
	IdleState();
	~IdleState();

	void Enter();
	eSTATE_TYPE Update(Player* player);
	void Exit();

private:

};

