#include "Flag.h"
#include "Agent.h"
#include "Game.h"
#include "Globals.h"

Flag::Flag(sf::Vector2f pos)
{
	Init(pos);
}

void Flag::Init(sf::Vector2f pos)
{
	m_shape.setPosition(pos);
	m_shape.setFillColor(sf::Color::Green);
	m_shape.setSize({40,40});
	m_shape.setOrigin(m_shape.getSize() * .5f);
	m_shape.setTexture(gl::CTexture::GetTexture("Flag"));
}

void Flag::Update()
{
	if (m_carrier != nullptr)
	{
		m_shape.setPosition(m_carrier->getPosition());
	}

	m_timeTillUp -= gl::DeltaTime::Time();
}

void Flag::Render(sf::RenderWindow* window)
{
	window->draw(m_shape);
}

void Flag::Destroy()
{
}

Agent* Flag::GetCarrier()
{
	return m_carrier;
}

void Flag::SetCarrier(Agent* carrier)
{
	m_carrier = carrier;
	if (carrier != nullptr)
		m_timeTillUp = 1.0f;
	else
		m_timeTillUp = 0.0f;	
}

sf::Vector2f Flag::GetPosition()
{
	return m_shape.getPosition();
}

void Flag::SetPosition(sf::Vector2f pos)
{
	m_shape.setPosition(pos);
}

float Flag::GetRadious()
{
	return m_radious;
}

bool Flag::CanBePickedUp()
{
	return m_timeTillUp <= 0;
}
