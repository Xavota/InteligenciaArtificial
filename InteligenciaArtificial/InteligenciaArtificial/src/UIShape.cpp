#include "UIShape.h"

namespace gl {
UIShape::UIShape()
{
	Init();
}

UIShape::UIShape(sf::FloatRect shapeTransform, sf::Texture* shapeTex)
{
	Init(shapeTransform, shapeTex);
}

UIShape::UIShape(sf::FloatRect shapeTransform, sf::Texture* shapeTex, sf::IntRect textureRect)
{
	Init(shapeTransform, shapeTex, textureRect);
}

UIShape::UIShape(sf::FloatRect shapeTransform, sf::Color fillColor, sf::Color outlineColor, float outlineTickness)
{
	Init(shapeTransform, fillColor, outlineColor, outlineTickness);
}

UIShape::~UIShape()
{
}

void UIShape::Init()
{
}

void UIShape::Init(sf::FloatRect shapeTransform, sf::Texture* shapeTex)
{
	m_shape.setSize({ shapeTransform.width, shapeTransform.height });
	m_position = { shapeTransform.left, shapeTransform.top };
	m_shape.setPosition(m_position);
	m_shape.setTexture(shapeTex);
}

void UIShape::Init(sf::FloatRect shapeTransform, sf::Texture* shapeTex, sf::IntRect textureRect)
{
	m_shape.setSize({ shapeTransform.width, shapeTransform.height });
	m_position = { shapeTransform.left, shapeTransform.top };
	m_shape.setPosition(m_position);
	m_shape.setTexture(shapeTex);
	m_shape.setTextureRect(textureRect);
}

void UIShape::Init(sf::FloatRect shapeTransform, sf::Color fillColor, sf::Color outlineColor, float outlineTickness)
{
	m_shape.setSize({ shapeTransform.width, shapeTransform.height });
	m_position = { shapeTransform.left, shapeTransform.top };
	m_shape.setPosition(m_position);
	m_shape.setFillColor(fillColor);
	m_shape.setOutlineColor(outlineColor);
	m_shape.setOutlineThickness(outlineTickness);
}

void UIShape::Reposition(sf::Vector2f wordlPosition)
{
	m_shape.setPosition(wordlPosition + m_position);
}

void UIShape::Update()
{
}

void UIShape::SetFillColor(const sf::Color fillColor)
{
	m_shape.setFillColor(fillColor);
}

void UIShape::SetOutlineColor(const sf::Color outlineColor)
{
	m_shape.setOutlineColor(outlineColor);
}

void UIShape::SetPosition(sf::Vector2f position)
{
	m_shape.setPosition(position + m_position);
}

void UIShape::SetPositionRect(sf::Vector2f position)
{
	Move(position - m_position);
	m_position = position;
}

void UIShape::SetSize(sf::Vector2f size)
{
	m_shape.setSize(size);
}

void UIShape::SetTranform(sf::IntRect buttonTransform)
{
	m_position = { (float)buttonTransform.left, (float)buttonTransform.top };
	m_shape.setPosition(m_position);
	m_shape.setSize({ (float)buttonTransform.width, (float)buttonTransform.height });
}

void UIShape::Move(sf::Vector2f moved)
{
	m_shape.move(moved);
	m_position += moved;
}

void UIShape::Render(sf::RenderWindow* window)
{
	window->draw(m_shape);
}

void UIShape::Destroy()
{
}
}