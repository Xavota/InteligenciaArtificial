#pragma once
#include "State.h"

class PunchState : public State
{
public:
	PunchState();
	~PunchState();

	void Enter(Player* a);
	eSTATE_TYPE Update();
	void Exit();

private:
	float m_timer = 0;
};

