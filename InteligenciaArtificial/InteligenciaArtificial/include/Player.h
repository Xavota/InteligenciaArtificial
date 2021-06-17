#pragma once
#include <SFML/Graphics.hpp>
#include "StateMachine.h"

class Player
{
public:
	Player() = default;
	~Player() = default;

	void Init(sf::Vector2f pos, sf::Vector2f size, sf::Texture* tex, float velocity, float jumpStrength);
	void Update();
	void Render(sf::RenderWindow* window);
	void Destroy();

private:
	float m_velocity;
	float m_jumpStrength;
	sf::RectangleShape m_shape;

	StateMachine m_machine;
};

