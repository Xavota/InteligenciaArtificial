#pragma once
#include "Anim_State.h"

class Anim_PunchAState : public Anim_State
{
public:
	Anim_PunchAState(std::vector<sf::IntRect> sequence, sf::Texture* atlasMap, float fps, bool repeat);
	~Anim_PunchAState();

	void Enter(class Player* player);
	eANIM_TYPE Update(class Player* player);
	void Exit(class Player* player);
};

