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

	/**
	  * @brief      Initialices the grid with a size and everything in black
	  * @param      tiles: the number of tiles in X and Y
	  * @param      size: the size of every node of the grid
	  * @bug	    No know Bugs
	*/
	void Init(sf::Vector2i tiles, sf::Vector2f size);
	/**
	  * @brief      Initialices the grid with a size and a grid of the state of every node
	  * @param      tiles: the number of tiles in X and Y
	  * @param      size: the size of every node of the grid
	  * @param      grid: the state of every node
	  * @param      wallGrid: what nodes has a wall
	  * @param      manager: The agent manager that controls the agent in the scene.
	  * @bug	    No know Bugs
	*/
	void Init(sf::Vector2i tiles, sf::Vector2f size, std::vector<std::vector<int>> grid, 
	          std::vector<std::vector<bool>> wallGrid, PathFindingAgentManager* manager);
	/**
	  * @brief      Updates the grid every frame. 
	  * @param      window: the window where it is placed. Neded for the mouse position
	  * @bug	    No know Bugs
	*/
	bool Update(sf::RenderWindow* window);
	/**
	  * @brief      Renderss the grid every frame.
	  * @param      window: the window where it is rendered to.
	  * @bug	    No know Bugs
	*/
	void Render(sf::RenderWindow* window);
	/**
	  * @brief      Frees the memory
	  * @bug	    No know Bugs
	*/
	void Destroy();

	/**
	  * @brief      Initializers of the diferent tyes of search
	  * @bug	    No know Bugs
	*/
	void BreathFirstSearch();
	void DepthFirstSearch();
	void DijstraSearch();
	void BestFirstSearch();
	void AStarSearch();

	/**
	  * @brief      Removes all the wall in the grid
	  * @bug	    No know Bugs
	*/
	void RemoveWalls();
	/**
	  * @brief      Restart the search state of every node
	  * @bug	    No know Bugs
	*/
	void RestartSearch();
	/**
	  * @brief      Restart all the states, walls and search of every node.
	  * @bug	    No know Bugs
	*/
	void RestartAll();

	/**
	  * @brief      Has to show the lines of the grid?
	  * @param      active: yes/no
	  * @bug	    No know Bugs
	*/
	void ShowLines(bool active);
	/**
	  * @brief      Has to show the wheights of the grid?
	  * @param      active: yes/no
	  * @bug	    No know Bugs
	*/
	void ShowWeights(bool active);

	/**
	  * @brief      Returns the node in the specified position
	  * @param      pos: the position in grid space
	  * @bug	    No know Bugs
	*/
	Node* GetNode(sf::Vector2i pos);


	/**
	  * @brief      Is the grid searching?
	  * @bug	    No know Bugs
	*/
	bool GetIsSearching();
	/**
	  * @brief      Has the grid found the end?
	  * @bug	    No know Bugs
	*/
	bool GetHasFound();
	/**
	  * @brief      The grid hasn't found the end.
	  * @bug	    No know Bugs
	*/
	bool GetGotError();

	/**
	  * @brief      Returns an array in order of the path from the start to the end
	  * @bug	    No know Bugs
	*/
	std::vector<Node*> GetPathToEnd();
	/**
	  * @brief      Returns all the grid
	  * @bug	    No know Bugs
	*/
	std::vector<std::vector<Node>>* GetNodeGrid();

private:
	/**
	  * @brief      Creates lines forming the path from the start to the end
	  * @bug	    No know Bugs
	*/
	void CreateLinesToTarget();

	/**
	  * @brief      The updates of every time of search. It executes once every frame for it to be
	  *				visualized on runtime.
	  * @bug	    No know Bugs
	*/
	bool BreathFirstSearchUpdate();
	bool DepthFirstSearchUpdate();
	void DijstraSearchUpdate();
	void BestFirstSearchUpdate();
	void AStarSearchUpdate();

	/**
	  * @brief      Returns the weight given to a specific type of grid
	  * @param      type: the type that we need to know ist weight
	  * @bug	    No know Bugs
	*/
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

