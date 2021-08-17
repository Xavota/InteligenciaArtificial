#include "MapEditorMenu.h"
#include "Globals.h"

#include "Game_FP.h"

void MapEditorMenu::Init()
{
	MenuManager::Init();

	Game_FP* g = getGame_FP();

	m_buttons.push_back(gl::Button(Game_FP::Grass, vector<void*>({g}), getGame_FP()->m_window,
		gl::UIShape(sf::FloatRect(128, 128, 128, 128), gl::CTexture::GetTexture("Grass"), { 800, 192, 32, 32 })));
	m_buttons.push_back(gl::Button(Game_FP::Sand, vector<void*>({ g }), getGame_FP()->m_window,
		gl::UIShape(sf::FloatRect(256, 128, 128, 128), gl::CTexture::GetTexture("Sand"), { 0, 0, 32, 32 })));
	m_buttons.push_back(gl::Button(Game_FP::Water, vector<void*>({ g }), getGame_FP()->m_window,
		gl::UIShape(sf::FloatRect(128, 256, 128, 128), gl::CTexture::GetTexture("Water"), { 256, 192, 32, 32 })));
	m_buttons.push_back(gl::Button(Game_FP::Wall, vector<void*>({ g }), getGame_FP()->m_window,
		gl::UIShape(sf::FloatRect(256, 256, 128, 128), gl::CTexture::GetTexture("Wall"), { 352, 0, 32, 32 })));
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
