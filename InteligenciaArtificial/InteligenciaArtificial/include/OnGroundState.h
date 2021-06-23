#pragma once
#include "State.h"

class OnGroundState : public State
{
public:
	OnGroundState();
	~OnGroundState();

	void Enter(Player* a);
	eSTATE_TYPE Update();
	void Exit();

private:

};

