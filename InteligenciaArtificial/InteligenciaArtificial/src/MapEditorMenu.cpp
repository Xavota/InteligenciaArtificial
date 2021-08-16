#include "MapEditorMenu.h"
#include "Globals.h"

#include "Game_FP.h"

void MapEditorMenu::Init()
{
	MenuManager::Init();

	m_buttons.push_back(gl::Button(Game_FP::a, vector<void*>(), getGame_FP()->m_window,
		gl::UIShape(sf::FloatRect(362, 437, 300, 50), sf::Color::Red, sf::Color::Green, 5.f)/*,
		gl::CTexture::GetTexture("Selector"), sf::Vector2f(50, 50), gl::Button::SelectorAligment::LEFT, 0/**/));
}

void MapEditorMenu::Reposition(sf::Vector2f wordlPosition)
{
	MenuManager::Reposition(wordlPosition);
}

void MapEditorMenu::Update()
{
	MenuManager::Update();
}

void MapEditorMenu::Render(sf::RenderWindow* window)
{
	MenuManager::Render(window);
}

void MapEditorMenu::Destroy()
{
	MenuManager::Destroy();
}
