#pragma once
#include "State.h"

class KickState : public State
{
public:
	KickState();
	~KickState();

	void Enter(Player* a);
	eSTATE_TYPE Update();
	void Exit();

private:
	float m_timer = 0;
};

