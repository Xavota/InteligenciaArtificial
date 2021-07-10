#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <map>

using namespace std;

namespace gl {
	/**
	  * @brief		Loads and store the fonts for later use in any part of the document
	*/
	class CFont
	{
	public:
		/**
		  * @brief		Adds a font to the list
		  * @param      name: the name of the font that will be stored as
		  * @param      fontName: the file where the font is
		  * @bug	    No know Bugs
		*/
		static void AddFont(string name, string fontName);
		/**
		  * @brief		Adds a font to the list
		  * @param      name: the name of the font that will be stored as
		  * @param      font: the font to replicate
		  * @bug	    No know Bugs
		*/
		static void AddFont(string name, sf::Font font);
		/**
		  * @brief		Returns a pointer to the font with that name
		  * @param      name: the name to identify the font
		  * @bug	    No know Bugs
		*/
		static sf::Font* GetFont(string name);
	private:
		static map<string, sf::Font> m_fonts;
	};
}
