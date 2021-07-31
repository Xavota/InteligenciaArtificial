#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <vector>
#include "Node.h"

enum class eSEARCH_TYPE
{
	NONE = -1,
	BREATH_FIRST,
	DEPTH_FIRST,
	DIJSTRA,
	BEST_FIRST,
	COUNT
};

struct sUnion
{
	Node* m_first;
	float weight;
	Node* m_end;
};

class Grid
{
public:
	Grid() = default;
	Grid(sf::Vector2i tiles, sf::Vector2f size);
	~Grid() = default;

	void Init(sf::Vector2i tiles, sf::Vector2f size);
	bool Update(sf::RenderWindow* window);
	void Render(sf::RenderWindow* window);
	void Destroy();

	void BreathFirstSearch();
	void DepthFirstSearch();
	void DijstraSearch();
	void BestFirstSearch();

	std::list<Node>* GetFromList(std::list<std::list<Node>>* list, int i);
	Node* GetFromDoubleList(std::list<std::list<Node>>* list, int i, int j);

	void RestartSearch();
	void RestartAll();

	void ShowLines(bool active);
	void ShowWeights(bool active);


private:
	void CreateLinesToTarget();

	bool BreathFirstSearchUpdate();
	bool DepthFirstSearchUpdate();
	void DijstraSearchUpdate();
	void BestFirstSearchUpdate();

private:
	/* Search */
	bool m_isSearching = false;
	Node* m_start = nullptr, * m_end = nullptr;
	bool m_found = false, m_error = false;
	eSEARCH_TYPE m_searchType = eSEARCH_TYPE::NONE;

	/* Breath First Search*/
	std::vector<Node*> m_order;
	int m_i = 0;

	/* Depth First Search */
	Node* m_current = nullptr;

	/* Dijstra Search */
	std::vector<std::vector<sUnion>> m_paths;

	//std::list<std::list<Node>> m_nodeGrid;
	std::vector<std::vector<Node>> m_nodeGrid;

	std::vector<sf::RectangleShape> m_linesToTarget;

	bool m_showWeghts = false;
};

