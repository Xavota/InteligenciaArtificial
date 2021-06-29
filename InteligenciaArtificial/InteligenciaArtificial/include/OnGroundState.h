#pragma once
#include "State.h"

class OnGroundState : public State
{
public:
	OnGroundState();
	~OnGroundState();

	void Enter();
	eSTATE_TYPE Update(Player* player);
	void Exit();

private:

};

