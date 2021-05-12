#include "Agent.h"
#include "Globals.h"

Agent::Agent(float x, float y, sf::Color color, eBEHAVIOUR behaviour)
{
	Init(x, y, color, behaviour);
}

void Agent::Init(float x, float y, sf::Color color, eBEHAVIOUR behaviour)
{
	m_shape.setPosition(x, y);
	m_shape.setSize({10, 10});
	m_shape.setFillColor(color);
	m_shape.setOrigin({m_shape.getSize().x / 2, m_shape.getSize().y / 2 });

	m_maxVelocity = 150;// + rand() % 150;

	m_currentBehaviour = behaviour;
}

void Agent::Update()
{
	sf::Vector2f movement;
	switch(m_currentBehaviour)
	{
	case eBEHAVIOUR::SEEK: 
		movement = m_moveToPosition - m_shape.getPosition();
		break;
	case eBEHAVIOUR::FLEE:
		movement = m_shape.getPosition() - m_moveToPosition;
		break;
	}
	float lenght = pow(movement.x * movement.x + movement.y * movement.y, .5f);
	if (lenght != 0)
	{
		movement /= lenght;

		sf::Vector2f steering = movement - m_currentVelocity;
		steering = (steering / pow(steering.x * steering.x + steering.y * steering.y, .5f)) * m_maxSteeringForce;

		m_currentVelocity = m_currentVelocity + steering;
		m_currentVelocity = (m_currentVelocity / pow(m_currentVelocity.x * m_currentVelocity.x + m_currentVelocity.y * m_currentVelocity.y, .5f));

		Move(m_currentVelocity * (m_maxVelocity * (lenght < 25 ? (lenght/25) : 1)) * gl::DeltaTime::Time());
	}
}

void Agent::MoveTo(sf::Vector2f pos)
{
	m_moveToPosition = pos;
}

void Agent::Move(sf::Vector2f velocity)
{
	m_shape.setPosition(m_shape.getPosition() + velocity);
}

void Agent::Render(sf::RenderWindow* window)
{
	window->draw(m_shape);
}

void Agent::Destroy()
{
}

Agent::~Agent()
{
}
