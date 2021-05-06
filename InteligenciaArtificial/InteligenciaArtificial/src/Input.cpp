#include "Input.h"

namespace gl {
vector<Input::KEY> Input::m_keys;
vector<Input::MouseButton> Input::m_mouseButtons =
			{ Input::MouseButton(sf::Mouse::Left), Input::MouseButton(sf::Mouse::Right), Input::MouseButton(sf::Mouse::Middle) };

bool Input::GetKeyPressed(sf::Keyboard::Key keyCode)
{
	for (KEY& key : m_keys) {
		if (key.m_key == keyCode) {
			return key.m_wasPressed ? false : key.m_isPressed;
		}
	}
	return false;
}

bool Input::GetKey(sf::Keyboard::Key keyCode)
{
	for (KEY& key : m_keys) {
		if (key.m_key == keyCode) {
			return key.m_isPressed;
		}
	}
	return false;
}

bool Input::GetKeyReleased(sf::Keyboard::Key keyCode)
{
	for (KEY& key : m_keys) {
		if (key.m_key == keyCode) {
			return key.m_wasPressed ? !key.m_isPressed : false;
		}
	}
	return false;
}

bool Input::GetMouseButtonDown(int button)
{
	if (button < 3)
		return m_mouseButtons[button].m_wasPressed ? false : sf::Mouse::isButtonPressed(m_mouseButtons[button].m_button);
	return false;
}

/* 1: Left
 2: Right
 3: Middle*/
bool Input::GetMouseButton(int button)
{
	if (button < 3)
		return sf::Mouse::isButtonPressed(m_mouseButtons[button].m_button);
	return false;
}

bool Input::GetMouseButtonUp(int button)
{
	if (button < 3)
		return m_mouseButtons[button].m_wasPressed ? !sf::Mouse::isButtonPressed(m_mouseButtons[button].m_button) : false;
	return false;
}

void Input::HandleInputs(sf::Keyboard::Key keyCode, bool isPressed)
{
	for (KEY& key : m_keys) {
		if (key.m_key == keyCode) {
			key.m_isPressed = isPressed;
			return;
		}
	}

	m_keys.push_back(KEY(keyCode, isPressed));
}

void Input::Update()
{
	for (KEY& key : m_keys) {
		key.m_wasPressed = key.m_isPressed;
	}

	for (MouseButton& button : m_mouseButtons) {
		button.m_wasPressed = sf::Mouse::isButtonPressed(button.m_button);
	}
}
}