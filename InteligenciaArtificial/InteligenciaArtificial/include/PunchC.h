#pragma once
#include "PunchState.h"

class PunchC : public PunchState
{
public:
	PunchC();
	~PunchC();

	void Enter();
	ePUNCH_TYPE UpdatePunch(Player* player);
	void Exit();

private:
};
