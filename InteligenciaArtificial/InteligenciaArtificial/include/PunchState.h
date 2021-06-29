#pragma once
#include "State.h"
#include <vector>

enum class ePUNCH_TYPE
{
	NONE = -1,
	PUNCHA,
	PUNCHB,
	PUNCHC,
	RETURN,
	COUNT
};


class PunchState : public State
{
public:
	PunchState();
	~PunchState();

	void Enter();
	eSTATE_TYPE Update(Player* player);
	void Exit();
	virtual ePUNCH_TYPE UpdatePunch(Player* player){return ePUNCH_TYPE::NONE;}

private:
	PunchState* m_punchState = nullptr;

	std::vector<PunchState*> m_punchStates;
};

