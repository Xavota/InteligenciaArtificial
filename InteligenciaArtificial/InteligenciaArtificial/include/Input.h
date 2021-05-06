#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

namespace gl {
class Input
{
public:
	static bool GetKeyPressed(sf::Keyboard::Key);
	static bool GetKey(sf::Keyboard::Key);
	static bool GetKeyReleased(sf::Keyboard::Key);
	static bool GetMouseButtonDown(int button);
	static bool GetMouseButton(int button);
	static bool GetMouseButtonUp(int button);
private:
	static void HandleInputs(sf::Keyboard::Key, bool isPressed);
	static void Update();
private:
	friend class Game;
	class KEY {
	public:
		KEY(sf::Keyboard::Key key, bool isPressed) : m_key(key), m_isPressed(isPressed) {}
		sf::Keyboard::Key m_key = sf::Keyboard::Unknown;
		bool m_isPressed = false;
		bool m_wasPressed = false;
	};
	class MouseButton {
	public:
		MouseButton(sf::Mouse::Button button) : m_button(button) {}
		sf::Mouse::Button m_button;
		bool m_wasPressed = false;
	};
	static vector<KEY> m_keys;
	static vector<MouseButton> m_mouseButtons;
};
}
