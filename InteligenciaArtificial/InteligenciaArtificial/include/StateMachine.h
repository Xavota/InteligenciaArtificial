#pragma once
#include "State.h"

class Player;

class StateMachine
{
public:
	StateMachine();
	~StateMachine();

	void Init(Player* p);
	void Update();
	void Destroy();

private:
	Player* m_pl;
	State* m_state = nullptr;

};