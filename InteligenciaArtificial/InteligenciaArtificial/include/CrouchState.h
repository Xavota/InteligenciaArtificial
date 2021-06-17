#pragma once
#include "State.h"

class CrouchState : public State
{
public:
	CrouchState();
	~CrouchState();

	void Enter(Player* a);
	State* Update();
	void Exit();

private:

};

