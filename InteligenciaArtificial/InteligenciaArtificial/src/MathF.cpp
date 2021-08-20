#include "MathF.h"

namespace gl
{
	float MathF::vectorLength(sf::Vector2f vec)
	{
		return pow(vec.x * vec.x + vec.y * vec.y, .5f);
	}
	
	sf::Vector2f MathF::normalizeVector(sf::Vector2f vec)
	{
		float len = vectorLength(vec);
		if (len == 0)
		{
			return sf::Vector2f(0, 0);
		}
		return vec / len;
	}
	
	sf::Vector2f MathF::truncateVector(sf::Vector2f vec, float length)
	{
		return normalizeVector(vec) * length;
	}
	
	float MathF::distanceVector(sf::Vector2f vec1, sf::Vector2f vec2)
	{
		return vectorLength(vec2 - vec1);
	}
	
	float MathF::dot(sf::Vector2f vec1, sf::Vector2f vec2)
	{
		return vec1.x * vec2.x + vec1.y * vec2.y;
	}
	
	sf::Vector2f MathF::rightVector(sf::Vector2f vec)
	{
		return sf::Vector2f(-vec.y, vec.x);
	}
	
	void MathF::placeLineFromTwoPoints(sf::RectangleShape& line, sf::Vector2f pos1, sf::Vector2f pos2)
	{
		line.setPosition(pos1);	
		sf::Vector2f ori = pos2 - pos1;
		line.setSize({ 3.f, vectorLength(ori) });
		float angle = atan((ori.y) / (ori.x)) * 180.f / 3.14159265f;
		if (ori.x < 0)
		{
			angle += 180;
		}
		else if (ori.y < 0)
		{
			angle += 360;
		}
	
		line.setRotation(angle - 90);/**/
	}
}