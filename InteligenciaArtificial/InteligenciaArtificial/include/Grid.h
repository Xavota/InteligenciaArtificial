#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <vector>
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

	void StartSearch();

	std::list<Node>* GetFromList(std::list<std::list<Node>>* list, int i);
	Node* GetFromDoubleList(std::list<std::list<Node>>* list, int i, int j);

	void RestartSearch();
	void RestartAll();

private:
	void CreateLinesToTarget();

private:
	std::vector<Node*> m_order;
	bool m_isSearching = false;
	Node* m_start = nullptr, * m_end = nullptr;

	bool m_found = false;

	int i = 0;

	std::list<std::list<Node>> m_nodeGrid;

	std::vector<sf::RectangleShape> m_linesToTarget;
};

