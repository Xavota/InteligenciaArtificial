#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <vector>
#include "Node.h"
#include "MouseInfo.h"
#include "PathFindingAgentManager.h"

enum class eSEARCH_TYPE
{
	NONE = -1,
	BREATH_FIRST,
	DEPTH_FIRST,
	DIJSTRA,
	BEST_FIRST,
	A_STAR,
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
	void Init(sf::Vector2i tiles, sf::Vector2f size, std::vector<std::vector<int>> grid, 
	          std::vector<std::vector<bool>> wallGrid, PathFindingAgentManager* manager);
	bool Update(sf::RenderWindow* window);
	void Render(sf::RenderWindow* window);
	void Destroy();

	void BreathFirstSearch();
	void DepthFirstSearch();
	void DijstraSearch();
	void BestFirstSearch();
	void AStarSearch();

	void RemoveWalls();
	void RestartSearch();
	void RestartAll();

	void ShowLines(bool active);
	void ShowWeights(bool active);

	Node* GetNode(sf::Vector2i pos);


	bool GetIsSearching();
	bool GetHasFound();
	bool GetGotError();

	std::vector<Node*> GetPathToEnd();
	std::vector<std::vector<Node>>* GetNodeGrid();

private:
	void CreateLinesToTarget();

	bool BreathFirstSearchUpdate();
	bool DepthFirstSearchUpdate();
	void DijstraSearchUpdate();
	void BestFirstSearchUpdate();
	void AStarSearchUpdate();

	float GetWeight(eNODE_PATH_TYPE type);

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

	//std::list<std::list<Node>> m_nodeGrid;
	std::vector<std::vector<Node>> m_nodeGrid;
	sf::Vector2f m_cellSize;

	std::vector<sf::RectangleShape> m_linesToTarget;
	std::vector<Node*> m_path;

	bool m_showWeghts = false;

	PathFindingAgentManager* m_manager;
};

