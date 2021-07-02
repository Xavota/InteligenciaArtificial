#pragma once
#include "Anim_State.h"
#include <vector>

class Animation
{
public: 
	Animation();
	~Animation();

	void Init();
	void Update(class Player* player);
	void Destroy();

private:
	Anim_State* m_state;

	std::vector<Anim_State*> m_states;

};

