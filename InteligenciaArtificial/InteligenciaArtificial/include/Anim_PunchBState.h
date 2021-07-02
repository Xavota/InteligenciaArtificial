#pragma once
#include "Anim_State.h"
class Anim_PunchBState : public Anim_State
{
public:
	Anim_PunchBState(std::vector<sf::IntRect> sequence, sf::Texture* atlasMap, float fps, bool repeat);
	~Anim_PunchBState();

	void Enter(class Player* player);
	eANIM_TYPE Update(class Player* player);
	void Exit(class Player* player);
};

