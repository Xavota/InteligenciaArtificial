#pragma once
#include <SFML/Graphics.hpp>

class Camera
{
public:
	Camera() = default;
	/**
	  * @brief		Construct the camera. Calls the Init function
	  * @param      initView: the initial view zone
	  * @param      sensibility: the sensibility of the movement
	  * @bug	    No know Bugs
	*/
	Camera(sf::FloatRect initView, float sensibility);
	~Camera() = default;

	/**
	  * @brief		Initialize the values of the camera
	  * @param      initView: the initial view zone
	  * @param      sensibility: the sensibility of the movement
	  * @bug	    No know Bugs
	*/
	void Init(sf::FloatRect initView, float sensibility);
	/**
	  * @brief		Updates the size and center of the camera and sets it to the window.
	  * @param      window: the window that will be changing its view
	  * @bug	    No know Bugs
	*/
	void Update(sf::RenderWindow* window);

	/**
	  * @brief		Returns the center of the camera
	  * @bug	    No know Bugs
	*/
	sf::Vector2f GetCenter();

private:
	sf::View m_camera;
	float m_sensibility;
};

