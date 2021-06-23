#pragma once
#include "State.h"

class CrouchState : public State
{
public:
	CrouchState();
	~CrouchState();

	void Enter(Player* a);
	eSTATE_TYPE Update();
	void Exit();

private:

};

