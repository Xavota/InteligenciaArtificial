#pragma once
#include "State.h"

class PunchState : public State
{
public:
	PunchState();
	~PunchState();

	void Enter(Player* a);
	State* Update();
	void Exit();

private:
	float m_timer = 0;
};

