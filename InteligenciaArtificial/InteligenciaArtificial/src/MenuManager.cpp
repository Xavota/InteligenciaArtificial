#include "MenuManager.h"

namespace gl {
void MenuManager::Init()
{
}

void MenuManager::Reposition(sf::Vector2f wordlPosition, sf::Vector2f cameraSize)
{
	for (Button& button : m_buttons) {
		button.SetPosition(wordlPosition, cameraSize);
	}
	for (UIShape& shape : m_shapes) {
		shape.Reposition(wordlPosition, cameraSize);
	}
}

void MenuManager::Update()
{
	for (Button& button : m_buttons) {
		if (button.Update())
			break;
	}
	for (Button& button : m_buttons) {
		if (button.IsMouseOver()) {
			for (Button& but : m_buttons) {
				but.m_isSelected = false;
			}
			button.m_isSelected = true;
		}
	}
	for (UIShape& shape : m_shapes) {
		shape.Update();
	}
}

void MenuManager::Render(sf::RenderWindow* window)
{
	for (UIShape& shape : m_shapes) {
		shape.Render(window);
	}
	for (Button& button : m_buttons) {
		button.Render(window);
	}
}

void MenuManager::Destroy()
{
	for (Button& button : m_buttons) {
		button.Destroy();
	}
	for (UIShape& shape : m_shapes) {
		shape.Destroy();
	}
	m_buttons.clear();
	m_shapes.clear();
}
}