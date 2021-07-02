#pragma once
#include "Anim_State.h"

class Anim_CrouchState : public Anim_State
{
public:
	Anim_CrouchState(std::vector<sf::IntRect> sequence, sf::Texture* atlasMap, float fps, bool repeat);
	~Anim_CrouchState();

	void Enter(class Player* player);
	eANIM_TYPE Update(class Player* player);
	void Exit(class Player* player);
};

