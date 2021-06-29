#pragma once
#include "State.h"

class KickState : public State
{
public:
	KickState();
	~KickState();

	void Enter();
	eSTATE_TYPE Update(Player* player);
	void Exit();

private:
};

