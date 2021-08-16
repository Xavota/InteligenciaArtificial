#include "UI.h"
#include "MenuManager.h"

namespace gl {
sf::RenderWindow* UI::m_window = nullptr;
MenuManager* UI::m_menu = nullptr;

void UI::Init(sf::RenderWindow* window)
{
	m_window = window;
	if (m_menu != nullptr) {
		m_menu->Init();
	}
}

void UI::Update()
{
	if (m_menu != nullptr) {
		m_menu->Reposition(m_window->getView().getCenter() + sf::Vector2f(-int(m_window->getSize().x / 2), -int(m_window->getSize().y / 2)));
		m_menu->Update();
	}
}

void UI::ChangeUI(MenuManager* menu)
{
	if (m_menu != nullptr) {
		m_menu->Destroy();
	}
	m_menu = menu;
	if (m_menu != nullptr) {
		m_menu->Init();
	}
}

void UI::Render(sf::RenderWindow* window)
{
	if (m_menu != nullptr) {
		m_menu->Render(window);
	}
}

void UI::Destroy()
{
	if (m_menu != nullptr) {
		m_menu->Destroy();
		delete m_menu;
		m_menu = nullptr;
	}
}
}