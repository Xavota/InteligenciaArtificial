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
		sf::Vector2f center = m_window->getView().getCenter();
		sf::Vector2f size = m_window->getView().getSize();
		sf::Vector2f ratio = {m_window->getView().getSize().x / m_window->getSize().x,
			                 m_window->getView().getSize().y / m_window->getSize().y};

		m_menu->Reposition(center - sf::Vector2f(int(size.x / (2)), int(size.y / (2))), ratio);
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