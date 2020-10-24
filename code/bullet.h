#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>


class bullet {

public:

	bullet();
	bullet(sf::Vector2f dir);
	~bullet();

	void setPosition(sf::Vector2f newPos);

	sf::Vector2f getPosition();

	void fire();
	void fireDir(float x, float y);        //set bullet's direction when an object is firing
	void fireSpeed(int speed);  //change the movement of the bullet if the object which is firing is moving

	void setDirection(sf::Vector2f dir);
	sf::Vector2f getDirection();

	void draw(sf::RenderWindow& window);

protected:
	sf::RectangleShape proiettile;
	sf::Vector2f direction;
};


