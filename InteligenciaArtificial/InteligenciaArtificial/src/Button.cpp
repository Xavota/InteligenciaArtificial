#include "Button.h"
#include <string>
#include "Globals.h"

namespace gl {
Button::Button(void (*function)(std::vector<void*>), std::vector<void*> parameters, sf::RenderWindow* window,
	UIShape shape,
	string text, sf::Font* font, sf::Color textColor, unsigned int minSize, unsigned int maxSize, TextAlignment alignment,
	sf::Texture* selectorTex, sf::Vector2f selectorSize, SelectorAligment selectorAlign, float selectorDistance)
{
	Init(function, parameters, window,
		shape,
		text, font, textColor, minSize, maxSize, alignment,
		selectorTex, selectorSize, selectorAlign, selectorDistance);
}

Button::Button(void(*function)(std::vector<void*>), std::vector<void*> parameters, sf::RenderWindow* window, 
	UIShape shape, 
	string text, sf::Font* font, sf::Color textColor, unsigned int minSize, unsigned int maxSize, TextAlignment alignment)
{
	Init(function, parameters, window,
		shape,
		text, font, textColor, minSize, maxSize, alignment);
}

Button::Button(void(*function)(std::vector<void*>), std::vector<void*> parameters, sf::RenderWindow* window, 
	UIShape shape, 
	sf::Texture* selectorTex, sf::Vector2f selectorSize, SelectorAligment selectorAlign, float selectorDistance)
{
	Init(function, parameters, window,
		shape,
		selectorTex, selectorSize, selectorAlign, selectorDistance);
}

Button::Button(void(*function)(std::vector<void*>), std::vector<void*> parameters, sf::RenderWindow* window, 
	UIShape shape)
{
	Init(function, parameters, window,
		shape);
}

Button::~Button()
{
}

void Button::Init(void (*function)(std::vector<void*>), std::vector<void*> parameters, sf::RenderWindow* window,
	UIShape shape,
	string text, sf::Font* font, sf::Color textColor, unsigned int minSize, unsigned int maxSize, TextAlignment alignment,
	sf::Texture* selectorTex, sf::Vector2f selectorSize, SelectorAligment selectorAlign, float selectorDistance)
{
	m_function = function;
	m_parameters = parameters;
	m_window = window;
	m_buttonShape = shape;
	SetText(text, font, textColor, minSize, maxSize, alignment);
	SetSelector(selectorTex, selectorSize, selectorAlign, selectorDistance);
}

void Button::Init(void (*function)(std::vector<void*>), std::vector<void*> parameters, sf::RenderWindow* window,
	UIShape shape,
	string text, sf::Font* font, sf::Color textColor, unsigned int minSize, unsigned int maxSize, TextAlignment alignment)
{
	m_function = function;
	m_parameters = parameters;
	m_window = window;
	m_buttonShape = shape;
	SetText(text, font, textColor, minSize, maxSize, alignment);
}

void Button::Init(void (*function)(std::vector<void*>), std::vector<void*> parameters, sf::RenderWindow* window,
	UIShape shape,
	sf::Texture* selectorTex, sf::Vector2f selectorSize, SelectorAligment selectorAlign, float selectorDistance)
{
	m_function = function;
	m_parameters = parameters;
	m_window = window;
	m_buttonShape = shape;
	SetSelector(selectorTex, selectorSize, selectorAlign, selectorDistance);
}

void Button::Init(void (*function)(std::vector<void*>), std::vector<void*> parameters, sf::RenderWindow* window,
	UIShape shape)
{
	m_function = function;
	m_parameters = parameters;
	m_window = window;
	m_buttonShape = shape;
}

bool Button::Update()
{
	if (m_isSelected) {
		if ((Input::GetKeyPressed(sf::Keyboard::W) || Input::GetKeyPressed(sf::Keyboard::Up)) && m_selectionUp != nullptr) {
			this->m_isSelected = false;
			m_selectionUp->m_isSelected = true;
			return true;
		}
		if ((Input::GetKeyPressed(sf::Keyboard::A) || Input::GetKeyPressed(sf::Keyboard::Left)) && m_selectionLeft != nullptr) {
			this->m_isSelected = false;
			m_selectionLeft->m_isSelected = true;
			return true;
		}
		if ((Input::GetKeyPressed(sf::Keyboard::S) || Input::GetKeyPressed(sf::Keyboard::Down)) && m_selectionDown != nullptr) {
			this->m_isSelected = false;
			m_selectionDown->m_isSelected = true;
			return true;
		}
		if ((Input::GetKeyPressed(sf::Keyboard::D) || Input::GetKeyPressed(sf::Keyboard::Right)) && m_selectionRight != nullptr) {
			this->m_isSelected = false;
			m_selectionRight->m_isSelected = true;
			return true;
		}
		if (IsClicked() || Input::GetKeyPressed(sf::Keyboard::Return)) {
			OnClick();
			return true;
		}
	}
	return false;
}

bool Button::IsMouseOver()
{
	return m_buttonShape.GetTranformi().intersects(sf::IntRect(sf::Mouse::getPosition(*m_window), sf::Vector2i(1, 1)));
}

bool Button::IsClicked()
{
	return IsMouseOver() && Input::GetMouseButtonDown(0);
}

void Button::OnClick()
{
	m_function(m_parameters);
}

void Button::SetFillColor(const sf::Color fillColor)
{
	m_buttonShape.SetFillColor(fillColor);
}

void Button::SetOutlineColor(const sf::Color outlineColor)
{
	m_buttonShape.SetOutlineColor(outlineColor);
}

void Button::SetPosition(sf::Vector2f position, sf::Vector2f cameraSize)
{
	m_buttonShape.Reposition(position, cameraSize);
	AlignText(m_textAligment);
	AlignSelector(m_selectorAligment, m_selectorDistance);
}

void Button::SetPositionRect(sf::Vector2f position)
{
	m_buttonShape.SetPositionRect(position);
	AlignText(m_textAligment);
	AlignSelector(m_selectorAligment, m_selectorDistance);
}

void Button::SetSize(sf::Vector2f size)
{
	m_buttonShape.SetSize(size);
}

void Button::SetTranform(sf::IntRect buttonTransform)
{
	m_buttonShape.SetPosition({ (float)buttonTransform.left, (float)buttonTransform.top });
	m_buttonShape.SetSize({ (float)buttonTransform.width, (float)buttonTransform.height });
}

void Button::SetText(string text, sf::Font* font, sf::Color textColor, unsigned int minSize, unsigned int maxSize, TextAlignment aligment)
{
	m_text.setFont(*font);
	m_text.setString(text);
	m_text.setCharacterSize(minSize);
	m_text.setFillColor(textColor);

	float sizex = m_buttonShape.GetSizef().x - 10;
	float sizey = m_buttonShape.GetSizef().y - 10;
	unsigned int sizeSum = 0;

	while (m_text.getGlobalBounds().width < sizex && m_text.getGlobalBounds().height < sizey && minSize + sizeSum < maxSize) {
		sizeSum++;
		m_text.setCharacterSize(minSize + sizeSum);
	}

	AlignText(aligment);
	AlignSelector(m_selectorAligment, m_selectorDistance);
}

void Button::AlignText(TextAlignment aligment)
{
	m_textAligment = aligment;
	switch (m_textAligment)
	{
	case Button::TextAlignment::NONE:
		break;
	case Button::TextAlignment::LEFT: {
		float alignx = 5.f;
		float aligny = (m_buttonShape.GetSizef().y - m_text.getGlobalBounds().height) / 2;
		m_text.setPosition(m_buttonShape.GetPositionf() + sf::Vector2f(alignx, aligny));
		break;
	}
	case Button::TextAlignment::CENTER: {
		float alignx = (m_buttonShape.GetSizef().x - m_text.getGlobalBounds().width) / 2;
		float aligny = (m_buttonShape.GetSizef().y - m_text.getGlobalBounds().height) / 2;
		m_text.setPosition(m_buttonShape.GetPositionf() + sf::Vector2f(alignx, aligny));
		break;
	}
	case Button::TextAlignment::RIGHT: {
		float alignx = (m_buttonShape.GetSizef().x - m_text.getGlobalBounds().width) - 5.f;
		float aligny = (m_buttonShape.GetSizef().y - m_text.getGlobalBounds().height) / 2;
		m_text.setPosition(m_buttonShape.GetPositionf() + sf::Vector2f(alignx, aligny));
		break;
	}
	default:
		break;
	}
}

void Button::SetSelector(sf::Texture* selectorTex, sf::Vector2f selectorSize, SelectorAligment selectorAlign, float selectorDistance)
{
	m_selector.setTexture(selectorTex);
	m_selector.setSize(selectorSize);
	AlignSelector(selectorAlign, selectorDistance);
}

void Button::AlignSelector(SelectorAligment selectorAlign, float selectorDistance)
{
	m_selectorAligment = selectorAlign;
	m_selectorDistance = selectorDistance;
	switch (m_selectorAligment)
	{
	case Button::SelectorAligment::NONE:
		break;
	case Button::SelectorAligment::UP: {
		float alignx = (m_buttonShape.GetSizef().x - m_selector.getSize().x) / 2;
		float aligny = -(m_selector.getSize().y + m_selectorDistance);
		m_selector.setPosition(m_buttonShape.GetPositionf() + sf::Vector2f(alignx, aligny));
		break;
	}
	case Button::SelectorAligment::LEFT: {
		float alignx = -(m_selector.getSize().x + m_selectorDistance);
		float aligny = (m_buttonShape.GetSizef().y - m_selector.getSize().y) / 2;
		m_selector.setPosition(m_buttonShape.GetPositionf() + sf::Vector2f(alignx, aligny));
		break;
	}
	case Button::SelectorAligment::CENTER: {
		float alignx = (m_buttonShape.GetSizef().x - m_selector.getSize().x) / 2;
		float aligny = (m_buttonShape.GetSizef().y - m_selector.getSize().y) / 2;
		m_selector.setPosition(m_buttonShape.GetPositionf() + sf::Vector2f(alignx, aligny));
		break;
	}
	case Button::SelectorAligment::RIGHT: {
		float alignx = (m_buttonShape.GetSizef().x + m_selectorDistance);
		float aligny = (m_buttonShape.GetSizef().y - m_selector.getSize().y) / 2;
		m_selector.setPosition(m_buttonShape.GetPositionf() + sf::Vector2f(alignx, aligny));
		break;
	}
	case Button::SelectorAligment::DOWN: {
		float alignx = (m_buttonShape.GetSizef().x - m_selector.getSize().x) / 2;
		float aligny = (m_buttonShape.GetSizef().y + m_selectorDistance);
		m_selector.setPosition(m_buttonShape.GetPositionf() + sf::Vector2f(alignx, aligny));
		break;
	}
	default:
		break;
	}
}

void Button::ConectUp(Button* conection)
{
	m_selectionUp = conection;
}

void Button::ConectLeft(Button* conection)
{
	m_selectionLeft = conection;
}

void Button::ConectDown(Button* conection)
{
	m_selectionDown = conection;
}

void Button::ConectRight(Button* conection)
{
	m_selectionRight = conection;
}

void Button::Render(sf::RenderWindow* window)
{
	m_buttonShape.Render(window);
	window->draw(m_text);
	if (m_isSelected)
		window->draw(m_selector);
}

void Button::Destroy()
{
}
}