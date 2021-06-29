#pragma once
#include "PunchState.h"

class PunchA : public PunchState
{
public:
	PunchA();
	~PunchA();

	void Enter();
	ePUNCH_TYPE UpdatePunch(Player* player);
	void Exit();

private:
};