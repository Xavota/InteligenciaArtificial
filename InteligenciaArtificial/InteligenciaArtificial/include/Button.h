#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "UIShape.h"

using namespace std;

namespace gl {
class Button
{
public:
	enum class TextAlignment {
		NONE = -1, LEFT, CENTER, RIGHT
	};
	enum class SelectorAligment {
		NONE = -1, UP, LEFT, CENTER, RIGHT, DOWN
	};
	Button() {}
	Button(void (*function)(std::vector<void*>), std::vector<void*> parameters, sf::RenderWindow* window,
		UIShape shape,
		string text, sf::Font* font, sf::Color textColor, unsigned int minSize, unsigned int maxSize, TextAlignment alignment,
		sf::Texture* selectorTex, sf::Vector2f selectorSize, SelectorAligment selectorAlign, float selectorDistance);
	Button(void (*function)(std::vector<void*>), std::vector<void*> parameters, sf::RenderWindow* window,
		UIShape shape,
		string text, sf::Font* font, sf::Color textColor, unsigned int minSize, unsigned int maxSize, TextAlignment alignment);
	Button(void (*function)(std::vector<void*>), std::vector<void*> parameters, sf::RenderWindow* window,
		UIShape shape,
		sf::Texture* selectorTex, sf::Vector2f selectorSize, SelectorAligment selectorAlign, float selectorDistance);
	Button(void (*function)(std::vector<void*>), std::vector<void*> parameters, sf::RenderWindow* window,
		UIShape shape);
	~Button();

	void Init(void (*function)(std::vector<void*>), std::vector<void*> parameters, sf::RenderWindow* window,
		UIShape shape,
		string text, sf::Font* font, sf::Color textColor, unsigned int minSize, unsigned int maxSize, TextAlignment alignment,
		sf::Texture* selectorTex, sf::Vector2f selectorSize, SelectorAligment selectorAlign, float selectorDistance);
	void Init(void (*function)(std::vector<void*>), std::vector<void*> parameters, sf::RenderWindow* window,
		UIShape shape,
		string text, sf::Font* font, sf::Color textColor, unsigned int minSize, unsigned int maxSize, TextAlignment alignment);
	void Init(void (*function)(std::vector<void*>), std::vector<void*> parameters, sf::RenderWindow* window,
		UIShape shape,
		sf::Texture* selectorTex, sf::Vector2f selectorSize, SelectorAligment selectorAlign, float selectorDistance);
	void Init(void (*function)(std::vector<void*>), std::vector<void*> parameters, sf::RenderWindow* window,
		UIShape shape);
	bool Update();
	void SetFillColor(const sf::Color fillColor);
	void SetOutlineColor(const sf::Color outlineColor);
	void SetPosition(sf::Vector2f position);
	void SetSize(sf::Vector2f size);
	void SetTranform(sf::IntRect buttonTransform);
	void SetText(string text, sf::Font* font, sf::Color textColor, unsigned int minSize, unsigned int maxSize, TextAlignment alignment);
	void SetSelector(sf::Texture* selectorTex, sf::Vector2f selectorSize, SelectorAligment selectorAlign, float selectorDistance);
	sf::Color GetFillColor() { return m_buttonShape.GetFillColor(); }
	sf::Color GetOutlineColor() { return m_buttonShape.GetOutlineColor(); }
	sf::Vector2i GetPositioni() { return m_buttonShape.GetPositioni(); }
	sf::Vector2i GetSizei() { return m_buttonShape.GetSizei(); }
	sf::IntRect GetTranformi() { return m_buttonShape.GetTranformi(); }
	sf::Vector2f GetPositionf() { return m_buttonShape.GetPositionf(); }
	sf::Vector2f GetSizef() { return m_buttonShape.GetSizef(); }
	sf::FloatRect GetTranformf() { return m_buttonShape.GetTranformf(); }
	void ConectUp(Button* conection);
	void ConectLeft(Button* conection);
	void ConectDown(Button* conection);
	void ConectRight(Button* conection);
	void SetIsSelected(bool selected) { m_isSelected = selected; }
	void Render(sf::RenderWindow* window);
	void Destroy();
private:
	bool IsMouseOver();
	bool IsClicked();
	void OnClick();
	void SetPositionRect(sf::Vector2f position); 
	void AlignText(TextAlignment aligment);
	void AlignSelector(SelectorAligment selectorAlign, float selectorDistance);
private:
	friend class UI;
	friend class Start_menu;
	friend class MenuManager;

	UIShape m_buttonShape;
	sf::Text m_text;
	TextAlignment m_textAligment = TextAlignment::NONE;
	sf::RectangleShape m_selector;
	SelectorAligment m_selectorAligment = SelectorAligment::NONE;
	float m_selectorDistance = 0;

	void (*m_function)(std::vector<void*>) = nullptr;
	std::vector<void*> m_parameters;
	bool m_isPressed = false;
	bool m_isSelected = false;

	Button* m_selectionUp = nullptr;
	Button* m_selectionLeft = nullptr;
	Button* m_selectionDown = nullptr;
	Button* m_selectionRight = nullptr;

	sf::RenderWindow* m_window = nullptr;
};
}
