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
	float m_upWeight = 0;
	Node* m_right = nullptr;
	float m_rightWeight = 0;
	Node* m_down = nullptr;
	float m_downWeight = 0;
	Node* m_left = nullptr;
	float m_leftWeight = 0;

	Node* m_parent = nullptr;
	float m_parentWeight = 0;

	bool m_searched = false;

	int m_facesSeen = 0;

private:
	sf::RectangleShape m_shape;

	eNODE_STATE m_state = eNODE_STATE::NONE;
	eNODE_STATE m_tempSate = eNODE_STATE::BLANK;

	static std::map<eNODE_STATE, sf::Color> m_colors;
};

