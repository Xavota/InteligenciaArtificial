#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Node.h"

class Grid
{
public:
	Grid() = default;
	Grid(sf::IntRect rect, sf::Vector2i tiles);
	~Grid() = default;

	void Init(sf::IntRect rect, sf::Vector2i tiles);
	void Update(sf::RenderWindow* window);
	void Render(sf::RenderWindow* window);
	void Destroy();

	std::list<Node>* GetFromList(std::list<std::list<Node>>* list, int i);
	Node* GetFromDoubleList(std::list<std::list<Node>>* list, int i, int j);

private:
	std::list<std::list<Node>> m_nodeGrid;
};

