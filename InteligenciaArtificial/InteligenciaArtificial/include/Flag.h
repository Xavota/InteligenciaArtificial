#pragma once
#include <SFML/Graphics.hpp>
class Agent;
class Flag
{
public:
	Flag() = default;
	Flag(sf::Vector2f pos);
	~Flag() = default;

	void Init(sf::Vector2f pos);
	void Update();
	void Render(sf::RenderWindow* window);
	void Destroy();

	Agent* GetCarrier();
	void SetCarrier(Agent* carrier);

	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f pos);
	float GetRadious();

private:
	sf::RectangleShape m_shape;
	float m_radious;

	Agent* m_carrier = nullptr;
};

