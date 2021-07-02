#include "CTexture.h"

namespace gl {
map<string, sf::Texture> CTexture::m_textures{};
void CTexture::AddTexture(string name, string fileName)
{
	sf::Texture tex;
	if (!tex.loadFromFile(fileName)) 
	{
		cout << "archivo no encontrado" << endl;
		return;
	}
	m_textures.insert(make_pair(name, tex));
}

void CTexture::AddTexture(string name, sf::Image image)
{
	sf::Texture tex;
	if (!tex.loadFromImage(image)) 
	{
		cout << "imagen no valida" << endl;
		return;
	}
	m_textures.insert(make_pair(name, tex));
}

void CTexture::AddTexture(string name, string fileName, sf::Color maskColor)
{
	sf::Image img;
	if (!img.loadFromFile(fileName))
	{
		cout << "archivo no encontrado" << endl;
		return;
	}
	img.createMaskFromColor(maskColor);

	sf::Texture tex;
	if (!tex.loadFromImage(img)) 
	{
		cout << "imagen no valida" << endl;
		return;
	}

	m_textures.insert(make_pair(name, tex));
}

void CTexture::AddTexture(string name, sf::Image image, sf::Color maskColor)
{
	image.createMaskFromColor(maskColor);

	sf::Texture tex;
	if (!tex.loadFromImage(image))
	{
		cout << "imagen no valida" << endl;
		return;
	}

	m_textures.insert(make_pair(name, tex));
}

sf::Texture* CTexture::GetTexture(string name)
{
	if (m_textures.find(name) != m_textures.end()) {
		return &m_textures[name];
	}
	cout << "Textura no existente" << endl;
	return nullptr;
}
}