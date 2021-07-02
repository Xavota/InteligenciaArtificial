#pragma once
#include "Anim_State.h"
class Anim_PunchCState : public Anim_State
{
public:
	Anim_PunchCState(std::vector<sf::IntRect> sequence, sf::Texture* atlasMap, float fps, bool repeat);
	~Anim_PunchCState();

	void Enter(class Player* player);
	eANIM_TYPE Update(class Player* player);
	void Exit(class Player* player);	
};

