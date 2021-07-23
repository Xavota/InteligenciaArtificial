#pragma once
#include <SFML/Graphics.hpp>
#include <map>

enum class eNODE_STATE
{
	NONE = -1,
	BLANK,
	WALL,
	START,
	END,
	COUNT
};

class Node
{
public:
	Node(sf::Vector2f pos, sf::Vector2f size);
	~Node();

	void Init(sf::Vector2f pos, sf::Vector2f size);
	void Update(sf::RenderWindow* window);
	void Render(sf::RenderWindow* window);
	void Destroy();

	void ChangeState(eNODE_STATE state);
	void ChangeTempState(eNODE_STATE state);
	eNODE_STATE GetState();
	eNODE_STATE GetTempState();

	sf::Vector2f GetPosition();
	sf::Vector2f GetSize();

	void SetColor(sf::Color color);
	void SetParent(Node* parent);
	void Searched();

	void RestartSearch();
	void RestartAll();

public:
	Node* m_up = nullptr;
	Node* m_right = nullptr;
	Node* m_down = nullptr;
	Node* m_left = nullptr;

	Node* m_parent = nullptr;

	bool m_searched = false;

private:
	sf::RectangleShape m_shape;

	eNODE_STATE m_state = eNODE_STATE::NONE;
	eNODE_STATE m_tempSate = eNODE_STATE::BLANK;

	bool m_in = false;


	static std::map<eNODE_STATE, sf::Color> m_colors;
};

