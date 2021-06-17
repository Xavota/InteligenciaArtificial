#pragma once
#include "State.h"

class IdleState : public State
{
public:
	IdleState();
	~IdleState();

	void Enter(Player* a);
	State* Update();
	void Exit();

private:

};

