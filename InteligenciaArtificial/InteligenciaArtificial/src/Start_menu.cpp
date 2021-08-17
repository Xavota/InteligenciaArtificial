#include "Start_menu.h"
#include "CFont.h"
#include "CTexture.h"
#include "Game.h"

void Start_menu::Init()
{
	MenuManager::Init();
	Game* g = getGame();

	m_buttons.push_back(gl::Button(Game::Start, vector<void*>({g}), GetGameWindow(),
		gl::UIShape(sf::FloatRect(362, 437, 300, 50), sf::Color::Transparent, sf::Color::Transparent, 1.f),
		"Start", gl::CFont::GetFont("Font"), sf::Color::White, 20, 70, gl::Button::TextAlignment::CENTER,
		gl::CTexture::GetTexture("Selector"), sf::Vector2f(50, 50), gl::Button::SelectorAligment::LEFT, 0));

	m_buttons.push_back(gl::Button(Game::Quit, vector<void*>({ g }), GetGameWindow(),
		gl::UIShape(sf::FloatRect(362, 537, 300, 50), sf::Color::Transparent, sf::Color::Transparent, 1.f),
		"Quit", gl::CFont::GetFont("Font"), sf::Color::White, 20, 70, gl::Button::TextAlignment::CENTER,
		gl::CTexture::GetTexture("Selector"), sf::Vector2f(50, 50), gl::Button::SelectorAligment::LEFT, 0));

	m_buttons[0].ConectUp(&m_buttons[1]);
	m_buttons[0].ConectDown(&m_buttons[1]);
	m_buttons[1].ConectUp(&m_buttons[0]);
	m_buttons[1].ConectDown(&m_buttons[0]);
	m_buttons[0].SetIsSelected(true);
}

void Start_menu::Reposition(sf::Vector2f wordlPosition, sf::Vector2f cameraSize)
{
	MenuManager::Reposition(wordlPosition, cameraSize);
}

void Start_menu::Update()
{
	MenuManager::Update();
}

void Start_menu::Render(sf::RenderWindow* window)
{
	MenuManager::Render(window);
}

void Start_menu::Destroy()
{
	MenuManager::Destroy();
}

