#pragma once
#include "State.h"

class CrouchState : public State
{
public:
	CrouchState();
	~CrouchState();

	void Enter();
	eSTATE_TYPE Update(Player* player);
	void Exit();

private:

};

