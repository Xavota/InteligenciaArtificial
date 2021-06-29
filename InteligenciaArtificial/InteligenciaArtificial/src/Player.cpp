#include "Player.h"

void Player::Init(sf::Vector2f pos, sf::Vector2f size, sf::Texture* tex, float velocity, float jumpStrength, StateMachine* machine)
{
	m_shape.setPosition(pos);
	m_shape.setSize(size);
	m_shape.setTextureRect(sf::IntRect({3,115},{26,56}));
	m_shape.setTexture(tex);
	
	m_velocity = velocity;
	m_jumpStrength = jumpStrength;

	m_machine = machine;
}

void Player::Update()
{
	m_machine->Update(this);
}

void Player::Render(sf::RenderWindow* window)
{
	window->draw(m_shape);
}

void Player::Destroy()
{
	m_machine->Destroy();
}

eSTATE_TYPE Player::GetState()
{
	return m_state;
}

void Player::SetState(eSTATE_TYPE s)
{
	m_state = s;
}

ePUNCH_TYPE Player::GetPunchState()
{
	return m_punchState;
}

void Player::SetPunchState(ePUNCH_TYPE s)
{
	m_punchState = s;
}
