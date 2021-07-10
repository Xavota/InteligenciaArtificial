#include "Camera.h"
#include "Globals.h"

Camera::Camera(sf::FloatRect initView, float sensibility)
{
	Init(initView, sensibility);
}

void Camera::Init(sf::FloatRect initView, float sensibility)
{
	m_camera.reset(initView);
	m_sensibility = sensibility;
}

void Camera::Update(sf::RenderWindow* window)
{
	static sf::Vector2i lastPos = sf::Mouse::getPosition(*window);
	if (gl::Input::GetMouseButton(1))
	{
		sf::Vector2i currentPos = sf::Mouse::getPosition(*window);
		sf::Vector2f deltaMove = sf::Vector2f{(float)currentPos.x, (float)currentPos .y} - sf::Vector2f{(float)lastPos.x, (float)lastPos.y};
		sf::Vector2f center = m_camera.getCenter();
		center -= deltaMove * m_sensibility;
		m_camera.setCenter(center);
	}
	lastPos = sf::Mouse::getPosition(*window);

	if (gl::Input::GetKey(sf::Keyboard::W))
	{
		m_camera.setSize(m_camera.getSize() * .99f);
	}

	if (gl::Input::GetKey(sf::Keyboard::S))
	{
		m_camera.setSize(m_camera.getSize() * 1.01f);
	}

	window->setView(m_camera);
}

sf::Vector2f Camera::GetCenter()
{
	return m_camera.getCenter();
}
