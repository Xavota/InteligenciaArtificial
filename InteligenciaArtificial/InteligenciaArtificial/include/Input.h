#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

namespace gl {
	/**
	  * @brief		Keeps track of all the inputs and store its values to be accesed in every part of the document
	*/
	class Input
	{
	public:
		/**
		  * @brief      Returns true if the key was pressed in this update
		  * @param      keyCode: the key checked
		  * @bug	    No know Bugs
		*/
		static bool GetKeyPressed(sf::Keyboard::Key keyCode);
		/**
		  * @brief      Returns true if the key is being pressed in this update
		  * @param      keyCode: the key checked
		  * @bug	    No know Bugs
		*/
		static bool GetKey(sf::Keyboard::Key keyCode);
		/**
		  * @brief      Returns true if the key was pressed on the last update and not in this
		  * @param      keyCode: the key checked
		  * @bug	    No know Bugs
		*/
		static bool GetKeyReleased(sf::Keyboard::Key keyCode);
		/**
		  * @brief      Returns true if the mouse button was pressed in this update (0 = left, 1 = right, 3 = middle)
		  * @param      keyCode: the key checked
		  * @bug	    No know Bugs
		*/
		static bool GetMouseButtonDown(int button);
		/**
		  * @brief      Returns true if the mouse button is being pressed in this update (0 = left, 1 = right, 3 = middle)
		  * @param      keyCode: the key checked
		  * @bug	    No know Bugs
		*/
		static bool GetMouseButton(int button);
		/**
		  * @brief      Returns true if the mouse button was pressed on the last update and not in this (0 = left, 1 = right, 3 = middle)
		  * @param      keyCode: the key checked
		  * @bug	    No know Bugs
		*/
		static bool GetMouseButtonUp(int button);
	
	private:
		/**
		  * @brief      Check the changes on the keys beign pressed or not
		  * @param      keyCode: the key checked
		  * @param      isPressed: if the key is beign pressed or not
		  * @bug	    No know Bugs
		*/
		static void HandleInputs(sf::Keyboard::Key keyCode, bool isPressed);
		/**
		  * @brief      Updates the 'wasPressed' property, for the Pressed and Release functions
		  * @bug	    No know Bugs
		*/
		static void Update();
	
	private:
		friend class Game;
		/**
		  * @brief		The data needed to keep track of the keboard keys inputs
		*/
		class KEY {
		public:
			KEY(sf::Keyboard::Key key, bool isPressed) : m_key(key), m_isPressed(isPressed) {}
			sf::Keyboard::Key m_key = sf::Keyboard::Unknown;
			bool m_isPressed = false;
			bool m_wasPressed = false;
		};

		/**
		  * @brief		The data needed to keep track of the mouse buttons inputs
		*/
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
