#pragma once
#include "PunchState.h"

class PunchB : public PunchState
{
public:
	PunchB();
	~PunchB();

	void Enter();
	ePUNCH_TYPE UpdatePunch(Player* player);
	void Exit();

private:
};
