#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>

using namespace std;

namespace gl {
class CTexture
{
public:
	static void AddTexture(string name, string fileName);
	static void AddTexture(string name, sf::Texture tex);
	static void AddTexture(string name, sf::RectangleShape shape);
	static void AddTexture(string name, sf::CircleShape shape);
	static void AddTexture(string name, sf::Image image);
	static sf::Texture* GetTexture(string name);
private:
	static map<string, sf::Texture> m_textures;
};
}
