#include "Player.h"

void Player::Init(sf::Vector2f pos, sf::Vector2f size, sf::Texture* tex, float velocity, float jumpStrength)
{
	m_shape.setPosition(pos);
	m_shape.setSize(size);
	m_shape.setTextureRect(sf::IntRect({3,115},{26,56}));
	m_shape.setTexture(tex);
	
	m_velocity = velocity;
	m_jumpStrength = jumpStrength;

	m_machine.Init(this);
}

void Player::Update()
{
	m_machine.Update();
}

void Player::Render(sf::RenderWindow* window)
{
	window->draw(m_shape);
}

void Player::Destroy()
{
	m_machine.Destroy();
}
