#pragma once
#include "State.h"

class OnGroundState : public State
{
public:
	OnGroundState();
	~OnGroundState();

	void Enter(Player* a);
	State* Update();
	void Exit();

private:

};

