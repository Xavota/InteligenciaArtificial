#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

enum class eANIM_TYPE
{
	NONE = -1,
	IDLE,
	CROUCH,
	PUNCHA,
	PUNCHB,
	PUNCHC,
	KICK,
	COUNT
};

class Anim_State
{
public: 
	Anim_State() = default;
	virtual ~Anim_State() = default;

	virtual void Enter(class Player* player);
	virtual eANIM_TYPE Update(class Player* player);
	virtual void Exit(class Player* player);
protected:
	std::vector<sf::IntRect> m_sequenceRects;
	sf::Texture* m_atlasMap = nullptr;

	float m_fps = 0;
	bool m_repeat = false;
};

