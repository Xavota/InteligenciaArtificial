#include "Game.h"
#include "Globals.h"

void Game::run()
{
	init();

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (m_window->isOpen())
	{
		processEvents();

		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate >= timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			gl::DeltaTime::Update(timePerFrame.asSeconds());
			update();
			gl::Input::Update();
		}
		render();
	}

	destroy();
}

void Game::init()
{
	m_window = new sf::RenderWindow(sf::VideoMode(500, 500), "SFML Template");
	m_shape.setFillColor(sf::Color::Red);
	m_shape.setPosition({100, 100});
	m_shape.setRadius(25);
	gl::DeltaTime::AddTimer("test");
	gl::DeltaTime::SetTimer("test", 2);
	gl::DeltaTime::AddTimer("test2");
	gl::DeltaTime::StopTimer("test2");
}

void Game::update()
{
	static bool uno = false;
	if (gl::DeltaTime::TimerExist("test"))
	{
		cout << gl::DeltaTime::GetTimer("test") << "\t" << gl::DeltaTime::GetTimer("test2") << endl;
		if (gl::DeltaTime::GetTimer("test") > 5)
		{
			if (!uno)
			{
				gl::DeltaTime::RestartTimer("test");
				uno = true;
				gl::DeltaTime::StopTimer("test");
				gl::DeltaTime::StartTimer("test2");
			}
			else
			{
				gl::DeltaTime::DeleteTimer("test");
			}
		}
		if (gl::DeltaTime::GetTimer("test2") > 3)
		{
			gl::DeltaTime::RestartTimer("test2");
			gl::DeltaTime::StopTimer("test2");
			gl::DeltaTime::StartTimer("test");
		}
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			gl::Input::HandleInputs(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			gl::Input::HandleInputs(event.key.code, false);
			break;
		case sf::Event::Closed:
			m_window->close();
			break;
		}
	}
}

void Game::render()
{
	m_window->clear();
	m_window->draw(m_shape);
	m_window->display();
}

void Game::destroy()
{
	delete m_window;
}