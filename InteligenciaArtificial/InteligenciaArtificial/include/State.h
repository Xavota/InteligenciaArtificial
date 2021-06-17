#pragma once
class Player;

class State
{
public:
	State();
	virtual ~State();

	virtual void Enter(Player* a) = 0;
	virtual State* Update() = 0;
	virtual void Exit() = 0;

protected:
	Player* m_player;
};

