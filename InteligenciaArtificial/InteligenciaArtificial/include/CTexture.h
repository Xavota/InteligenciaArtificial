#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>

using namespace std;

namespace gl {
	/**
	  * @brief		Loads and store the textures for later use in any part of the document
	*/
	class CTexture
	{
	public:
		/**
		  * @brief		Adds a texture to the list
		  * @param      name: the name of the texture that will be stored as
		  * @param      fileName: the file where the texture is
		  * @bug	    No know Bugs
		*/
		static void AddTexture(string name, string fileName);
		/**
		  * @brief		Adds a texture to the list
		  * @param      name: the name of the texture that will be stored as
		  * @param      image: the image to convert into a texture
		  * @bug	    No know Bugs
		*/
		static void AddTexture(string name, sf::Image image);
	
		/**
		  * @brief		Adds a texture to the list and make a mask with the given color
		  * @param      name: the name of the texture that will be stored as
		  * @param      fileName: the file where the texture is
		  * @param      maskColor: the color to wich the mask will be applied
		  * @bug	    No know Bugs
		*/
		static void AddTexture(string name, string fileName, sf::Color maskColor);
		/**
		  * @brief		Adds a texture to the list and make a mask with the given color
		  * @param      name: the name of the texture that will be stored as
		  * @param      image: the image to convert into a texture
		  * @param      maskColor: the color to wich the mask will be applied
		  * @bug	    No know Bugs
		*/
		static void AddTexture(string name, sf::Image image, sf::Color maskColor);
	
		/**
		  * @brief		Returns a pointer to the texture with that name
		  * @param      name: the name to identify the texture
		  * @bug	    No know Bugs
		*/
		static sf::Texture* GetTexture(string name);
	private:
		static map<string, sf::Texture> m_textures;
	};
}
