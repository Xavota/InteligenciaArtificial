#pragma once
#include <SFML/Graphics.hpp>
enum class eBEHAVIOUR
{
	NONE = -1,
	SEEK,
	FLEE
};
class Agent
{
public:
	Agent() = default;
	Agent(float x, float y, sf::Color color, eBEHAVIOUR behaviour);
	void Init(float x, float y, sf::Color color, eBEHAVIOUR behaviour);
	void Update();
	void MoveTo(sf::Vector2f pos);
	void Move(sf::Vector2f velocity);
	sf::Vector2f getPosition() { return m_shape.getPosition(); }
	void Render(sf::RenderWindow* window);
	void Destroy();
	~Agent();
private:
	sf::RectangleShape m_shape;

	sf::Vector2f m_moveToPosition;

	float m_maxVelocity = 150;
	sf::Vector2f m_currentVelocity;
	float m_maxSteeringForce = .2f;

	eBEHAVIOUR m_currentBehaviour = eBEHAVIOUR::NONE;
};

