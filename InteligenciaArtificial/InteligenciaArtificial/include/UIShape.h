#pragma once
#include <SFML/Graphics.hpp>

namespace gl {
class UIShape
{
public:
	UIShape();
	UIShape(sf::FloatRect shapeTransform, sf::Texture* shapeTex);
	UIShape(sf::FloatRect shapeTransform, sf::Color fillColor, sf::Color outlineColor, float outlineTickness);
	~UIShape();
	void Init();
	void Init(sf::FloatRect shapeTransform, sf::Texture* shapeTex);
	void Init(sf::FloatRect shapeTransform, sf::Color fillColor, sf::Color outlineColor, float outlineTickness);
	void Reposition(sf::Vector2f wordlPosition);
	void Update();
	void SetFillColor(const sf::Color fillColor);
	void SetOutlineColor(const sf::Color outlineColor);
	void SetPosition(sf::Vector2f position);
	void SetPositionRect(sf::Vector2f position);
	void SetSize(sf::Vector2f size);
	void SetTranform(sf::IntRect buttonTransform);
	sf::Color GetFillColor() { return m_shape.getFillColor(); }
	sf::Color GetOutlineColor() { return m_shape.getOutlineColor(); }
	sf::Vector2i GetPositioni() { return sf::Vector2i(m_shape.getPosition().x, m_shape.getPosition().y); }
	sf::Vector2i GetSizei() { return sf::Vector2i(m_shape.getSize().x, m_shape.getSize().y); }
	sf::IntRect GetTranformi() { return sf::IntRect(m_position.x, m_position.y, m_shape.getSize().x, m_shape.getSize().y); }
	sf::Vector2f GetPositionf() { return sf::Vector2f(m_shape.getPosition().x, m_shape.getPosition().y); }
	sf::Vector2f GetSizef() { return sf::Vector2f(m_shape.getSize().x, m_shape.getSize().y); }
	sf::FloatRect GetTranformf() { return sf::FloatRect(m_position.x, m_position.y, m_shape.getSize().x, m_shape.getSize().y); }
	void Move(sf::Vector2f moved);
	void Render(sf::RenderWindow* window);
	void Destroy();
private:
	sf::RectangleShape m_shape;
	sf::Vector2f m_position;
};
}
